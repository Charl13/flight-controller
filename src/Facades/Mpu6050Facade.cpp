#include "Mpu6050Facade.h"
#include <MPU6050_6Axis_MotionApps20.h>

Mpu6050Facade* Mpu6050Facade::instance = nullptr;

Mpu6050Facade::Mpu6050Facade(void) {
}

Mpu6050Facade *Mpu6050Facade::getInstance() {
    if (!instance) {
        instance = new Mpu6050Facade();

        instance->initializeMpu6050();
    }
    return instance;
}

void Mpu6050Facade::initializeMpu6050(void) {
    mpu6050 = new MPU6050();

    mpu6050->initialize();

    if (!(isConnected = mpu6050->testConnection())) {
        return;
    }
    if (mpu6050->dmpInitialize() != 0) {
        return;
    }
    mpu6050->CalibrateAccel(6);
    mpu6050->CalibrateGyro(6);

    mpu6050->setDMPEnabled(dmpIsEnabled = true);

    return;
}

Angles Mpu6050Facade::getAngles(void) {
    Quaternion quaternions;  // [w, x, y, z]
    VectorFloat gravity;     // [x, y, z]
    float yawPitchRoll[3];   // [yaw, pitch, roll]

    if (mpu6050->dmpGetCurrentFIFOPacket(fifoBuffer)) {
        mpu6050->dmpGetQuaternion(&quaternions, fifoBuffer);
        mpu6050->dmpGetGravity(&gravity, &quaternions);
        mpu6050->dmpGetYawPitchRoll(yawPitchRoll, &quaternions, &gravity);
    }
    Angles angles = {
        .yaw = Axis(yawPitchRoll[0] * 180 / M_PI),
        .pitch = Axis(yawPitchRoll[1] * 180 / M_PI),
        .roll = Axis(yawPitchRoll[2] * 180 / M_PI),
    };

    return angles;
}

bool Mpu6050Facade::isReady(void) {
    return isConnected && dmpIsEnabled;
}
