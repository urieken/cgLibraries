/**
 * @file ITexture..hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for Texture interface.
 * @version 0.1
 * @date 2021-10-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_DISPLAY_ITEXTURE_HPP_
#define CGL_LIBRARY_INCLUDE_DISPLAY_ITEXTURE_HPP_

#include <display/IRenderer.hpp>

#include <display/Color.hpp>

#include <cstdint>
#include <string>
#include <system_error>
#include <utility>

namespace cgl {
namespace display {
/**
 * @brief The texture interface
 */
class ITexture {
public:
    virtual ~ITexture() = default;
    /**
     * @brief Load a texture from file.
     * 
     * @param path The path to the texture file.
     * @param renderer The renderer where the texture will be created from.
     * @return std::error_condition Error result from the operation.
     */
    // virtual auto Load(const std::string& path,
    //     IRenderer& renderer) -> std::error_condition = 0;
    /**
     * @brief Create the texture.
     * 
     * @param renderer The renderer where the texture will be created from.
     * @return std::error_condition Error result from the operation.
     */
    virtual auto Create(IRenderer& renderer) -> std::error_condition = 0;
    /**
     * @brief Load a texture from file.
     * 
     * @param path The path to the texture file.
     * @param renderer The renderer where the texture will be created from.
     * @param key The color key.
     * @return std::error_condition Error result from the operation.
     */
    // virtual auto Load(const std::string& path,
    //     IRenderer& renderer, const Color& key) -> std::error_condition = 0;
    /**
     * @brief 
     * 
     * @param renderer The renderer where the texture will be created from.
     * @param key The color key.
     * @return std::error_condition Error result from the operation.
     */
    virtual auto Create(IRenderer& renderer, const Color& key)
        -> std::error_condition = 0;
    /**
     * @brief Get the raw pointer to the texture structure.
     * 
     * @return void* The raw pointer to the texture structure.
     */
    virtual auto Get() const -> void* = 0;
    /**
     * @brief Get the texture dimensions.
     * 
     * @return std::pair<int, int> The texture dimensions.
     */
    virtual auto GetDimensions() const -> std::pair<int, int> = 0;
    /**
     * @brief Set the color modulation components.
     * 
     * @param red The red component
     * @param green The green component
     * @param blue The blue component
     */
    virtual auto SetColorModulation(std::uint8_t red,
        std::uint8_t green, std::uint8_t blue) -> void = 0;
};

}  // namespace display
}  // namespace cgl


#endif /* CGL_LIBRARY_INCLUDE_DISPLAY_ITEXTURE_HPP_ */
