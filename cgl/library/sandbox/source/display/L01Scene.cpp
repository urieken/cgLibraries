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
#include <imgui/IMGuiSDLRenderer.hpp>

#include <memory>
#include <stdexcept>

namespace Command = ::cgl::command;
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
    L01Scene{event, TITLE, {TOP, LEFT, WIDTH, HEIGHT}} {}

L01Scene::L01Scene(const std::uint32_t& event,
    const std::string& title, const Rect& rect) :
    SandboxScene{event, title, rect} {}

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
                if ((EventType() == data->type) &&
                   (Id() == data->window.windowID)) {
                    
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
        return SandboxScene::OnEvent(event);
    }
    return false;
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
    auto commands = CommandQueue();
    commands->push(
        std::make_unique<Command::SDLRendererCommand>(*GetRenderer(),
        Command::SDLRendererCommand::Operation::SetDrawColor, color));
    commands->push(
        std::make_unique<Command::SDLRendererCommand>(*GetRenderer(),
        Command::SDLRendererCommand::Operation::Clear));
    commands->push(
        std::make_unique<Command::SDLRendererCommand>(*GetRenderer(),
        Command::SDLRendererCommand::Operation::Present));
}

}  // namespace display
}  // namespace cgl