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

const double TEMPERATURE_RESUME_THRESHOLD = 45.0;
const double TEMPERATURE_HIGH_THRESHOLD   = 50.0;
const double TEMPERATURE_VERY_HIGH_THRESHOLD = 60.0;

bool Battery::ReadProperty(const char *property, int &value)
{
    char filename[256];
    char buf[256];
    sprintf(filename, "%s/%s", BATTERY_DEV_PATH, property);

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

    return ret;
}

bool Battery::ReadProperty(const char *property, double &value)
{
    char filename[256];
    char buf[256];
    sprintf(filename, "%s/%s", BATTERY_DEV_PATH, property);
    bool ret = false;
    if (0 == access(filename, W_OK))
    {
        int fd = open(filename, O_RDONLY);
        if (fd != -1){
            ssize_t len =  read(fd, buf, sizeof(buf));

            if (len > 0)
            {
                buf[len] = '\0';
                value = atol(buf);
                ret = true;
            }
            close(fd);
        }
    }

    return ret;
}

bool Battery::ReadProperty(const char *property, char *value, int max_value_length)
{
    char filename[256];
    char buf[256];
    sprintf(filename, "%s/%s", BATTERY_DEV_PATH, property);

    bool ret = false;
    if (0 == access(filename, W_OK))
    {
        int fd  = open(filename, O_RDONLY);
        if (fd > 0){
            ssize_t len = read(fd, buf, sizeof(buf));
            buf[len] = '\0';
            if (len > 0){
                if (len < max_value_length)
                    strncpy(value, buf, len-1);
                else
                    strncpy(value, buf, max_value_length);
                ret = true;
            }
            close(fd);
        }
    }

    return ret;
}

int Battery::ReadBatteryInfo(Battery *battery)
{
    char date[12];
    char manufacturer[24];
    char model[12];
    char serial[24];
    char status[24];

    memset(date, 0, sizeof(date));
    memset(manufacturer, 0, sizeof(manufacturer));
    memset(model, 0, sizeof(model));
    memset(serial, 0, sizeof(serial));
    memset(status, 0, sizeof(status));

    int remainCapacity, fullChargeCapacity, designCapacity;
    remainCapacity = fullChargeCapacity = designCapacity = 0;

    int modeRegister, batteryStatus, relativeCap, abosoluteCharge, runTimeToEmpty;
    modeRegister = batteryStatus = relativeCap = abosoluteCharge = runTimeToEmpty = 0;

    int averageTimeToFull, averageTimeToEmpty;
    averageTimeToFull = averageTimeToEmpty = 0;

    int bPresent, temp, voltage, current, averageCurrent, constantChargeCurrent, constantChargeVoltage;
    temp = voltage = current = averageCurrent = constantChargeCurrent = constantChargeVoltage = 0;

    int maxError, cycleCount, broadcast;
    bPresent = maxError = cycleCount = broadcast = 0;

    int ret = ReadProperty("present", bPresent);
    if (!ret)
    {
        sd_journal_print(LOG_ERR, "read battery present property failed\n");
        return -1;
    }

    battery->setPresent(bPresent);
    if (bPresent == 1)
    {
        ReadProperty("status",  status, sizeof(status));
        ReadProperty("charge_now",          remainCapacity);
        ReadProperty("charge_full",         fullChargeCapacity);
        ReadProperty("charge_full_design",  designCapacity);
        ReadProperty("mode_register",       modeRegister);
        ReadProperty("status_register",     batteryStatus);
        ReadProperty("capacity",            relativeCap);
        ReadProperty("absolute_charge",     abosoluteCharge);
        ReadProperty("time_to_empty_avg",   averageTimeToEmpty);
        ReadProperty("time_to_full_avg",    averageTimeToFull);
        ReadProperty("max_error",           maxError);
        ReadProperty("cycle_count",         cycleCount);
        ReadProperty("broadcast",           broadcast);
        ReadProperty("voltage_now",         voltage);
        ReadProperty("current_now",         current);
        ReadProperty("constant_charge_current", constantChargeCurrent);
        ReadProperty("constant_charge_voltage", constantChargeVoltage);
        ReadProperty("temp",                temp);
        ReadProperty("time_to_empty_now",   runTimeToEmpty);
        ReadProperty("current_avg",         averageCurrent);

        ReadProperty("date", date, sizeof(date));
        ReadProperty("manufacturer", manufacturer, sizeof(manufacturer));
        ReadProperty("model_name", model, sizeof(model));
        ReadProperty("serial_number", serial, sizeof(serial));

        battery->setSerialNumber(serial);
        battery->setManufactoryDate(date);
        battery->setManufactory(manufacturer);
        battery->setModelName(model);
        battery->setRemainCapacity((quint32)remainCapacity/1000);
        battery->setFullCap((quint32)fullChargeCapacity/1000);
        battery->setFullDesignCap((quint32)designCapacity/1000);

        if (strcasecmp(status, STR_BATTERY_CHARGING)){
            battery->setChargingStatus(STR_BATTERY_CHARGING);
        }
        else if (strcasecmp(status, STR_BATTERY_DISCHARGING))
        {
            battery->setChargingStatus(STR_BATTERY_DISCHARGING);
        }
        battery->setModeRegister(modeRegister);
        battery->setVoltage((quint32)voltage/1000);
        battery->setCurrent((quint32)current/1000);
        battery->setAverageCurrent((quint32)averageCurrent/1000);

        double temperature  = temp/10.0;
        battery->setTemperature(temperature);

        battery->setConstantChargeCurrent((quint32)constantChargeCurrent);
        battery->setConstantChargeVoltage((quint32)constantChargeVoltage);

        battery->setRelativeCapacity((quint32)relativeCap);
        battery->setAbsoluteCharge((quint32)abosoluteCharge);

        battery->setRunTimeToEmpty((quint32)runTimeToEmpty/60); //minutes
        battery->setAverageTimeToFull((quint32)averageTimeToFull/60);
        battery->setAverageTimeToEmpty((quint32)averageTimeToEmpty/60);

        battery->setCycleCount((quint32)cycleCount);
        battery->setMaxError((quint32)maxError);
        battery->setStatusRegister(batteryStatus);

        if (modeRegister & BATTERY_MODE_CONDITION_FLAG)
        {
            battery->setCalibrationRequire(true);
        }
        else
        {
            battery->setCalibrationRequire(true);
        }
    }

    return 0;
}

void Battery::ActiveBattery()
{
    sd_journal_print(LOG_INFO, "active battery");
    const int chargingCurrent = 500;
    const int chargingVoltage = 12600;
    Charger::setProperty("constant_charge_current", chargingCurrent);
    Charger::setProperty("constant_charge_voltage", chargingVoltage);
    Charger::setProperty("status", 1);
    int timeout = 5;
    int status = 0;
    for(int i = 0; i < timeout; i++){
        if (ReadProperty("status", status) )
            break;
        sleep(1);
    }
}

bool Battery::IsBatteryQualified()
{
    char modelName[128];
    memset(modelName, 0x0, sizeof(modelName));
    Battery::ReadProperty("model_name", modelName, sizeof(modelName));
    if (strcasecmp("t508",modelName) == 0)
    {
        return true;
    }

    return false;
}

bool Battery::IsBatterySupport()
{
    char modelName[128];
    memset(modelName, 0x0, sizeof(modelName));
    Battery::ReadProperty("model_name", modelName, sizeof(modelName));
    //sd_journal_print(LOG_INFO, "modelName = %s\n", modelName);
    const char *whilte_list[5] = {"p508", "202cjc", "-ph", "t508", "p510"};
    for (int i = 0; i < 5; i++){
        if (strcasecmp(modelName, whilte_list[i]) == 0){
            return true;
        }
    }
    sd_journal_print(LOG_INFO, "IsBatterySupport return false ,model_name=%s", modelName);

    return false;
}

bool Battery::IsBatteryPresent()
{
    int present;

    if (!Battery::ReadProperty("present", present ))
    {
        sd_journal_print(LOG_INFO, "read battery property failed");
        return false;
    }

    if (present)
    {
        return true;
    }
    else
        return false;
}

void updateDbusProperty(Battery *battery)
{
    g_object_set(G_OBJECT(object_battery), BATTERY_PROPERTY_PRESENT, battery->present(), NULL);
    g_object_set(G_OBJECT(object_battery), BATTERY_PROPERTY_SERIAL_NUMBER, battery->serialNumber().toLatin1().data(), NULL);
    g_object_set(G_OBJECT(object_battery), BATTERY_PROPERTY_MODEL, battery->modelName().toLatin1().data(), NULL);
    g_object_set(G_OBJECT(object_battery), BATTERY_PROPERTY_MANUFACTURER, battery->manufactory().toLatin1().data(), NULL);
    g_object_set(G_OBJECT(object_battery), BATTERY_PROPERTY_DATE, battery->manufactoryDate().toLatin1().data(), NULL);
    g_object_set(G_OBJECT(object_battery), BATTERY_PROPERTY_CURRENT_AVG, battery->averageCurrent(), NULL);
    g_object_set(G_OBJECT(object_battery), BATTERY_PROPERTY_TIME_TO_EMPTY, battery->runTimeToEmpty(), NULL);
    g_object_set(G_OBJECT(object_battery), BATTERY_PROPERTY_TEMP, battery->temperature(), NULL);
    g_object_set(G_OBJECT(object_battery), BATTERY_PROPERTY_CONST_CHARG_VOL, battery->constantChargeVoltage(), NULL);
    g_object_set(G_OBJECT(object_battery), BATTERY_PROPERTY_CONST_CHARG_CUR, battery->constantChargeCurrent(), NULL);
    g_object_set(G_OBJECT(object_battery), BATTERY_PROPERTY_CURRENT_NOW, battery->current(), NULL);
    g_object_set(G_OBJECT(object_battery), BATTERY_PROPERTY_VOLTAGE_NOW, battery->voltage(), NULL);
    //g_object_set(G_OBJECT(object_battery), BATTERY_PROPERTY_BROADCAST, battery->broadcast);
    g_object_set(G_OBJECT(object_battery), BATTERY_PROPERTY_CYCLE_COUNT, battery->cycleCount(), NULL);
    g_object_set(G_OBJECT(object_battery), BATTERY_PROPERTY_MAX_ERROR, battery->maxError(), NULL);
    g_object_set(G_OBJECT(object_battery), BATTERY_PROPERTY_TIME_TO_FULL_AVG, battery->averageTimeToFull(), NULL);
    g_object_set(G_OBJECT(object_battery), BATTERY_PROPERTY_TIME_TO_EMPTY_AVG, battery->averageTimeToEmpty(), NULL);
    g_object_set(G_OBJECT(object_battery), BATTERY_PROPERTY_ABSOLUTE_CHARGE, battery->absoluteCharge(), NULL);
    g_object_set(G_OBJECT(object_battery), BATTERY_PROPERTY_CAP, battery->remainCapacity(), NULL);
    g_object_set(G_OBJECT(object_battery), BATTERY_PROPERTY_STATUS_REG, battery->statusRegister(), NULL);
    g_object_set(G_OBJECT(object_battery), BATTERY_PROPERTY_MODE_REG, battery->modeRegister(), NULL);
    g_object_set(G_OBJECT(object_battery), BATTERY_PROPERTY_CHARGE_FULL_DESIGN, battery->fullDesignCap(), NULL);
    g_object_set(G_OBJECT(object_battery), BATTERY_PROPERTY_CHARGE_FULL, battery->fullCap(), NULL);
    g_object_set(G_OBJECT(object_battery), BATTERY_PROPERTY_CHARGE_NOW, battery->remainCapacity(), NULL);
    g_object_set(G_OBJECT(object_battery), BATTERY_PROPERTY_STATUS, battery->chargingStatus().toLatin1().data(), NULL);
    g_object_set(G_OBJECT(object_battery), BATTERY_PROPERTY_QUALIFIED, battery->qualified(), NULL);
}

//debug command:dbus-send --system --type=signal  /org/philips/battery org.philips.batteryMgr.BatteryWarn uint32:2
BatteryPollThread::BatteryPollThread()
{
    batteryStatus = new Battery();

    connect(batteryStatus, &Battery::presentChanged, this, [this](){
        if (!this->batteryStatus->present() ){
            emit_dbus_battery_warn(BATTERY_DBUS_SIGNAL_UNPLUG);
            Charger::stopCharging();
        }
        else{
            emit_dbus_battery_warn(BATTERY_DBUS_SIGNAL_PLUG);
            int status;
            if (Battery::ReadProperty("status", status) == false)
                Battery::ActiveBattery();

            if (Battery::IsBatteryQualified()){
                set_dbus_battery_qualified(true);
                Charger::resumeCharging();
            }
            else if (Battery::IsBatterySupport())
            {
                set_dbus_battery_qualified(false);
            }
            else
            {
                set_dbus_battery_qualified(false);
                //warnFlag |= BATTERY_DBUS_SIGNAL_UNSUPPORT;
            }
        }
    });

    connect(batteryStatus, &Battery::temperatureChanged, this, [this](){
        if (this->batteryStatus->present() ){
            if (batteryStatus->temperature() > TEMPERATURE_HIGH_THRESHOLD){
                //if battery temperature high,sleep 1s and read again
                double temperature = 0.0;
                Battery::ReadProperty("temp", temperature);
                if (temperature >= TEMPERATURE_VERY_HIGH_THRESHOLD){
                    qint32 warnFlag = batteryStatus->warnFlag();
                    warnFlag |= BATTERY_DBUS_SIGNAL_TEMP_VERY_HIGH;
                    warnFlag &= ~BATTERY_DBUS_SIGNAL_TEMP_HIGH;
                    batteryStatus->setWarnFlag(warnFlag);
                }
                else if (temperature >= TEMPERATURE_HIGH_THRESHOLD){
                    qint32 warnFlag = batteryStatus->warnFlag();
                    warnFlag |= BATTERY_DBUS_SIGNAL_TEMP_HIGH;
                    warnFlag &= ~BATTERY_DBUS_SIGNAL_TEMP_VERY_HIGH;
                    batteryStatus->setWarnFlag(warnFlag);
                }
                else if (temperature <= TEMPERATURE_RESUME_THRESHOLD)
                {
                    qint32 warnFlag = batteryStatus->warnFlag();
                    warnFlag &= ~BATTERY_DBUS_SIGNAL_TEMP_HIGH;
                    warnFlag &= ~BATTERY_DBUS_SIGNAL_TEMP_VERY_HIGH;
                    batteryStatus->setWarnFlag(warnFlag);
                }
            }
        }
    });

    connect(batteryStatus, &Battery::statusRegisterChanged, this, [this](){
        if (this->batteryStatus->present() ){
            //if status register changed ,read again
            qint32 statusRegister;
            Battery::ReadProperty(BATTERY_PROPERTY_STATUS, statusRegister);
            qint32 warnFlag = batteryStatus->warnFlag();
            if (statusRegister & BATTERY_STATUS_OVER_CHARGED)
            {
                warnFlag |= BATTERY_DBUS_SIGNAL_OVER_CHARGE;
            }
            else
            {
                warnFlag &= ~BATTERY_DBUS_SIGNAL_OVER_CHARGE;
            }

            if (statusRegister & BATTERY_STATUS_OVER_TEMPERATURE)
            {
                warnFlag |= BATTERY_DBUS_SIGNAL_OVER_TEMP;
            }
            else
            {
                warnFlag &= ~BATTERY_DBUS_SIGNAL_OVER_TEMP;
            }

            if (statusRegister & BATTERY_STATUS_FULLY_CHARGED)
            {
                warnFlag |= BATTERY_DBUS_SIGNAL_FULLY_CHARGED;
            }
            else{
                if (warnFlag & BATTERY_DBUS_SIGNAL_FULLY_CHARGED){
                    warnFlag &= ~BATTERY_DBUS_SIGNAL_FULLY_CHARGED;
                }
            }
            batteryStatus->setWarnFlag(warnFlag);
        }
    });

    connect(batteryStatus, &Battery::cycleCountChanged, this, [this](){
        if (this->batteryStatus->present() ){
            qint32 warnFlag = batteryStatus->warnFlag();
            if (this->batteryStatus->cycleCount() >= BATTERY_CYCLE_COUNT_OVER_THRESHOLD)
            {
                warnFlag |= BATTERY_DBUS_SIGNAL_OVER_CYCLE;
            }
            else
            {
                warnFlag &= ~BATTERY_DBUS_SIGNAL_OVER_CYCLE;
            }
            batteryStatus->setWarnFlag(warnFlag);
        }
    });

    connect(batteryStatus, &Battery::fullDesignCapChanged, this, &BatteryPollThread::caculatorSoh);
    connect(batteryStatus, &Battery::fullCapChanged, this, &BatteryPollThread::caculatorSoh);

    connect(batteryStatus, &Battery::warnFlagChanged, this, &BatteryPollThread::processBatteryWarn);
}

void BatteryPollThread::caculatorSoh()
{
    double fullChargeCapacity = batteryStatus->fullCap();
    double designChargeCapacity = batteryStatus->fullDesignCap();

    qint32 warnFlag = batteryStatus->warnFlag();
    if (fullChargeCapacity < BATTERY_SOH_LOW_THRESHOLD * designChargeCapacity)
    {
        warnFlag |= BATTERY_DBUS_SIGNAL_SOH_LOW;
    }
    else
    {
        warnFlag &= ~BATTERY_DBUS_SIGNAL_SOH_LOW;
    }
    batteryStatus->setWarnFlag(warnFlag);
}

void BatteryPollThread::processBatteryWarn(){
    qint32 warnFlag = batteryStatus->warnFlag();

    if (warnFlag){
        sd_journal_print(LOG_INFO,"warnFlag=%x, prewarnflag=%x", warnFlag);
        emit_dbus_battery_warn((quint32)warnFlag);
        Charger::stopCharging();

        if (warnFlag & BATTERY_DBUS_SIGNAL_TEMP_VERY_HIGH){
            sd_journal_print(LOG_INFO, "Battery warn,temperature >= 60 degree, temperature=%f", batteryStatus->temperature());
        }
        if (warnFlag & BATTERY_DBUS_SIGNAL_TEMP_HIGH)
        {
            sd_journal_print(LOG_INFO, "Battery warn,Temperature >= 50 degree, temperature = %f", batteryStatus->temperature());
        }
        if (warnFlag & BATTERY_DBUS_SIGNAL_OVER_CHARGE)
        {
            sd_journal_print(LOG_INFO, "Battery warn,Battery detect over charged");
        }
        if (warnFlag & BATTERY_DBUS_SIGNAL_OVER_TEMP)
        {
            sd_journal_print(LOG_INFO, "Battery detect over temperature");
        }
        if (warnFlag & BATTERY_DBUS_SIGNAL_OVER_CYCLE)
        {
            sd_journal_print(LOG_INFO, "Battery warn,cycle count> 600,cycleCount=%d", batteryStatus->cycleCount());
        }
        if (warnFlag & BATTERY_DBUS_SIGNAL_SOH_LOW)
        {
            sd_journal_print(LOG_INFO, "battery warn, soh < 50%%");
        }

        if (warnFlag & BATTERY_DBUS_SIGNAL_UNSUPPORT)
        {
            sd_journal_print(LOG_INFO, "Battery warn,battery unsupport");
        }
        if (warnFlag & BATTERY_DBUS_SIGNAL_FULLY_CHARGED)
        {
            sd_journal_print(LOG_INFO, "Battery warn, fully charged");
        }
    }
    else
    {
        emit_dbus_battery_warn(BATTERY_DBUS_SIGNAL_RESUME_NORMAL);
        if (!Charger::isCharging()){
            sd_journal_print(LOG_INFO, "battery warning clear,resume charging");
            Charger::resumeCharging();
        }
    }
}

void BatteryPollThread::run()
{
    sd_journal_print(LOG_INFO, "start battery loop thread");
    bool batteryPresent = 0;

    waitDbusReady();

    while(1){
        batteryPresent = Battery::IsBatteryPresent();
        batteryStatus->setPresent(batteryPresent);

        if (0 == batteryPresent)
        {
            sleep(2);
            continue;
        }

        Battery::ReadBatteryInfo(batteryStatus);
        updateDbusProperty(batteryStatus);
        sleep(2);
    }
}

