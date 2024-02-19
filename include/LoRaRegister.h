
#ifndef LORA_REGISTER_H
#define LORA_REGISTER_H

#include <stdint.h>
namespace LoRaRegister
{
    static const uint8_t RegFifo = 0x00;
    static const uint8_t RegOpMode = 0x01;
    // 0x02 unused
    // 0x03 unused
    // 0x04 unused
    // 0x05 unused
    static const uint8_t RegFrfMsb = 0x06;
    static const uint8_t RegFrfMid = 0x07;
    static const uint8_t RegFrfLsb = 0x08;
    static const uint8_t RegPaConfig = 0x09;
    static const uint8_t RegPaRamp = 0x0A;
    static const uint8_t RegOcp = 0x0B;
    static const uint8_t RegLna = 0x0C;
    static const uint8_t RegFifoAddrPtr = 0x0D;
    static const uint8_t RegFifoTxBaseAddr = 0x0E;
    static const uint8_t RegFifoRxBaseAddr = 0x0F;
    static const uint8_t FifoRxCurrentAddr = 0x10;
    static const uint8_t RegIrqFlagsMask = 0x11;
    static const uint8_t RegIrqFlags = 0x12;
    static const uint8_t RegRxNbBytes = 0x13;
    static const uint8_t RegRxHeaderCntValueMsb = 0x14;
    static const uint8_t RegRxHeaderCntValueLsb = 0x15;
    static const uint8_t RegRxPacketCntValueMsb = 0x16;
    static const uint8_t RegRxPacketCntValueLsb = 0x17;
    static const uint8_t RegModemStat = 0x18;
    static const uint8_t RegPktSnrValue = 0x19;
    static const uint8_t RegPktRssiValue = 0x1A;
    static const uint8_t RegRssiValue = 0x1B;
    static const uint8_t RegHopChannel = 0x1C;
    static const uint8_t RegModemConfig1 = 0x1D;
    static const uint8_t RegModemConfig2 = 0x1E;
    static const uint8_t RegSymbTimeoutLsb = 0x1F;
    static const uint8_t RegPreambleMsb = 0x20;
    static const uint8_t RegPreambleLsb = 0x21;
    static const uint8_t RegPayloadLength = 0x22;
    static const uint8_t RegMaxPayloadLength = 0x23;
    static const uint8_t RegHopPeriod = 0x24;
    static const uint8_t RegFifoRxByteAddr = 0x25;
    static const uint8_t RegModemConfig3 = 0x26;
    // 0x27 RESERVED
    static const uint8_t RegFeiMsb = 0x28;
    static const uint8_t RegFeiMid = 0x29;
    static const uint8_t RegFeiLsb = 0x2A;
    // 0x2B RESERVED
    static const uint8_t RegRssiWideband = 0x2C;
    // 0x2D RESERVED
    // 0x2E RESERVED
    // 0x2F RESERVED
    // 0x30 RESERVED
    static const uint8_t RegDetectOptimize = 0x31;
    // 0x32 RESERVED
    static const uint8_t RegInvertIQ = 0x33;
    // 0x34 RESERVED
    // 0x35 RESERVED
    // 0x36 RESERVED
    static const uint8_t RegDetectionThreshold = 0x37;
    // 0x38 RESERVED
    static const uint8_t RegSyncWord = 0x39;
    // 0x3A RESERVED
    // 0x3B RESERVED
    // 0x3C RESERVED
    // 0x3D RESERVED
    // 0x3E RESERVED
    // 0x3F RESERVED
    static const uint8_t RegDioMapping1 = 0x40;
    static const uint8_t RegDioMapping2 = 0x41;
    static const uint8_t RegVersion = 0x42;
    // 0x43 UNUSED
    // 0x44 UNUSED
    // 0x45 UNUSED
    // 0x46 UNUSED
    // 0x47 UNUSED
    // 0x48 UNUSED
    // 0x49 UNUSED
    // 0x4A UNUSED
    static const uint8_t RegTcxo = 0x4B;
    // 0x4C UNUSED
    static const uint8_t RegPaDac = 0x4D;
    // 0x4E UNUSED
    // 0x4F UNUSED
    // 0x50 UNUSED
    // 0x51 UNUSED
    // 0x52 UNUSED
    // 0x53 UNUSED
    // 0x54 UNUSED
    // 0x55 UNUSED
    // 0x56 UNUSED
    // 0x57 UNUSED
    // 0x58 UNUSED
    // 0x59 UNUSED
    // 0x5A UNUSED
    static const uint8_t RegFormerTemp = 0x5B;
    // 0x5C UNUSED
    // 0x5D UNUSED
    // 0x5E UNUSED
    // 0x5F UNUSED
    // 0x60 UNUSED
    static const uint8_t RegAgcRef = 0x61;
    static const uint8_t RegAgcThresh1 = 0x62;
    static const uint8_t RegAgcThresh2 = 0x63;
    static const uint8_t RegAgcThresh3 = 0x64;
    // 0x65 UNUSED
    // 0x66 UNUSED
    // 0x67 UNUSED
    // 0x68 UNUSED
    // 0x69 UNUSED
    // 0x6A UNUSED
    // 0x6B UNUSED
    // 0x6C UNUSED
    // 0x6D UNUSED
    // 0x6E UNUSED
    // 0x6F UNUSED
    static const uint8_t RegPll = 0x70;
} // namespace LoRaRegister

#endif /* LORA_REGISTER_H */