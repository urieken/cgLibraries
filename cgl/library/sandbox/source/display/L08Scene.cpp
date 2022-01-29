/**
 * @file L08Scene.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Source for lesson 08 scene.
 * @version 0.1
 * @date 2022-01-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <SDL2/SDL_pixels.h>

#include <command/SDLRendererCommand.hpp>
#include <command/SDLRendererGeometryCommand.hpp>
#include <display/SDLRenderer.hpp>
#include <display/SDLWindow.hpp>
#include <display/L08Scene.hpp>
#include <geometry/IGeometryElement.hpp>
#include <imgui/IMGuiSDLRenderer.hpp>

#include <memory>
#include <stdexcept>

namespace Command = ::cgl::command;
namespace Display = ::cgl::display;
namespace Event = ::cgl::event;
namespace Geometry = ::cgl::geometry;
namespace ImGui = ::cgl::sandbox::imgui;

using ImGuiEvent = ImGui::IMGuiSDLRenderer::ImGuiEvent;
using GeometryElement = Geometry::IGeometryElement;
using DrawOperation = ::cgl::command::SDLRendererCommand::Operation;

namespace cgl {
namespace display {

constexpr auto TITLE{"LESSON_08"};
constexpr auto TOP{200};
constexpr auto LEFT{1281};
constexpr auto WIDTH{200};
constexpr auto HEIGHT{200};

L08Scene::L08Scene(const std::uint32_t& event) :
    mSceneEvent{event},
    mWindow{nullptr},
    mRenderer{nullptr},
    mClearColor{0, 0, 0, 255},
    mDrawColor{0, 255, 0, 255},
    mFillColor{0, 0, 255, 255} {
}

L08Scene::~L08Scene() {

}

auto L08Scene::OnEvent(const Event::IEvent &event) -> bool {
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
                        auto colors = static_cast<float*>(data->user.data1);
                        mClearColor = {
                            static_cast<std::uint8_t>(255 * colors[0]),
                            static_cast<std::uint8_t>(255 * colors[1]),
                            static_cast<std::uint8_t>(255 * colors[2]),
                            static_cast<std::uint8_t>(255 * colors[3])
                        };
                        AppendSetDrawColorCommand();
                        return true;
                    }break;
                    case ImGuiEvent::DrawColorChange : {
                        auto colors = static_cast<float*>(data->user.data1);
                        mDrawColor = {
                            static_cast<std::uint8_t>(255 * colors[0]),
                            static_cast<std::uint8_t>(255 * colors[1]),
                            static_cast<std::uint8_t>(255 * colors[2]),
                            static_cast<std::uint8_t>(255 * colors[3])
                        };
                        return true;
                    }break;
                    case ImGuiEvent::FillColorChange : {
                        auto colors = static_cast<float*>(data->user.data1);
                        mFillColor = {
                            static_cast<std::uint8_t>(255 * colors[0]),
                            static_cast<std::uint8_t>(255 * colors[1]),
                            static_cast<std::uint8_t>(255 * colors[2]),
                            static_cast<std::uint8_t>(255 * colors[3])
                        };
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

auto L08Scene::OnUpdate() -> void {
    while(!mCommandQueue.empty()) {
        mCommandQueue.front()->Execute();
        mCommandQueue.pop();
    }    
}

auto L08Scene::Id() const -> std::uint32_t {
    if (nullptr == mWindow) {
        throw std::runtime_error{
            std::string(__PRETTY_FUNCTION__) + ":Window = nullptr"};
    }
    return mWindow->GetId();
}

auto L08Scene::Visible(bool visible) -> void {
    mWindow->Visible(visible);
}

auto L08Scene::Setup() -> bool {
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

auto L08Scene::OnKeyDownEvent(const SDL_KeyboardEvent& event) -> bool {
    auto element = GeometryElement{{50, 50, 150, 150}};
    element.setColors({
        {mDrawColor.r, mDrawColor.g, mDrawColor.b, mDrawColor.a},
        {mFillColor.r, mFillColor.g, mFillColor.b, mFillColor.a}});
    switch(event.keysym.sym) {
        case SDLK_r : {
            AppendDrawCommand(DrawOperation::DrawRect);
            return true;
        }break;
        case SDLK_p : {
            AppendDrawCommand(DrawOperation::DrawPoint);
            return true;
        }break;
        case SDLK_l : {
            AppendDrawCommand(DrawOperation::DrawLine);
            return true;
        }break;
        case SDLK_f : {
            AppendDrawCommand(DrawOperation::DrawFillRect);
            return true;
        }break;
        default:break;
    }
    return false;
}

auto L08Scene::OnWindowEvent(const SDL_WindowEvent& event) -> bool {
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

auto L08Scene::AppendSetDrawColorCommand() -> void {
    mCommandQueue.push(
        std::make_unique<Command::SDLRendererCommand>(*mRenderer,
        Command::SDLRendererCommand::Operation::SetDrawColor, mClearColor));
    mCommandQueue.push(
        std::make_unique<Command::SDLRendererCommand>(*mRenderer,
        Command::SDLRendererCommand::Operation::Clear));
    mCommandQueue.push(
        std::make_unique<Command::SDLRendererCommand>(*mRenderer,
        Command::SDLRendererCommand::Operation::Present));
}

auto L08Scene::AppendDrawCommand(
    const Command::SDLRendererCommand::Operation& operation) -> void {
    auto element = GeometryElement{{50, 50, 150, 150}};
    element.setColors({
        {mDrawColor.r, mDrawColor.g, mDrawColor.b, mDrawColor.a},
        {mFillColor.r, mFillColor.g, mFillColor.b, mFillColor.a}});
    mCommandQueue.push(
        std::make_unique<Command::SDLRendererCommand>(*mRenderer,
        Command::SDLRendererCommand::Operation::SetDrawColor, mClearColor));
    mCommandQueue.push(
        std::make_unique<Command::SDLRendererCommand>(*mRenderer,
        Command::SDLRendererCommand::Operation::Clear));
    mCommandQueue.push(
        std::make_unique<Command::SDLRendererGeometryCommand>(*mRenderer,
        operation, element));
    mCommandQueue.push(
        std::make_unique<Command::SDLRendererCommand>(*mRenderer,
        Command::SDLRendererCommand::Operation::Present));
}

}  // namespace display
}  // namespace cgl