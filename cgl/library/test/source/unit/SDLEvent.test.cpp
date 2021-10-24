/**
 * @file SDLEvent.test.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Unit test for SDLEvent
 * @version 0.1
 * @date 2021-10-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <event/IEvent.hpp>
#include <event/SDLEvent.hpp>

#include <memory>

#include <gtest/gtest.h>

namespace Event = ::cgl::event;

namespace cgl {
namespace event {
namespace test {
/**
 * @brief Test fixture for SDLEvent
 */
class SDLEventTest : public ::testing::Test {
protected:
    /**
     * @brief Pointer to the test object.
     */
    std::unique_ptr<Event::IEvent> mEvent;
    /**
     * @brief Setup the test environment.
     */
    auto SetUp() -> void override {
        mEvent = std::make_unique<Event::SDLEvent>(
            Event::EventType::Core,
            Event::EventSource::SDL);
    }
};
/**
 * @brief Construct a new test object
 * 
 * @test Verify null event from defaults
 */
TEST_F(SDLEventTest, testConstruction) {
    mEvent = std::make_unique<Event::SDLEvent>();
    EXPECT_EQ(nullptr, mEvent->Data());
    EXPECT_EQ(Event::EventType::Core, mEvent->Type());
    EXPECT_EQ(Event::EventSource::None, mEvent->Source());
}
/**
 * @brief Construct a new test object
 * 
 * @test Verify null event
 */
TEST_F(SDLEventTest, testNullEvent) {
    EXPECT_EQ(nullptr, mEvent->Data());
    EXPECT_EQ(Event::EventType::Core, mEvent->Type());
    EXPECT_EQ(Event::EventSource::SDL, mEvent->Source());
}

}  // namespace test
}  // namespace event
}  // namespce cgl
