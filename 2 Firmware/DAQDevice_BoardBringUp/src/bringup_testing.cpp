/**
 * @file bringup_testing.cpp
 * @author Jasper Yun
 * @brief contains functions to do testing of the board's functions.
 * @version 0.1
 * 
 * 
 */


// custom libraries
#include "bringup_testing.hpp"
#include "ADCmcp33151.hpp"
#include "AnalogMux.hpp"
#include "BSP.hpp"
#include "pinDefs.h"
#include "RelayDrivers.hpp"

// arduino libraries
#include <Arduino.h>

void bringup_testing::blinky_onboardLED(long delayDuration, uint16_t numBlinks) {
    Serial.println("Starting blinky onboard LED test...");
    BSP::initPins();
    
    if (numBlinks == 0) { // blink forever
        while (1) {
            digitalWrite(DEBUG_LED1_PIN, HIGH);
            delay(delayDuration);
            digitalWrite(DEBUG_LED1_PIN, LOW);
            delay(delayDuration);
        }
    }
    else {
        for (uint16_t i = 0; i < numBlinks; i++) {
            digitalWrite(DEBUG_LED1_PIN, HIGH);
            delay(delayDuration);
            digitalWrite(DEBUG_LED1_PIN, LOW);
            delay(delayDuration); 
        }
    }
}
