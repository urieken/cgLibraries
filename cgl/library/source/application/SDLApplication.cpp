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

namespace Event = ::cgl::event;
namespace System = ::cgl::system;

namespace cgl {
namespace application {

SDLApplication::SDLApplication(int argc, char** argv) :
    mWindow{nullptr} {
    System::unused(argc, argv);
}

SDLApplication::~SDLApplication() {
}

auto SDLApplication::Run() -> int {
    if (0 != ::SDL_Init(SDL_INIT_EVERYTHING)) {
        SDL_Log("Failed to initialize SDL. Error = %s",
            ::SDL_GetError());
        return -1;
    }
    ::SDL_Log("SDL initialized");
    SDL_Window* window = ::SDL_CreateWindow("SDL_Application",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            800, 600, SDL_WINDOW_SHOWN);
    ::SDL_Delay(2000);
    return 0;
}

auto SDLApplication::OnEvent(const Event::IEvent& event) -> bool {
    auto type = event.Type();
    switch (type) {
        case Event::EventType::Init : {
            return Setup();
        }break;
        case Event::EventType::Quit : {
            Cleanup();
            return true;
        }break;
        default:break;
    }
    return false;
}

auto SDLApplication::Setup() -> bool {
    ::SDL_Log("Setting up SDLApplication");
    if (0 != ::SDL_Init(SDL_INIT_EVERYTHING)) {
        ::SDL_LogCritical(SDL_LOG_CATEGORY_ERROR,
            "Failed to initialize SDL. Error = %s", ::SDL_GetError());
        return false;
    }
    mWindow = ::SDL_CreateWindow("SDL_Application",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            800, 600, SDL_WINDOW_SHOWN);
    return nullptr != mWindow;
}

auto SDLApplication::Cleanup() -> void {
    ::SDL_Log("Shutting down SDL");
    ::SDL_Quit();
}

}  // namespace application
}  // namespace cgl
