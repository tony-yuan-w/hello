#include "battery_dbus.h"
#include "dbus_server.h"
#include "battery.h"

G_DEFINE_TYPE(BatteryDbus, battery_dbus, TYPE_ORG_PHILIPS_BATTERY_MGR_SKELETON);

BatteryDbus *
battery_dbus_new (void)
{
  return BATTERY_DBUS (g_object_new (TYPE_BATTERY_DBUS, NULL));
}

static void
battery_dbus_get_property (GObject      *object,
  guint         prop_id,
  GValue       *value,
  GParamSpec   *pspec G_GNUC_UNUSED)
{
  g_print("---------------battery_dbus_get_property---------------\n");
  //org_philips_battery_mgr_skeleton_get_instance_private(ORG_PHILIPS_BATTERY_MGR_SKELETON (object));
  /*
  GDBusInterfaceInfo *info = org_philips_battery_mgr_interface_info();
  GString *propertyName = g_string_new(info->properties[prop_id-1]->name);
  g_print("get property %s\n", propertyName->str);

  if (g_string_equal(propertyName, g_string_new(BATTERY_PROPERTY_QUALIFIED)))
  {
      bool bQualified = Battery::IsBatteryQualified();
      g_value_set_boolean(value, bQualified);
  }
  else if (g_string_equal(propertyName, g_string_new(BATTERY_PROPERTY_PRESENT)))
  {
      bool bPresent = Battery::IsBatteryPresent();
      g_value_set_boolean(value, bPresent);
  }
  else if (g_string_equal(propertyName, g_string_new(BATTERY_PROPERTY_SERIAL_NUMBER))||
           g_string_equal(propertyName, g_string_new(BATTERY_PROPERTY_MODEL))||
           g_string_equal(propertyName, g_string_new(BATTERY_PROPERTY_MANUFACTURER))||
           g_string_equal(propertyName, g_string_new(BATTERY_PROPERTY_DATE))||
           g_string_equal(propertyName, g_string_new(BATTERY_PROPERTY_STATUS))||
           g_string_equal(propertyName, g_string_new(BATTERY_PROPERTY_SERIAL_NUMBER)))
  {
      char strValue[128];
      memset(strValue, 0x0, sizeof(strValue));
      Battery::ReadProperty(propertyName->str, strValue, sizeof(strValue));
      g_value_set_string(value, strValue);
  }
  else if (g_string_equal(propertyName, g_string_new(BATTERY_PROPERTY_TIME_TO_EMPTY))||
           g_string_equal(propertyName, g_string_new(BATTERY_PROPERTY_CYCLE_COUNT)) ||
           g_string_equal(propertyName, g_string_new(BATTERY_PROPERTY_CURRENT_AVG))||
           g_string_equal(propertyName, g_string_new(BATTERY_PROPERTY_TEMP)) ||
           g_string_equal(propertyName, g_string_new(BATTERY_PROPERTY_CONST_CHARG_VOL)) ||
           g_string_equal(propertyName, g_string_new(BATTERY_PROPERTY_CONST_CHARG_CUR)) ||
           g_string_equal(propertyName, g_string_new(BATTERY_PROPERTY_CURRENT_NOW)) ||
           g_string_equal(propertyName, g_string_new(BATTERY_PROPERTY_MAX_ERROR)) ||
           g_string_equal(propertyName, g_string_new(BATTERY_PROPERTY_TIME_TO_EMPTY)) ||
           g_string_equal(propertyName, g_string_new(BATTERY_PROPERTY_TIME_TO_EMPTY_AVG)) ||
           g_string_equal(propertyName, g_string_new(BATTERY_PROPERTY_ABSOLUTE_CHARGE)) ||
           g_string_equal(propertyName, g_string_new(BATTERY_PROPERTY_CAP)) ||
           g_string_equal(propertyName, g_string_new(BATTERY_PROPERTY_STATUS_REG)) ||
           g_string_equal(propertyName, g_string_new(BATTERY_PROPERTY_MODE_REG)) ||
           g_string_equal(propertyName, g_string_new(BATTERY_PROPERTY_CHARGE_FULL_DESIGN)) ||
           g_string_equal(propertyName, g_string_new(BATTERY_PROPERTY_CHARGE_FULL)) ||
           g_string_equal(propertyName, g_string_new(BATTERY_PROPERTY_CHARGE_NOW))
           )
  {
      int propertyValue = 0;
      Battery::ReadProperty(propertyName->str, propertyValue);
      g_value_set_uint(value, (guint)propertyValue);
  }
    */
}

static void
battery_dbus_set_property (GObject      *object,
  guint         prop_id,
  const GValue *value,
  GParamSpec   *pspec)
{
    g_print("battery_dbus_set_property\n");
    //OrgPhilipsBatteryMgrSkeleton *skeleton = ORG_PHILIPS_BATTERY_MGR_SKELETON (object);
    G_OBJECT_CLASS (battery_dbus_parent_class)->set_property(object, prop_id, value, pspec);
}

static void
battery_dbus_init (BatteryDbus *skeleton)
{
    g_print("battery dbus instance init\n");
}

static void
battery_dbus_class_init (BatteryDbusClass *klass)
{
  g_print("battery dbus class init\n");
  GObjectClass *gobject_class;
  gobject_class = G_OBJECT_CLASS (klass);

  gobject_class->get_property = battery_dbus_get_property;
  gobject_class->set_property = battery_dbus_set_property;

  org_philips_battery_mgr_override_properties (gobject_class, 1);
}
