/**
 * BSP.h
 * 
 * Board Support Package header file.
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

#pragma once
#include <stdint.h>

// variables
#define ARRAY_SIZE  10
extern volatile unsigned long time_buffer[ARRAY_SIZE];
extern volatile float adc_values[ARRAY_SIZE];
extern volatile uint8_t arr_position;
extern volatile uint8_t isReadyToPrint;
extern volatile uint8_t channelNo;


// function prototypes
void BSP_init();

float readBoardTemperature();

void setHSAINMuxChannel(uint8_t channel);
void setLSAINMuxChannel(uint8_t channel);
void setLSGainMux(uint8_t gainValue);
void setHSGainMux(uint8_t gainValue);
