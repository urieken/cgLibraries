/**
 * @file CoreEvent.test.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Unit test for CoreEvent
 * @version 0.1
 * @date 2021-10-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <event/IEvent.hpp>
#include <event/CoreEvent.hpp>

#include <memory>

#include <gtest/gtest.h>

namespace Event = ::cgl::event;

namespace cgl {
namespace event {
namespace test {

using Source = Event::EventSource;
using Type = Event::EventType;

/**
 * @brief Test fixture for CoreEvent
 */
class CoreEventTest : public ::testing::Test {
protected:
    /**
     * @brief Pointer to test event.
     */
    std::unique_ptr<Event::CoreEvent> mEvent;
};
/**
 * @brief Construct a new test object
 * 
 * @test Verify default event properties.
 */
TEST_F(CoreEventTest, testConstruction) {
    mEvent = std::make_unique<Event::CoreEvent>();
    EXPECT_EQ(nullptr, mEvent->Data());
}
/**
 * @brief Construct a new test object
 * 
 * @test Verify custom event properties.
 */
TEST_F(CoreEventTest, testParameterizedConstruction) {
    mEvent = std::make_unique<Event::CoreEvent>(Type::Unknown,
        Source::Unknown);
    EXPECT_EQ(nullptr, mEvent->Data());
}

}  // namespace test
}  // namespace event
}  // namespace cgl
