// Copyright 2020. Ulysses Don Rieken
/*! \file sdl_event_listener.cpp
    \brief Implementation for event listener interface.

    SDL event listener class.
 */

#include <SDL2/SDL.h>

#include <thread>

#include <event/sdl_event_listener.hpp>

//! Crazy Galen's Libraries
namespace cgl {
/*!
 * \addtogroup cgl
 * @{
 */
//! Crazy Galen's Event classes.
namespace event {
/*!
 * \addtogroup event
 * @{
 */

SDLEventListener::SDLEventListener() {
    mHandlers.clear();
}

SDLEventListener::~SDLEventListener() {
    mHandlers.clear();
}

void SDLEventListener::registerHandler(const EventHandler& handler) {
    mHandlers.push_back(handler);
}

void SDLEventListener::startListening() {
    bool bDone{false};
    while (!bDone) {
        SDL_Event event;
        while (::SDL_PollEvent(&event)) {
            // std::thread handlerThread {
                // [&handlerThread, &event, &bDone, this](){
                    ievent evt;
                    evt.setPayload(EVENT_ID::SDL_EVENT, sizeof(event), &event);
                    for (auto handler : mHandlers) {
                        if (handler) {
                            bDone = handler(evt);
                        }
                    }
                // }
            // };
            // handlerThread.join();
        }
    }
}

/*! @} End of Doxygen Groups*/
}  // namespace event
/*! @} End of Doxygen Groups*/
}  // namespace cgl
