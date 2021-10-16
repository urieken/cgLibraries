/**
 * @file SDLApplication.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Source for SDL application base.
 * @version 0.1
 * @date 2021-10-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <application/SDLApplication.hpp>

#include <event/CoreEvent.hpp>

#include <system/Unused.hpp>

namespace Display = ::cgl::display;
namespace Event = ::cgl::event;
namespace System = ::cgl::system;

namespace cgl {
namespace application {

SDLApplication::SDLApplication(int argc, char** argv) :
    mWindow{nullptr},
    mRenderer{nullptr},
    mUpdateRequested{false} {
    System::unused(argc, argv);
}

SDLApplication::~SDLApplication() {
}

auto SDLApplication::OnEvent(const Event::IEvent& event) -> bool {
    bool result{true};
    if (Event::EventSource::SDL == event.Source()) {
        auto data = static_cast<const SDL_Event*>(event.Data());
        switch(data->type) {
            case SDL_QUIT : {
                Cleanup();
                result = false;
            }break;
            case SDL_KEYDOWN : {
                result = OnKeyDownEvent(data->key);
            }break;
            case SDL_KEYUP : {
                result = OnKeyUpEvent(data->key);
            }break;
            default:break;
        }
    } else {
        switch (event.Type()) {
            case Event::EventType::Init : {
                result = Setup();
            }break;
            default : break;
        }
    }
    OnUpdate();
    return result;
}

auto SDLApplication::Setup() -> bool {
    ::SDL_Log("Setting up SDLApplication");
    if (0 != ::SDL_Init(SDL_INIT_EVERYTHING)) {
        ::SDL_LogCritical(SDL_LOG_CATEGORY_ERROR,
            "Failed to initialize SDL. Error = %s", ::SDL_GetError());
        return false;
    }
    mWindow = std::make_unique<Display::SDLWindow>("SDL_Application",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            800, 600, SDL_WINDOW_SHOWN);
    if (nullptr == mWindow) {
        return false;
    }
    mRenderer = std::make_unique<Display::SDLRenderer>(
        mWindow->GetId(), -1, SDL_RENDERER_ACCELERATED);
    return nullptr != mRenderer;
}

auto SDLApplication::Cleanup() -> void {
    ::SDL_Log("Shutting down SDL");
    ::SDL_Quit();
}

auto SDLApplication::OnKeyDownEvent(const SDL_KeyboardEvent& event) -> bool {
    // ::SDL_Log("Key down : %d", event.keysym.sym);
    switch(event.keysym.sym) {
        case SDLK_r : {
            mRenderer->SetDrawColor(255UL, 0UL, 0UL, 255UL);
            mUpdateRequested = true;
        } break;
        case SDLK_g : {
            mRenderer->SetDrawColor(0UL, 255UL, 0UL, 255UL);
            mUpdateRequested = true;
        } break;
        case SDLK_b : {
            mRenderer->SetDrawColor(0UL, 0UL, 255UL, 255UL);
            mUpdateRequested = true;
        } break;
        default:break;
    }
    return true;
}

auto SDLApplication::OnKeyUpEvent(const SDL_KeyboardEvent& event) -> bool {
    // ::SDL_Log("Key up : %d", event.keysym.sym);
    switch(event.keysym.sym) {
        case SDLK_ESCAPE : {
            Cleanup();
            return false;
        } break;
        default:break;
    }
    return true;
}

auto SDLApplication::OnUpdate() -> void {
    if (mUpdateRequested) {
        mRenderer->Clear();
        mRenderer->Present();
        mUpdateRequested = false;
    }
}

}  // namespace application
}  // namespace cgl
