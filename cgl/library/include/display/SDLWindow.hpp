/**
 * @file SDLWindow.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for SDLWindow
 * @version 0.1
 * @date 2021-10-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_DISPLAY_SDL_WINDOW_HPP_
#define CGL_LIBRARY_INCLUDE_DISPLAY_SDL_WINDOW_HPP_

#include <display/IWindow.hpp>

#include <cstdint>
#include <string>

#include <SDL2/SDL.h>

namespace cgl {
namespace display {
/**
 * @brief The SDL window.
 */
class SDLWindow : public IWindow {
public:
    SDLWindow() = delete;
    /**
     * @brief Construct a new SDLWindow object.
     * 
     * @param title The window title.
     * @param left The window left coordinate.
     * @param top The window top coordinate.
     * @param width The window width.
     * @param height The window height.
     * @param flags The window flags.
     */
    SDLWindow(const std::string& title,
        int left, int top, int width, int height,
        std::uint32_t flags);
    /**
     * @brief Destroy the SDLWindow object
     */
    virtual ~SDLWindow();
    /**
     * 
     * @brief Get the window ID.
     * 
     * @return const std::uint32_t The the window ID.
     */
    auto GetId() const -> const std::uint32_t override;
private:
    /**
     * @brief Pointer to SDLWindow
     */
    SDL_Window* mWindow;
};

}  // namespace display
}  // namespace cgl

#endif /* CGL_LIBRARY_INCLUDE_DISPLAY_SDL_WINDOW_HPP_ */
