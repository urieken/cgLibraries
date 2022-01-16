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
    IEvent{},
    mData{} {
}

CoreEvent::CoreEvent(const EventType& type,
    const EventSource& source) :
    IEvent{type, source},
    mData{} {
}

CoreEvent::CoreEvent(const EventType& type, const EventSource& source,
    const std::string& data) :
    IEvent{type, source},
    mData{data} {
}

auto CoreEvent::Data() const -> const void* {
    return mData.data();
}

}  // namespace event
}  // namespace cgl
