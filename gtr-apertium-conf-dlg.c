/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * gtr-apertium-conf-dlg.c
 * Copyright (C) Deniz Koçak 2009 <deniz.kocak@linux.org.tr>
 * 
 * gtr-apertium-conf-dlg.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * gtr-apertium-conf-dlg.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "gtr-apertium-conf-dlg.h"

G_DEFINE_TYPE (GtrApertiumConfDlg, gtr_apertium_conf_dlg, GTK_TYPE_DIALOG);

static DBusGProxy *proxy = NULL;

typedef struct {
	GtkTable *table;
	GtkComboBox *lang_pair;
	GtkCheckButton *mark_unknown;
	GtkButton *color_selection;
	GtkWidget *frame;
	gchar **pairs;
} GtrApertiumConfDlgPriv;

#define GET_PRIV(object) G_TYPE_INSTANCE_GET_PRIVATE(object, GTR_TYPE_APERTIUM_CONF_DLG, GtrApertiumConfDlgPriv)

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
											APERTIUM_INFO_SERVICE_NAME,
											APERTIUM_INFO_OBJECT_PATH,
											APERTIUM_INFO_INTERFACE,
											&error);
	g_return_val_if_fail(proxy != NULL, FALSE);	
	
	g_debug("proxy %d\n", proxy);
	return TRUE;
}

static void
get_available_pairs(GtrApertiumConfDlgPriv *priv)
{
	if (proxy == NULL)
		g_print("dbus init %d\n", apertium_dbus_init());
	
	dbus_g_proxy_call(proxy,
					  "modes",
					  NULL,		//error is NULL
					  G_TYPE_INVALID,
					   G_TYPE_STRV,
					  &(priv->pairs),
					  G_TYPE_INVALID); 

}

static void
on_dialog_ok_cb(GtkDialog *dialog, guint response, gpointer user_data)
{
	GConfClient *client = NULL;
	
	GtrApertiumConfDlgPriv *priv = GET_PRIV(dialog);
	client = gconf_client_get_default();
	
	switch (response)
	{
		case 55:
		{
			if (client != NULL)
			{
				gconf_client_set_string(client, APERTIUM_LANG_PAIR, gtk_combo_box_get_active_text(priv->lang_pair), NULL);
				gconf_client_set_bool(client, APERTIUM_MARK_UNKNOWN, gtk_toggle_button_get_active(priv->mark_unknown), NULL);
				//gconf_client_set_string(client, APERTIUM_HIGHLIGHT_COLOR, gtk_combo_box_get_active_text(priv->lang_pair), NULL);
				g_object_unref(client);
			}
			gtk_widget_destroy(dialog);
		}
	}
}

static void
get_color_selection(GtkDialog *dialog, guint response, gpointer user_data)
{
	GdkColor current_color;
	
	switch(response)
	{
		case GTK_RESPONSE_OK:
		{
			GtkWidget *color = gtk_color_selection_dialog_get_color_selection(dialog);
			gtk_color_selection_get_current_color(GTK_COLOR_SELECTION(color), &current_color);
			gtk_widget_destroy(dialog);
			g_print("#%d%d%d%d\n", current_color.red, current_color.green, current_color.blue);
		}
		break;
		
		case GTK_RESPONSE_CANCEL:
		{
			gtk_widget_destroy(dialog);
		}
	}
}

static void
on_color_selection_clicked(GtkButton *button, gpointer user_data)
{
	GtkWidget *selection;
	GtkWidget *color_button;
	
	selection = gtk_color_selection_dialog_new("Bir renk seçin");
	g_signal_connect(G_OBJECT(selection), "response", G_CALLBACK(get_color_selection), NULL);
	
	gtk_widget_show(selection);
}

GtkWidget*
gtr_apertium_conf_dlg_new()
{
  	return GTR_APERTIUM_CONF_DLG(g_object_new(GTR_TYPE_APERTIUM_CONF_DLG, NULL));
}

static void
gtr_apertium_conf_dlg_init (GtrApertiumConfDlg *object)
{
	GtrApertiumConfDlgPriv *priv = GET_PRIV(object);
	GtkWidget *content_area;
	GtkWidget *label;
	guint i;
	gboolean mark_unknown;
	gchar *lang_pair;
	GConfClient *client;

	client = gconf_client_get_default();
	g_print("gclient\n");
	get_available_pairs(priv);
	
	priv->frame = gtk_frame_new(C_("Dialog frame", "Configuration Dialog"));
	priv->table = gtk_table_new(3, 2, TRUE);
	priv->lang_pair = gtk_combo_box_new_text();
	priv->mark_unknown = gtk_check_button_new();
	priv->color_selection = gtk_button_new_with_label("Select a Color");
	
	g_signal_connect(G_OBJECT(priv->color_selection), "clicked", G_CALLBACK(on_color_selection_clicked), NULL);
	
	for (i = 0; priv->pairs[i] != NULL; i++)
	{
		gtk_combo_box_append_text(priv->lang_pair, priv->pairs[i]);
	}
	
	label = gtk_label_new(C_("Languages", "Select a pair"));
	gtk_table_attach(GTK_TABLE(priv->table), label, 0, 1, 0, 1, GTK_EXPAND, GTK_EXPAND, 0, 0);
	label = gtk_label_new(C_("Mark Unknown", "Mark unknown"));
	gtk_table_attach(GTK_TABLE(priv->table), label, 0, 1, 1, 2, GTK_EXPAND, GTK_EXPAND, 0, 0);
	label = gtk_label_new(C_("Color Selection", "Select Highlight color"));
	gtk_table_attach(GTK_TABLE(priv->table), label, 0, 1, 2, 3, GTK_EXPAND, GTK_EXPAND, 0, 0);
	
	mark_unknown = gconf_client_get_bool(client, APERTIUM_MARK_UNKNOWN, NULL);
	lang_pair = gconf_client_get_string(client, APERTIUM_LANG_PAIR, NULL);
	if (mark_unknown != NULL)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(priv->mark_unknown), mark_unknown);
	g_object_unref(client);
	
	g_print("%s %d\n", lang_pair, mark_unknown);
			
	gtk_table_attach(GTK_TABLE(priv->table), priv->lang_pair, 1, 2, 0, 1, GTK_EXPAND, GTK_EXPAND, 0, 0);
	gtk_table_attach(GTK_TABLE(priv->table), priv->mark_unknown, 1, 2, 1, 2, GTK_EXPAND, GTK_EXPAND, 0, 0);
	gtk_table_attach(GTK_TABLE(priv->table), priv->color_selection, 1, 2, 2, 3, GTK_EXPAND, GTK_EXPAND, 0, 0);
	content_area = gtk_dialog_get_content_area(GTK_DIALOG(object));
	gtk_container_add(GTK_CONTAINER(priv->frame), priv->table);	
	gtk_container_add(GTK_CONTAINER(content_area), priv->frame);
	
	gtk_dialog_add_button(object, GTK_STOCK_OK, 55);
	g_signal_connect(G_OBJECT(object), "response", G_CALLBACK(on_dialog_ok_cb), NULL);
}

static void
gtr_apertium_conf_dlg_finalize (GObject *object)
{
	GtrApertiumConfDlgPriv *priv = GET_PRIV(object);
	g_strfreev(priv->pairs);
	G_OBJECT_CLASS (gtr_apertium_conf_dlg_parent_class)->finalize (object);
}

static void
gtr_apertium_conf_dlg_class_init (GtrApertiumConfDlgClass *klass)
{
	GObjectClass* object_class = G_OBJECT_CLASS (klass);
	GtkDialogClass* parent_class = GTK_DIALOG_CLASS (klass);

	object_class->finalize = gtr_apertium_conf_dlg_finalize;
	
	g_type_class_add_private(klass, sizeof(GtrApertiumConfDlgPriv));
}

