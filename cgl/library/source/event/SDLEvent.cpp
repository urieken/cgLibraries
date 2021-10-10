/**
 * @file SDLEvent.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Source for SDLEvent
 * @version 0.1
 * @date 2021-10-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <event/SDLEvent.hpp>

namespace cgl {
namespace event {

SDLEvent::SDLEvent() :
    IEvent{EventType::Core, EventSource::None},
    mData{nullptr} {
}

SDLEvent::SDLEvent(const EventType& type,
    const EventSource& source, SDL_Event* data) :
    IEvent{type, source},
    mData{data} {
}

auto SDLEvent::Data() const -> const void* {
    return mData;
}

}  // namespace event
}  // namespace cgl