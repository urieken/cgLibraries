/**
 * @file SDLRenderer.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for SDLRenderer
 * @version 0.1
 * @date 2021-10-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_DISPLAY_SDL_RENDERER_HPP_
#define CGL_LIBRARY_INCLUDE_DISPLAY_SDL_RENDERER_HPP_

#include <display/IRenderer.hpp>

#include <cstdint>

#include <SDL2/SDL.h>

namespace cgl {
namespace display {

/**
 * @brief Wrapper for SDL_Renderer
 */
class SDLRenderer : public IRenderer {
public:
    SDLRenderer() = delete;
    /**
     * @brief Construct a new SDLRenderer object
     * 
     * @param windowId The id for the renderer's target window.
     * @param index The index for the rendering driver.
     * @param flags The renderer flags.
     */
    SDLRenderer(std::uint32_t windowId, int index, std::uint32_t flags);
    /**
     * @brief Destroy the SDLRenderer object
     */
    virtual ~SDLRenderer();
        /**
     * @brief Clear the renderer.
     */
    auto Clear() -> void override;
    /**
     * @brief Set the draw color.
     * 
     * @param red The red channel.
     * @param green The green channel.
     * @param blue The blue channel.
     * @param alpha The alpha channel.
     */
    auto SetDrawColor(std::uint8_t red, std::uint8_t green,
        std::uint8_t blue, std::uint8_t alpha) -> void override;
    /**
     * @brief Present the renderer to the target window.
     */
    auto Present() -> void override;
private:
    /**
     * @brief Pointer to the opaque renderer.
     */
    SDL_Renderer* mRenderer;
};

}  // namespace display
}  // namespace cgl

#endif /* CGL_LIBRARY_INCLUDE_DISPLAY_SDL_RENDERER_HPP_ */