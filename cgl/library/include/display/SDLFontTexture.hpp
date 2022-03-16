/**
 * @file SDLFontTexture.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for SDL font texture
 * @version 0.1
 * @date 2022-03-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_DISPLAY_SDL_FONT_TEXTURE_HPP_
#define CGL_LIBRARY_INCLUDE_DISPLAY_SDL_FONT_TEXTURE_HPP_


#include <display/Color.hpp>
#include <display/IRenderer.hpp>
#include <display/SDLTexture.hpp>

#include <string>
#include <system_error>

#include <SDL2/SDL_ttf.h>

namespace cgl {
namespace display {

/**
 * @brief The SDL font texture
 */
class SDLFontTexture : public SDLTexture {
public:
    /**
     * @brief Construct a new SDLFontTexture object
     */
    SDLFontTexture();
    /**
     * @brief Destroy the SDLFontTexture object
     */
    virtual ~SDLFontTexture();
    /**
     * @brief Load a font from file.
     * 
     * @param path The path to the font file.
     * @param renderer The renderer where the texture will be created from.
     * @return std::error_condition Error result from the operation.
     */
    // auto Load(const std::string& path, IRenderer& renderer)
    //     -> std::error_condition override;
    /**
     * @brief Load a font from file.
     * 
     * @param path The path to the font file.
     * @param renderer The renderer where the texture will be created from.
     * @param key The color key.
     * @return std::error_condition Error result from the operation.
     */
    // auto Load(const std::string& path, IRenderer& renderer,
    //     const Color& key) -> std::error_condition override;
private:
    /**
     * @brief The SDL font structure.
     */
    TTF_Font* mFont;
};

}  // namespace display
}  // namespace cgl

#endif//CGL_LIBRARY_INCLUDE_DISPLAY_SDL_FONT_TEXTURE_HPP_
