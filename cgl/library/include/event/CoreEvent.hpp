/**
 * @file CodeEvent.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for Core Event.
 * @version 0.1
 * @date 2021-10-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <event/IEvent.hpp>

#ifndef CGL_LIBRARY_INCLUDE_EVENT_CORE_HPP_
#define CGL_LIBRARY_INCLUDE_EVENT_CORE_HPP_

namespace cgl {
namespace event {
/**
 * @brief Wrapper for core events.
 */
class CoreEvent final : public IEvent {
public:
    /**
     * @brief Construct a new CoreEvent object
     */
    CoreEvent();
    /**
     * @brief Construct a new CoreEvent object
     * 
     * @param type The CoreEvent subtype
     */
    explicit CoreEvent(const EventType& type);
    ~CoreEvent() = default;
    /**
     * @brief Returns the event type.
     * 
     * @return EventType The event type.
     */
    auto Type() const -> const EventType override;
private:
    /**
     * @brief The event type
     */
    EventType mType;
};

}  // namespace event
}  // namespace cgl

#endif /* CGL_LIBRARY_INCLUDE_EVENT_CORE_HPP_ */
