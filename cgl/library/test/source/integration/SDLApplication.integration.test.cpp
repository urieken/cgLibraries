/**
 * @file SDLApplication.integration.test.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Integration test for SDLApplication
 * @version 0.1
 * @date 2021-10-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <application/IApplication.hpp>
#include <application/SDLApplication.hpp>
#include <error/CGLError.hpp>
#include <event/CoreEvent.hpp>
#include <event/SDLEvent.hpp>
#include <event/SDLEventListener.hpp>
#include <system/Arguments.hpp>

#include <memory>
#include <sstream>

#include <gtest/gtest.h>

#include <SDL2/SDL.h>

namespace Application = ::cgl::application;
namespace Error = ::cgl::error;
namespace Event = ::cgl::event;
namespace System = ::cgl::system;

using Code = Error::ErrorCode;

namespace cgl {
namespace application {
namespace test {
/**
 * @brief Test fixture for SDLApplication
 */
class SDLApplicationTest : public ::testing::Test {
protected:
    /**
     * @brief The configuration data.
     */
    std::stringstream mInputStream;
    /**
     * @brief The arguments for the application.
     */
    System::Arguments mArguments;
    /**
     * @brief Pointer to the test application.
     */
    std::unique_ptr<Application::IApplication> mApplication;
    /**
     * @brief Pointer to test event listener.
     */
    std::unique_ptr<Event::SDLEventListener> mEventListener;
    /**
     * @brief Setup the test environment.
     */
    auto SetUp() -> void override {
        PrepareTestConfiguration();
        mApplication =
            std::make_unique<Application::SDLApplication>(mArguments);
        mEventListener =
            std::make_unique<Event::SDLEventListener>(*mApplication);
    }
    /**
     * @brief Teardown the test environment.
     */
    auto TearDown() -> void override {
        SDL_Event event;
        event.type = SDL_QUIT;

        mEventListener->PushEvent(Event::SDLEvent{
            Event::EventType::Core, Event::EventSource::SDL, &event});
    }
    /**
     * @brief Prepare the test configuration.
     */
    auto PrepareTestConfiguration() -> void {
        mInputStream << "sdl_init_flags:0x00000001u\n"
            << "sdl_window_flags:0x00000004u\n"
            << "name:SDLApplicationt\n"
            << "top:0\nleft:0\nwidth:200\nheight:200\n";
        auto parseResult = mArguments.ProcessInputStream(mInputStream,
            "([a-zA-Z0-9 \\_\\-]+)");
        EXPECT_EQ(static_cast<int>(Code::NoError), parseResult.value());
    }
};
/**
 * @brief Construct a new test object
 * 
 * @test Verify initialization
 */
TEST_F(SDLApplicationTest, testApplicationSetup) {
    mEventListener->PushEvent(Event::CoreEvent(Event::EventType::Init,
        Event::EventSource::None));
}
/**
 * @brief Construct a new test object
 * 
 * @test Verify unhandled core event
 */
TEST_F(SDLApplicationTest, testUnhandledCoreEvent) {
    Event::SDLEventListener listener{*mApplication};
    mEventListener->PushEvent(Event::CoreEvent(Event::EventType::Unknown,
        Event::EventSource::None));
}
/**
 * @brief Construct a new test object
 * 
 * @test Verify key down events
 */
TEST_F(SDLApplicationTest, testKeyDownEvents) {
    Event::SDLEventListener listener{*mApplication};
    mEventListener->PushEvent(Event::CoreEvent(Event::EventType::Init,
        Event::EventSource::None));
    SDL_Event event;
    event.type = SDL_KEYDOWN;

    event.key.keysym.sym = SDLK_r;
    mEventListener->PushEvent(Event::SDLEvent{
        Event::EventType::Core, Event::EventSource::SDL, &event});
    ::SDL_Delay(500);
    event.key.keysym.sym = SDLK_g;
    mEventListener->PushEvent(Event::SDLEvent{
        Event::EventType::Core, Event::EventSource::SDL, &event});
    ::SDL_Delay(500);
    event.key.keysym.sym = SDLK_b;
    mEventListener->PushEvent(Event::SDLEvent{
        Event::EventType::Core, Event::EventSource::SDL, &event});
    ::SDL_Delay(500);
    event.key.keysym.sym = SDLK_x;
    mEventListener->PushEvent(Event::SDLEvent{
        Event::EventType::Core, Event::EventSource::SDL, &event});
}
/**
 * @brief Construct a new test object
 * 
 * @test Verify key up events
 */
TEST_F(SDLApplicationTest, testKeyUpEvents) {
    Event::SDLEventListener listener{*mApplication};
    mEventListener->PushEvent(Event::CoreEvent(Event::EventType::Init,
        Event::EventSource::None));
    SDL_Event event;
    event.type = SDL_KEYUP;

    event.key.keysym.sym = SDLK_x;
    mEventListener->PushEvent(Event::SDLEvent{
        Event::EventType::Core, Event::EventSource::SDL, &event});
    event.key.keysym.sym = SDLK_ESCAPE;
    mEventListener->PushEvent(Event::SDLEvent{
        Event::EventType::Core, Event::EventSource::SDL, &event});
}
/**
 * @brief Construct a new test object
 * 
 * @test Verify mouse motion event
 */
TEST_F(SDLApplicationTest, testMouseMotionSDLEvent) {
    Event::SDLEventListener listener{*mApplication};
    mEventListener->PushEvent(Event::CoreEvent(Event::EventType::Init,
        Event::EventSource::None));
    SDL_Event event;
    event.type = SDL_MOUSEMOTION;
    mEventListener->PushEvent(Event::SDLEvent{
        Event::EventType::Core, Event::EventSource::SDL, &event});
}


}  // namespace test
}  // namespace application
}  // namespace cgl
