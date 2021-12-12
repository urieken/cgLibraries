/**
 * @file SDLSpriteSheet.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for SDLSpriteSheet
 * @version 0.1
 * @date 2021-12-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef FBAB3647_759A_457A_A7F6_EF66E28E273F
#define FBAB3647_759A_457A_A7F6_EF66E28E273F

#include <display/SDLTexture.hpp>

#include <display/Color.hpp>
#include <display/SDLRenderer.hpp>

#include <string>
#include <system_error>
#include <utility>

namespace cgl {
namespace display {
/**
 * @brief Wrapper class for spritesheet texture.
 */
class SDLSpriteSheet : SDLTexture {
public:
    virtual ~SDLSpriteSheet() = default;
    /**
     * @brief Load a texture from file.
     * 
     * @param path The path to the texture file.0
     * @param renderer The renderer where the texture will be created from.
     * @return std::error_condition Error result from the operation.
     */
    auto Load(const std::string& path, IRenderer& renderer)
        -> std::error_condition override;
    /**
     * @brief Load a texture from file.
     * 
     * @param path The path to the texture file.
     * @param renderer The renderer where the texture will be created from.
     * @param key The color key.
     * @return std::error_condition Error result from the operation.
     */
    auto Load(const std::string& path, IRenderer& renderer,
        const Color& key) -> std::error_condition override;
};

}  // namespace display
}  // namespace cgl

#endif /* FBAB3647_759A_457A_A7F6_EF66E28E273F */
