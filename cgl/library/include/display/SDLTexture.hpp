/**
 * @file SDLTexture.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for SDLTexture
 * @version 0.1
 * @date 2021-10-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_DISPLAY_SDL_TEXTURE_HPP_
#define CGL_LIBRARY_INCLUDE_DISPLAY_SDL_TEXTURE_HPP_

#include <display/ITexture.hpp>

#include <display/Color.hpp>
#include <display/SDLRenderer.hpp>

#include <string>
#include <system_error>
#include <utility>

#include <SDL2/SDL.h>

namespace cgl {
namespace display {
/**
 * @brief Wrapper for SDL_Texture
 */
class SDLTexture : public ITexture {
public:
    SDLTexture() = delete;
    /**
     * @brief Destroy the SDLTexture object
     */
    virtual ~SDLTexture();
    /**
     * @brief Construct a new SDLTexture object
     * 
     * @param path Path to the image file.
     */
    explicit SDLTexture(const std::string& path);
    /**
     * @brief Create the texture.
     * 
     * @param renderer The renderer where the texture will be created from.
     * @return std::error_condition Error result from the operation.
     */
    auto Create(IRenderer& renderer) -> std::error_condition override;
    /**
     * @brief Create the texture.
     * 
     * @param renderer The renderer where the texture will be created from.
     * @param key The color key.
     * @return std::error_condition Error result from the operation.
     */
    auto Create(IRenderer& renderer, const Color& key)
        -> std::error_condition override;
    /**
     * @brief Get the raw pointer to the texture structure.
     * 
     * @return void* The raw pointer to the texture structure.
     */
    auto Get() const -> void* override;
    /**
     * @brief Get the texture dimensions.
     * 
     * @return std::pair<int, int> The texture dimensions.
     */
    auto GetDimensions() const -> std::pair<int, int> override;
    /**
     * @brief Set the color modulation components.
     * 
     * @param red The red component
     * @param green The green component
     * @param blue The blue component
     */
    auto SetColorModulation(std::uint8_t red,
        std::uint8_t green, std::uint8_t blue) -> void override;
protected:
    /**
     * @brief Pointer to the SDL texture structure.
     */
    SDL_Texture* mTexture;
    /**
     * @brief The path to image filename.
     */
    std::string mPath;
};

}  // namespace display
}  // namespace cgl


#endif /* CGL_LIBRARY_INCLUDE_DISPLAY_SDL_TEXTURE_HPP_ */
