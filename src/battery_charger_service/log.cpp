#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <gio/gio.h>
#include <systemd/sd-journal.h>

#include "battery.h"

#define LOG_MAX_SIZE  2*1024*1024

/*
inline void rotateLog(int *fd)
{
    if (*fd != -1) {
        unsigned long long fileSize = getFileSize(*fd);
        if (fileSize > MAX_SIZE) {
            char newname[2048];
            close(*fd);
            *fd = -1;
            snprintf(newname, sizeof(newname), "%s.old", name);
            rename(name, newname);
            *fd = openOutput();
        }
    }
}
*/

int write_log(const char *filename, const char *string)
{
    struct stat statbuf;
    if (stat(filename, &statbuf) == 0)
    {
        if (statbuf.st_size > LOG_MAX_SIZE)
        {
            sd_journal_print(LOG_INFO, "battery log reach max size");
            unlink(filename);
        }
    }

    int fd = open(filename, O_RDWR|O_CREAT|O_APPEND, S_IRWXU);
    if (fd < 0)
    {
        sd_journal_print(LOG_ERR, "can't open %s\n", filename);
        return -1;
    }

    struct tm *tm;
    time_t now;
    char format_time[50];

    now = time(NULL);
    tm  = localtime(&now);
    strftime(format_time, sizeof(format_time), "%Y/%m/%d %H:%M:%S ", tm);

    char str[1024];
    snprintf(str, sizeof(str), "%s %s\n", format_time, string);

    int ret = 0;
    if (-1 == write(fd, str, strlen(str) ))
    {
        sd_journal_print(LOG_INFO, "write file error, fd = %d, errno = %d\n", fd, errno);
        ret = -1;
    }

    close(fd);
    return ret;
}
void * log_thread_proc(void *arg)
{
    char battery_id[128];
    int  present, voltage, temperature, remain_capacity, full_charge_capacity, relative_state_of_charge, current, cycle_count, max_error, battery_status;

    char string[512];

    while(1)
    {
        voltage = 0;
        temperature = 0;
        remain_capacity = 0;
        full_charge_capacity = 0;
        relative_state_of_charge = 0;
        current = 0;
        cycle_count = 0;
        max_error = 0;
        battery_status = 0;
        present = 0;

        memset(battery_id, 0, sizeof(battery_id) );

        Battery::ReadProperty("serial_number", battery_id, sizeof(battery_id) );
        Battery::ReadProperty("voltage_now", voltage);
        Battery::ReadProperty("current_now", current);
        Battery::ReadProperty("temp", temperature);
        float temperature_f = temperature/10.0;
        Battery::ReadProperty("charge_now", remain_capacity);
        Battery::ReadProperty("charge_full", full_charge_capacity);
        Battery::ReadProperty("cycle_count", cycle_count);
        Battery::ReadProperty("max_error", max_error);
        Battery::ReadProperty("status_register", battery_status);
        Battery::ReadProperty("capacity", relative_state_of_charge);
        Battery::ReadProperty("present", present);

        if (present)
        {
            sprintf(string, "Battery id = %s, Voltage = %d mV, Current= %d mA Temperature = %.1f C, Remain Capacity = %d mAh, Full Charge Capacity=%d mAh RelativeStateOfCharge = %d%%, CycleCount=%d MaxError = %d%%, Battery Status=0x%0x",
                             battery_id, voltage/1000, current/1000, temperature_f,
                             remain_capacity/1000, full_charge_capacity/1000, relative_state_of_charge,
                             cycle_count, max_error, battery_status);
            sd_journal_print(LOG_INFO, "%s", string);
        }

        sleep(120);
    }

    return NULL;
}


void log_thread()
{
    pthread_t log_thread_id;

    int ret = pthread_create(&log_thread_id, NULL, &log_thread_proc, NULL);
    if (ret != 0)
    {
        sd_journal_print(LOG_ERR, "create thread fail:%d\n", errno);
    }
}
