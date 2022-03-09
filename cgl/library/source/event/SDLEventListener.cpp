/**
 * @file SDLEventListener.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Source for SDLEventListener
 * @version 0.1
 * @date 2021-10-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "event/CoreEvent.hpp"
#include "event/IEvent.hpp"
#include <event/SDLEventListener.hpp>
#include <event/SDLEvent.hpp>

#include <application/IApplication.hpp>

#include <SDL2/SDL.h>

namespace Application = ::cgl::application;
namespace Event = ::cgl::event;

namespace cgl {
namespace event {

SDLEventListener::SDLEventListener(::Application::IApplication& app) :
    mApplication{app} {
}

auto SDLEventListener::Start() -> int {
    if (SDL_INIT_EVENTS != ::SDL_WasInit(SDL_INIT_EVENTS)) {
        ::SDL_LogCritical(SDL_LOG_CATEGORY_ERROR,
            "SDL event subsystem was not initialized");
        // Might want to return an `std::error_condition` here.
        return -1;
    } else {
        ::SDL_Log("SDL event subsystem initialized");
        auto customEvent = ::SDL_RegisterEvents(1);
        auto coreEvent = Event::CoreEvent {
            Event::EventType::Update,
            Event::EventSource::None
        };
        mListening = true;
        while(mListening) {
            SDL_Event event;
            while (::SDL_PollEvent(&event)) {
                mListening = mApplication.OnEvent(Event::SDLEvent{
                    Event::EventType::Core,Event::EventSource::SDL,
                    &event});
            };
            mApplication.OnIdle();
        };
    }
    return 0;
}

auto SDLEventListener::Stop() -> void {
    mListening = false;
}

auto SDLEventListener::PushEvent(const IEvent& event) -> void {
    mListening = mApplication.OnEvent(event);
}

}  // namespace cgl
}  // namespace event
