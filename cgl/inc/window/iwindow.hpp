// Copyright 2020, Ulysses Don Rieken
/*! \file iwindow.hpp
    \brief Header for window interface.

    Base class for window classes.
 */
#ifndef CGL_INC_WINDOW_IWINDOW_HPP_
#define CGL_INC_WINDOW_IWINDOW_HPP_

#include <string>
#include <common/shapes.hpp>
#include <event/sdl_event_listener.hpp>

using iRect = cgl::common::Rect<int>;

namespace event = cgl::event;

//! Crazy Galen's Libraries
namespace cgl {
    /*!
 * \addtogroup cgl
 * @{
 */
//! Crazy Galen's Window classes.
namespace window {
/*!
 * \addtogroup window
 * @{
 */
//! Window interface
class IWindow {
 public:
    event::EventHandler onEvent;
    auto create(const std::string& title,
        const iRect& windowRect, Uint32 windowFlags) virtual bool = 0;
    auto destroy() virtual void = 0;
};
/*! @} End of Doxygen Groups*/
}  // namespace window
/*! @} End of Doxygen Groups*/
}  // namespace cgl

#endif  // CGL_INC_WINDOW_IWINDOW_HPP_
