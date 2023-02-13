/**
 * RelayDrivers.cpp
 * 
 * From perspective of DAQ device, want all the relay drivers
 * to appear as one black box to write to (set active/inactive) 
 * without dealing with which IO expander to write to.
 * 
 * Author: Jasper Yun
 */

#include "RelayDrivers.hpp"
#include "Adafruit_MCP23008.h" // archived library, may need to use newer library in future
#include <Arduino.h>
#include "pinDefs.h"

// private functions


// private variables
Adafruit_MCP23008 mcp1; // relay channels 1-8
Adafruit_MCP23008 mcp2; // relay channels 9-16
Adafruit_MCP23008 mcp3; // relay channels 17-24

void RelayDrivers::init() {
  mcp1.begin(IO_EXPANSION_1_I2C_ADDR);
  mcp2.begin(IO_EXPANSION_2_I2C_ADDR);
  mcp3.begin(IO_EXPANSION_3_I2C_ADDR);

  // set all pins as outputs
  for (uint8_t i = 0; i < 8; i++) {
    mcp1.pinMode(i, OUTPUT);
    mcp2.pinMode(i, OUTPUT);
    mcp3.pinMode(i, OUTPUT);
  }
}

void RelayDrivers::setRelayActivatedState(uint8_t channel, bool activatedState) {
  if ( (channel - 1) < 8) { // channels are 1-based on board, but 0-based in code :(
    mcp1.digitalWrite( (channel - 1) % 8, activatedState);
  } 
  else if ( (channel - 1) < 15) {
    mcp2.digitalWrite( (channel - 1) % 8, activatedState);
  } 
  else if ( (channel - 1) < 24) {
    mcp3.digitalWrite( (channel - 1) % 8, activatedState);
  }
  else {
    // should be invalid
    Serial.println("Invalid relay channel number for activation");
  }
}

bool RelayDrivers::getRelayActivatedState(uint8_t channel) {
  uint8_t gpio_reg_contents = 0;
  if ( (channel - 1) < 8) { // channels are 1-based on board, but 0-based in code :(
    gpio_reg_contents = mcp1.readGPIO();
  } 
  else if ( (channel - 1) < 15) {
    gpio_reg_contents = mcp2.readGPIO();
  } 
  else if ( (channel - 1) < 24) {
    gpio_reg_contents = mcp3.readGPIO();
  }
  else {
    // should be invalid
    Serial.println("Invalid relay channel number for get state");
  }

  return ( (gpio_reg_contents & (1 << (channel - 1))) == 1) ? true : false;
}
