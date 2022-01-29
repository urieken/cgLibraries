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

#include <display/L01Scene.hpp>

#include <command/SDLRendererCommand.hpp>
#include <display/SDLRenderer.hpp>
#include <display/SDLWindow.hpp>
#include <imgui/IMGuiSDLRenderer.hpp>

#include <memory>
#include <stdexcept>

namespace Command = ::cgl::command;
namespace Display = ::cgl::display;
namespace Event = ::cgl::event;
namespace ImGui = ::cgl::sandbox::imgui;

using ImGuiEvent = ImGui::IMGuiSDLRenderer::ImGuiEvent;

namespace cgl {
namespace display {

constexpr auto TITLE{"LESSON_01"};
constexpr auto TOP{0};
constexpr auto LEFT{1281};
constexpr auto WIDTH{150};
constexpr auto HEIGHT{150};

L01Scene::L01Scene(const std::uint32_t& event) :
    mSceneEvent{event},
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
            case SDL_WINDOWEVENT : {
                return OnWindowEvent(data->window);
            }break;
            default: {
                if ((mSceneEvent == data->type) &&
                   (mWindow->GetId() == data->window.windowID)) {
                    
                    switch(static_cast<ImGuiEvent>(data->user.code)) {
                    case ImGuiEvent::ClearColorChange : {
                        auto colors = static_cast<int*>(data->user.data1);
                        auto arg  = SDL_Color{
                            static_cast<std::uint8_t>(colors[0]),
                            static_cast<std::uint8_t>(colors[1]),
                            static_cast<std::uint8_t>(colors[2]),
                            255};

                        AppendSetDrawColorCommand(arg);
                        return true;
                    }break;
                    default:break;
                    }
                }
            }break;
        }
    } else {
        switch(event.Type()) {
            case Event::EventType::Init : {
                return Setup();
            }break;
            default:break;
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
        throw std::runtime_error{
            std::string(__PRETTY_FUNCTION__) + ":Window = nullptr"};
    }
    return mWindow->GetId();
}

auto L01Scene::Visible(bool visible) -> void {
    mWindow->Visible(visible);
}

auto L01Scene::Setup() -> bool {
    if (mWindow = std::make_unique<Display::SDLWindow>(TITLE, TOP,
        LEFT, WIDTH, HEIGHT, SDL_WINDOW_HIDDEN);nullptr == mWindow) {
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
            AppendSetDrawColorCommand(SDL_Color{255, 0, 0, 255});
            return true;
        }break;
        case SDLK_g : {
            AppendSetDrawColorCommand(SDL_Color{0, 255, 0, 255});
            return true;
        }break;
        case SDLK_b : {
            AppendSetDrawColorCommand(SDL_Color{0, 0, 255, 255});
            return true;
        }break;
        default:break;
    }
    return false;
}

auto L01Scene::OnWindowEvent(const SDL_WindowEvent& event) -> bool {
    switch(event.event) {
        case SDL_WINDOWEVENT_MOVED : {
            ::SDL_Log("%s - WINDOW MOVE EVENT : %d,%d",
                __PRETTY_FUNCTION__ , event.data1, event.data2);
            return true;
        }break;
        default:break;
    }
    return false;
}

auto L01Scene::AppendSetDrawColorCommand(const SDL_Color& color) -> void {
    mCommandQueue.push(
        std::make_unique<Command::SDLRendererCommand>(*mRenderer,
        Command::SDLRendererCommand::Operation::SetDrawColor, color));
    mCommandQueue.push(
        std::make_unique<Command::SDLRendererCommand>(*mRenderer,
        Command::SDLRendererCommand::Operation::Clear));
    mCommandQueue.push(
        std::make_unique<Command::SDLRendererCommand>(*mRenderer,
        Command::SDLRendererCommand::Operation::Present));
}

}  // namespace display
}  // namespace cgl