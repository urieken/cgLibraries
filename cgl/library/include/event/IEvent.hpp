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
    InitWithData,
    Update,
    Quit,
    // Maximum value for EventType. Any new
    // items should be added before this.
    Unknown
};
/**
 * @brief The event source.
 */
enum class EventSource {
    None = 0UL,
    SDL,
    IMGUI,
    // Maximum value for EventSource. Any new
    // items should be added before this.
    Unknown
};

/**
 * @brief The Event interface
 */
class IEvent {
public:
    virtual ~IEvent() = default;
    /**
     * @brief Construct a new IEvent object
     */
    IEvent();
    /**
     * @brief Construct a new IEvent object
     * 
     * @param type The CoreEvent.
     * @param source The EventSource.
     */
    IEvent(const EventType& type, const EventSource& source);
    /**
     * @brief Returns the event type.
     * 
     * @return const EventType The event type.
     */
    virtual auto Type() const -> const EventType;
    /**
     * @brief Returns the event source.
     * 
     * @return const EventSource The event source.
     */
    virtual auto Source() const -> const EventSource;
    /**
     * @brief Returns a pointer to event data.
     * 
     * @return const void* The pointer event data.
     */
    virtual auto Data() const -> const void* = 0;
private:
    /**
     * @brief The event type
     */
    EventType mType;
    /**
     * @brief The event source.
     */
    EventSource mSource;
};

}  // namespace event
}  // namespace cgl

#endif /* CGL_LIBRARY_INCLUDE_EVENT_IEVENT_HPP_ */
