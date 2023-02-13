/**
 * AnalogMux.cpp
 * 
 * Class implementation file for AnalogMux.
 * Valid for 1:8 and 1:4 muxes.
 * 
 * In constructor, pass -1 to enable_pinNum to indicate
 * that the mux is always enabled.
 * 
 * Author: Jasper Yun
 */

#include "AnalogMux.hpp"
#include <Arduino.h>

AnalogMux::AnalogMuxAnalogMux(uint8_t ctrlPin_a0, uint8_t ctrlPin_a1, uint8_t ctrlPin_a2, int8_t enable_pinNum, uint8_t numChannels, long switchSettleTimens=250) {
  ctrl_a0 = ctrlPin_a0;
  ctrl_a1 = ctrlPin_a1;
  ctrl_a2 = ctrlPin_a2;
  enable_pin = enable_pinNum;
  numChannels = numChannels;
  switchSettleTime = switchSettleTimens; // ns

  if (enable_pin >= 0) {
    isEnabled = false;
    setEnabled(false);  
  } else { // negative value for enable_pin denotes always enabled
    isEnabled = true;
  }
}

void AnalogMux::setChannel(uint8_t channel) {
  // check that channel number is valid 
  if (channel > numChannels) {
    Serial.println("Invalid channel number requested.");
    return; // invalid
  } 
  else {
    // channel numbers start from 0!
    if (numChannels == 8) {  
      digitalWrite(ctrl_a0, channel & 0x1); // if odd, set ctrl_a0 = 1
      digitalWrite(ctrl_a1, channel & 0x2);
      digitalWrite(ctrl_a2, channel & 0x4);
    } 
    else if (numChannels == 4) {
      digitalWrite(ctrl_a0, channel & 0x1);
      digitalWrite(ctrl_a1, channel & 0x2);
    }
    delayNanoseconds(switchSettleTime);
  }
}

void AnalogMux::setEnabled(bool enableState) {
  if (enable_pin >= 0) {
    digitalWrite(enable_pin, enableState);
    isEnabled = enableState;  
  }
}

bool AnalogMux::getEnabled() {
  return isEnabled;
}
