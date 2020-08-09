// Copyright 2020. Ulysses Don Rieken
/*! \file ievent_listener.hpp
    \brief Header for event listener interface.

    Base class for event listener classes.
 */

#ifndef CGL_INC_EVENT_IEVENT_LISTENER_HPP_
#define CGL_INC_EVENT_IEVENT_LISTENER_HPP_

#include <functional>

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
using EventHandler = std::function<bool(ievent&)>;
//! Event Listener interface
class ieventListener {
 public:
    //! Default DTOR.
    virtual ~ieventListener() = default;
    /*!
     * \brief Register event handler to handler list.
     * \param handler The event handler to be registered. 
     */ 
    virtual void registerHandler(const EventHandler& handler) = 0;
    //! Start listening for events.
    virtual void startListening() = 0;
};
/*! @} End of Doxygen Groups*/
}  // namespace event
/*! @} End of Doxygen Groups*/
}  // namespace cgl

#endif  // CGL_INC_EVENT_IEVENT_LISTENER_HPP_
