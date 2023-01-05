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
#define MUX_SWITCH_TIME   250       // ns

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

// IO expander
#define IO_EXPANSION_NRESET_PIN 7
#define IO_EXPANSION_INT_PIN    8
#define IO_EXPANSION_1_I2C_ADDR 0x20 // debug LED1, LED2, and relay channels 1-6
#define IO_EXPANSION_2_I2C_ADDR 0X21 // relay channels 7-8, DIO ports

// IO expander connected pins
#define DEBUG_LED1_PIN              IO_EXP_1_CH0
#define DEBUG_LED2_PIN              IO_EXP_1_CH1
#define RELAY_DRIVER_EN_CH_1_PIN    IO_EXP_1_CH2
#define RELAY_DRIVER_EN_CH_2_PIN    IO_EXP_1_CH3
#define RELAY_DRIVER_EN_CH_3_PIN    IO_EXP_1_CH4
#define RELAY_DRIVER_EN_CH_4_PIN    IO_EXP_1_CH5
#define RELAY_DRIVER_EN_CH_5_PIN    IO_EXP_1_CH6
#define RELAY_DRIVER_EN_CH_6_PIN    IO_EXP_1_CH7
#define RELAY_DRIVER_EN_CH_7_PIN    IO_EXP_2_CH6
#define RELAY_DRIVER_EN_CH_8_PIN    IO_EXP_2_CH7
#define DIO_1_PIN                   IO_EXP_2_CH0
#define DIO_2_PIN                   IO_EXP_2_CH1
#define DIO_3_PIN                   IO_EXP_2_CH2
#define DIO_4_PIN                   IO_EXP_2_CH3
#define DIO_5_PIN                   IO_EXP_2_CH4
#define DIO_6_PIN                   IO_EXP_2_CH5

// IO expander channels
#define IO_EXP_1_CH0    0
#define IO_EXP_1_CH1    1
#define IO_EXP_1_CH2    2
#define IO_EXP_1_CH3    3
#define IO_EXP_1_CH4    4
#define IO_EXP_1_CH5    5
#define IO_EXP_1_CH6    6
#define IO_EXP_1_CH7    7
#define IO_EXP_2_CH0    0
#define IO_EXP_2_CH1    1
#define IO_EXP_2_CH2    2
#define IO_EXP_2_CH3    3
#define IO_EXP_2_CH4    4
#define IO_EXP_2_CH5    5
#define IO_EXP_2_CH6    6
#define IO_EXP_2_CH7    7



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
