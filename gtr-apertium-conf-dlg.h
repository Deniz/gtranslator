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

#ifndef _GTR_APERTIUM_CONF_DLG_H_
#define _GTR_APERTIUM_CONF_DLG_H_

#include <glib-object.h>
#include <gtk/gtk.h>
#include <glib/gi18n.h>
#include <gconf/gconf-client.h>
#include "apertium-plugin.h"

G_BEGIN_DECLS

#define GTR_TYPE_APERTIUM_CONF_DLG             (gtr_apertium_conf_dlg_get_type ())
#define GTR_APERTIUM_CONF_DLG(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTR_TYPE_APERTIUM_CONF_DLG, GtrApertiumConfDlg))
#define GTR_APERTIUM_CONF_DLG_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), GTR_TYPE_APERTIUM_CONF_DLG, GtrApertiumConfDlgClass))
#define GTR_IS_APERTIUM_CONF_DLG(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTR_TYPE_APERTIUM_CONF_DLG))
#define GTR_IS_APERTIUM_CONF_DLG_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), GTR_TYPE_APERTIUM_CONF_DLG))
#define GTR_APERTIUM_CONF_DLG_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), GTR_TYPE_APERTIUM_CONF_DLG, GtrApertiumConfDlgClass))

#define APERTIUM_BASE_KEY "/apps/gtranslator/plugins/apertium"
#define APERTIUM_MARK_UNKNOWN APERTIUM_BASE_KEY "/mark_unknown"
#define APERTIUM_LANG_PAIR APERTIUM_BASE_KEY "/lang_pair"
#define APERTIUM_HIGHLIGHT_COLOR APERTIUM_BASE_KEY "/highlight_color"

typedef struct _GtrApertiumConfDlgClass GtrApertiumConfDlgClass;
typedef struct _GtrApertiumConfDlg GtrApertiumConfDlg;

struct _GtrApertiumConfDlgClass
{
	GtkDialogClass parent_class;
};

struct _GtrApertiumConfDlg
{
	GtkDialog parent_instance;
};

GType gtr_apertium_conf_dlg_get_type (void) G_GNUC_CONST;
GtkWidget* gtr_apertium_conf_dlg_new();

G_END_DECLS

#endif /* _GTR_APERTIUM_CONF_DLG_H_ */
