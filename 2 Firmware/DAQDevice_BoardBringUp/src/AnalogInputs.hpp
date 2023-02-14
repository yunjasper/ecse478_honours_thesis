/**
 * AnalogInputs.hpp
 * 
 * Abstracts away analog muxes and ADCs.
 * 
 * Author: Jasper Yun
 * 
 */

#pragma once
#include <stdint.h>

enum AnalogInputsGains {
        gain_1 = 0,
        gain_10,
        gain_50,
        gain_100
};

class AnalogInputs {

    public:
        void init();
        float hs_se_ain_readChannel(uint8_t channel);
        float hs_de_ain_readChannel(uint8_t channel);
        float ls_se_ain_readChannel(uint8_t channel);

        void hs_se_ain_setGain(enum AnalogInputsGains gain);
        void hs_de_ain_setGain(enum AnalogInputsGains gain);
        void ls_se_ain_setGain(enum AnalogInputsGains gain);

};