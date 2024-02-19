#include "LoRaDevice.h"

LoRaDevice::LoRaDevice(ecl::Transport &transport) : m_transport(transport),
                                                    m_state(LoRaState::WAITING){};

LoRaError LoRaDevice::init()
{
    return LoRaError::UNIMPLEMENTED;
}