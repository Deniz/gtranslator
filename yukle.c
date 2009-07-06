/*
 *      yukle.c
 *      
 *      Copyright 2009 deniz <deniz@deniz>
 *      
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *      
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *      
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */


#include "custom-widget.h"

typedef void (*yaz)(const char*);

int main(int argc, char** argv)
{
	gtk_init(&argc, &argv);
	
	
	GtkWidget* window;
	GtkWidget* custom;
	GtkWidget* vbox;
	GtkWidget* button;
	GModule* module;
	yaz func_ptr;
	
	
	module = g_module_open("./libyazi.so.1.0.1", G_MODULE_BIND_LAZY);
	
	if (module == NULL)
		g_print("Unable to open shared object\n");
		
	
	if (g_module_symbol(module, "yazdir", (gpointer*) &func_ptr) == TRUE)
	{
		func_ptr("Deniz Kocak");
	}
	
	else
	{
		g_print("Symbol not found\n");
	}
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	custom = custom_widget_new();
	vbox = gtk_vbox_new(TRUE, 5);

	gtk_window_set_default_size(GTK_WINDOW(window), 200, 400);
	g_print("Custom is %p\n", custom);

	gtk_box_pack_start_defaults(GTK_BOX(vbox), custom);
	gtk_container_set_border_width(GTK_CONTAINER(window), 5);
	gtk_container_add(GTK_CONTAINER(window), vbox);
	gtk_widget_show_all(window);
	
	gtk_main();
	
	return 0;
}
