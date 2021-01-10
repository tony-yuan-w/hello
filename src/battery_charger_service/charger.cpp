#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <gio/gio.h>
#include <systemd/sd-journal.h>
#include "battery.h"
#include "charger.h"
#include "dbus_server.h"

static bool volatile g_stopCharging = false;
static bool volatile g_prohibitCharge = false;

Charger::Charger()
{
}

bool Charger::readProperty(const char *property, int &value)
{
    char filename[256];
    char buf[256];
    sprintf(filename, "%s/%s", CHARGER_PATH, property);

    bool ret = false;
    if (0 == access(filename, W_OK))
    {
        int fd = open(filename, O_RDONLY);
        if (fd != -1){
            ssize_t len =  read(fd, buf, sizeof(buf));

            if (len > 0)
            {
                buf[len] = '\0';
                value = atoi(buf);
                ret = true;
            }
            close(fd);
        }
    }

    if (!ret)
        sd_journal_print(LOG_INFO, "read charger property %s failed", property);

    return ret;
}

int Charger::setProperty(const char *property, int value)
{
    char filename[256];
    sprintf(filename, "%s/%s", CHARGER_PATH, property);
    char strValue[64];
    sprintf(strValue, "%d", value);

    int ret = -1;

    if (0 == access(filename, W_OK))
    {
        int fd = open(filename, O_RDWR);
        if (fd != -1){
            if (write(fd, strValue, strlen(strValue)) > 0){
                ret = 0;
            }
            else{
                sd_journal_print(LOG_INFO, "set property failed");
            }
            close(fd);
        }
    }

    return ret;
}

void Charger::stopCharging()
{
    g_print("stop charging...\n");

    if (g_stopCharging == false){
        g_stopCharging = true;
        setProperty("status", 2);
        setProperty("constant_charge_current", 0);
        setProperty("constant_charge_voltage", 0);
    }
}

void Charger::prohibitCharge()
{
    g_prohibitCharge = true;
    stopCharging();
}

void Charger::resumeCharging()
{
    if (!g_prohibitCharge){
        g_stopCharging = false;
        sd_journal_print(LOG_INFO, "resume charging, g_stopCharging flag = %d", g_stopCharging);
        setProperty("status", 1);
    }
}

void Charger::allowCharging()
{
    g_prohibitCharge = false;
    resumeCharging();
}

bool Charger::isCharging()
{
    int value;
    Charger::readProperty("status", value);
    if (value == 1){
        return true;
    }
    return false;
}

void * charging_thread(void *arg)
{
    int battery_const_current, battery_const_voltage;
    int battery_present = 0;

    battery_const_current = battery_const_voltage = 0;
    bool ret = true;
    Battery::ReadProperty("constant_charge_current", battery_const_current);
    Battery::ReadProperty("constant_charge_voltage", battery_const_voltage);
    Battery::ReadProperty("present", battery_present);

    int ac_online = 0;
    sleep(1);
    Charger::readProperty("online", ac_online);
    set_dbus_charger_ac_online(ac_online);

    sd_journal_print(LOG_INFO, "start charger thread");
    waitDbusReady();

    int value = 0;
    time_t lasttime = 0;

    g_stopCharging = false;

    while(1)
    {
        value = 0;

        Charger::readProperty("online", value);

        if (ac_online != value)
        {
            sleep(1);
            Charger::readProperty("online", value);
            if (ac_online != value){
                ac_online = value;
                set_dbus_charger_ac_online(ac_online);
                emit_dbus_ac_change(value);
                sd_journal_print(LOG_INFO, "AC status change, value=%d", ac_online);
                lasttime = 0;
            }
        }

        if (g_stopCharging){
            sleep(1);
            lasttime = 0;
            continue;
        }

        battery_const_current = 0;
        ret = Battery::ReadProperty("constant_charge_current", battery_const_current);

        battery_const_voltage = 0;
        ret = Battery::ReadProperty("constant_charge_voltage", battery_const_voltage);

        static int logInterval = 0;
        logInterval++;
        if (logInterval > 30){
            logInterval = 0;
            sd_journal_print(LOG_INFO, "ac_online = %d, battery_const_current=%d,battery_const_voltage=%d",
                         ac_online, battery_const_current, battery_const_voltage);
        }

        if ((ac_online == 1) && (battery_const_current > 0) && (battery_const_voltage > 0) )
        {
            time_t curtime = time(NULL);
            //no need set too frequency
            if (abs(curtime - lasttime >= 30)){
                lasttime = curtime;

                Charger::setProperty("status", 1);
                int charge_currrent = battery_const_current;
                if (battery_const_current > 2048)
                {
                    charge_currrent = 1946;
                }
                else if (battery_const_current >= 1024 && battery_const_current < 2048)
                {
                    charge_currrent = battery_const_current*0.95;
                }
                else if (battery_const_current >= 512 && battery_const_current < 1024)
                {
                    charge_currrent = battery_const_current*0.85;
                }
                else if (battery_const_current > 0 && battery_const_current < 512)
                {
                    charge_currrent = battery_const_current*0.75;
                }
                sd_journal_print(LOG_INFO, "set charging current=%d,charging voltage=%d",
                                 charge_currrent, battery_const_voltage);
                Charger::setProperty("constant_charge_current", charge_currrent);
                Charger::setProperty("constant_charge_voltage", battery_const_voltage);
            }
        }

        sleep(1);
    }

    sd_journal_print(LOG_INFO, "Charger poll thread end\n");

    return NULL;
}
