/**
 * @file bringup_testing.hpp
 * @author Jasper Yun
 * @brief header file for bringup testing so that functions can be used in the main arduino sketch.
 * 
 */

#pragma once
#include "AnalogInputs.hpp"
#include <stdint.h>

namespace bringup_testing {

    void init(); // wraps BSP::initPins()

    // basic tests
    void blinky_onboardLED(long delayDuration, uint16_t numBlinks);
    void blinky_FIOs(long delayDuration, uint16_t numBlinks);
    void blinky_DIOs(long delayDuration, uint16_t numBlinks);

    // relays
    void relays_all_toggle(long delayDuration);
    
    // analog input tests
    void ain_LS_SE_cycle_through(long delayDuration, uint16_t readsPerChannel, enum AnalogInputsGains gain);
    void ain_HS_SE_cycle_through(long delayDuration, uint16_t readsPerChannel, enum AnalogInputsGains gain);
    void ain_HS_DE_cycle_through(long delayDuration, uint16_t readsPerChannel, enum AnalogInputsGains gain);



}