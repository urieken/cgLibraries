/**
 * @file IEvent.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for Event interface.
 * @version 0.1
 * @date 2021-10-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_EVENT_IEVENT_HPP_
#define CGL_LIBRARY_INCLUDE_EVENT_IEVENT_HPP_

namespace cgl {
namespace event {

/**
 * @brief The event types.
 */
enum class EventType {
    Core = 0UL,
    Init,
    Quit
};

/**
 * @brief The Event interface
 */
class IEvent {
public:
    virtual ~IEvent() = default;
    /**
     * @brief Returns the event type.
     * 
     * @return EventType The event type.
     */
    virtual auto Type() const -> const EventType = 0;
};

}  // namespace event
}  // namespace cgl

#endif /* CGL_LIBRARY_INCLUDE_EVENT_IEVENT_HPP_ */
