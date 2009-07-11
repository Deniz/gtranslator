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

#ifndef _CUSTOM_WIDGET_H_
#define _CUSTOM_WIDGET_H_

#include <glib-object.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define CUSTOM_TYPE_WiDGET             (custom_widget_get_type ())
#define CUSTOM_WiDGET(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), CUSTOM_TYPE_WiDGET, CustomWidget))
#define CUSTOM_WiDGET_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), CUSTOM_TYPE_WiDGET, CustomWidgetClass))
#define CUSTOM_IS_WiDGET(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CUSTOM_TYPE_WiDGET))
#define CUSTOM_IS_WiDGET_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), CUSTOM_TYPE_WiDGET))
#define CUSTOM_WiDGET_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), CUSTOM_TYPE_WiDGET, CustomWidgetClass))

typedef struct _CustomWidgetClass CustomWidgetClass;
typedef struct _CustomWidget CustomWidget;

struct _CustomWidgetClass
{
	GtkHBoxClass parent_class;
};

struct _CustomWidget
{
	GtkHBox parent_instance;
};

GType custom_widget_get_type (void) G_GNUC_CONST;
GType custom_widget_register_type (GTypeModule * module);
GtkWidget* custom_widget_new();

G_END_DECLS

#endif /* _CUSTOM_WIDGET_H_ */
