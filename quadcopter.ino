#include <Arduino.h>
#include "./src/Controllers/FlightController.h"

#define INTERRUPT_PIN 2

FlightController flightController = FlightController(&Firmata);

void setup() {
    flightController.setup();
}

void loop() {
    flightController.run();
}
