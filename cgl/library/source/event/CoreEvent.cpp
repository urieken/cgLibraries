/**
 * @file CoreEvent.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Source for Core Event
 * @version 0.1
 * @date 2021-10-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <event/CoreEvent.hpp>

namespace cgl {
namespace event {

CoreEvent::CoreEvent() :
    IEvent{} {
}

CoreEvent::CoreEvent(const EventType& type,
    const EventSource& source) :
    IEvent{type, source} {
}

auto CoreEvent::Data() const -> const void* {
    return nullptr;
}

}  // namespace event
}  // namespace cgl
