#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <signal.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "dbus_client.h"

int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        printf("syntax: %s {stop_charging/resume_charging} \n", argv[0]);
        return -1;
    }

    InitDBusCommunication();

    if(!DBusServiceIsReady()){
        g_print("service is not ready.\n");
        return -1;
    }

    GError *syncMethodError = NULL;

    if (strcasecmp("stop_charging", argv[1]) == 0)
    {
        stopCharging(&syncMethodError);
    }
    else if (strcasecmp("resume_charging", argv[1]) == 0)
    {
        resumeCharging(&syncMethodError);
    }
    else
    {
        printf("syntax: %s {stop_charging/resume_charging} \n", argv[0]);
    }

    DeInitDBusCommunication();

    return 0;
}
