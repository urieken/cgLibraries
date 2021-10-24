/**
 * @file SDLEventListener.integration.test.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Integration test for SDLEventListener
 * @version 0.1
 * @date 2021-10-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <event/IEventListener.hpp>
#include <event/SDLEvent.hpp>
#include <event/SDLEventListener.hpp>

#include <MockApplication.hpp>

#include <memory>

#include <gtest/gtest.h>

#include <SDL2/SDL.h>

namespace Event = ::cgl::event;

using MockApplication = ::cgl::application::test::MockApplication;

namespace cgl {
namespace event {
namespace test {
/**
 * @brief Test fixture for SDLEventListener
 */
class SDLEventListenerTest : public ::testing::Test {
protected:
    /**
     * @brief Pointer to the test object.
     */
    std::unique_ptr<Event::IEventListener> mListener;
    /**
     * @brief Setup the test environment.
     */
    auto SetUp() -> void override {
        auto result = ::SDL_Init(SDL_INIT_EVENTS);
        EXPECT_EQ(0, result);
        if (0 != result) {
            ::SDL_Log("Failed to initialize SDL events : %d(%s)\n",
            result, ::SDL_GetError());
        }
    }
    /**
     * @brief Teardown the test environment.
     */
    auto TearDown() -> void override {
        ::SDL_Quit();
    }
    /**
     * @brief Push a quit event in the SDL event queue.
     */
    auto PushSDLQuitEvent() -> void {
        SDL_Event event;
        event.type = SDL_QUIT;
        auto result = ::SDL_PushEvent(&event);
        EXPECT_EQ(1, result);
        if (1 != result) {
            ::SDL_Log("Pushed SDL_QUIT with result : %d(%s)\n",
            result, ::SDL_GetError());
        }
    }
};
/**
 * @brief Construct a new test object
 * 
 * @test Verify SDLEventListener for SDL_QUIT
 */
TEST_F(SDLEventListenerTest, testListeningForQuitEvent) {
    MockApplication mockApplication{};

    mListener = std::make_unique<Event::SDLEventListener>(mockApplication);
    PushSDLQuitEvent();

    EXPECT_CALL(mockApplication, OnEvent(::testing::_))
        .WillRepeatedly(::testing::Return(false));
    EXPECT_EQ(0, mListener->Start());
}
/**
 * @brief Construct a new test object
 * 
 * @test Verify SDLEventListener::pushEvent
 */
TEST_F(SDLEventListenerTest, testPushingEvent) {
    MockApplication mockApplication{};
    mListener = std::make_unique<Event::SDLEventListener>(mockApplication);

    EXPECT_CALL(mockApplication, OnEvent(::testing::_))
        .WillOnce(::testing::Return(false));
    mListener->PushEvent(Event::SDLEvent{
        Event::EventType::Core,Event::EventSource::SDL, nullptr});
}
/**
 * @brief Construct a new test object
 * 
 * @test Verify SDLEventListener start with uninitialized event subsystem
 */
TEST_F(SDLEventListenerTest, testListeningWithUninitializedEventSubsystem) {
    MockApplication mockApplication{};
    mListener = std::make_unique<Event::SDLEventListener>(mockApplication);
    TearDown();
    EXPECT_EQ(-1, mListener->Start());
    // Include a call to Stop for coverage.
    mListener->Stop();
}

}  // namespace test
}  // namespace event
}  // namespace cgl
