/**
 * ADC_mcp33151.cpp
 * 
 * Class implementation file
 * 
 * Author: Jasper Yun
 */

#include "ADCmcp33151.hpp"
#include <Arduino.h>
#include <SPI.h>

// constructor
ADCmcp33151::ADCmcp33151(uint8_t csPin, long SPIFreq, float refV, uint8_t numBits=14) {
  cs = csPin;
  SPIFrequency = SPIFreq;
  refVoltage = refV;
  numBits = numBits;
}

float ADCmcp33151::readVoltage(void) {
  uint16_t raw = spiread16();
  return ((float) (raw * refVoltage) / (1 << numBits));
}

uint16_t ADCmcp33151::spiread16(void) {
  uint8_t buf[2] = {0};
  digitalWrite(cs, LOW);
  SPI.endTransaction();
  SPI.beginTransaction(SPISettings(SPIFrequency, MSBFIRST, SPI_MODE0));
  for (uint8_t i = 0; i < 2; i++) {
    buf[i] = SPI.transfer(0);
  }
  SPI.endTransaction();
  digitalWrite(cs, HIGH);

  uint16_t res = buf[0];
  res <<= 8;
  res |= buf[1];
  res >>= 2;

  return res;
}
