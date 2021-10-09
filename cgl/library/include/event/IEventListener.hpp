/**
 * @file IEventListener.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for EventListener interface.
 * @version 0.1
 * @date 2021-10-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_EVENT_IEVENT_LISTENER_HPP_
#define CGL_LIBRARY_INCLUDE_EVENT_IEVENT_LISTENER_HPP_

#include <event/IEvent.hpp>

#include <application/IApplication.hpp>

namespace cgl {
namespace event {

/**
 * @brief The Event interface
 */
class IEventListener {
public:
    virtual ~IEventListener() = default;
    /**
     * @brief Start listening.
     * 
     * @return int The return code for the application.
     */
    virtual auto Start() -> int = 0;
    /**
     * @brief Stop listening.
     */
    virtual auto Stop() -> void = 0;
    /**
     * @brief Push a custom user event to the listener.
     * 
     * @param event The event to be pushed.
     */
    virtual auto PushEvent(const IEvent& event) -> void = 0;
};

}  // namespace event
}  // namespace cgl

#endif /* CGL_LIBRARY_INCLUDE_EVENT_IEVENT_LISTENER_HPP_ */