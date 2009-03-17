#include	"apertium-plugin.h"

static DBusGConnection *conn = NULL;
static DBusGProxy *proxy = NULL;
static gchar *ceviri = NULL;

gboolean apertium_dbus_init()
{
	GError *error = NULL;
	
	conn = dbus_g_bus_get(DBUS_BUS_SESSION, &error);
	
	if (conn == NULL) {
		g_warning("Error %s\n", error->message);
		return FALSE;
	}
	else
	{
		g_debug("conn object is %d\n", conn);
	}

	proxy = dbus_g_proxy_new_for_name_owner(conn,
											APERTIUM_SERVICE_NAME,
											APERTIUM_OBJECT_PATH,
											APERTIUM_INTERFACE,
											&error);
		
	g_debug("proxy %d\n", proxy);
									
	if (proxy == NULL || error != NULL)
	{
		g_warning("Cannot connect to the apertium service : %s\n", error->message);
		g_error_free(error);
		return FALSE;
	}
	else
	{
		return TRUE;
	}
	
}

gboolean apertium_dbus_translate(const gchar* given_string, gboolean mark_unknown, gchar *translated_string)
{
		
	GError *error = NULL;
	gchar *ceviri = NULL;
	GHashTable *hash = NULL;
	gchar *option_key = "mark_unknown";
	gchar *option_value = NULL;
	
	hash = g_hash_table_new(g_str_hash, g_str_equal);
	
	if (mark_unknown == TRUE)
	{
		g_hash_table_insert(hash, "mark_unknown", "true");
	}
	else
	{
		g_hash_table_insert(hash, "mark_unknown", "false");
	}
	
	dbus_g_proxy_call(proxy, "translate", &error, 
					G_TYPE_STRING, "en-es", 
					DBUS_TYPE_G_STRING_STRING_HASHTABLE, hash, 
					G_TYPE_STRING, given_string,
					G_TYPE_INVALID,
					G_TYPE_STRING,
					&translated_string,
					G_TYPE_INVALID);
									
	g_hash_table_destroy(hash);
	
	if (error)
		return FALSE;
	else
		return TRUE;
}


int main(int argc, char** argv)
{
	if (argc <= 1)
		return 1;
	
	g_type_init();	
	
	if (apertium_dbus_init() == FALSE)
		g_error("apertium_dbus_init, unable to connect apertium DBUS service");
	else
	{
		apertium_dbus_translate(argv[1], TRUE, ceviri);	
		g_print("%s is : %s\n", argv[1], ceviri);
		g_free(ceviri);
		g_object_unref(proxy);
	}	
	return 0;
}
