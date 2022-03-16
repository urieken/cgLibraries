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

}  // namespace display
}  // namespace cgl
 