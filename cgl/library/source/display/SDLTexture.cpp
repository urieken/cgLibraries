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

#include <SDL2/SDL_render.h>
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

auto SDLTexture::Load(const std::string& path,
    IRenderer& renderer, const Color& key) -> std::error_condition {
    SDL_Surface* loadedSurface = ::IMG_Load(path.c_str());
    if (nullptr == loadedSurface) {
        ::SDL_LogCritical(SDL_LOG_CATEGORY_ERROR,
            "Failed to load image %s[%s]", path.c_str(), ::IMG_GetError());
        return Error::makeErrorCondition(Code::ImageLoadFailure);
    }
    if (0 != ::SDL_SetColorKey(loadedSurface, SDL_TRUE,
        ::SDL_MapRGB(loadedSurface->format, key.red, key.green, key.blue))) {
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

auto SDLTexture::GetDimensions() const -> std::pair<int, int> {
    int width{0};
    int height{0};
    if (0 != ::SDL_QueryTexture(mTexture, nullptr, nullptr, &width, &height)) {
        ::SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Failed to query texture dimensions. [%s]", ::SDL_GetError());
    }
    return {width, height};
}

auto SDLTexture::SetColorModulation(std::uint8_t red,
    std::uint8_t green, std::uint8_t blue) -> void {
    if(0 != ::SDL_SetTextureColorMod(mTexture, red, green, blue)){
        ::SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Failed to set texture color modulation. [%s]", ::SDL_GetError());
    }
}

}  // namespace display
}  // namespace cgl
