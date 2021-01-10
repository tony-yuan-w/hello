#include <gio/gio.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <systemd/sd-journal.h>

#include "charger.h"
#include "dbus_server.h"
#include "battery.h"
#include "charger.h"

#ifdef G_OS_UNIX
#include <gio/gunixfdlist.h>
/* For STDOUT_FILENO */
#include <unistd.h>
#endif

//dbus-send --session --dest=org.philips.charger_battery --print-reply
// /org/philips/battery org.freedesktop.DBus.Properties.Get string:org.philips.batteryMgr string:cycle_count

#include "battery_dbus.h"

static guint owner_id;
BatteryDbus *object_battery = NULL;
OrgPhilipsChargerMgr *object_charger = NULL;

static gboolean
handle_stop_charging (OrgPhilipsChargerMgr           *interface,
                       GDBusMethodInvocation  *invocation,
                       gpointer                user_data)
{
    Charger::prohibitCharge();
    org_philips_charger_mgr_complete_stop_charging(interface, invocation);
    return TRUE;
}

static gboolean
handle_resume_charging (OrgPhilipsChargerMgr           *interface,
                       GDBusMethodInvocation  *invocation,
                       gpointer                user_data)
{
    Charger::allowCharging();
    org_philips_charger_mgr_complete_resume_charging(interface, invocation);
    return TRUE;
}


void emit_dbus_battery_warn(unsigned int type)
{
    if (object_battery)
        org_philips_battery_mgr_emit_battery_warn(ORG_PHILIPS_BATTERY_MGR (object_battery), type);
}

void emit_dbus_ac_change(bool ac_online)
{
    if (object_charger)
        org_philips_charger_mgr_emit_ac_change(ORG_PHILIPS_CHARGER_MGR (object_charger), ac_online);
}

void set_dbus_charger_ac_online(bool value){
    if (object_charger){
        g_object_set (G_OBJECT (object_charger), "ac-online", value, NULL);
    }
}

void set_dbus_battery_qualified(bool qualified){
    if (object_battery){
        org_philips_battery_mgr_set_qualified(ORG_PHILIPS_BATTERY_MGR (object_battery), qualified);
    }
}

static void
on_bus_acquired (GDBusConnection *connection,
                 const gchar     *name,
                 gpointer         user_data)
{
  GError *error = NULL;
  g_print( "GBusAcquired_Callback, name is %s, user_data: %s\n", name, (char *)user_data );

  object_charger = org_philips_charger_mgr_skeleton_new();

  //connect step
  g_signal_connect( object_charger, "handle-stop-charging", G_CALLBACK( handle_stop_charging), NULL );
  g_signal_connect( object_charger, "handle-resume-charging", G_CALLBACK( handle_resume_charging), NULL );

  g_dbus_interface_skeleton_export( G_DBUS_INTERFACE_SKELETON( object_charger ), connection, "/org/philips/charger", &error );
  if( NULL != error )
  {
      g_print( "Failed to export object: %s\n", error->message );
      g_error_free( error );
  }

  object_battery = battery_dbus_new();
  g_dbus_interface_skeleton_export( G_DBUS_INTERFACE_SKELETON( object_battery ), connection, "/org/philips/battery", &error );
  if( NULL != error )
  {
      g_print( "Failed to export object: %s\n", error->message );
      g_error_free( error );
  }

}

static void
on_name_acquired (GDBusConnection *connection,
                  const gchar     *name,
                  gpointer         user_data)
{
}

static void
on_name_lost (GDBusConnection *connection,
              const gchar     *name,
              gpointer         user_data)
{
  sd_journal_print(LOG_INFO, "dbus on_name_lost");
  exit (1);
}

int gdbus_init ()
{
  /* We are lazy here - we don't want to manually provide
   * the introspection data structures - so we just build
   * them from XML.
   */
    //guint owner_id;

    owner_id = g_bus_own_name (G_BUS_TYPE_SESSION,
                               "org.philips.charger_battery",
                               G_BUS_NAME_OWNER_FLAGS_NONE,
                               on_bus_acquired,
                               on_name_acquired,
                               on_name_lost,
                               NULL,
                               NULL);

    sleep(1);

  return 0;
}

int gdbus_uninit()
{
    g_bus_unown_name (owner_id);

    return 0;
}

bool waitDbusReady()
{
    int timeout = 5;
    do{
        if ((object_battery != NULL ) && (object_charger != NULL))
            break;
        sleep(1);
        timeout--;
        if (timeout <= 0){
            g_print("wait dbus ready failed\n");
            return false;
        }

    }while(1);

    return true;
}
