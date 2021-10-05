#ifndef SRC_FIRMATA_FIRMATAMPU6050_H_
#define SRC_FIRMATA_FIRMATAMPU6050_H_

#include "./../Facades/Mpu6050Facade.h"

#include <string.h>
#include <Arduino.h>
#include <FirmataFeature.h>

#define SYSEX_MPU6050_COMMAND 0x50
#define SYSEX_MPU6050_SUBCOMMAND_REPORT_ANGLES 0x01

class FirmataMpu6050: public FirmataFeature {
    public:
        explicit FirmataMpu6050(Mpu6050Facade *mpu6050);
        void handleCapability(byte pin);
        bool handlePinMode(byte pin, int mode);
        bool handleSysex(byte command, byte argc, byte* argv);
        void reset(void);

        void report(void);
        void reportAngles(void);

    private:
        Mpu6050Facade *mpu6050;
        bool shouldReportAngles = true;
};

#endif  // SRC_FIRMATA_FIRMATAMPU6050_H_
