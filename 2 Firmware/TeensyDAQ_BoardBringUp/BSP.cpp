/**
 * BSP.c
 * 
 * Board Support Package source file.
 * Contains functions for board functions.
 * 
 * HS  = high speed
 * LS  = low speed
 * SE  = single-ended (analog inputs)
 * DE  = differential (analog inputs)
 * AIN = analog inputs
 * 
 * IO  = input/output
 * FIO = flexible IO (digital)
 * 
 * Author: Jasper Yun
 */

#include "BSP.h"
#include <Arduino.h>
#include <SPI.h>

// global variables
volatile unsigned long time_buffer[ARRAY_SIZE];
volatile float adc_values[ARRAY_SIZE];
volatile uint8_t arr_position = 0;
volatile uint8_t isReadyToPrint = 0;
volatile uint8_t channelNo = 0;

void BSP_init() {
  
  pinMode(CS_HS_ADC, OUTPUT);
  pinMode(CS_LS_ADC, OUTPUT);
  
  pinMode(MUX_HS_AIN_A0, OUTPUT);
  pinMode(MUX_HS_AIN_A1, OUTPUT);
  pinMode(MUX_HS_GAIN_A0, OUTPUT);
  pinMode(MUX_HS_GAIN_A1, OUTPUT);
  pinMode(MUX_LS_SELECT_A0, OUTPUT);
  pinMode(MUX_LS_SELECT_A1, OUTPUT);
  pinMode(MUX_LS_AIN_1_A0, OUTPUT);
  pinMode(MUX_LS_AIN_1_A1, OUTPUT);
  pinMode(MUX_LS_AIN_1_A2, OUTPUT);
  pinMode(MUX_LS_AIN_2_A0, OUTPUT);
  pinMode(MUX_LS_AIN_2_A1, OUTPUT);
  pinMode(MUX_LS_AIN_2_A2, OUTPUT);
  pinMode(MUX_LS_GAIN_A0, OUTPUT);
  pinMode(MUX_LS_GAIN_A1, OUTPUT);
  
  pinMode(FIO_1_PIN, OUTPUT);
  pinMode(FIO_2_PIN, OUTPUT);
  pinMode(FIO_3_PIN, OUTPUT);
  pinMode(FIO_4_PIN, OUTPUT);
  pinMode(FIO_5_PIN, OUTPUT);
  pinMode(FIO_6_PIN, OUTPUT);
  pinMode(FIO_7_PIN, OUTPUT);
  pinMode(FIO_8_PIN, OUTPUT);
  pinMode(FIO_9_PIN, OUTPUT);
  pinMode(FIO_10_PIN, OUTPUT);
  pinMode(DEBUG_LED3, OUTPUT);  

  digitalWrite(CS_HS_ADC, HIGH);
  digitalWrite(CS_LS_ADC, HIGH);
  
  digitalWrite(MUX_HS_AIN_A0, LOW);
  digitalWrite(MUX_HS_AIN_A1, LOW);
  digitalWrite(MUX_HS_GAIN_A0, LOW);
  digitalWrite(MUX_HS_GAIN_A1, LOW);
  digitalWrite(MUX_LS_SELECT_A0, LOW);
  digitalWrite(MUX_LS_SELECT_A1, LOW);
  digitalWrite(MUX_LS_AIN_1_A0, LOW);
  digitalWrite(MUX_LS_AIN_1_A1, LOW);
  digitalWrite(MUX_LS_AIN_1_A2, LOW);
  digitalWrite(MUX_LS_AIN_2_A0, LOW);
  digitalWrite(MUX_LS_AIN_2_A1, LOW);
  digitalWrite(MUX_LS_AIN_2_A2, LOW);
  digitalWrite(MUX_LS_GAIN_A0, LOW);
  digitalWrite(MUX_LS_GAIN_A1, LOW);
  
  digitalWrite(FIO_1_PIN, HIGH);
  digitalWrite(FIO_2_PIN, HIGH);
  digitalWrite(FIO_3_PIN, HIGH);
  digitalWrite(FIO_4_PIN, HIGH);
  digitalWrite(FIO_5_PIN, HIGH);
  digitalWrite(FIO_6_PIN, HIGH);
  digitalWrite(FIO_7_PIN, HIGH);
  digitalWrite(FIO_8_PIN, HIGH);
  digitalWrite(FIO_9_PIN, HIGH);
  digitalWrite(FIO_10_PIN, HIGH);
  digitalWrite(DEBUG_LED3, LOW);

}


uint16_t spiread16(uint8_t cs) {
  
  uint8_t buf[2] = {0};
  digitalWrite(cs, LOW);
  SPI.endTransaction();
  SPI.beginTransaction(SPISettings(ADC_SPI_FREQ, MSBFIRST, SPI_MODE0));
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

uint16_t spiread16_callback() {
  uint8_t cs = CS_HS_ADC;
//  noInterrupts();
  
  uint8_t buf[2] = {0};
  digitalWrite(cs, LOW);
  SPI.endTransaction();
  SPI.beginTransaction(SPISettings(ADC_SPI_FREQ, MSBFIRST, SPI_MODE0));
  for (uint8_t i = 0; i < 2; i++) {
    buf[i] = SPI.transfer(0);
  }
  SPI.endTransaction();
  digitalWrite(cs, HIGH);

  uint16_t res = buf[0];
  res <<= 8;
  res |= buf[1];
  res >>= 2;

  adc_values[arr_position] = (float) (res * VOLTAGE_REFERENCE / (1 << ADC_RESOLUTION));
  time_buffer[arr_position++] = millis();
  
  if (arr_position == ARRAY_SIZE) {
    arr_position = 0;
    isReadyToPrint = 1;
  }
  
//  interrupts();
  return res; 
}


float readBoardTemperature() {
  analogReadResolution(12);
  uint16_t raw = analogRead(BOARD_TEMP_SENSOR_PIN);
  float voltage = raw * 3.3 / 4096; // assuming 12 bit ADC mode
  float temperature = (voltage - BOARD_TEMP_SENSOR_OUTPUT_0C) / BOARD_TEMP_SENSOR_SLOPE;
  return temperature;
}

// note that channel starts counting from zero!
void setHSAINMuxChannel(uint8_t channel) {
  if (channel < 4) {
    digitalWrite(MUX_HS_AIN_A0, channel & 0x1);
    digitalWrite(MUX_HS_AIN_A1, channel & (0x1 << 1));  
  }
  else {
    // do nothing, invalid input
    Serial.println("Invalid HS AIN channel requested");
  } 
}

// note that channel starts counting from zero!
void setLSAINMuxChannel(uint8_t channel) {
  if (channel < 8) {
    digitalWrite(MUX_LS_SELECT_A0, 1);
    digitalWrite(MUX_LS_SELECT_A1, 0);

    digitalWrite(MUX_LS_AIN_1_A0, (channel & 0x1));
    digitalWrite(MUX_LS_AIN_1_A1, channel & (0x1 << 1));
    digitalWrite(MUX_LS_AIN_1_A2, channel & (0x1 << 2));  
  }
  else if (channel < 16) {
    digitalWrite(MUX_LS_SELECT_A0, 0);
    digitalWrite(MUX_LS_SELECT_A1, 0);
    
    digitalWrite(MUX_LS_AIN_2_A0, (channel & 0x1));
    digitalWrite(MUX_LS_AIN_2_A1, channel & (0x1 << 1));
    digitalWrite(MUX_LS_AIN_2_A2, channel & (0x1 << 2));
  }
  else {
    // do nothing, invalid input
    Serial.println("Invalid LS AIN channel requested");
  }
}

/**
 * valid inputs: 1, 10, 50, 100 v/v gain
 */
void setLSGainMux(uint8_t gainValue) {
  if (gainValue == 1) {
    digitalWrite(MUX_LS_GAIN_A0, 0);
    digitalWrite(MUX_LS_GAIN_A1, 0);
  }
  else if (gainValue == 10) {
    digitalWrite(MUX_LS_GAIN_A0, 1);
    digitalWrite(MUX_LS_GAIN_A1, 0);
  }
  else if (gainValue == 50) {
    digitalWrite(MUX_LS_GAIN_A0, 0);
    digitalWrite(MUX_LS_GAIN_A1, 1);
  }
  else if (gainValue == 100) {
    digitalWrite(MUX_LS_GAIN_A0, 1);
    digitalWrite(MUX_LS_GAIN_A1, 1);
  }
  else {
    Serial.println("Invalid LS gain setting requested");
  }
}

/**
 * valid inputs: 1, 10, 50, 100 v/v gain
 */
void setHSGainMux(uint8_t gainValue) {
  if (gainValue == 1) {
    digitalWrite(MUX_HS_GAIN_A0, 0);
    digitalWrite(MUX_HS_GAIN_A1, 0);
  }
  else if (gainValue == 10) {
    digitalWrite(MUX_HS_GAIN_A0, 1);
    digitalWrite(MUX_HS_GAIN_A1, 0);
  }
  else if (gainValue == 50) {
    digitalWrite(MUX_HS_GAIN_A0, 0);
    digitalWrite(MUX_HS_GAIN_A1, 1);
  }
  else if (gainValue == 100) {
    digitalWrite(MUX_HS_GAIN_A0, 1);
    digitalWrite(MUX_HS_GAIN_A1, 1);
  }
  else {
    Serial.println("Invalid HS gain setting requested");
  }
}
