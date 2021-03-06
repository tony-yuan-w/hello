/*
 * Generated by gdbus-codegen 2.56.4. DO NOT EDIT.
 *
 * The license of this code is the same as for the D-Bus interface description
 * it was derived from.
 */

#ifndef __DBUS_GENERATE_SERVER_H__
#define __DBUS_GENERATE_SERVER_H__

#include <gio/gio.h>

G_BEGIN_DECLS


/* ------------------------------------------------------------------------ */
/* Declarations for org.philips.chargerMgr */

#define TYPE_ORG_PHILIPS_CHARGER_MGR (org_philips_charger_mgr_get_type ())
#define ORG_PHILIPS_CHARGER_MGR(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_ORG_PHILIPS_CHARGER_MGR, OrgPhilipsChargerMgr))
#define IS_ORG_PHILIPS_CHARGER_MGR(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_ORG_PHILIPS_CHARGER_MGR))
#define ORG_PHILIPS_CHARGER_MGR_GET_IFACE(o) (G_TYPE_INSTANCE_GET_INTERFACE ((o), TYPE_ORG_PHILIPS_CHARGER_MGR, OrgPhilipsChargerMgrIface))

struct _OrgPhilipsChargerMgr;
typedef struct _OrgPhilipsChargerMgr OrgPhilipsChargerMgr;
typedef struct _OrgPhilipsChargerMgrIface OrgPhilipsChargerMgrIface;

struct _OrgPhilipsChargerMgrIface
{
  GTypeInterface parent_iface;



  gboolean (*handle_resume_charging) (
    OrgPhilipsChargerMgr *object,
    GDBusMethodInvocation *invocation);

  gboolean (*handle_stop_charging) (
    OrgPhilipsChargerMgr *object,
    GDBusMethodInvocation *invocation);

  gboolean  (*get_ac_online) (OrgPhilipsChargerMgr *object);

  gboolean  (*get_test) (OrgPhilipsChargerMgr *object);

  void (*ac_change) (
    OrgPhilipsChargerMgr *object,
    gboolean arg_state);

};

GType org_philips_charger_mgr_get_type (void) G_GNUC_CONST;

GDBusInterfaceInfo *org_philips_charger_mgr_interface_info (void);
guint org_philips_charger_mgr_override_properties (GObjectClass *klass, guint property_id_begin);


/* D-Bus method call completion functions: */
void org_philips_charger_mgr_complete_stop_charging (
    OrgPhilipsChargerMgr *object,
    GDBusMethodInvocation *invocation);

void org_philips_charger_mgr_complete_resume_charging (
    OrgPhilipsChargerMgr *object,
    GDBusMethodInvocation *invocation);



/* D-Bus signal emissions functions: */
void org_philips_charger_mgr_emit_ac_change (
    OrgPhilipsChargerMgr *object,
    gboolean arg_state);



/* D-Bus method calls: */
void org_philips_charger_mgr_call_stop_charging (
    OrgPhilipsChargerMgr *proxy,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean org_philips_charger_mgr_call_stop_charging_finish (
    OrgPhilipsChargerMgr *proxy,
    GAsyncResult *res,
    GError **error);

gboolean org_philips_charger_mgr_call_stop_charging_sync (
    OrgPhilipsChargerMgr *proxy,
    GCancellable *cancellable,
    GError **error);

void org_philips_charger_mgr_call_resume_charging (
    OrgPhilipsChargerMgr *proxy,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean org_philips_charger_mgr_call_resume_charging_finish (
    OrgPhilipsChargerMgr *proxy,
    GAsyncResult *res,
    GError **error);

gboolean org_philips_charger_mgr_call_resume_charging_sync (
    OrgPhilipsChargerMgr *proxy,
    GCancellable *cancellable,
    GError **error);



/* D-Bus property accessors: */
gboolean org_philips_charger_mgr_get_ac_online (OrgPhilipsChargerMgr *object);
void org_philips_charger_mgr_set_ac_online (OrgPhilipsChargerMgr *object, gboolean value);

gboolean org_philips_charger_mgr_get_test (OrgPhilipsChargerMgr *object);
void org_philips_charger_mgr_set_test (OrgPhilipsChargerMgr *object, gboolean value);


/* ---- */

#define TYPE_ORG_PHILIPS_CHARGER_MGR_PROXY (org_philips_charger_mgr_proxy_get_type ())
#define ORG_PHILIPS_CHARGER_MGR_PROXY(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_ORG_PHILIPS_CHARGER_MGR_PROXY, OrgPhilipsChargerMgrProxy))
#define ORG_PHILIPS_CHARGER_MGR_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), TYPE_ORG_PHILIPS_CHARGER_MGR_PROXY, OrgPhilipsChargerMgrProxyClass))
#define ORG_PHILIPS_CHARGER_MGR_PROXY_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), TYPE_ORG_PHILIPS_CHARGER_MGR_PROXY, OrgPhilipsChargerMgrProxyClass))
#define IS_ORG_PHILIPS_CHARGER_MGR_PROXY(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_ORG_PHILIPS_CHARGER_MGR_PROXY))
#define IS_ORG_PHILIPS_CHARGER_MGR_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), TYPE_ORG_PHILIPS_CHARGER_MGR_PROXY))

typedef struct _OrgPhilipsChargerMgrProxy OrgPhilipsChargerMgrProxy;
typedef struct _OrgPhilipsChargerMgrProxyClass OrgPhilipsChargerMgrProxyClass;
typedef struct _OrgPhilipsChargerMgrProxyPrivate OrgPhilipsChargerMgrProxyPrivate;

struct _OrgPhilipsChargerMgrProxy
{
  /*< private >*/
  GDBusProxy parent_instance;
  OrgPhilipsChargerMgrProxyPrivate *priv;
};

struct _OrgPhilipsChargerMgrProxyClass
{
  GDBusProxyClass parent_class;
};

GType org_philips_charger_mgr_proxy_get_type (void) G_GNUC_CONST;

#if GLIB_CHECK_VERSION(2, 44, 0)
G_DEFINE_AUTOPTR_CLEANUP_FUNC (OrgPhilipsChargerMgrProxy, g_object_unref)
#endif

void org_philips_charger_mgr_proxy_new (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
OrgPhilipsChargerMgr *org_philips_charger_mgr_proxy_new_finish (
    GAsyncResult        *res,
    GError             **error);
OrgPhilipsChargerMgr *org_philips_charger_mgr_proxy_new_sync (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);

void org_philips_charger_mgr_proxy_new_for_bus (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
OrgPhilipsChargerMgr *org_philips_charger_mgr_proxy_new_for_bus_finish (
    GAsyncResult        *res,
    GError             **error);
OrgPhilipsChargerMgr *org_philips_charger_mgr_proxy_new_for_bus_sync (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);


/* ---- */

#define TYPE_ORG_PHILIPS_CHARGER_MGR_SKELETON (org_philips_charger_mgr_skeleton_get_type ())
#define ORG_PHILIPS_CHARGER_MGR_SKELETON(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_ORG_PHILIPS_CHARGER_MGR_SKELETON, OrgPhilipsChargerMgrSkeleton))
#define ORG_PHILIPS_CHARGER_MGR_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), TYPE_ORG_PHILIPS_CHARGER_MGR_SKELETON, OrgPhilipsChargerMgrSkeletonClass))
#define ORG_PHILIPS_CHARGER_MGR_SKELETON_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), TYPE_ORG_PHILIPS_CHARGER_MGR_SKELETON, OrgPhilipsChargerMgrSkeletonClass))
#define IS_ORG_PHILIPS_CHARGER_MGR_SKELETON(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_ORG_PHILIPS_CHARGER_MGR_SKELETON))
#define IS_ORG_PHILIPS_CHARGER_MGR_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), TYPE_ORG_PHILIPS_CHARGER_MGR_SKELETON))

typedef struct _OrgPhilipsChargerMgrSkeleton OrgPhilipsChargerMgrSkeleton;
typedef struct _OrgPhilipsChargerMgrSkeletonClass OrgPhilipsChargerMgrSkeletonClass;
typedef struct _OrgPhilipsChargerMgrSkeletonPrivate OrgPhilipsChargerMgrSkeletonPrivate;

struct _OrgPhilipsChargerMgrSkeleton
{
  /*< private >*/
  GDBusInterfaceSkeleton parent_instance;
  OrgPhilipsChargerMgrSkeletonPrivate *priv;
};

struct _OrgPhilipsChargerMgrSkeletonClass
{
  GDBusInterfaceSkeletonClass parent_class;
};

GType org_philips_charger_mgr_skeleton_get_type (void) G_GNUC_CONST;

#if GLIB_CHECK_VERSION(2, 44, 0)
G_DEFINE_AUTOPTR_CLEANUP_FUNC (OrgPhilipsChargerMgrSkeleton, g_object_unref)
#endif

OrgPhilipsChargerMgr *org_philips_charger_mgr_skeleton_new (void);


/* ------------------------------------------------------------------------ */
/* Declarations for org.philips.batteryMgr */

#define TYPE_ORG_PHILIPS_BATTERY_MGR (org_philips_battery_mgr_get_type ())
#define ORG_PHILIPS_BATTERY_MGR(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_ORG_PHILIPS_BATTERY_MGR, OrgPhilipsBatteryMgr))
#define IS_ORG_PHILIPS_BATTERY_MGR(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_ORG_PHILIPS_BATTERY_MGR))
#define ORG_PHILIPS_BATTERY_MGR_GET_IFACE(o) (G_TYPE_INSTANCE_GET_INTERFACE ((o), TYPE_ORG_PHILIPS_BATTERY_MGR, OrgPhilipsBatteryMgrIface))

struct _OrgPhilipsBatteryMgr;
typedef struct _OrgPhilipsBatteryMgr OrgPhilipsBatteryMgr;
typedef struct _OrgPhilipsBatteryMgrIface OrgPhilipsBatteryMgrIface;

struct _OrgPhilipsBatteryMgrIface
{
  GTypeInterface parent_iface;


  guint  (*get_absolute_charge) (OrgPhilipsBatteryMgr *object);

  guint  (*get_capacity) (OrgPhilipsBatteryMgr *object);

  guint  (*get_charge_full) (OrgPhilipsBatteryMgr *object);

  guint  (*get_charge_full_design) (OrgPhilipsBatteryMgr *object);

  guint  (*get_charge_now) (OrgPhilipsBatteryMgr *object);

  guint  (*get_constant_charge_current) (OrgPhilipsBatteryMgr *object);

  guint  (*get_constant_charge_voltage) (OrgPhilipsBatteryMgr *object);

  guint  (*get_current_avg) (OrgPhilipsBatteryMgr *object);

  guint  (*get_cycle_count) (OrgPhilipsBatteryMgr *object);

  const gchar * (*get_date) (OrgPhilipsBatteryMgr *object);

  const gchar * (*get_manufacturer) (OrgPhilipsBatteryMgr *object);

  guint  (*get_max_error) (OrgPhilipsBatteryMgr *object);

  gint  (*get_mode_register) (OrgPhilipsBatteryMgr *object);

  const gchar * (*get_model_name) (OrgPhilipsBatteryMgr *object);

  gboolean  (*get_present) (OrgPhilipsBatteryMgr *object);

  gboolean  (*get_qualified) (OrgPhilipsBatteryMgr *object);

  const gchar * (*get_serial_number) (OrgPhilipsBatteryMgr *object);

  const gchar * (*get_status) (OrgPhilipsBatteryMgr *object);

  gint  (*get_status_register) (OrgPhilipsBatteryMgr *object);

  guint  (*get_temp) (OrgPhilipsBatteryMgr *object);

  guint  (*get_time_to_empty_avg) (OrgPhilipsBatteryMgr *object);

  guint  (*get_time_to_empty_now) (OrgPhilipsBatteryMgr *object);

  guint  (*get_time_to_full_avg) (OrgPhilipsBatteryMgr *object);

  void (*battery_warn) (
    OrgPhilipsBatteryMgr *object,
    guint arg_type);

};

GType org_philips_battery_mgr_get_type (void) G_GNUC_CONST;

GDBusInterfaceInfo *org_philips_battery_mgr_interface_info (void);
guint org_philips_battery_mgr_override_properties (GObjectClass *klass, guint property_id_begin);


/* D-Bus signal emissions functions: */
void org_philips_battery_mgr_emit_battery_warn (
    OrgPhilipsBatteryMgr *object,
    guint arg_type);



/* D-Bus property accessors: */
gboolean org_philips_battery_mgr_get_qualified (OrgPhilipsBatteryMgr *object);
void org_philips_battery_mgr_set_qualified (OrgPhilipsBatteryMgr *object, gboolean value);

gboolean org_philips_battery_mgr_get_present (OrgPhilipsBatteryMgr *object);
void org_philips_battery_mgr_set_present (OrgPhilipsBatteryMgr *object, gboolean value);

guint org_philips_battery_mgr_get_cycle_count (OrgPhilipsBatteryMgr *object);
void org_philips_battery_mgr_set_cycle_count (OrgPhilipsBatteryMgr *object, guint value);

const gchar *org_philips_battery_mgr_get_status (OrgPhilipsBatteryMgr *object);
gchar *org_philips_battery_mgr_dup_status (OrgPhilipsBatteryMgr *object);
void org_philips_battery_mgr_set_status (OrgPhilipsBatteryMgr *object, const gchar *value);

guint org_philips_battery_mgr_get_charge_now (OrgPhilipsBatteryMgr *object);
void org_philips_battery_mgr_set_charge_now (OrgPhilipsBatteryMgr *object, guint value);

guint org_philips_battery_mgr_get_charge_full (OrgPhilipsBatteryMgr *object);
void org_philips_battery_mgr_set_charge_full (OrgPhilipsBatteryMgr *object, guint value);

guint org_philips_battery_mgr_get_charge_full_design (OrgPhilipsBatteryMgr *object);
void org_philips_battery_mgr_set_charge_full_design (OrgPhilipsBatteryMgr *object, guint value);

gint org_philips_battery_mgr_get_mode_register (OrgPhilipsBatteryMgr *object);
void org_philips_battery_mgr_set_mode_register (OrgPhilipsBatteryMgr *object, gint value);

gint org_philips_battery_mgr_get_status_register (OrgPhilipsBatteryMgr *object);
void org_philips_battery_mgr_set_status_register (OrgPhilipsBatteryMgr *object, gint value);

guint org_philips_battery_mgr_get_capacity (OrgPhilipsBatteryMgr *object);
void org_philips_battery_mgr_set_capacity (OrgPhilipsBatteryMgr *object, guint value);

guint org_philips_battery_mgr_get_absolute_charge (OrgPhilipsBatteryMgr *object);
void org_philips_battery_mgr_set_absolute_charge (OrgPhilipsBatteryMgr *object, guint value);

guint org_philips_battery_mgr_get_time_to_empty_avg (OrgPhilipsBatteryMgr *object);
void org_philips_battery_mgr_set_time_to_empty_avg (OrgPhilipsBatteryMgr *object, guint value);

guint org_philips_battery_mgr_get_time_to_full_avg (OrgPhilipsBatteryMgr *object);
void org_philips_battery_mgr_set_time_to_full_avg (OrgPhilipsBatteryMgr *object, guint value);

guint org_philips_battery_mgr_get_max_error (OrgPhilipsBatteryMgr *object);
void org_philips_battery_mgr_set_max_error (OrgPhilipsBatteryMgr *object, guint value);

guint org_philips_battery_mgr_get_constant_charge_current (OrgPhilipsBatteryMgr *object);
void org_philips_battery_mgr_set_constant_charge_current (OrgPhilipsBatteryMgr *object, guint value);

guint org_philips_battery_mgr_get_constant_charge_voltage (OrgPhilipsBatteryMgr *object);
void org_philips_battery_mgr_set_constant_charge_voltage (OrgPhilipsBatteryMgr *object, guint value);

guint org_philips_battery_mgr_get_temp (OrgPhilipsBatteryMgr *object);
void org_philips_battery_mgr_set_temp (OrgPhilipsBatteryMgr *object, guint value);

guint org_philips_battery_mgr_get_time_to_empty_now (OrgPhilipsBatteryMgr *object);
void org_philips_battery_mgr_set_time_to_empty_now (OrgPhilipsBatteryMgr *object, guint value);

guint org_philips_battery_mgr_get_current_avg (OrgPhilipsBatteryMgr *object);
void org_philips_battery_mgr_set_current_avg (OrgPhilipsBatteryMgr *object, guint value);

const gchar *org_philips_battery_mgr_get_date (OrgPhilipsBatteryMgr *object);
gchar *org_philips_battery_mgr_dup_date (OrgPhilipsBatteryMgr *object);
void org_philips_battery_mgr_set_date (OrgPhilipsBatteryMgr *object, const gchar *value);

const gchar *org_philips_battery_mgr_get_manufacturer (OrgPhilipsBatteryMgr *object);
gchar *org_philips_battery_mgr_dup_manufacturer (OrgPhilipsBatteryMgr *object);
void org_philips_battery_mgr_set_manufacturer (OrgPhilipsBatteryMgr *object, const gchar *value);

const gchar *org_philips_battery_mgr_get_model_name (OrgPhilipsBatteryMgr *object);
gchar *org_philips_battery_mgr_dup_model_name (OrgPhilipsBatteryMgr *object);
void org_philips_battery_mgr_set_model_name (OrgPhilipsBatteryMgr *object, const gchar *value);

const gchar *org_philips_battery_mgr_get_serial_number (OrgPhilipsBatteryMgr *object);
gchar *org_philips_battery_mgr_dup_serial_number (OrgPhilipsBatteryMgr *object);
void org_philips_battery_mgr_set_serial_number (OrgPhilipsBatteryMgr *object, const gchar *value);


/* ---- */

#define TYPE_ORG_PHILIPS_BATTERY_MGR_PROXY (org_philips_battery_mgr_proxy_get_type ())
#define ORG_PHILIPS_BATTERY_MGR_PROXY(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_ORG_PHILIPS_BATTERY_MGR_PROXY, OrgPhilipsBatteryMgrProxy))
#define ORG_PHILIPS_BATTERY_MGR_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), TYPE_ORG_PHILIPS_BATTERY_MGR_PROXY, OrgPhilipsBatteryMgrProxyClass))
#define ORG_PHILIPS_BATTERY_MGR_PROXY_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), TYPE_ORG_PHILIPS_BATTERY_MGR_PROXY, OrgPhilipsBatteryMgrProxyClass))
#define IS_ORG_PHILIPS_BATTERY_MGR_PROXY(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_ORG_PHILIPS_BATTERY_MGR_PROXY))
#define IS_ORG_PHILIPS_BATTERY_MGR_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), TYPE_ORG_PHILIPS_BATTERY_MGR_PROXY))

typedef struct _OrgPhilipsBatteryMgrProxy OrgPhilipsBatteryMgrProxy;
typedef struct _OrgPhilipsBatteryMgrProxyClass OrgPhilipsBatteryMgrProxyClass;
typedef struct _OrgPhilipsBatteryMgrProxyPrivate OrgPhilipsBatteryMgrProxyPrivate;

struct _OrgPhilipsBatteryMgrProxy
{
  /*< private >*/
  GDBusProxy parent_instance;
  OrgPhilipsBatteryMgrProxyPrivate *priv;
};

struct _OrgPhilipsBatteryMgrProxyClass
{
  GDBusProxyClass parent_class;
};

GType org_philips_battery_mgr_proxy_get_type (void) G_GNUC_CONST;

#if GLIB_CHECK_VERSION(2, 44, 0)
G_DEFINE_AUTOPTR_CLEANUP_FUNC (OrgPhilipsBatteryMgrProxy, g_object_unref)
#endif

void org_philips_battery_mgr_proxy_new (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
OrgPhilipsBatteryMgr *org_philips_battery_mgr_proxy_new_finish (
    GAsyncResult        *res,
    GError             **error);
OrgPhilipsBatteryMgr *org_philips_battery_mgr_proxy_new_sync (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);

void org_philips_battery_mgr_proxy_new_for_bus (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
OrgPhilipsBatteryMgr *org_philips_battery_mgr_proxy_new_for_bus_finish (
    GAsyncResult        *res,
    GError             **error);
OrgPhilipsBatteryMgr *org_philips_battery_mgr_proxy_new_for_bus_sync (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);


/* ---- */

#define TYPE_ORG_PHILIPS_BATTERY_MGR_SKELETON (org_philips_battery_mgr_skeleton_get_type ())
#define ORG_PHILIPS_BATTERY_MGR_SKELETON(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), TYPE_ORG_PHILIPS_BATTERY_MGR_SKELETON, OrgPhilipsBatteryMgrSkeleton))
#define ORG_PHILIPS_BATTERY_MGR_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), TYPE_ORG_PHILIPS_BATTERY_MGR_SKELETON, OrgPhilipsBatteryMgrSkeletonClass))
#define ORG_PHILIPS_BATTERY_MGR_SKELETON_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), TYPE_ORG_PHILIPS_BATTERY_MGR_SKELETON, OrgPhilipsBatteryMgrSkeletonClass))
#define IS_ORG_PHILIPS_BATTERY_MGR_SKELETON(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), TYPE_ORG_PHILIPS_BATTERY_MGR_SKELETON))
#define IS_ORG_PHILIPS_BATTERY_MGR_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), TYPE_ORG_PHILIPS_BATTERY_MGR_SKELETON))

typedef struct _OrgPhilipsBatteryMgrSkeleton OrgPhilipsBatteryMgrSkeleton;
typedef struct _OrgPhilipsBatteryMgrSkeletonClass OrgPhilipsBatteryMgrSkeletonClass;
typedef struct _OrgPhilipsBatteryMgrSkeletonPrivate OrgPhilipsBatteryMgrSkeletonPrivate;

struct _OrgPhilipsBatteryMgrSkeleton
{
  /*< private >*/
  GDBusInterfaceSkeleton parent_instance;
  OrgPhilipsBatteryMgrSkeletonPrivate *priv;
};

struct _OrgPhilipsBatteryMgrSkeletonClass
{
  GDBusInterfaceSkeletonClass parent_class;
};

GType org_philips_battery_mgr_skeleton_get_type (void) G_GNUC_CONST;

#if GLIB_CHECK_VERSION(2, 44, 0)
G_DEFINE_AUTOPTR_CLEANUP_FUNC (OrgPhilipsBatteryMgrSkeleton, g_object_unref)
#endif

OrgPhilipsBatteryMgr *org_philips_battery_mgr_skeleton_new (void);


G_END_DECLS

#endif /* __DBUS_GENERATE_SERVER_H__ */
