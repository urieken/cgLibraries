// Copyright 2020. Ulysses Don Rieken

#include <cstring>

#include <window/sdl_window.hpp>

namespace cgl {
namespace window {

bool SDLWindow::handleEvent(event::ievent& evt) {
    bool bReturn{false};
    SDL_Event sdlEvt;
    if (cgl::event::EVENT_ID::SDL_EVENT == evt.getId()) {
        std::memmove(&sdlEvt, evt.getPayload(), sizeof(SDL_Event));
        if (SDL_QUIT == sdlEvt.type) {
            bReturn = true;
        }
    }
    return bReturn;
}

SDLWindow::SDLWindow() :
    m_pWindow{nullptr} {
    onEvent = std::bind(&SDLWindow::handleEvent, this, std::placeholders::_1);
}

SDLWindow::~SDLWindow() {}

bool SDLWindow::create(const std::string& title,
    const iRect& windowRect, Uint32 windowFlags) {
    m_pWindow = ::SDL_CreateWindow(title.c_str(),
        windowRect.top, windowRect.left,
        windowRect.width, windowRect.height, windowFlags);
    return nullptr != m_pWindow;
}

void SDLWindow::destroy() {
    if (nullptr != m_pWindow) {
        ::SDL_DestroyWindow(m_pWindow);
        m_pWindow = nullptr;
    }
}

}  // namespace window
}  // namespace cgl
