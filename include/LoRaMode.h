#ifndef LORA_MODE_H
#define LORA_MODE_H

#include <stdint.h>

namespace LoRaMode
{
    static const uint8_t longRangeMode = 0x80;
    static const uint8_t sleep = 0x00;
    static const uint8_t standby = 0x01;
    static const uint8_t tx = 0x03;
    static const uint8_t rxContinuous = 0x05;
    static const uint8_t rxSingle = 0x06;
} // namespace LoRaMode

#endif /* LORA_MODE_H */