/**
 * @file SDLWindow.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Source for SDLWindow
 * @version 0.1
 * @date 2021-10-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <display/SDLWindow.hpp>

namespace cgl {
namespace display {

SDLWindow::SDLWindow(const std::string& title,
    int left, int top, int width, int height,
    std::uint32_t flags) {
    if (mWindow = ::SDL_CreateWindow(title.c_str(), top, left, width,
        height, flags);nullptr == mWindow) {
        ::SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to create window : %s",
            ::SDL_GetError());
    }
}

SDLWindow::~SDLWindow() {
    if (nullptr != mWindow) {
        ::SDL_DestroyWindow(mWindow);
        mWindow = nullptr;
    }
}

auto SDLWindow::GetId() const -> const std::uint32_t {
    if (nullptr == mWindow) {
        return 0UL;
    }
    return ::SDL_GetWindowID(mWindow);
}

}  // namespace display
}  // namespace cgl
