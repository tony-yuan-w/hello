#ifndef CHARGER_H
#define CHARGER_H

#define CHARGER_PATH "/tmp/sys/class/power_supply/bq24725a@2-0009"

extern void * charging_thread(void *arg);

class Charger
{
public:
    Charger();

    static bool readProperty(const char *property, int &value);
    static int  setProperty(const char *property, int value);

    static void stopCharging();
    static void prohibitCharge();
    static void resumeCharging();
    static bool isCharging();
    static void allowCharging();
};

#endif // CHARGER_H
