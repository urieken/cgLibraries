/**
 * @file SDLRenderer.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Source for SDLRenderer
 * @version 0.1
 * @date 2021-10-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <display/SDLRenderer.hpp>

namespace cgl {
namespace display {

SDLRenderer::SDLRenderer(std::uint32_t windowId,
    int index, std::uint32_t flags) {
    if (mRenderer = ::SDL_CreateRenderer(::SDL_GetWindowFromID(windowId),
        index, flags); nullptr == mRenderer) {
        ::SDL_Log("Failed to create renderer : %s", ::SDL_GetError());
    }
}

SDLRenderer::~SDLRenderer() {
    if (nullptr != mRenderer) {
        ::SDL_DestroyRenderer(mRenderer);
        mRenderer = nullptr;
    }
}

auto SDLRenderer::Clear() -> void {
    if (0 != ::SDL_RenderClear(mRenderer)) {
        ::SDL_Log("Failed to clear the renderer : %s", SDL_GetError());
    }
}

auto SDLRenderer::SetDrawColor(std::uint8_t red, std::uint8_t green,
    std::uint8_t blue, std::uint8_t alpha) -> void {
    if (0 != ::SDL_SetRenderDrawColor(mRenderer, red, green, blue, alpha)) {
        ::SDL_Log("Failed to set the renderer draw color : %s",
            SDL_GetError());
    }
}

auto SDLRenderer::Present() -> void {
    ::SDL_RenderPresent(mRenderer);
}

auto SDLRenderer::Get() const -> void* {
    return mRenderer;
}

auto SDLRenderer::Copy(ITexture& texture) -> bool {
    if (0 == ::SDL_RenderCopy(mRenderer,
        static_cast<SDL_Texture*>(texture.Get()), nullptr, nullptr)) {
        return true;
    }
   ::SDL_Log("Failed to copy texture to renderer : %s",
        SDL_GetError());
    return false;
}

auto SDLRenderer::Copy(ITexture& texture,
    const Rect& source, const Rect& dest) -> bool {
    SDL_Rect src{source.top, source.left, source.width, source.height};
    SDL_Rect dst{dest.top, dest.left, dest.width, dest.height};
    if (0 == ::SDL_RenderCopy(mRenderer,
        static_cast<SDL_Texture*>(texture.Get()), &src, &dst)) {
        return true;
    }
   ::SDL_Log("Failed to copy texture to renderer : %s",
        SDL_GetError());
    return false;
}

}  // namespace display
}  // namespace cgl
