// Copyright 2020. Ulysses Don Rieken
#include <gtest/gtest.h>

#include <memory>
#include <cstdint>
#include <system_error>

#include <event/ievent.hpp>
#include <error/error_types.hpp>

namespace events = cgl::event;

namespace cgl {
namespace event {
namespace tests {

constexpr auto UNKNOWN = "UNKNOWN";
constexpr auto NO_ERROR = "NO_ERROR";
constexpr auto CGL_ERROR_CATEGORY = "CGL_ERROR";

struct  payload_t{
    std::uint8_t a;
    std::uint16_t b;
    std::uint32_t c;
    std::uint64_t d;
};

class EventTestF : public ::testing::Test {
 protected:
    payload_t mPayload;
    std::unique_ptr<events::iEvent> mEvent;

    void SetUp() override {
        mEvent = std::make_unique<events::iEvent>();
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
    EXPECT_EQ(length, mEvent->getPayloadLength());
}

TEST_F(EventTestF, DISABLED_testSetAndGetErrorCodeForNoError) {
    mEvent->setError(
        std::make_shared<std::error_code>(
            static_cast<int>(cgl::error::CGL_ERROR::NO_ERROR),
            cgl::error::cglErrorCategory{}));
    EXPECT_EQ(std::string{NO_ERROR},
        mEvent->getError()->message());
    EXPECT_EQ(std::string{CGL_ERROR_CATEGORY},
        std::string{mEvent->getError()->category().name()});
    EXPECT_EQ(cgl::error::CGL_ERROR::NO_ERROR,
        static_cast<cgl::error::CGL_ERROR>(mEvent->getError()->value()));
}

TEST_F(EventTestF, DISABLED_testSetAndGetErrorCodeForUnknownError) {
    mEvent->setError(
        std::make_shared<std::error_code>(
            static_cast<int>(cgl::error::CGL_ERROR::UNKNOWN),
            cgl::error::cglErrorCategory{}));
    EXPECT_EQ(std::string{UNKNOWN},
        mEvent->getError()->message());
    EXPECT_EQ(std::string{CGL_ERROR_CATEGORY},
        std::string{mEvent->getError()->category().name()});
    EXPECT_EQ(cgl::error::CGL_ERROR::UNKNOWN,
        static_cast<cgl::error::CGL_ERROR>(mEvent->getError()->value()));
}
}  // namespace tests
}  // namespace event
}  // namespace cgl
