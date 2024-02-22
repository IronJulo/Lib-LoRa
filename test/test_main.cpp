#include <gtest/gtest.h>

#include "Transport.h"
#include "Transaction.h"

class FakeSpi : public ecl::Transport
{
private:
public:
    FakeSpi(/* FakeHal fakeHal */) : ecl::Transport(ecl::Endianness::BIG)
    {
    }
    ~FakeSpi()
    {
    }

    bool lock()
    {
    }

    bool unLock()
    {
    }

public:
    void write(uint8_t data)
    {
    }
    uint8_t read()
    {
    }
    uint8_t transfer(uint8_t data)
    {
    }
    void begin()
    {
    }
    ecl::Transaction startTransaction()
    {
    }
};

TEST(BasicTests, BT1)
{
    EXPECT_EQ(50, 50);
}