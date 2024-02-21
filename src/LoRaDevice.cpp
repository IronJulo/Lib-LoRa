#include "LoRaDevice.h"

LoRaDevice::LoRaDevice(ecl::Transport &transport,
                       ecl::AbstractGpio &reset,
                       ecl::AbstractGpio &dio0) : m_transport(transport),
                                                  m_reset(reset),
                                                  m_dio0(dio0),
                                                  m_state(LoRaState::WAITING){};

LoRaError LoRaDevice::init(long frequency)
{
    // m_chipSelect.setDirection(ecl::Gpio::Direction::OUTPUT);
    // m_chipSelect.setState(ecl::Gpio::State::HIGH);

    // if (m_reset){ // TODO boolify this
    if (true)
    {
        m_reset.setDirection(ecl::Gpio::Direction::OUTPUT);
        m_reset.setState(ecl::Gpio::State::LOW);
        // delay(10); // TODO mock time
        m_reset.setState(ecl::Gpio::State::HIGH);
        // delay(10); // TODO mock time
    }

    m_transport.begin();

    uint8_t version;
    readRegister(LoRaRegister::RegVersion, version);

    if (version != 0x12)
        return LoRaError::UNSUPPORTED_VERSION;

    sleep();
    setFrequency(frequency);

    return LoRaError::UNIMPLEMENTED;
}

LoRaError LoRaDevice::readRegister(uint8_t address, uint8_t &data)
{
    return transfer(address & 0x7f, data);
}

LoRaError LoRaDevice::writeRegister(uint8_t address, uint8_t value)
{
    return transfer(address | 0x80, value);
}

LoRaError LoRaDevice::transfer(uint8_t address, uint8_t &data)
{
    // m_chipSelect.setState(ecl::Gpio::State::LOW);
    if (ecl::Transaction transaction = m_transport.startTransaction())
    {
        transaction.transfer(address);
        uint8_t response = transaction.transfer(data);
        data = response;
    }
    else
    {
        return LoRaError::UNKNOWN; // TODO
    }
    // m_chipSelect.setState(ecl::Gpio::State::HIGH);

    return LoRaError::OK;
}

LoRaError LoRaDevice::sleep()
{
    return writeRegister(LoRaRegister::RegOpMode, LoRaMode::longRangeMode | LoRaMode::sleep);
}

LoRaError LoRaDevice::setFrequency(long frequency)
{
    m_frequency = frequency;

    uint64_t realFreq = ((uint64_t)frequency << 19) / 32000000;
    writeRegister(LoRaRegister::RegFrfMsb, ((realFreq & 0b111111110000000000000000) >> 16));
    writeRegister(LoRaRegister::RegFrfMid, ((realFreq & 0b000000001111111100000000) >> 8));
    writeRegister(LoRaRegister::RegFrfLsb, ((realFreq & 0b000000000000000011111111) >> 0));

    return LoRaError::OK; // TODO add a LoRaError res; res &= write...
}