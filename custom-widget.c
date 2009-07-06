/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * custom-widget.c
 * Copyright (C) Deniz Koçak 2009 <deniz.kocak@linux.org.tr>
 * 
 * custom-widget.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * custom-widget.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "custom-widget.h"
#include "apertium-plugin.h"
#include "gtr-apertium-conf-dlg.h"

G_DEFINE_TYPE (CustomWidget, custom_widget, GTK_TYPE_HBOX);

static DBusGProxy *proxy = NULL;

typedef struct {
	GtkWidget* original;
	GtkWidget* translation;
	GtkWidget* button;
	GtkWidget* conf_dlg;
	GtkWidget* vbox;
	GtkWidget* hbox;
} CustomWidgetPriv;


#define GET_PRIV(object) G_TYPE_INSTANCE_GET_PRIVATE(object, CUSTOM_TYPE_WiDGET, CustomWidgetPriv)


static void
show_dlg(GtkButton* button, gpointer user_data)
{
	GtkWidget* dlg = gtr_apertium_conf_dlg_new();
	gtk_widget_show_all(dlg);
}


static void
highlight_unknown_text(GtkTextBuffer *buffer)
{
	GtkTextIter start_iter;
	GtkTextIter match_start, match_end;
	GtkTextTag *text_tag
	gint offset;
	
	if (text_tag == NULL)
		text_tag = gtk_text_buffer_create_tag(buffer,
											  "unknown_text",
											  "foreground",
											  "red",
											   NULL);
											   
	gtk_text_buffer_get_start_iter(buffer, &start_iter);
	
	while(gtk_text_iter_forward_search(&start_iter,
									   "*",
									   GTK_TEXT_SEARCH_TEXT_ONLY | 
									   GTK_TEXT_SEARCH_VISIBLE_ONLY,
									   &match_start,
									   &match_end,
									   NULL))
	{
		gtk_text_buffer_apply_tag_by_name(buffer, "unknown_text", &match_start, &match_end);
		offset = gtk_text_iter_get_offset(&match_end);
		gtk_text_buffer_get_iter_at_offset(buffer, &start_iter, offset);
	}									   
}

static void
update_translation_text(gchar* text, CustomWidgetPriv *priv)
{
	GtkTextBuffer *translation_buffer;
	gchar *translated_string;
	
	translated_string = g_locale_to_utf8(text,
											 -1,
											 0,
											 0,
											 0);
	translation_buffer = gtk_text_view_get_buffer(priv->translation);
	gtk_text_buffer_set_text(translation_buffer, translated_string, -1);
	g_free(translated_string);
}

static void
on_translate_end(DBusGProxy *proxy,
				DBusGProxyCall *call,
				CustomWidgetPriv *priv)
{
	gchar *translated_string = NULL;
	GError *error = NULL;
	
	dbus_g_proxy_end_call(proxy, 
						  call,
						  &error,
						  G_TYPE_STRING,
						  &translated_string,
						  G_TYPE_INVALID);
	
	g_print("Async translated string : %s\n", translated_string);
	update_translation_text(translated_string, priv);			  
	highlight_unknown_text(gtk_text_view_get_buffer(priv->translation));
	if (translated_string != NULL)
		g_free(translated_string);
}

static gboolean 
apertium_dbus_init()
{
	DBusGConnection *conn = NULL;
	GError *error = NULL;
	
	conn = dbus_g_bus_get(DBUS_BUS_SESSION, &error);
	
	if (conn == NULL) {
		g_warning("Hata %s\n", error->message);
		return FALSE;
	}
	else
	{
		g_debug("conn %d\n", conn);
	}

	proxy = dbus_g_proxy_new_for_name_owner(conn,
											APERTIUM_SERVICE_NAME,
											APERTIUM_OBJECT_PATH,
											APERTIUM_INTERFACE,
											&error);
	g_return_val_if_fail(proxy != NULL, FALSE);	
	
	g_debug("proxy %d\n", proxy);
	return TRUE;
}

static void 
apertium_dbus_translate(const gchar* given_string, gboolean mark_unknown, CustomWidgetPriv *priv)
{
	GHashTable *hash = NULL;
	gchar *option_key = "mark_unknown";
	gchar *option_value = NULL;
	gboolean unicode;
	gchar *valid_end;
	
	hash = g_hash_table_new(g_str_hash, g_str_equal);
	
	if (mark_unknown == TRUE)
	{
		g_hash_table_insert(hash, "mark_unknown", "true");
	}
	else
	{
		g_hash_table_insert(hash, "mark_unknown", "false");
	}
	unicode = g_utf8_validate(given_string, -1, &valid_end);
		if (unicode == FALSE)
		g_print("End of valid data : %s \n", valid_end);
	else
		g_print("New Original string : %s \n", given_string);
		
	dbus_g_proxy_begin_call(proxy, 
							"translate", 
							(DBusGProxyCallNotify) on_translate_end,
							priv,
							NULL,
							G_TYPE_STRING, "en-es", 
							DBUS_TYPE_G_STRING_STRING_HASHTABLE, hash, 
							G_TYPE_STRING, given_string,
							G_TYPE_INVALID
							);
					
													
	g_hash_table_destroy(hash);
}


static void
apertium_translate(GtkButton* button, gpointer user_data)
{
	CustomWidgetPriv *priv = (CustomWidgetPriv*) user_data;
	GtkTextIter start;
	GtkTextIter end;
	GtkTextBuffer *original_buffer;
	GConfClient *client;
	gchar *original;
	gboolean mark_unknown;
	
	client = gconf_client_get_default();
	mark_unknown = gconf_client_get_bool(client, APERTIUM_MARK_UNKNOWN, NULL);
	
	original_buffer = gtk_text_view_get_buffer(priv->original);
	gtk_text_buffer_get_start_iter (original_buffer, &start);
  	gtk_text_buffer_get_end_iter (original_buffer, &end);
	original = gtk_text_buffer_get_text(original_buffer, &start, &end, FALSE);
	
	
	apertium_dbus_translate(original, mark_unknown, priv);
	g_free(original);
}

static void
custom_widget_init (CustomWidget *object)
{
	g_print("custom_widget_init\n");
	/* TODO: Add initialization code here */
	gboolean result = apertium_dbus_init();
	
	CustomWidgetPriv* priv = GET_PRIV(object);
	priv->original = gtk_text_view_new();
	priv->translation = gtk_text_view_new();
	priv->button = gtk_button_new_with_label("Deneme");
	priv->conf_dlg = gtk_button_new_with_label("Ayar");
	priv->vbox = gtk_vbox_new(FALSE, 5);
	priv->hbox = gtk_hbox_new(TRUE, 5);
	
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(priv->original), GTK_WRAP_WORD);
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(priv->translation), GTK_WRAP_WORD);
	
	if (result == TRUE)
		g_signal_connect(G_OBJECT(priv->button), "clicked", G_CALLBACK(apertium_translate), priv);
		g_signal_connect(G_OBJECT(priv->conf_dlg), "clicked", G_CALLBACK(show_dlg), priv);
		
	gtk_box_pack_start(GTK_BOX(priv->vbox), priv->original, TRUE, TRUE, TRUE);
	gtk_box_pack_start(GTK_BOX(priv->vbox), priv->translation, TRUE, TRUE, TRUE);
	gtk_box_pack_start_defaults(GTK_BOX(priv->hbox), priv->button);
	gtk_box_pack_start_defaults(GTK_BOX(priv->hbox), priv->conf_dlg);
	gtk_box_pack_start(GTK_BOX(priv->vbox), priv->hbox, FALSE, FALSE, FALSE);
	gtk_box_pack_start_defaults(GTK_BOX(object), priv->vbox);
}

static void
custom_widget_finalize (GObject *object)
{
	g_print("custom_widget_finalize\n");
	/* TODO: Add deinitalization code here */
	
	G_OBJECT_CLASS (custom_widget_parent_class)->finalize (object);
}

static void
custom_widget_class_init (CustomWidgetClass *klass)
{
	GObjectClass* object_class = G_OBJECT_CLASS (klass);
	GtkHBoxClass* parent_class = GTK_HBOX_CLASS (klass);

	g_type_class_add_private(klass, sizeof(CustomWidgetPriv));
	object_class->finalize = custom_widget_finalize;
}

GtkWidget* custom_widget_new()
{
	return GTK_WIDGET(g_object_new(CUSTOM_TYPE_WiDGET, NULL));
}
