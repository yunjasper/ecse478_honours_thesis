/**
 * pinDefs.h
 * 
 * Contains pin definitions and function prototypes.
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

// ADC digital chip select pins
#define CS_LS_SE_ADC    9
#define CS_HS_SE_ADC    32
#define CS_HS_DE_ADC    10

// ADC parameters
#define VOLTAGE_REFERENCE 4.999     // Volts
#define ADC_RESOLUTION    14        // bits
#define ADC_SPI_FREQ      400000  // Hz

// analog mux control pins
#define MUX_HS_DE_AIN_A0     3
#define MUX_HS_DE_AIN_A1     2
#define MUX_HS_DE_GAIN_A0    5
#define MUX_HS_DE_GAIN_A1    4

#define MUX_HS_SE_AIN_A0     17
#define MUX_HS_SE_AIN_A1     22
#define MUX_HS_SE_AIN_A2     23
#define MUX_HS_SE_GAIN_A0    15
#define MUX_HS_SE_GAIN_A1    16

#define MUX_LS_SE_1_EN       41     // enables mux for LS SE group
#define MUX_LS_SE_2_EN       40     // since A0, A1, A2 are shared control pins
#define MUX_LS_SE_3_EN       39     // mux 1: LS SE AIN 1-8
#define MUX_LS_AIN_A0        35     // mux 2: LS SE AIN 9-16
#define MUX_LS_AIN_A1        36     // mux 3: LS SE AIN 17-24
#define MUX_LS_AIN_A2        37
#define MUX_LS_GAIN_A0       34
#define MUX_LS_GAIN_A1       33

#define MUX_LS_SE_SEL_A0     14
#define MUX_LS_SE_SEL_A1     38

#define MUX_SWITCH_TIME      250       // ns

// FIO pins (connected directly to Teensy)
#define FIO_1_PIN         0
#define FIO_2_PIN         1
#define FIO_3_PIN         24
#define FIO_4_PIN         25
#define FIO_5_PIN         26
#define FIO_6_PIN         27
#define FIO_7_PIN         28
#define FIO_8_PIN         29
#define FIO_9_PIN         30
#define FIO_10_PIN        31

// IO expanders
#define IO_EXPANSION_NRESET_PIN 7
#define IO_EXPANSION_INT_PIN    8
#define IO_EXPANSION_1_I2C_ADDR 0x20 // relay channels 1-8
#define IO_EXPANSION_2_I2C_ADDR 0X21 // relay channels 9-16
#define IO_EXPANSION_3_I2C_ADDR 0x22 // relay channels 17-24
#define IO_EXPANSION_4_I2C_ADDR 0x23 // DIO 1-6, debug LEDs 2 and 3

#define DIO_1_PIN                    IO_EXP_CH0
#define DIO_2_PIN                    IO_EXP_CH1
#define DIO_3_PIN                    IO_EXP_CH2
#define DIO_4_PIN                    IO_EXP_CH3
#define DIO_5_PIN                    IO_EXP_CH4
#define DIO_6_PIN                    IO_EXP_CH5
#define DEBUG_LED2_PIN               IO_EXP_CH6
#define DEBUG_LED3_PIN               IO_EXP_CH7

#define DEBUG_LED1_PIN    20
#define BUZZER_PIN        6

enum IOExpanderChannels {
  IO_EXP_CH0 = 0,
  IO_EXP_CH1 = 1,
  IO_EXP_CH2 = 2,
  IO_EXP_CH3 = 3,
  IO_EXP_CH4 = 4,
  IO_EXP_CH5 = 5,
  IO_EXP_CH6 = 6,
  IO_EXP_CH7 = 7,
};

// board temperature sensor
#define BOARD_TEMP_SENSOR_PIN         A7
#define BOARD_TEMP_SENSOR_SLOPE       0.01  // V/deg C
#define BOARD_TEMP_SENSOR_OUTPUT_0C   0.5   // V at 0 deg C

// red LED on board for debugging purposes
#define DEBUG_LED3        20
