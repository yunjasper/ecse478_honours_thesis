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
        gain_1 = 1,
        gain_10 = 2,
        gain_50 = 3,
        gain_100 = 4
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