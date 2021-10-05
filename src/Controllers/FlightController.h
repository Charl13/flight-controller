#ifndef SRC_CONTROLLERS_FLIGHTCONTROLLER_H_
#define SRC_CONTROLLERS_FLIGHTCONTROLLER_H_

#include "./../Firmata/FirmataMpu6050.h"

#include <ConfigurableFirmata.h>
#include <FirmataExt.h>
#include <FirmataFeature.h>
#include <FirmataReporting.h>

struct FlightControllerConfiguration {
    bool firmataIsEnabled = true;
    uint32_t i2cClockFrequency = 400000;
    uint16_t serialBaudRate = 57600;
};

class FlightController {
    public:
        explicit FlightController(FirmataClass *firmata);

        void setup();

        void enableI2c();
        void enableFirmata();
        void configureFirmataFeatures();

        void run();

    private:
        FlightControllerConfiguration config;

        FirmataClass *firmata;
        FirmataExt *firmataExt;
        FirmataReporting *firmataReporting;
        FirmataMpu6050 *firmataMpu6050;
};

#endif  // SRC_CONTROLLERS_FLIGHTCONTROLLER_H_
