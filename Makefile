.PHONY: all
all: apertium-plugin

CC := gcc
DEBUG := -g
GTK_LIBS := $(shell pkg-config --libs --cflags gtk+-2.0)
DBUS_LIBS := $(shell pkg-config --libs  --cflags dbus-glib-1)
GCONF_LIBS := $(shell pkg-config --libs  --cflags gconf-2.0)
CFLAGS := $(GTK_LIBS) $(DBUS_LIBS) $(GCONF_LIBS)

apertium-plugin: custom-widget.o gtr-apertium-conf-dlg.o yukle.o
	$(CC) -Wall $(CFLAGS) $^ -o $@

custom-widget.o: custom-widget.c custom-widget.h
	$(CC) -Wall $(CFLAGS) -c $< -o $@

gtr-apertium-conf-dlg.o: gtr-apertium-conf-dlg.c gtr-apertium-conf-dlg.h
	$(CC) -Wall $(CFLAGS) -c $< -o $@

yukle.o: yukle.c
	$(CC) -Wall $(CFLAGS) -c $< -o $@
			
.PHONY: clean

clean:	
	$(RM) *.o		
