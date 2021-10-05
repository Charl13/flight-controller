#ifndef SRC_SUPPORT_AXIS_H_
#define SRC_SUPPORT_AXIS_H_

#include <stdint.h>

class Axis {
    public:
        explicit Axis(float angle);
        int16_t toInt16(void);
        float toFloat(void);
        uint8_t* toInt16Bytes(void);

    protected:
        float angle;
};

#endif  // SRC_SUPPORT_AXIS_H_
