/**
 * @file IEvent.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Source for Event interface
 * @version 0.1
 * @date 2021-10-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <event/IEvent.hpp>

namespace cgl {
namespace event {

IEvent::IEvent() :
    mType{EventType::Unknown},
    mSource{EventSource::None} {
}

IEvent::IEvent(const EventType& type, const EventSource& source) :
    mType{type},
    mSource{source} {
}

auto IEvent::Type() const -> const EventType {
    return IEvent::mType;
}

auto IEvent::Source() const -> const EventSource {
    return IEvent::mSource;
}

}
}  // namespace cgl
