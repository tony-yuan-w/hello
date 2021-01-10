#ifndef __LIB_CLIENT__
#define __LIB_CLIENT__

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <glib-2.0/glib.h>

#include "dbus_generate_client.h"

#define RET_SIGNAL_HANDLE_SIZE 3


static void cb_OwnerNameChangedNotify(GObject *object, GParamSpec *pspec, gpointer userdata);

void stopCharging(GError** pError);
void resumeCharging(GError** pError);

bool DBusServiceIsReady(void);
bool InitDBusCommunication(void);
bool DeInitDBusCommunication(void);

#endif

