#ifndef BATTERY_DBUS_H
#define BATTERY_DBUS_H

#include "dbus_generate_server.h"

#define TYPE_BATTERY_DBUS (battery_dbus_get_type ())
#define BATTERY_DBUS(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_BATTERY_DBUS, BatteryDbus))
#define BATTERY_DBUS_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), TYPE_BATTERY_DBUS, BatteryDbusClass))
#define BATTERY_DBUS_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), TYPE_BATTERY_DBUS, BatteryDbusClass))
#define IS_BATTERY_DBUS(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_BATTERY_DBUS))
#define IS_BATTERY_DBUS_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), TYPE_BATTERY_DBUS))

typedef struct _BatteryDbus BatteryDbus;
typedef struct _BatteryDbusClass BatteryDbusClass;

struct _BatteryDbus
{
  /*< private >*/
  OrgPhilipsBatteryMgrSkeleton parent_instance;
};

struct _BatteryDbusClass
{
  OrgPhilipsBatteryMgrSkeletonClass parent_class;
  //GObjectClass parent_class;
};

GType battery_dbus_get_type (void) G_GNUC_CONST;

BatteryDbus *battery_dbus_new (void);

#endif
