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

#ifndef _GTRANSLATOR_APERTIUM_PLUGIN_H_
#define _GTRANSLATOR_APERTIUM_PLUGIN_H_

#include <glib-object.h>
#include "plugin.h"

G_BEGIN_DECLS

#define GTR_TYPE_APERTIUM_PLUGIN             (gtranslator_apertium_plugin_get_type ())
#define GTR_APERTIUM_PLUGIN(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTR_TYPE_APERTIUM_PLUGIN, GtranslatorApertiumPlugin))
#define GTR_APERTIUM_PLUGIN_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), GTR_TYPE_APERTIUM_PLUGIN, GtranslatorApertiumPluginClass))
#define GTR_IS_APERTIUM_PLUGIN(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTR_TYPE_APERTIUM_PLUGIN))
#define GTR_IS_APERTIUM_PLUGIN_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), GTR_TYPE_APERTIUM_PLUGIN))
#define GTR_APERTIUM_PLUGIN_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), GTR_TYPE_APERTIUM_PLUGIN, GtranslatorApertiumPluginClass))

typedef struct _GtranslatorApertiumPluginClass GtranslatorApertiumPluginClass;
typedef struct _GtranslatorApertiumPlugin GtranslatorApertiumPlugin;

struct _GtranslatorApertiumPluginClass
{
	GtranslatorPluginClass parent_class;
};

struct _GtranslatorApertiumPlugin
{
	GtranslatorPlugin parent_instance;
};

GType gtranslator_apertium_plugin_register_type   (GTypeModule * module);
GType gtranslator_apertium_plugin_get_type (void) G_GNUC_CONST;

G_END_DECLS

#endif /* _GTRANSLATOR_APERTIUM_PLUGIN_H_ */
