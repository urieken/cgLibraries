/**
 * @file L01Scene.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Source for lesson 01 scene
 * @version 0.1
 * @date 2022-01-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "command/ICommand.hpp"
#include <display/L01Scene.hpp>

#include <command/SDLRendererCommand.hpp>
#include <display/SDLRenderer.hpp>
#include <display/SDLWindow.hpp>

#include <memory>
#include <stdexcept>

namespace Command = ::cgl::command;
namespace Display = ::cgl::display;
namespace Event = ::cgl::event;

namespace cgl {
namespace display {

constexpr auto TITLE{"LESSON 01"};
constexpr auto TOP{100};
constexpr auto LEFT{100};
constexpr auto WIDTH{300};
constexpr auto HEIGHT{300};

L01Scene::L01Scene() :
    mWindow{nullptr},
    mRenderer{nullptr} {
}

L01Scene::~L01Scene() {

}

auto L01Scene::OnEvent(const Event::IEvent& event) -> bool {
    if (Event::EventSource::SDL == event.Source()) {
        auto data = static_cast<const SDL_Event*>(event.Data());
        switch(data->type) {
            case SDL_KEYDOWN : {
                return OnKeyDownEvent(data->key);
            }break;
            default:break;
        }
    } else {
        switch(event.Type()) {
            case Event::EventType::Init : {
                return Setup();
            }break;
            default : break;
        }
    }
    return false;
}

auto L01Scene::OnUpdate() -> void {
    while(!mCommandQueue.empty()) {
        mCommandQueue.front()->Execute();
        mCommandQueue.pop();
    }    
}

auto L01Scene::Id() const -> std::uint32_t {
    if (nullptr == mWindow) {
        throw std::runtime_error{"Window = nullptr"};
    }
    return mWindow->GetId();
}

auto L01Scene::Setup() -> bool {
    if (mWindow = std::make_unique<Display::SDLWindow>(TITLE, TOP,
        LEFT, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);nullptr == mWindow) {
        ::SDL_Log("Failed to create window : %s", ::SDL_GetError());
        return false;
    }
    if (mRenderer = std::make_unique<Display::SDLRenderer>(mWindow->GetId(),
        -1, SDL_RENDERER_ACCELERATED); nullptr == mRenderer) {
        ::SDL_Log("Failed to create renderer : %s", ::SDL_GetError());
        return false;
    }
    return true;
}

auto L01Scene::OnKeyDownEvent(const SDL_KeyboardEvent& event) -> bool {
    switch(event.keysym.sym) {
        case SDLK_r : {
            mCommandQueue.push(
                std::make_unique<Command::SDLRendererCommand>(*mRenderer,
                    Command::SDLRendererCommand::Operation::SetDrawColor,
                    SDL_Color{255, 0, 0, 255}));
            mCommandQueue.push(
                std::make_unique<Command::SDLRendererCommand>(*mRenderer,
                    Command::SDLRendererCommand::Operation::Clear));
            mCommandQueue.push(
                std::make_unique<Command::SDLRendererCommand>(*mRenderer,
                    Command::SDLRendererCommand::Operation::Present));
            return true;
        }break;
        case SDLK_g : {
            mCommandQueue.push(
                std::make_unique<Command::SDLRendererCommand>(*mRenderer,
                    Command::SDLRendererCommand::Operation::SetDrawColor,
                    SDL_Color{0, 255, 0, 255}));
            mCommandQueue.push(
                std::make_unique<Command::SDLRendererCommand>(*mRenderer,
                    Command::SDLRendererCommand::Operation::Clear));
            mCommandQueue.push(
                std::make_unique<Command::SDLRendererCommand>(*mRenderer,
                    Command::SDLRendererCommand::Operation::Present));
            return true;
        }break;
        case SDLK_b : {
            mCommandQueue.push(
                std::make_unique<Command::SDLRendererCommand>(*mRenderer,
                    Command::SDLRendererCommand::Operation::SetDrawColor,
                    SDL_Color{0, 0, 255, 255}));
            mCommandQueue.push(
                std::make_unique<Command::SDLRendererCommand>(*mRenderer,
                    Command::SDLRendererCommand::Operation::Clear));
            mCommandQueue.push(
                std::make_unique<Command::SDLRendererCommand>(*mRenderer,
                    Command::SDLRendererCommand::Operation::Present));
            return true;
        }break;
        default:break;
    }
    return false;
}

}  // namespace display
}  // namespace cgl