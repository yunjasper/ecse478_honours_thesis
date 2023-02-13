/**
 * BSP.cpp
 * 
 * Board Support Package for DAQ Device.
 * 
 * Author: Jasper Yun
 * 
 */

#include "BSP.hpp"
#include <Arduino.h>
#include "pinDefs.h"

void BSP::initPins() {
    // set pin modes
    pinMode(CS_LS_SE_ADC, OUTPUT);
    pinMode(CS_HS_SE_ADC, OUTPUT);
    pinMode(CS_HS_DE_ADC, OUTPUT);

    pinMode(MUX_HS_DE_AIN_A0, OUTPUT);
    pinMode(MUX_HS_DE_AIN_A1, OUTPUT);
    pinMode(MUX_HS_DE_GAIN_A0, OUTPUT);
    pinMode(MUX_HS_DE_GAIN_A1, OUTPUT);

    pinMode(MUX_HS_SE_AIN_A0, OUTPUT);
    pinMode(MUX_HS_SE_AIN_A1, OUTPUT);
    pinMode(MUX_HS_SE_AIN_A2, OUTPUT);
    pinMode(MUX_HS_SE_GAIN_A0, OUTPUT);
    pinMode(MUX_HS_SE_GAIN_A1, OUTPUT);

    pinMode(MUX_LS_SE_1_EN, OUTPUT);
    pinMode(MUX_LS_SE_2_EN, OUTPUT);
    pinMode(MUX_LS_SE_3_EN, OUTPUT);

    pinMode(MUX_LS_AIN_A0, OUTPUT);
    pinMode(MUX_LS_AIN_A1, OUTPUT);
    pinMode(MUX_LS_AIN_A2, OUTPUT);

    // FIOs configured as inputs by default
    pinMode(FIO_1_PIN, INPUT);
    pinMode(FIO_2_PIN, INPUT);
    pinMode(FIO_3_PIN, INPUT);
    pinMode(FIO_4_PIN, INPUT);
    pinMode(FIO_5_PIN, INPUT);
    pinMode(FIO_6_PIN, INPUT);
    pinMode(FIO_7_PIN, INPUT);
    pinMode(FIO_8_PIN, INPUT);
    pinMode(FIO_9_PIN, INPUT);
    pinMode(FIO_10_PIN, INPUT);

    pinMode(DEBUG_LED1_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);

    pinMode(IO_EXPANSION_NRESET_PIN, OUTPUT);
    pinMode(IO_EXPANSION_INT_PIN, INPUT);

    // set default states
    digitalWrite(CS_LS_SE_ADC, HIGH); // high for idle CS in SPI
    digitalWrite(CS_HS_SE_ADC, HIGH);
    digitalWrite(CS_HS_DE_ADC, HIGH);

    digitalWrite(MUX_HS_DE_AIN_A0, LOW);
    digitalWrite(MUX_HS_DE_AIN_A1, LOW);
    digitalWrite(MUX_HS_DE_GAIN_A0, LOW);
    digitalWrite(MUX_HS_DE_GAIN_A1, LOW);

    digitalWrite(MUX_HS_SE_AIN_A0, LOW);
    digitalWrite(MUX_HS_SE_AIN_A1, LOW);
    digitalWrite(MUX_HS_SE_AIN_A2, LOW);
    digitalWrite(MUX_HS_SE_GAIN_A0, LOW);
    digitalWrite(MUX_HS_SE_GAIN_A1, LOW);

    digitalWrite(MUX_LS_SE_1_EN, LOW);
    digitalWrite(MUX_LS_SE_2_EN, LOW);
    digitalWrite(MUX_LS_SE_3_EN, LOW);

    digitalWrite(MUX_LS_AIN_A0, LOW);
    digitalWrite(MUX_LS_AIN_A1, LOW);
    digitalWrite(MUX_LS_AIN_A2, LOW);

    digitalWrite(DEBUG_LED1_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);

    digitalWrite(IO_EXPANSION_NRESET_PIN, HIGH); // active low
    
}

float BSP::readBoardTemperature() {
  analogReadResolution(12);
  uint16_t raw = analogRead(BOARD_TEMP_SENSOR_PIN);
  float voltage = raw * 3.3 / (1 << 12); // assuming 12 bit ADC mode
  float temperature = (voltage - BOARD_TEMP_SENSOR_OUTPUT_0C) / BOARD_TEMP_SENSOR_SLOPE;
  return temperature;
}
