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

#include <event/SDLEventListener.hpp>
#include <event/CoreEvent.hpp>

#include <application/IApplication.hpp>

#include <SDL2/SDL.h>

namespace Application = ::cgl::application;
namespace Event = ::cgl::event;

namespace cgl {
namespace event {

SDLEventListener::SDLEventListener(::Application::IApplication& app) :
    mApplication{app} {
}

auto SDLEventListener::Start() -> void {
    if (SDL_INIT_EVENTS != ::SDL_WasInit(SDL_INIT_EVENTS)) {
        // Might want to return an `std::error_condition` here.
        ::SDL_LogCritical(SDL_LOG_CATEGORY_ERROR,
            "SDL Events was not initialized");
    } else {
        ::SDL_Log("SDL Events initialized");
        mListening = true;
        while(mListening) {
            SDL_Event event;
            while (::SDL_PollEvent(&event)) {
                switch (event.type){
                case SDL_QUIT : {
                    // Might want to do an `SDLEvent` here instead.
                    // But for now, we'll just use `CoreEvent` to see
                    // if this works.
                    mApplication.OnEvent(Event::CoreEvent(Event::EventType::Quit));
                    mListening = false;
                }break;
                default:break;
                }
            };
        };
    }
}

auto SDLEventListener::Stop() -> void {
    mListening = false;
}

auto SDLEventListener::PushEvent(const IEvent& event) -> void {
    mApplication.OnEvent(event);
}

auto SDLEventListener::Subscribe(Application::IApplication& app) -> void {
    mApplication = app;
}

}  // namespace cgl
}  // namespace event
