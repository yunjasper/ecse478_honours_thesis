/**
 * AnalogInputs.cpp
 * 
 * Abstracts away analog muxes and ADCs.
 * 
 * Author: Jasper Yun
 * 
 */

#include "AnalogInputs.hpp"
#include "ADCmcp33151.hpp"
#include "AnalogMux.hpp"
#include "pinDefs.h"

#include <Arduino.h>

// TODO: CONSIDER USING AN INTERFACE INSTEAD

// private variables
AnalogMux hs_se_ain(
    MUX_HS_SE_AIN_A0,
    MUX_HS_SE_AIN_A1,
    MUX_HS_SE_AIN_A2,
    -1, // always enabled
    8,
    MUX_SWITCH_TIME
);

AnalogMux hs_de_ain(
    MUX_HS_DE_AIN_A0,
    MUX_HS_DE_AIN_A1,
    -1,
    -1, // always enabled
    4,
    MUX_SWITCH_TIME
);

AnalogMux ls_se_1_ain( // channels 1-8
    MUX_LS_AIN_A0,
    MUX_LS_AIN_A1,
    MUX_LS_AIN_A2,
    MUX_LS_SE_1_EN,
    8,
    MUX_SWITCH_TIME
);

AnalogMux ls_se_2_ain( // channels 9-16
    MUX_LS_AIN_A0,
    MUX_LS_AIN_A1,
    MUX_LS_AIN_A2,
    MUX_LS_SE_2_EN,
    8,
    MUX_SWITCH_TIME
);

AnalogMux ls_se_3_ain( // channels 17-24
    MUX_LS_AIN_A0,
    MUX_LS_AIN_A1,
    MUX_LS_AIN_A2,
    MUX_LS_SE_3_EN,
    8,
    MUX_SWITCH_TIME
);

AnalogMux hs_se_gain(
    MUX_HS_SE_GAIN_A0,
    MUX_HS_SE_GAIN_A1,
    -1,
    -1,
    4,
    MUX_SWITCH_TIME
);

AnalogMux hs_de_gain(
    MUX_HS_DE_GAIN_A0,
    MUX_HS_DE_GAIN_A1,
    -1,
    -1,
    4,
    MUX_SWITCH_TIME
);

AnalogMux ls_se_gain(
    MUX_LS_GAIN_A0,
    MUX_LS_GAIN_A1,
    -1,
    -1,
    4,
    MUX_SWITCH_TIME
);

AnalogMux ls_se_select(
    MUX_LS_SE_SEL_A0,
    MUX_LS_SE_SEL_A1,
    -1,
    -1,
    4, 
    MUX_SWITCH_TIME
);

ADCmcp33151 adc_hs_se(CS_HS_SE_ADC, ADC_SPI_FREQ, VOLTAGE_REFERENCE, ADC_RESOLUTION);
ADCmcp33151 adc_hs_de(CS_HS_DE_ADC, ADC_SPI_FREQ, VOLTAGE_REFERENCE, ADC_RESOLUTION);
ADCmcp33151 adc_ls_se(CS_LS_SE_ADC, ADC_SPI_FREQ, VOLTAGE_REFERENCE, ADC_RESOLUTION);

void AnalogInputs::init() {
    hs_se_ain_setGain(gain_1);
    hs_de_ain_setGain(gain_1);
    ls_se_ain_setGain(gain_1);

    ls_se_ain_readChannel(1);
    hs_de_ain_readChannel(1);
    hs_se_ain_readChannel(1);

    ls_se_1_ain.setEnabled(true);   // no actual harm in all simultaneously enabled
    ls_se_2_ain.setEnabled(true);
    ls_se_3_ain.setEnabled(true);
}

float AnalogInputs::hs_se_ain_readChannel(uint8_t channel) {
    // todo: add volatile int to class member to remember which channel is currently set
    // evaluate whether adding a check is more optimal than always setting the new channel
    hs_se_ain.setChannel(channel - 1);
    return adc_hs_se.readVoltage();
}

float AnalogInputs::hs_de_ain_readChannel(uint8_t channel) {
    hs_de_ain.setChannel(channel - 1);
    return adc_hs_de.readVoltage();
}

float AnalogInputs::ls_se_ain_readChannel(uint8_t channel) {
    channel -= 1; // app level is 1-based, board-logic-level is 0-based

    if (channel > 24 || channel < 0) {
        Serial.println("LS SE AIN set channel: invalid channel requested");
    }
    
    if (channel < 8) {
        ls_se_select.setChannel(3-1); // see schematics
        ls_se_1_ain.setChannel(channel);
    }
    else if (channel < 16) {
        ls_se_select.setChannel(2-1); // see schematics
        ls_se_2_ain.setChannel(channel % 8);
    }
    else if (channel < 24) {
        ls_se_select.setChannel(1-1); // see schematics
        ls_se_3_ain.setChannel(channel % 8);
    }
    
    return adc_ls_se.readVoltage();
}

void AnalogInputs::hs_se_ain_setGain(enum AnalogInputsGains gain) {
    // gains are coded in enum so can use as channel number directly
    hs_se_gain.setChannel(gain);
}

void AnalogInputs::hs_de_ain_setGain(enum AnalogInputsGains gain) {
    // gains are coded in enum so can use as channel number directly
    hs_de_gain.setChannel(gain);
}

void AnalogInputs::ls_se_ain_setGain(enum AnalogInputsGains gain) {
    // gains are coded in enum so can use as channel number directly
    ls_se_gain.setChannel(gain);
}

