/**
 * @file SDLEventListener.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.co)
 * @brief Header for SDLEventListener
 * @version 0.1
 * @date 2021-10-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_EVENT_SDL_EVENT_LISTENER_HPP_
#define CGL_LIBRARY_INCLUDE_EVENT_SDL_EVENT_LISTENER_HPP_

#include <event/IEventListener.hpp>

#include <application/IApplication.hpp>

namespace cgl {
namespace event {
/**
 * @brief Listener for SDL events
 */
class SDLEventListener final : public IEventListener {
public:
    SDLEventListener() = delete;
    /**
     * @brief Construct a new SDLEventListener object 
     * 
     * @param app The subscriber.
     */
    SDLEventListener(::cgl::application::IApplication& app);
    /**
     * @brief Start listening.
     */
    auto Start() -> void override;
    /**
     * @brief Stop listening.
     */
    auto Stop() -> void override;
    /**
     * @brief Push a custom user event to the listener.
     * 
     * @param event The event to be pushed.
     */
    auto PushEvent(const IEvent& event) -> void override;
    /**
     * @brief Subcribe to event notifications.
     * 
     * @param app The subscriber.
     */
    auto Subscribe(::cgl::application::IApplication& app) -> void override;
private:
    /**
     * @brief The event subscriber
     */
    ::cgl::application::IApplication& mApplication;
    /**
     * @brief The listening flag.
     */
    bool mListening;
};

}  // namespace event
}  // namespace cgl

#endif /* CGL_LIBRARY_INCLUDE_EVENT_SDL_EVENT_LISTENER_HPP_ */
