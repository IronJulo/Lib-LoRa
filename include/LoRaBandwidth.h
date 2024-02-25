#ifndef LORA_BANDWIDTH_H
#define LORA_BANDWIDTH_H

#include <stdint.h>

namespace LoRaBandwidth
{
    static const uint8_t BW_7800 = 0;
    static const uint8_t BW_10400 = 1;
    static const uint8_t BW_15600 = 2;
    static const uint8_t BW_20800 = 3;
    static const uint8_t BW_31250 = 4;
    static const uint8_t BW_41700 = 5;
    static const uint8_t BW_62500 = 6;
    static const uint8_t BW_125000 = 7;
    static const uint8_t BW_250000 = 8;
    static const uint8_t BW_500000 = 9;
} // namespace LoRaMode

#endif /* LORA_BANDWIDTH_H */