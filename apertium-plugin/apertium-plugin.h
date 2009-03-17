#include 	<glib.h>
#include	<glib-object.h>
#include	<dbus/dbus.h>
#include	<dbus/dbus-glib.h>

#define 	APERTIUM_SERVICE_NAME	"org.apertium.mode"
#define 	APERTIUM_INTERFACE		"org.apertium.Translate"
#define 	APERTIUM_OBJECT_PATH	"/"

gboolean apertium_dbus_init();
gboolean apertium_dbus_translate(const gchar*, gboolean, gchar*);

