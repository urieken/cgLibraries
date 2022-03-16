/**
 * @file SDLFontTexture.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Source for SDL font texture.
 * @version 0.1
 * @date 2022-03-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <display/SDLFontTexture.hpp>

#include <error/CGLError.hpp>

namespace Error = ::cgl::error;

using Code = Error::ErrorCode;

namespace cgl {
namespace display {

SDLFontTexture::SDLFontTexture() :
    mFont{nullptr} {
}

SDLFontTexture::~SDLFontTexture() {
    if(nullptr != mFont) {
        ::TTF_CloseFont(mFont);
        mFont = nullptr;
    }
}

auto SDLFontTexture::Load(const std::string& path, IRenderer& renderer)
    -> std::error_condition {
    return Error::makeErrorCondition(Code::NoError);
}

auto SDLFontTexture::Load(const std::string& path, IRenderer& renderer,
    const Color& key) -> std::error_condition {
    return Error::makeErrorCondition(Code::NoError);
}

}  // namespace display
}  // namespace cgl
