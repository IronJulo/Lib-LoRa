#include <iostream>
#include <iomanip>
#include <gtest/gtest.h>

#include "Transport.h"
#include "Transaction.h"

#include "LoRaDevice.h"

#define WRITE_MASK 0x80
#define READ_MASK 0x7F

class FakeSpi : public ecl::Transport
{
public:
    const uint8_t registerAddressError = LoRaRegister::RegMax;

    uint8_t m_registerMap[LoRaRegister::RegMax]{0};
    uint8_t m_rwAddress = registerAddressError;
    bool m_locked = false;

public:
    FakeSpi(/* FakeHal fakeHal */) : ecl::Transport(ecl::Endianness::BIG)
    {
    }

    ~FakeSpi()
    {
    }

    void setRWAddress(uint8_t address) { m_rwAddress = address; }
    uint8_t getRWAddress() { return m_rwAddress; }

    bool lock() override
    {
        m_locked = true;
        m_rwAddress = registerAddressError;
        return m_locked;
    }

    bool unLock() override
    {
        m_locked = false;
        m_rwAddress = registerAddressError;
        return m_locked;
    }

    void write(uint8_t data) override
    {
        if (m_rwAddress == registerAddressError)
            return; // TODO throw
        m_registerMap[m_rwAddress & 0x7f] = data;
    }

    uint8_t read() override
    {
        if (m_rwAddress == registerAddressError)
            return 0xFF; // TODO throw
        return m_registerMap[m_rwAddress & 0x7f];
    }

    uint8_t transfer(uint8_t data) override
    {
        if (!m_locked)
        {
            return 0xFF; // TODO throw
        }

        if (m_rwAddress == registerAddressError)
        {
            m_rwAddress = data;
            return 0xFF;
        }
        if (m_rwAddress & 0x80)
        {
            write(data);
            return 0xFF;
        }
        else
        {
            return read();
        }
    }

    void begin() override
    {
    }

    ecl::Transaction startTransaction() override
    {
        return ecl::Transaction(static_cast<ecl::Transaction>(*this));
    }
};

class FakeGpio : public ecl::AbstractGpio
{

    void setDirection(ecl::Gpio::Direction direction) override
    {
        AbstractGpio::setDirection(direction);
    }

    void setResistor(ecl::Gpio::Resistor resistor) override
    {
        AbstractGpio::setResistor(resistor);
    }

    void setState(ecl::Gpio::State state) override
    {
        AbstractGpio::setState(state);
    }

    ecl::Gpio::State getState() override
    {
        return AbstractGpio::getState();
    }

    void configureInterrupt(ecl::Gpio::InterruptEdge edge, ecl::Gpio::InterruptCallback callback) override
    {
        AbstractGpio::configureInterrupt(edge, callback);
    }
};

class FakeSpiFixture : public testing::Test
{
public:
    FakeSpi *fakeSpi1;
    virtual void SetUp()
    {
        fakeSpi1 = new FakeSpi();
    }

    virtual void TearDown()
    {
        delete fakeSpi1;
    }
};

class LoRaDeviceFixture : public testing::Test
{
public:
    /*
        This value is available in the library but we dont want the tests to change if the library change.
    */
    const int FXOSC = 32000000;
    LoRaDevice *loraDevice1;
    FakeSpi *fakeSpi1;
    FakeGpio *fakeResetGPIO;
    FakeGpio *fakeDIO0GPIO;

    virtual void SetUp()
    {
        fakeSpi1 = new FakeSpi();
        fakeResetGPIO = new FakeGpio();
        fakeDIO0GPIO = new FakeGpio();

        loraDevice1 = new LoRaDevice(*fakeSpi1, *fakeResetGPIO, *fakeDIO0GPIO);
    }

    virtual void TearDown()
    {
        delete loraDevice1;
        delete fakeSpi1;
        delete fakeResetGPIO;
        delete fakeDIO0GPIO;
    }
};

TEST_F(FakeSpiFixture, ReadValue)
{
    fakeSpi1->setRWAddress(0x00);
    ASSERT_EQ(0, fakeSpi1->read());
}

TEST_F(FakeSpiFixture, WriteValue)
{
    fakeSpi1->setRWAddress(0x00);
    fakeSpi1->write(0x42);
    ASSERT_EQ(0x42, fakeSpi1->read());
}

TEST_F(FakeSpiFixture, TransferValueR)
{
    fakeSpi1->lock();
    fakeSpi1->transfer(0x00 & 0x7F);
    ASSERT_EQ(0x00, fakeSpi1->transfer(0x00));
    fakeSpi1->unLock();
}

TEST_F(FakeSpiFixture, TransferValueW)
{
    fakeSpi1->lock();
    fakeSpi1->transfer(0x00 | 0x80);
    fakeSpi1->transfer(0x42);
    fakeSpi1->unLock();

    fakeSpi1->lock();
    fakeSpi1->transfer(0x00 & 0x7F);
    ASSERT_EQ(0x42, fakeSpi1->transfer(0x00));
    fakeSpi1->unLock();
}

TEST_F(LoRaDeviceFixture, ReadRegister)
{
    uint8_t result = 0;
    loraDevice1->readRegister(0x00, result);
    ASSERT_EQ(0x00, result);
}

TEST_F(LoRaDeviceFixture, WriteRegister)
{
    loraDevice1->writeRegister(0x00, 0x42);
    uint8_t result = 0;
    loraDevice1->readRegister(0x00, result);
    ASSERT_EQ(0x42, result);
}

TEST_F(LoRaDeviceFixture, SetFrequency)
{
    long frequency = 433E6;
    ASSERT_NE(LoRaError::UNIMPLEMENTED, loraDevice1->setFrequency(frequency)) << "Warning Unimplemented Test";

    uint8_t msb = 0;
    loraDevice1->readRegister(LoRaRegister::RegFrfMsb, msb);
    uint8_t mid = 0;
    loraDevice1->readRegister(LoRaRegister::RegFrfMid, mid);
    uint8_t lsb = 0;
    loraDevice1->readRegister(LoRaRegister::RegFrfLsb, lsb);

    /*
        Now this is kinda odd for a test but the value written by setFrequency is modified by the library so we'll do the math here
        Actually we're testing that the library is using the formula from the datasheet.
    */

    uint64_t result = 0;
    result += ((((uint64_t)msb) << 16) & 0b111111110000000000000000);
    result += ((((uint64_t)mid) << 8) & 0b000000001111111100000000);
    result += ((((uint64_t)lsb) << 0) & 0b000000000000000011111111);
    result = (FXOSC / (1 << 19)) * result;

    uint64_t expectedResult = (double)frequency / ((double)FXOSC / (1 << 19));
    expectedResult = (FXOSC / (1 << 19)) * expectedResult;

    ASSERT_EQ(expectedResult, result);
}

TEST_F(LoRaDeviceFixture, SetSpreadingFactor)
{
    uint8_t spreadingFactor = 12;
    ASSERT_NE(LoRaError::UNIMPLEMENTED, loraDevice1->setSpreadingFactor(spreadingFactor)) << "Warning Unimplemented Test";

    uint8_t modemConfig2 = 0;
    loraDevice1->readRegister(LoRaRegister::RegModemConfig2, modemConfig2);

    ASSERT_EQ(spreadingFactor, (modemConfig2 >> 4));
}

TEST_F(LoRaDeviceFixture, SetTooHighSpreadingFactor)
{
    uint8_t spreadingFactor = 50;
    ASSERT_NE(LoRaError::UNIMPLEMENTED, loraDevice1->setSpreadingFactor(spreadingFactor)) << "Warning Unimplemented Test";

    uint8_t modemConfig2 = 0;
    loraDevice1->readRegister(LoRaRegister::RegModemConfig2, modemConfig2);

    ASSERT_NE(spreadingFactor, (modemConfig2 >> 4));
    ASSERT_EQ(12, (modemConfig2 >> 4));
}

TEST_F(LoRaDeviceFixture, SetTooLowSpreadingFactor)
{
    uint8_t spreadingFactor = 2;
    ASSERT_NE(LoRaError::UNIMPLEMENTED, loraDevice1->setSpreadingFactor(spreadingFactor)) << "Warning Unimplemented Test";

    uint8_t modemConfig2 = 0;
    loraDevice1->readRegister(LoRaRegister::RegModemConfig2, modemConfig2);

    ASSERT_NE(spreadingFactor, (modemConfig2 >> 4));
    ASSERT_EQ(6, (modemConfig2 >> 4));
}

TEST_F(LoRaDeviceFixture, SetCodingRate)
{
    uint8_t codingRate = 1;
    ASSERT_NE(LoRaError::UNIMPLEMENTED, loraDevice1->setCodingRate(codingRate)) << "Warning Unimplemented Test";

    uint8_t modemConfig1 = 0;
    loraDevice1->readRegister(LoRaRegister::RegModemConfig1, modemConfig1);
    std::cout << "value: " << (int)(modemConfig1) << std::endl;

    ASSERT_EQ(codingRate, ((modemConfig1 & 0b00001110) >> 1));
}

TEST_F(LoRaDeviceFixture, SetTooHighCodingRate)
{
    uint8_t codingRate = 500;
    ASSERT_NE(LoRaError::UNIMPLEMENTED, loraDevice1->setCodingRate(codingRate)) << "Warning Unimplemented Test";

    uint8_t modemConfig1 = 0;
    loraDevice1->readRegister(LoRaRegister::RegModemConfig1, modemConfig1);

    ASSERT_NE(codingRate, ((modemConfig1 & 0b00001110) >> 1));
    ASSERT_EQ(1, ((modemConfig1 & 0b00001110) >> 1));
}

TEST_F(LoRaDeviceFixture, SetTooLowCodingRate)
{
    uint8_t codingRate = 0;
    ASSERT_NE(LoRaError::UNIMPLEMENTED, loraDevice1->setCodingRate(codingRate)) << "Warning Unimplemented Test";

    uint8_t modemConfig1 = 0;
    loraDevice1->readRegister(LoRaRegister::RegModemConfig1, modemConfig1);

    ASSERT_NE(codingRate, ((modemConfig1 & 0b00001110) >> 1));
    ASSERT_EQ(1, ((modemConfig1 & 0b00001110) >> 1));
}

TEST_F(LoRaDeviceFixture, SetBandwith)
{
    uint8_t bandwith = 1;
    ASSERT_NE(LoRaError::UNIMPLEMENTED, loraDevice1->setBandwith(bandwith)) << "Warning Unimplemented Test";

    uint8_t modemConfig1 = 0;
    loraDevice1->readRegister(LoRaRegister::RegModemConfig1, modemConfig1);

    ASSERT_EQ(bandwith, (modemConfig1 >> 4));
}

TEST_F(LoRaDeviceFixture, SetTooHighBandwith)
{
    uint8_t bandwith = 10;
    ASSERT_NE(LoRaError::UNIMPLEMENTED, loraDevice1->setBandwith(bandwith)) << "Warning Unimplemented Test";

    uint8_t modemConfig1 = 0;
    loraDevice1->readRegister(LoRaRegister::RegModemConfig1, modemConfig1);

    ASSERT_NE(bandwith, (modemConfig1 >> 4));
    ASSERT_EQ(7, (modemConfig1 >> 4));
}

TEST_F(LoRaDeviceFixture, SetChannel)
{
    ASSERT_NE(LoRaError::UNIMPLEMENTED, loraDevice1->setChannel(40)) << "Warning Unimplemented Test";
}
