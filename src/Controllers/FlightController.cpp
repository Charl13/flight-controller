#include "FlightController.h"
#include "./../Facades/Mpu6050Facade.h"

#include <stdint.h>
#include <stdio.h>
#include <Arduino.h>
#include <Wire.h>
#include <ConfigurableFirmata.h>
#include <FirmataReporting.h>
#include <FirmataExt.h>

FlightController::FlightController(FirmataClass* firmata) : firmata(firmata) {
}

void FlightController::setup() {
    enableI2c();
    enableFirmata();
    configureFirmataFeatures();
}

void FlightController::enableI2c() {
    Wire.begin();
    Wire.setClock(config.i2cClockFrequency);
}

void FlightController::enableFirmata() {
    firmataExt = new FirmataExt();

    firmata->setFirmwareNameAndVersion(
        "ConfigurableFirmata",
        FIRMATA_FIRMWARE_MAJOR_VERSION,
        FIRMATA_FIRMWARE_MINOR_VERSION);

    firmata->begin(config.serialBaudRate);

    config.firmataIsEnabled = true;
}

void FlightController::configureFirmataFeatures() {
    Mpu6050Facade* mpu6050 = Mpu6050Facade::getInstance();

    firmataReporting = new FirmataReporting();
    firmataMpu6050 = new FirmataMpu6050(mpu6050);

    firmataExt->addFeature(*firmataReporting);
    firmataExt->addFeature(*firmataMpu6050);
}

void FlightController::run(void) {
    if (config.firmataIsEnabled) {
        while (firmata->available()) {
            firmata->processInput();
        }
        if (firmataReporting->elapsed()) {
            firmataMpu6050->report();
        }
    }
}
