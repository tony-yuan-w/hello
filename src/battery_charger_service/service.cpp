#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <pthread.h>
#include <gio/gio.h>
#include <systemd/sd-journal.h>

#include "dbus_server.h"
#include "charger.h"
#include "battery.h"

extern void log_thread();

GMainLoop *loop;

void exitProcess(int signo)
{
    sd_journal_print(LOG_INFO, "Catch signal:%d\n", signo);
    Charger::stopCharging();
    exit(1);
}

int main(int argc, char **argv)
{
    //daemon(1, 1);

    sd_journal_print(LOG_INFO, "start charger service\n");
    loop = g_main_loop_new (NULL, false);
    signal(SIGINT, exitProcess);

    gdbus_init();

    pthread_t charge_thread_id;
    int ret = pthread_create(&charge_thread_id, NULL, &charging_thread, NULL);
    if (ret != 0)
    {
        sd_journal_print(LOG_INFO, "create thread fail:%d\n", errno);
    }

    BatteryPollThread batteryPoll;
    batteryPoll.start();

    log_thread();

    g_main_loop_run(loop);
    
    gdbus_uninit();
    
    return 0;
}
