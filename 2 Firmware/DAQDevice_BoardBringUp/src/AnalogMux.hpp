/**
 * analog_mux.hpp
 * 
 * Header file for Analog_Mux class
 * 
 * Author: Jasper Yun
 */

#pragma once
#include <stdint.h>

class AnalogMux {
  public:
    void setChannel(uint8_t channel);
    void setEnabled(bool enableState);
    bool getEnabled(void);

    // constructor
    AnalogMux(uint8_t ctrlPin_a0, uint8_t ctrlPin_a1, uint8_t ctrlPin_a2, int8_t enable_pinNum, uint8_t numberOfChannels, long switchSettleTimens);

  private:
    bool isEnabled;
    
    // control pins
    uint8_t ctrl_a0;
    uint8_t ctrl_a1;
    uint8_t ctrl_a2; // needed for 8:1 mux
    uint8_t enable_pin; 
    
    uint8_t numChannels;
    long switchSettleTime;
};
