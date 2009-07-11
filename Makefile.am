# Apertium plugin
plugindir = $(libdir)/gtranslator/plugins

INCLUDES =                                                      \
	-I$(top_srcdir) 				\
	-I$(top_srcdir)/src				\
	-I$(top_srcdir)/src/plugin-system		\
	-I$(top_srcdir)/src/toolbareditor		\
	-DPIXMAPSDIR=\""$(datadir)"/pixmaps/gtranslator\"       \
	-DDATADIR=\""$(pkgdatadir)"\"                           \
	$(GTRANSLATOR_CFLAGS) 				\
	$(SOUP_CFLAGS)				\
	$(WARN_CFLAGS)					\
	$(DISABLE_DEPRECATED_CFLAGS)			\
	-DGTR_LOCALEDIR=\""$(prefix)/$(DATADIRNAME)/locale"\"

plugin_LTLIBRARIES = libapertiumplugin.la

libapertiumplugin_la_SOURCES = \
	custom-widget.c \
	custom-widget.h\
	gtranslator-apertium-plugin.c \
	gtranslator-apertium-plugin.h \
	gtr-apertium-conf-dlg.c \
	gtr-apertium-conf-dlg.h

libapertiumplugin_la_LDFLAGS = \
	$(PLUGIN_LIBTOOL_FLAGS)				\
	$(GTRANSLATOR_LIBS)					\
	$(APERTIUM_LIBS)

pixmaps_dir = $(datadir)/pixmaps/gtranslator
pixmaps__DATA = \
	apertium.png

# Plugin Info

plugin_in_files = apertium-plugin.gtranslator-plugin.desktop.in

%.gtranslator.plugin: %.gtranslator-plugin.desktop.in $(INTLTOOL_MERGE) $(wildcard $(top_srcdir)/po/*po) ; $(INTLTOOL_MERGE) $(top_srcdir)/po $< $@ -d -u -c $(top_builddir)/po/.intltool-merge-cache

plugin_DATA = $(plugin_in_files:.gtranslator-plugin.desktop.in=.gtranslator.plugin)

EXTRA_DIST = $(pixmaps__DATA) $(plugin_in_files)

CLEANFILES = $(plugin_DATA)
DISTCLEANFILES = $(plugin_DATA)

