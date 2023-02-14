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
ADCmcp33151::ADCmcp33151(uint8_t csPin, long SPIFreq, float refV, uint8_t numberOfBits) {
  cs = csPin;
  SPIFrequency = SPIFreq;
  refVoltage = refV;
  numBits = numberOfBits;
}

float ADCmcp33151::readVoltage(void) {
  // ((float) (raw * VOLTAGE_REFERENCE) / (1 << ADC_RESOLUTION))

  float raw = (float) spiread16();
  Serial.print("Raw value = ");
  Serial.println(raw);

  float denominator = (float) (1 << numBits);
  Serial.print("denominator = ");
  Serial.println(denominator);

  float voltage = raw * refVoltage / denominator;
  Serial.print("Voltage = ");
  Serial.println(voltage);
  
  return voltage;
}

// if this function hangs, check that SPI.begin() is called somewhere during setup
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
