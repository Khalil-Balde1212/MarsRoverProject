#ifndef ENCODER_DPS_H
#define ENCODER_DPS_H

#include "../robot_const.h"
#include <Arduino.h>

namespace encoders
{
    /**
     * @brief The encoder counts for each wheel. 0-2 is front left to rear left and 3-5 is front right to rear right
     */
    extern volatile int encoderCounts[6];

    /**
     * @brief Initializes the encoders
     * @note call this in setup
     */
    void initEncoders();
}

#endif // ENCODER_DPS_H