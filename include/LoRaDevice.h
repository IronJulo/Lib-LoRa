#ifndef LORA_DEVICE_H
#define LORA_DEVICE_H

#include "LoRaError.h"
#include "LoRaState.h"
#include "LoRaRegister.h"

#include "Transport.h"
#include "Transaction.h"


class LoRaDevice
{
private:
    ecl::Transport &m_transport;
    LoRaState m_state;

public:
    LoRaDevice(ecl::Transport &transport);
    ~LoRaDevice() = default;

    LoRaError init();
};

#endif /* LORA_DEVICE_H */