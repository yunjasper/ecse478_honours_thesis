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
#include <Adafruit_MCP23008.h>

// private functions


void bringup_testing::init() {
    BSP::initPins();
}

void bringup_testing::blinky_onboardLED(long delayDuration, uint16_t numBlinks) {
    Serial.println("Starting blinky onboard LED test...");
    
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

void bringup_testing::blinky_FIOs(long delayDuration, uint16_t numBlinks) {
    Serial.println("Starting blinky onboard LED test...");
    
    uint8_t pinsArray[] = {
        FIO_1_PIN, 
        FIO_2_PIN, 
        FIO_3_PIN, 
        FIO_4_PIN, 
        FIO_5_PIN, 
        FIO_6_PIN, 
        FIO_7_PIN, 
        FIO_8_PIN, 
        FIO_9_PIN, 
        FIO_10_PIN, 
    };

    for (uint8_t i = 0; i < 10; i++) {
        pinMode(pinsArray[i], OUTPUT);
        digitalWrite(pinsArray[i], LOW);
    }

    // blink away
    if (numBlinks == 0) {
        while (1) {
            for (uint8_t i = 0; i < 10; i++) {
                digitalWrite(pinsArray[i], !digitalRead(pinsArray[i]));
                delay(delayDuration);
            }
        }
    }
    else {
        for (uint16_t i = 0; i < numBlinks; i++) {
            for (uint8_t i = 0; i < 10; i++) {
                digitalWrite(pinsArray[i], !digitalRead(pinsArray[i]));
                delay(delayDuration);
            }
        }
    }

}

void bringup_testing::blinky_DIOs(long delayDuration, uint16_t numBlinks) {
    Adafruit_MCP23008 mcp;
    mcp.begin(IO_EXPANSION_4_I2C_ADDR);

    // set all pins as outputs
    for(uint8_t i = 0; i < 8; i++) {
        mcp.pinMode(i, OUTPUT);
    }

    // blink away
    if (numBlinks == 0) {
        while (1) {
            for (uint8_t i = 0; i < 8; i++) {
                mcp.digitalWrite(i, !mcp.digitalRead(i));
                delay(delayDuration);
            }
        }
    }
    else {
        for (uint16_t i = 0; i < numBlinks; i++) {
            for (uint8_t i = 0; i < 10; i++) {
                mcp.digitalWrite(i, !mcp.digitalRead(i));
                delay(delayDuration);
            }
        }
    }

}

void bringup_testing::relays_all_toggle(long delayDuration) {

    RelayDrivers::init();
    bool state = false;

    while (1) {
        for (uint8_t channel = 1; channel <= 24; channel++) {
            RelayDrivers::setRelayActivatedState(channel,state);
        }
        state = !state;
        delay(delayDuration);
    }
}