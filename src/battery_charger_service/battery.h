#ifndef BATTERY_H
#define BATTERY_H

#include <QObject>
#include <QThread>

#define	BATTERY_STATUS_OVER_CHARGED			(0x1 << 15)
#define	BATTERY_STATUS_TERMINATE_CHARGE			(0x1 << 14)
#define	BATTERY_STATUS_RESERVED_1			(0x1 << 13)
#define	BATTERY_STATUS_OVER_TEMPERATURE			(0x1 << 12)
#define	BATTERY_STATUS_TERMINATE_DISCHARGE		(0x1 << 11)
#define	BATTERY_STATUS_RESERVED_2			(0x1 << 10)
#define	BATTERY_STATUS_REMAINING_CAPACITY		(0x1 << 9)
#define	BATTERY_STATUS_REMAINING_TIME			(0x1 << 8)
#define	BATTERY_STATUS_INITIALIZED			(0x1 << 7)
#define	BATTERY_STATUS_FULLY_CHARGED			(0x1 << 5)
#define	BATTERY_STATUS_FULLY_DISCHARGED			(0x1 << 4)

#define BATTERY_MODE_INTERNAL_CHARGE_CONTROLLER		(0x1 << 0)		//Read-Only, 0: Not supported, 1: supported
#define BATTERY_MODE_PRIMARY_BATTERY_SUPPORT		(0x1 << 1)		//R, 0: not supported, 1: Supported
#define	BATTERY_MODE_CONDITION_FLAG			(0x1 << 7)		//R, 0: Battery OK, 1: calibration Requested
#define	BATTERY_MODE_CHARGE_CONTROLLER_ENABLED		(0x1 << 8)		//0: Internal charger disabled; 1: Enalbed;
#define	BATTERY_MODE_PRIMARY_BATTERY			(0x1 << 9)		//0: Operating in secondary role; 1: In primary role
#define	BATTERY_MODE_ALARM				(0x1 << 13)		//0: Enable AlarmWarning broadcast to host and charger; 1: Disabled
#define	BATTERY_MODE_CHARGER				(0x1 << 14)		//0: Enable ChargeCurrent and ChargeVoltage broadcast
#define BATTERY_MODE_CAPACITY				(0x1 << 15)		//0: Report in mA/mAH; 1: in 10 mA/mAH

//battery flag
#define BATTERY_STATUS_CHARGING     1
#define BATTERY_STATUS_DISCHARGING  2

#define STR_BATTERY_CHARGING    "charging"
#define STR_BATTERY_DISCHARGING "discharging"
//dbus signal var
#define BATTERY_DBUS_SIGNAL_TEMP_HIGH          (1<<0)
#define BATTERY_DBUS_SIGNAL_TEMP_VERY_HIGH     (1<<1)
#define BATTERY_DBUS_SIGNAL_OVER_TEMP          (1<<2)
#define BATTERY_DBUS_SIGNAL_OVER_CHARGE        (1<<3)
#define BATTERY_DBUS_SIGNAL_OVER_CYCLE         (1<<4)
#define BATTERY_DBUS_SIGNAL_SOH_LOW            (1<<5)
#define BATTERY_DBUS_SIGNAL_RESUME_NORMAL      (1<<6)
#define BATTERY_DBUS_SIGNAL_UNPLUG             (1<<7)
#define BATTERY_DBUS_SIGNAL_PLUG               (1<<8)
#define BATTERY_DBUS_SIGNAL_LEVEL_LOW          (1<<9)
#define BATTERY_DBUS_SIGNAL_LEVEL_VERY_LOW     (1<<10)
#define BATTERY_DBUS_SIGNAL_UNQUALIFED         (1<<11)
#define BATTERY_DBUS_SIGNAL_UNSUPPORT          (1<<12)
#define BATTERY_DBUS_SIGNAL_FULLY_CHARGED      (1<<13)

#define BATTERY_DEV_PATH "/tmp/sys/class/power_supply/sbs-2-000b"

#define BATTERY_PROPERTY_PRESENT        "present"
#define BATTERY_PROPERTY_SERIAL_NUMBER  "serial_number"
#define BATTERY_PROPERTY_MODEL          "model_name"
#define BATTERY_PROPERTY_MANUFACTURER   "manufacturer"
#define BATTERY_PROPERTY_DATE           "date"
#define BATTERY_PROPERTY_CURRENT_AVG       "current_avg"
#define BATTERY_PROPERTY_TIME_TO_EMPTY  "time_to_empty_now"
#define BATTERY_PROPERTY_TEMP           "temp"
#define BATTERY_PROPERTY_CONST_CHARG_VOL   "constant_charge_voltage"
#define BATTERY_PROPERTY_CONST_CHARG_CUR   "constant_charge_current"
#define BATTERY_PROPERTY_CURRENT_NOW        "current_now"
#define BATTERY_PROPERTY_VOLTAGE_NOW        "voltage_now"
#define BATTERY_PROPERTY_BROADCAST          "broadcast"
#define BATTERY_PROPERTY_CYCLE_COUNT        "cycle_count"
#define BATTERY_PROPERTY_MAX_ERROR          "max_error"
#define BATTERY_PROPERTY_TIME_TO_FULL_AVG    "time_to_full_avg"
#define BATTERY_PROPERTY_TIME_TO_EMPTY_AVG  "time_to_empty_avg"
#define BATTERY_PROPERTY_ABSOLUTE_CHARGE    "absolute_charge"
#define BATTERY_PROPERTY_CAP                "capacity"
#define BATTERY_PROPERTY_STATUS_REG         "status_register"
#define BATTERY_PROPERTY_MODE_REG           "mode_register"
#define BATTERY_PROPERTY_CHARGE_FULL_DESIGN   "charge_full_design"
#define BATTERY_PROPERTY_CHARGE_FULL        "charge_full"
#define BATTERY_PROPERTY_CHARGE_NOW         "charge_now"
#define BATTERY_PROPERTY_STATUS             "status"
#define BATTERY_PROPERTY_QUALIFIED          "qualified"

#define BATTERY_CYCLE_COUNT_OVER_THRESHOLD  600
#define BATTERY_SOH_LOW_THRESHOLD           0.5

class Battery:public QObject{
    Q_OBJECT

public:
    Q_PROPERTY(QString serialNumber READ serialNumber WRITE setSerialNumber NOTIFY serialNumberChanged)
    Q_PROPERTY(QString manufactoryDate READ manufactoryDate WRITE setManufactoryDate NOTIFY manufactoryDateChanged)
    Q_PROPERTY(QString manufactory READ manufactory WRITE setManufactory NOTIFY manufactoryChanged)
    Q_PROPERTY(QString modelName READ modelName WRITE setModelName NOTIFY modelNameChanged)
    Q_PROPERTY(QString chargingStatus READ chargingStatus WRITE setChargingStatus NOTIFY chargingStatusChanged)
    Q_PROPERTY(qint32 modeRegister READ modeRegister WRITE setModeRegister NOTIFY modeRegisterChanged)
    Q_PROPERTY(qint32 statusRegister READ statusRegister WRITE setStatusRegister NOTIFY statusRegisterChanged)
    Q_PROPERTY(bool calibrationRequire READ calibrationRequire WRITE setCalibrationRequire NOTIFY calibrationRequireChanged)
    Q_PROPERTY(quint32 voltage READ voltage WRITE setVoltage NOTIFY voltageChanged)
    Q_PROPERTY(quint32 current READ current WRITE setCurrent NOTIFY currentChanged)
    Q_PROPERTY(quint32 averageCurrent READ averageCurrent WRITE setAverageCurrent NOTIFY averageCurrentChanged)
    Q_PROPERTY(double temperature READ temperature WRITE setTemperature NOTIFY temperatureChanged)
    Q_PROPERTY(quint32 constantChargeCurrent READ constantChargeCurrent WRITE setConstantChargeCurrent NOTIFY constantChargeCurrentChanged)
    Q_PROPERTY(quint32 constantChargeVoltage READ constantChargeVoltage WRITE setConstantChargeVoltage NOTIFY constantChargeVoltageChanged)
    Q_PROPERTY(quint32 runTimeToEmpty READ runTimeToEmpty WRITE setRunTimeToEmpty NOTIFY runTimeToEmptyChanged)
    Q_PROPERTY(quint32 averageTimeToFull READ averageTimeToFull WRITE setAverageTimeToFull NOTIFY averageTimeToFullChanged)
    Q_PROPERTY(quint32 averageTimeToEmpty READ averageTimeToEmpty WRITE setAverageTimeToEmpty NOTIFY averageTimeToEmptyChanged)
    Q_PROPERTY(quint32 maxError READ maxError WRITE setMaxError NOTIFY maxErrorChanged)
    Q_PROPERTY(quint32 cycleCount READ cycleCount WRITE setCycleCount NOTIFY cycleCountChanged)
    Q_PROPERTY(quint32 absoluteCharge READ absoluteCharge WRITE setabsoluteCharge NOTIFY absoluteChargeChanged)
    Q_PROPERTY(quint32 remainCapacity READ remainCapacity WRITE setRemainCapacity NOTIFY remainCapacityChanged)
    Q_PROPERTY(quint32 fullDesignCap READ fullDesignCap WRITE setFullDesignCap NOTIFY fullDesignCapChanged)
    Q_PROPERTY(quint32 fullCap READ fullCap WRITE setFullCap NOTIFY fullCapChanged)
    Q_PROPERTY(quint32 relativeCapacity READ relativeCapacity WRITE setRelativeCapacity NOTIFY relativeCapacityChanged)

    Q_PROPERTY(qint32 warnFlag READ warnFlag WRITE setWarnFlag NOTIFY warnFlagChanged)

    Q_PROPERTY(bool qualified READ qualified WRITE setQualified NOTIFY qualifiedChanged)
    Q_PROPERTY(bool present READ present WRITE setPresent NOTIFY presentChanged)

public:
    static int ReadBatteryInfo(Battery *batteryInfo);
    static bool ReadProperty(const char *property, int &value);
    static bool ReadProperty(const char *property, double &value);
    static bool ReadProperty(const char *property, char *value, int max_value_length);
    static bool IsBatteryQualified();
    static bool IsBatterySupport();
    static bool IsBatteryPresent();
    static void ActiveBattery();

private:
    QString _serialNumber;
    QString _manufactoryDate;
    QString _manufactory;
    QString _modelName;
    QString _chargingStatus;

    qint32 _modeRegister;
    qint32 _statusRegister;
    bool _calibrationRequire;
    bool _present;
    bool _qualified;

    quint32 _voltage;
    quint32 _current;
    quint32 _averageCurrent;
    double _temperature;
    quint32 _constChargeCurrent;
    quint32 _constChargeVoltage;
    quint32 _runTimeToEmpty;
    quint32 _runTimeToFull;
    quint32 _averageTimeToFull;
    quint32 _averageTimeToEmpty;
    quint32 _maxError;
    quint32 _cycleCount;
    quint32 _absoluteCharge;
    quint32 _fullDesignCap;
    quint32 _fullCap;
    quint32 _remainCapacity;
    quint32 _relativeCapacity;
    qint32 _warnFlag;

signals:
    void serialNumberChanged();
    void manufactoryDateChanged();
    void manufactoryChanged();
    void modelNameChanged();
    void modeRegisterChanged();
    void statusRegisterChanged();
    void calibrationRequireChanged();
    void presentChanged();
    void qualifiedChanged();

    void voltageChanged();
    void currentChanged();
    void averageCurrentChanged();
    void temperatureChanged();
    void constantChargeCurrentChanged();
    void constantChargeVoltageChanged();
    void runTimeToEmptyChanged();
    void runTimeToFullChanged();
    void averageTimeToFullChanged();
    void averageTimeToEmptyChanged();
    void maxErrorChanged();
    void cycleCountChanged();
    void absoluteChargeChanged();
    void fullDesignCapChanged();
    void fullCapChanged();
    void relativeCapacityChanged();
    void chargingStatusChanged();
    void remainCapacityChanged();
    void warnFlagChanged();

public:
    QString serialNumber(){return _serialNumber;}
    QString manufactoryDate(){return _manufactoryDate;}
    QString manufactory(){return _manufactory;}
    QString modelName(){return _modelName;}
    QString chargingStatus(){return _chargingStatus;}

    qint32 modeRegister(){return _modeRegister;}
    qint32 statusRegister(){return _statusRegister;}
    bool calibrationRequire(){return _calibrationRequire;}
    bool present(){return _present;}
    bool qualified(){return _qualified;}

    quint32 voltage(){return _voltage;}
    quint32 current(){return _current;}
    quint32 averageCurrent(){return _averageCurrent;}
    double temperature(){return _temperature;}
    quint32 constantChargeCurrent(){return _constChargeCurrent;}
    quint32 constantChargeVoltage(){return _constChargeVoltage;}
    quint32 runTimeToEmpty(){return _runTimeToEmpty;}
    quint32 runTimeToFull(){return _runTimeToFull;}
    quint32 averageTimeToFull(){return _averageTimeToFull;}
    quint32 averageTimeToEmpty(){return _averageTimeToEmpty;}
    quint32 maxError(){return _maxError;}
    quint32 cycleCount(){return _cycleCount;}
    quint32 absoluteCharge(){return _absoluteCharge;}
    quint32 fullDesignCap(){return _fullDesignCap;}
    quint32 fullCap(){return _fullCap;}
    quint32 remainCapacity(){return _remainCapacity;}
    quint32 relativeCapacity(){return _relativeCapacity;}
    qint32 warnFlag(){return _warnFlag;}

    void setSerialNumber(const QString &value){
        if (_serialNumber != value){
            _serialNumber = value;
            emit serialNumberChanged();
        }
    }

    void setManufactory(const QString value)
    {
        if (_manufactory != value){
            _manufactory = value;
            emit manufactoryChanged();
        }
    }
    void setManufactoryDate(const QString &value){
        if (_manufactoryDate != value){
            _manufactoryDate = value;
            emit manufactoryDateChanged();
        }
    }
    void setModelName(const QString &value){
        if (_modelName != value){
            _modelName = value;
            emit modelNameChanged();
        }
    }
    void setChargingStatus(const QString &value){
        if (_chargingStatus != value){
            _chargingStatus = value;
            emit chargingStatusChanged();
        }
    }

    void setModeRegister(const qint32 value){
        if (_modeRegister != value){
            _modeRegister = value;
            emit modeRegisterChanged();
        }
    }
    void setStatusRegister(const qint32 value){
        if (_statusRegister != value){
            _statusRegister = value;
            emit statusRegisterChanged();
        }
    }
    void setCalibrationRequire(bool value){
        if (_calibrationRequire != value){
            _calibrationRequire = value;
            emit calibrationRequireChanged();
        }
    }
    void setPresent(bool value){
        if (_present != value){
            _present = value;
            emit presentChanged();
        }
    }
    void setQualified(bool value){
        if (_qualified != value){
            _qualified = value;
            emit qualifiedChanged();
        }
    }

    void setVoltage(const quint32 value){
        if (_voltage != value){
            _voltage = value;
            emit voltageChanged();
        }
    }
    void setCurrent(const quint32 value){
        if (_current != value){
            _current = value;
            emit currentChanged();
        }
    }
    void setAverageCurrent(const quint32 value){
        if (_averageCurrent != value){
            _averageCurrent = value;
            emit averageCurrentChanged();
        }
    }
    void setTemperature(const double value){
        if (_temperature != value){
            _temperature = value;
            emit temperatureChanged();
        }
    }
    void setConstantChargeCurrent(const quint32 value){
        if (_constChargeCurrent != value){
            _constChargeCurrent = value;
            emit constantChargeCurrentChanged();
        }
    }
    void setConstantChargeVoltage(const quint32 value){
        if (_constChargeVoltage != value){
            _constChargeVoltage = value;
            emit constantChargeVoltageChanged();
        }
    }
    void setRunTimeToEmpty(const quint32 value){
        if (_runTimeToEmpty != value){
            _runTimeToEmpty = value;
            emit runTimeToEmptyChanged();
        }
    }
    void setRunTimeToFull(const quint32 value){
        if (_runTimeToFull != value){
            _runTimeToFull = value;
            emit runTimeToFullChanged();
        }
    }
    void setAverageTimeToFull(const quint32 value){
        if (_averageTimeToFull != value){
            _averageTimeToFull = value;
            emit averageTimeToFullChanged();
        }
    }
    void setAverageTimeToEmpty(const quint32 value){
        if (_averageTimeToEmpty != value){
            _averageTimeToEmpty = value;
            emit averageTimeToEmptyChanged();
        }
    }
    void setMaxError(const quint32 value){
        if (_maxError != value){
            _maxError = value;
            emit maxErrorChanged();
        }
    }
    void setCycleCount(const quint32 value){
        if (_cycleCount != value){
            _cycleCount = value;
            emit cycleCountChanged();
        }
    }
    void setAbsoluteCharge(const quint32 value){
        if (_absoluteCharge != value){
            _absoluteCharge = value;
            emit absoluteChargeChanged();
        }
    }
    void setFullDesignCap(const quint32 value){
        if (_fullDesignCap != value){
            _fullDesignCap = value;
            emit fullDesignCapChanged();
        }
    }
    void setFullCap(const quint32 value){
        if (_fullCap != value){
            _fullCap = value;
            emit fullCapChanged();
        }
    }
    void setRelativeCapacity(const quint32 value){
        if (_relativeCapacity != value){
            _relativeCapacity = value;
            emit relativeCapacityChanged();
        }
    }

    void setRemainCapacity(const quint32 value){
        if (_remainCapacity != value){
            _remainCapacity = value;
            emit remainCapacityChanged();
        }
    }

    void setWarnFlag(const qint32 value){
        if (_warnFlag != value){
            _warnFlag = value;
            emit warnFlagChanged();
        }
    }
};

class BatteryPollThread:public QThread{
    Q_OBJECT

public:
    BatteryPollThread();
    void run() override;

private:
    Battery *batteryStatus;

public slots:
    void caculatorSoh();
    void processBatteryWarn();
};

extern void * battery_poll_thread(void *arg);


#endif // BATTERY_H
