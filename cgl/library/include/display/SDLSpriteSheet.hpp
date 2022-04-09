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
#include <display/Rect.hpp>
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
    SDLSpriteSheet() = delete;
    virtual ~SDLSpriteSheet() = default;
    /**
     * @brief Construct a new SDLTexture object
     * 
     * @param path Path to the image file.
     */
    explicit SDLSpriteSheet(const std::string& path);
private:

};

}  // namespace display
}  // namespace cgl

#endif /* FBAB3647_759A_457A_A7F6_EF66E28E273F */
