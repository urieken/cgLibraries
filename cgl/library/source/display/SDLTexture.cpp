/**
 * @file SDLTexture.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Source for SDLTexture
 * @version 0.1
 * @date 2021-10-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <display/SDLTexture.hpp>

#include <error/CGLError.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace Error = ::cgl::error;

using Code = Error::ErrorCode;

namespace cgl {
namespace display {

SDLTexture::~SDLTexture() {
    if (nullptr != mTexture) {
        ::SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
    }
}

auto SDLTexture::Load(const std::string& path,
    IRenderer& renderer) -> std::error_condition {
    SDL_Surface* loadedSurface = ::IMG_Load(path.c_str());
    if (nullptr == loadedSurface) {
        ::SDL_LogCritical(SDL_LOG_CATEGORY_ERROR,
            "Failed to load image %s[%s]", path.c_str(), ::IMG_GetError());
        return Error::makeErrorCondition(Code::ImageLoadFailure);
    }
    mTexture = ::SDL_CreateTextureFromSurface(
        static_cast<SDL_Renderer*>(renderer.Get()), loadedSurface);
    if (nullptr ==  mTexture) {
        ::SDL_LogCritical(SDL_LOG_CATEGORY_ERROR,
            "Failed to create texture %s", ::SDL_GetError());
        return Error::makeErrorCondition(Code::TextureCreationFailure);
    }
    ::SDL_FreeSurface(loadedSurface);
    return Error::makeErrorCondition(Code::NoError);
}

auto SDLTexture::Get() const -> void* {
    return mTexture;
}

}  // namespace display
}  // namespace cgl
