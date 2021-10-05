#include "Axis.h"
#include <math.h>

Axis::Axis(float angle): angle(angle) {
}

int16_t Axis::toInt16(void) {
    return static_cast<int16_t>(angle);
}

float Axis::toFloat(void) {
    return angle;
}

uint8_t* Axis::toInt16Bytes(void) {
    uint16_t angle = roundf(toInt16());

    static uint8_t *bytes = static_cast<uint8_t*>(
        static_cast<void*>(&angle));

    return bytes;
}
