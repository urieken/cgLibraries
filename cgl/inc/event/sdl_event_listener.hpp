// Copyright 2020. Ulysses Don Rieken
/*! \file sdl_event_listener.hpp
    \brief Header for event listener interface.

    SDL event listener class.
 */

#ifndef CGL_INC_EVENT_SDL_EVENT_LISTENER_HPP_
#define CGL_INC_EVENT_SDL_EVENT_LISTENER_HPP_

#include <vector>

#include <event/ievent.hpp>
#include <event/ievent_listener.hpp>

//! Crazy Galen's Libraries
namespace cgl {
/*!
 * \addtogroup cgl
 * @{
 */
//! Crazy Galen's Event classes.
namespace event {
/*!
 * \addtogroup event
 * @{
 */
//! Event Listener interface
class SDLEventListener : public ieventListener {
 private:
    std::vector<EventHandler> mHandlers;
 public:
    //! CTOR
    SDLEventListener();
    //! Default DTOR.
    virtual ~SDLEventListener();
    /*!
     * \brief Register event handler to handler list.
     * \param handler The event handler to be registered. 
     */ 
    void registerHandler(const EventHandler& handler) override;
    //! Start listening for events.
    void startListening() override;
};
/*! @} End of Doxygen Groups*/
}  // namespace event
/*! @} End of Doxygen Groups*/
}  // namespace cgl

#endif  // CGL_INC_EVENT_SDL_EVENT_LISTENER_HPP_
