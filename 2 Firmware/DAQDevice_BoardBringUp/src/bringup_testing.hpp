/**
 * @file bringup_testing.hpp
 * @author Jasper Yun
 * @brief header file for bringup testing so that functions can be used in the main arduino sketch.
 * 
 */

#pragma once
#include <stdint.h>

namespace bringup_testing {

    // basic tests
    void blinky_onboardLED(long delayDuration, uint16_t numBlinks);
    void blinky_FIOs();

    // analog input tests
    void ain_LS_SE_cycle_through();



}