#ifndef SRC_FACADES_MPU6050FACADE_H_
#define SRC_FACADES_MPU6050FACADE_H_

#define MPU6050_INCLUDE_DMP_MOTIONAPPS20

#include <stdint.h>
#include "I2Cdev.h"
#include "helper_3dmath.h"
#include <MPU6050.h>
#include "./../Support/Axis.h"

struct Angles {
    Axis yaw;
    Axis pitch;
    Axis roll;
};

class Mpu6050Facade {
    public:
        static Mpu6050Facade *getInstance(void);
        Angles getAngles(void);

        bool isReady(void);

    protected:
        Mpu6050Facade(void);

        static Mpu6050Facade* instance;
        void initializeMpu6050(void);
        MPU6050* mpu6050 = nullptr;

        bool isConnected;
        bool dmpIsEnabled;
        uint8_t fifoBuffer[64];
};

#endif  // SRC_FACADES_MPU6050FACADE_H_
