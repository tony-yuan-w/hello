#ifndef DBUS_PROCESS_H
#define DBUS_PROCESS_H

#include "battery_dbus.h"
#include "dbus_generate_server.h"

extern BatteryDbus *object_battery;
extern OrgPhilipsChargerMgr *object_charger;

int gdbus_init();
int gdbus_uninit();
void emit_dbus_battery_warn(unsigned int type);
void emit_dbus_ac_change(bool ac_online);
void set_dbus_charger_ac_online(bool ac_online);
void set_dbus_battery_qualified(bool qualified);
bool waitDbusReady();

#endif // DBUS_PROCESS_H
