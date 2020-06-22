// Copyright 2020. Ulysses Don Rieken
#include <gtest/gtest.h>

#include <memory>
#include <cstdint>

#include <event/ievent.hpp>

namespace cgl {
namespace event {
namespace tests {

struct  payload_t{
    uint_fast8_t a;
    uint_fast16_t b;
    uint_fast32_t c;
    uint_fast64_t d;
};

class EventTestF : public ::testing::Test {
 protected:
    payload_t mPayload;
    std::unique_ptr<cgl::event::ievent<payload_t>> mEvent;
    void SetUp() override {
        mEvent = std::make_unique<cgl::event::ievent<payload_t>>();
        mPayload.a = 0x01;
        mPayload.b = 0x02;
        mPayload.c = 0x03;
        mPayload.d = 0x04;
    }
};

TEST_F(EventTestF, testSetAndGetData) {
    payload_t* payload{nullptr};
    uint_fast8_t id{0xFF};
    std::size_t length{sizeof mPayload};

    mEvent->setPayload(id, length, &mPayload);
    payload = mEvent->getPayload();
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
    EXPECT_EQ(length, mEvent->getPayloadLength());
}

}  // namespace tests
}  // namespace event
}  // namespace cgl
