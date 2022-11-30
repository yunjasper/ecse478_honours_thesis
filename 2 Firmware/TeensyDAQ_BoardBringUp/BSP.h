/**
 * BSP.h
 * 
 * Board Support Package header file.
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

#include <Arduino.h>

// ADC chip select pins
#define CS_LS_ADC   9
#define CS_HS_ADC   10

// ADC parameters
#define VOLTAGE_REFERENCE 4.999     // Volts
#define ADC_RESOLUTION    14        // bits
#define ADC_SPI_FREQ      40000000  // Hz

// analog mux pins
#define MUX_HS_AIN_A0     2
#define MUX_HS_AIN_A1     3
#define MUX_HS_GAIN_A0    5
#define MUX_HS_GAIN_A1    4
#define MUX_LS_SELECT_A0  14        // chooses between the two muxes for LS AIN
#define MUX_LS_SELECT_A1  38
#define MUX_LS_AIN_1_A0   35        // LS AIN 1 to 8
#define MUX_LS_AIN_1_A1   36
#define MUX_LS_AIN_1_A2   37
#define MUX_LS_AIN_2_A0   39        // LS AIN 9 to 16
#define MUX_LS_AIN_2_A1   41
#define MUX_LS_AIN_2_A2   40
#define MUX_LS_GAIN_A0    34
#define MUX_LS_GAIN_A1    33

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

// board temperature sensor
#define BOARD_TEMP_SENSOR_PIN         A7
#define BOARD_TEMP_SENSOR_SLOPE       0.01  // V/deg C
#define BOARD_TEMP_SENSOR_OUTPUT_0C   0.5   // V at 0 deg C

// red LED on board for debugging purposes
#define DEBUG_LED3        32


// variables
#define ARRAY_SIZE  10
extern volatile unsigned long time_buffer[ARRAY_SIZE];
extern volatile float adc_values[ARRAY_SIZE];
extern volatile uint8_t arr_position;
extern volatile uint8_t isReadyToPrint;
extern volatile uint8_t channelNo;


// function prototypes
void BSP_init();

uint16_t spiread16(uint8_t cs);
uint16_t spiread16_callback();

float readBoardTemperature();

void setHSAINMuxChannel(uint8_t channel);
void setLSAINMuxChannel(uint8_t channel);
void setLSGainMux(uint8_t gainValue);
void setHSGainMux(uint8_t gainValue);
