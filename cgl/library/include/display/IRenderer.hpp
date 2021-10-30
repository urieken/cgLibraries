/**
 * @file IRenderer.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.co)
 * @brief Header for Renderer interface
 * @version 0.1
 * @date 2021-10-11
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_DISPLAY_IRENDERER_HPP_
#define CGL_LIBRARY_INCLUDE_DISPLAY_IRENDERER_HPP_

#include <display/IRenderer.hpp>

#include <cstdint>

namespace cgl {
namespace display {

class ITexture;

/**
 * @brief The Renderer interface
 */
class IRenderer {
public:
    virtual ~IRenderer() = default;
    /**
     * @brief Clear the renderer.
     */
    virtual auto Clear() -> void = 0;
    /**
     * @brief Set the draw color.
     * 
     * @param red The red channel.
     * @param green The green channel.
     * @param blue The blue channel.
     * @param alpha The alpha channel.
     */
    virtual auto SetDrawColor(std::uint8_t red, std::uint8_t green,
        std::uint8_t blue, std::uint8_t alpha) -> void = 0;
    /**
     * @brief Present the renderer to the target window.
     */
    virtual auto Present() -> void = 0;
    /**
     * @brief Get a raw pointer to the renderer instance.
     * 
     * @return void* The pointer to the renderer instance.
     */
    virtual auto Get() const -> void* = 0;
    /**
     * @brief Copy a texture to the rendererer
     * 
     * @param texture The texture to be copied
     * @return true The operation succeeded.
     * @return false The operation failed.
     */
    virtual auto Copy(ITexture& texture) -> bool = 0;
};

}  // namespace display
}  // namespace cgl

#endif /* CGL_LIBRARY_INCLUDE_DISPLAY_IRENDERER_HPP_ */
