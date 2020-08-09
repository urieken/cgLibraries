// Copyright 2020. Ulysses Don Rieken
#include <gtest/gtest.h>

#include <memory>
#include <cstdio>
#include <cstdint>

#include <event/ievent.hpp>

namespace events = cgl::event;

namespace cgl {
namespace event {
namespace tests {

struct  payload_t{
    std::uint8_t a;
    std::uint16_t b;
    std::uint32_t c;
    std::uint64_t d;
};

class EventTestF : public ::testing::Test {
 protected:
    payload_t mPayload;
    std::unique_ptr<events::ievent> mEvent;

    void SetUp() override {
        mEvent = std::make_unique<events::ievent>();
        mPayload.a = 0x01;
        mPayload.b = 0x02;
        mPayload.c = 0x03;
        mPayload.d = 0x04;
    }
};

TEST_F(EventTestF, testSetAndGetData) {
    payload_t* payload{nullptr};
    std::uint8_t id{0xFF};
    std::size_t length{sizeof mPayload};

    mEvent->setPayload(id, length, &mPayload);
    payload = static_cast<payload_t*>(mEvent->getPayload());
    EXPECT_EQ(typeid(*payload), typeid(mPayload));
    EXPECT_EQ(typeid(payload->a), typeid(mPayload.a));
    EXPECT_EQ(typeid(payload->b), typeid(mPayload.b));
    EXPECT_EQ(typeid(payload->c), typeid(mPayload.c));
    EXPECT_EQ(typeid(payload->d), typeid(mPayload.d));
    EXPECT_EQ(id, mEvent->getId());
    EXPECT_EQ(payload->a, mPayload.a);
    EXPECT_EQ(payload->b, mPayload.b);
    EXPECT_EQ(payload->c, mPayload.c);
    EXPECT_EQ(payload->d, mPayload.d);
    std::printf("%zu:%zu\n", length, mEvent->getPayloadLength());
    EXPECT_EQ(length, mEvent->getPayloadLength());
}

}  // namespace tests
}  // namespace event
}  // namespace cgl
