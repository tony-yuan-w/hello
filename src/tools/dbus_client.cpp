#include <gio/gio.h>    /** GIO for dbus*/
#include <glib-2.0/glib.h>  /** GLIB for main loop*/
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

/**
    instance init
*/

#include "dbus_client.h"

static GMainLoop *pLoop = NULL;
static GDBusConnection *pConnection = NULL;
static OrgPhilipsChargerMgr *pProxy = NULL;

void stopCharging(GError** pError)
{
    org_philips_charger_mgr_call_stop_charging_sync(pProxy, NULL, pError);

    if (*pError == NULL){
        g_print("stopCharging call success\n");
    }
    else{
        g_print("client stopCharging: Failed to call method. Reason: %s.\n", (*pError)->message);
        g_error_free(*pError);
    }

    return;
}

void resumeCharging(GError** pError)
{
    org_philips_charger_mgr_call_resume_charging_sync(pProxy, NULL, pError);

    if (*pError == NULL){
        g_print("resumeCharging call success\n");
    }
    else{
        g_print("client resumeCharging: Failed to call method. Reason: %s.\n", (*pError)->message);
        g_error_free(*pError);
    }

    return;
}

bool DBusServiceIsReady(void)
{
    gchar *owner_name = NULL;
    owner_name = g_dbus_proxy_get_name_owner((GDBusProxy*)pProxy);
    if(NULL != owner_name)
    {
        //g_print("Owner Name: %s\n", owner_name);
        g_free(owner_name);
        return true;
    }
    else
    {
        g_print("Owner Name is NULL.\n");
        return false;
    }
}

bool InitDBusCommunication(void)
{
    bool bRet = TRUE;
    GError *pConnError = NULL;
    GError *pProxyError = NULL;

    do{
        bRet = TRUE;
        pLoop = g_main_loop_new(NULL, FALSE);   /** create main loop, but do not start it.*/

        /** First step: get a connection */
        pConnection = g_bus_get_sync(G_BUS_TYPE_SYSTEM, NULL, &pConnError);

        if (NULL == pConnError){
            /** Second step: try to get a connection to the given bus.*/
            pProxy = org_philips_charger_mgr_proxy_new_sync(pConnection,
                                        G_DBUS_PROXY_FLAGS_NONE,
                                        "org.philips.charger_battery",
                                        "/org/philips/charger",
                                        NULL,
                                        &pProxyError);
            if (0 == pProxy){
                g_print("InitDBusCommunication: Failed to create proxy. Reason: %s.\n", pProxyError->message);
                g_error_free(pProxyError);
                bRet = FALSE;
            }
        }
        else{
            g_print("InitDBusCommunication: Failed to connect to dbus. Reason: %s.\n", pConnError->message);
            g_error_free(pConnError);
            bRet = FALSE;
        }
    }while(FALSE == bRet);

    return bRet;
}

bool DeInitDBusCommunication(void)
{
    bool bRet = FALSE;

    if(0 != pLoop){
        g_main_loop_quit(pLoop);
        g_main_loop_unref(pLoop);
        bRet = TRUE;
    }

    return bRet;
}

