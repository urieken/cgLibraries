/**
 * @file SDLSpriteSheet.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Source SDLSpriteSheet
 * @version 0.1
 * @date 2021-12-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <display/SDLSpriteSheet.hpp>

#include <error/CGLError.hpp>

#include <system/Arguments.hpp>

#include <fstream>

#include <SDL2/SDL.h>

namespace Error = ::cgl::error;
// namespace System = ::cgl::system;

using Code = Error::ErrorCode;

namespace cgl {
namespace display {

SDLSpriteSheet::SDLSpriteSheet(const std::string& path) :
    SDLTexture{path} {
}

// auto SDLSpriteSheet::Load(const std::string& path,
//     IRenderer& renderer) -> std::error_condition {
//     return Error::makeErrorCondition(Code::NoError);
// }

// auto SDLSpriteSheet::Load(const std::string& path,
//     IRenderer& renderer, const Color& key) -> std::error_condition {
//     return Error::makeErrorCondition(Code::NoError);
// }

}  // namespace display
}  // namespace cgl
 