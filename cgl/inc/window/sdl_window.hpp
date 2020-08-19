// Copyright 2020, Ulysses Don Rieken
/*! \file sdl_window.hpp
    \brief Header for SDL window class.

    SDL window classes.
 */
#ifndef CGL_INC_WINDOW_SDL_WINDOW_HPP_
#define CGL_INC_WINDOW_SDL_WINDOW_HPP_

#include <SDL2/SDL.h>

#include <string>

#include <common/shapes.hpp>
#include <window/iwindow.hpp>

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
class SDLWindow  : public IWindow {
 private:
    SDL_Window* m_pWindow;
    
 public:

    SDLWindow();
    virtual ~SDLWindow();

    bool create(const std::string& title,
        const iRect& windowRect, Uint32 windowFlags) override;
    void destroy() override;

    bool handleEvent(event::ievent& evt);
};
/*! @} End of Doxygen Groups*/
}  // namespace window
/*! @} End of Doxygen Groups*/
}  // namespace cgl

#endif  // CGL_INC_WINDOW_SDL_WINDOW_HPP_
