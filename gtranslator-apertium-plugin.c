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

#include "gtranslator-apertium-plugin.h"



G_DEFINE_TYPE (GtranslatorApertiumPlugin, gtranslator_apertium_plugin, GTRANSLATOR_TYPE_PLUGiN);

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
	GtranslatorPluginClass* parent_class = GTRANSLATOR_PLUGiN_CLASS (klass);

	object_class->finalize = gtranslator_apertium_plugin_finalize;
}

