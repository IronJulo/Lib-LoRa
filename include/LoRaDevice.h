#ifndef LORA_DEVICE_H
#define LORA_DEVICE_H

#include "LoRaError.h"
#include "LoRaState.h"
#include "LoRaRegister.h"
#include "LoRaMode.h"

#include "Transport.h"
#include "Transaction.h"
#include "AbstractGpio.h"

class LoRaDevice
{
private:
    // oscillator frequency
    const int FXOSC = 32000000;

private:
    ecl::Transport &m_transport;
    ecl::AbstractGpio &m_reset;
    ecl::AbstractGpio &m_dio0;

    LoRaState m_state;

    long m_frequency;

public:
    LoRaDevice(ecl::Transport &transport, ecl::AbstractGpio &reset, ecl::AbstractGpio &dio0);
    ~LoRaDevice() = default;

    LoRaError init(long frequency);
    /**
     * @brief Reads a single byte from a specified register.
     * @param[in] address The register address from which to read.
     * @param[out] data Reference to a byte where the read data will be stored.
     * @return LoRaError indicating the success or type of failure of the operation.
     */
    LoRaError readRegister(uint8_t address, uint8_t &data);
    /**
     * @brief Writes a single byte to a specified LoRa register.
     * @param[in] address The register address to which the data will be written.
     * @param[in] data The byte of data to write to the register.
     * @return LoRaError indicating the success or type of failure of the operation.
     */
    LoRaError writeRegister(uint8_t address, uint8_t data);
    /**
     * @brief Transfers a byte of data to or from a specified LoRa register.
     * @param[in] address The register address for the transfer. The operation (read or write)
     *                    is determined by the most significant bit of the address.
     * @param[in,out] data On input, if writing, specifies the byte of data to write.
     *                     On output, if reading, the byte read is stored in this variable.
     * @return LoRaError indicating the success or type of failure of the transfer operation.
     */
    LoRaError transfer(uint8_t address, uint8_t &data);

    LoRaError sleep();
    LoRaError setFrequency(long frequency);
    LoRaError setSpreadingFactor(uint8_t spreadingFactor);
    LoRaError setCodingRate(uint8_t codingRade);
    LoRaError setBandwith(uint8_t bandwith);
    LoRaError setChannel(uint8_t channel);
};

#endif /* LORA_DEVICE_H */