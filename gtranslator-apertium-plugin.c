/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * gtranslator-apertium-plugin.c
 * Copyright (C) Deniz Koçak 2009 <deniz.kocak@linux.org.tr>
 * 
 * gtranslator-apertium-plugin.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * gtranslator-apertium-plugin.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "gtranslator-apertium-plugin.h"
#include "custom-widget.h"
#include "application.h"
#include "window.h"
#include "header.h"

#include <glib.h>
#include <glib/gi18n-lib.h>
#include <glib-object.h>
#include <gconf/gconf-client.h>
#include <gtk/gtk.h>

#define WINDOW_DATA_KEY	"GtranslatorApertiumPluginWindowData"

//G_DEFINE_TYPE (GtranslatorApertiumPlugin, gtranslator_apertium_plugin, GTRANSLATOR_TYPE_PLUGIN);

GTR_PLUGIN_REGISTER_TYPE_WITH_CODE (GtranslatorApertiumPlugin, gtranslator_apertium_plugin,
		gtranslator_apertium_register_type (module);
)
		
static void
impl_activate(GtranslatorPlugin *plugin,
	       GtranslatorWindow *window)
{
	GtkWidget *apertium;
	
	gtranslator_application_register_icon (GTR_APP, "apertium.png",
					       "apertium-plugin-icon");

	apertium = custom_widget_new();
	gtk_widget_show (apertium);

	gtranslator_window_add_widget (window,
				       apertium,
				       "GtranslatorApertiumPlugin",
				       _("Apertium"),
				       "apertium-plugin-icon",
				       GTR_WINDOW_PLACEMENT_LEFT);

	g_object_set_data(G_OBJECT(window),
			  WINDOW_DATA_KEY,
			  apertium);
}

static void
impl_deactivate(GtranslatorPlugin *plugin,
	       GtranslatorWindow *window)
{
	GtkWidget *apertium;

	apertium = (GtkWidget *) g_object_get_data (G_OBJECT (window),
						    WINDOW_DATA_KEY);
	g_return_if_fail (apertium != NULL);

	gtranslator_window_remove_widget (window, apertium);
	
	g_object_set_data (G_OBJECT (window), WINDOW_DATA_KEY, NULL);
}

static void
gtranslator_apertium_plugin_init (GtranslatorApertiumPlugin *object)
{
	/* TODO: Add initialization code here */
}

static void
gtranslator_apertium_plugin_finalize (GObject *object)
{
	/* TODO: Add deinitalization code here */

	G_OBJECT_CLASS (gtranslator_apertium_plugin_parent_class)->finalize (object);
}

static void
gtranslator_apertium_plugin_class_init (GtranslatorApertiumPluginClass *klass)
{
	GObjectClass* object_class = G_OBJECT_CLASS (klass);
	GtranslatorPluginClass* parent_class = GTR_PLUGIN_CLASS (klass);
	
	parent_class->activate = impl_activate;
	parent_class->deactivate = impl_deactivate;
	
	object_class->finalize = gtranslator_apertium_plugin_finalize;
}


