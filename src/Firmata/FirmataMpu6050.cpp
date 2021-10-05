#include "FirmataMpu6050.h"

FirmataMpu6050::FirmataMpu6050(Mpu6050Facade *mpu6050) : mpu6050(mpu6050) {
}

bool FirmataMpu6050::handlePinMode(byte pin, int mode) {
    return false;
}

bool FirmataMpu6050::handleSysex(byte command, byte argc, byte* argv) {
    return false;
}

void FirmataMpu6050::handleCapability(byte pin) {
}

void FirmataMpu6050::reset(void) {
}

void FirmataMpu6050::report(void) {
    reportAngles();
}

void FirmataMpu6050::reportAngles(void) {
    if (shouldReportAngles) {
        Angles angles = mpu6050->getAngles();

        uint8_t *yaw = angles.yaw.toInt16Bytes();
        // char *pitch = angles.pitch.toBytes();
        // char *roll = angles.roll.toBytes();

        uint8_t payload[sizeof(int16_t) * 1];

        memcpy(payload, yaw, sizeof(int16_t));
        // memcpy(payload + sizeof(int16_t), pitch, sizeof(int16_t));
        // memcpy(payload + sizeof(int16_t) * 2, roll, sizeof(int16_t));

        Firmata.sendSysex(
            SYSEX_MPU6050_COMMAND,
            sizeof(payload),
            payload);
    }
}

