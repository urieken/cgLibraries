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
    mType{EventType::Core} {
}

CoreEvent::CoreEvent(const EventType& type) :
    mType{type} {
}

auto CoreEvent::Type() const -> const EventType {
    return mType;
}

}  // namespace event
}  // namespace cgl
