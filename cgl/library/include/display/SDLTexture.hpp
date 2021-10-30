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

#include <display/SDLRenderer.hpp>

#include <string>
#include <system_error>

#include <SDL2/SDL.h>

namespace cgl {
namespace display {
/**
 * @brief Wrapper for SDL_Texture
 */
class SDLTexture : public ITexture {
public:
    /**
     * @brief Destroy the SDLTexture object
     */
    virtual ~SDLTexture();
    /**
     * @brief Load a texture from file.
     * 
     * @param path The path to the texture file.
     * @return std::error_condition Error result from the operation.
     */
    auto Load(const std::string& path,
        IRenderer& renderer) -> std::error_condition override;
    /**
     * @brief Get the raw pointer to the texture structure.
     * 
     * @return void* The raw pointer to the texture structure.
     */
    auto Get() const -> void* override;
private:
    /**
     * @brief Pointer to the SDL texture structure.
     */
    SDL_Texture* mTexture;
};

}  // namespace display
}  // namespace cgl


#endif /* CGL_LIBRARY_INCLUDE_DISPLAY_SDL_TEXTURE_HPP_ */