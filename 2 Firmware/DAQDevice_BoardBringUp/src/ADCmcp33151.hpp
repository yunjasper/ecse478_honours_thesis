/**
 * ADC_mcp33151.h
 * 
 * Header file for ADC_mcp33151 class.
 * 
 * Author: Jasper Yun
 */

#pragma once
#include <stdint.h>

class ADCmcp33151 {
  public: 
    float readVoltage(void);
    ADCmcp33151(uint8_t csPin, long SPIFreq, float refV, uint8_t numBits);

  private:
    uint8_t cs; // chip select for SPI
    float refVoltage;
    uint8_t numBits;
    long SPIFrequency;

    uint16_t spiread16(void);
    
};
