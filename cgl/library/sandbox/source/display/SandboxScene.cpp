/**
 * @file SandboxScene.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Source for base lesson scene
 * @version 0.1
 * @date 2022-01-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "command/ICommand.hpp"
#include "display/IRenderer.hpp"
#include "display/IWindow.hpp"
#include <display/SandboxScene.hpp>

#include <command/SDLRendererCommand.hpp>
#include <display/SDLRenderer.hpp>
#include <display/SDLWindow.hpp>
#include <imgui/IMGuiSDLRenderer.hpp>

#include <memory>
#include <stdexcept>
#include <string>

namespace Command = ::cgl::command;
namespace Display = ::cgl::display;
namespace Event = ::cgl::event;
namespace ImGui = ::cgl::sandbox::imgui;

using ImGuiEvent = ImGui::IMGuiSDLRenderer::ImGuiEvent;

namespace cgl {
namespace display {

constexpr auto TITLE{"SANDBOX"};
constexpr auto TOP{0};
constexpr auto LEFT{1281};
constexpr auto WIDTH{150};
constexpr auto HEIGHT{150};

SandboxScene::SandboxScene(const std::uint32_t& event) :
    SandboxScene{event, TITLE, {TOP, LEFT, WIDTH, HEIGHT}} {
}

SandboxScene::SandboxScene(const std::uint32_t& event,
    const std::string& title, const Rect& rect) :
    mSceneEvent{event}, mWindow{nullptr}, mRenderer{nullptr},
    mCommandQueue{}, mTitle{title}, mRect{rect} {}

auto SandboxScene::OnEvent(const Event::IEvent &event) -> bool {
    if (Event::EventSource::SDL == event.Source()) {
        auto data = static_cast<const SDL_Event*>(event.Data());
        switch(data->type) {
            default:break;
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

auto SandboxScene::OnUpdate() -> void {
    while(!mCommandQueue.empty()) {
        mCommandQueue.front()->Execute();
        mCommandQueue.pop();
    }    
}

auto SandboxScene::Id() const -> std::uint32_t {
    if (nullptr == mWindow) {
        throw std::runtime_error{
            std::string(__PRETTY_FUNCTION__) + ":Window = nullptr"};
    }
    return mWindow->GetId();
}

auto SandboxScene::Visible(bool visible) -> void {
    mWindow->Visible(visible);
}

auto SandboxScene::GetWindow() -> Display::IWindow* {
    return mWindow.get();
}

auto SandboxScene::GetRenderer() -> Display::IRenderer* {
    return mRenderer.get();
}

auto SandboxScene::EventType() const -> std::uint32_t const {
    return mSceneEvent;
}

auto SandboxScene::CommandQueue()
    -> std::queue<std::unique_ptr<Command::ICommand>>* {
    return &mCommandQueue;
}

auto SandboxScene::Setup() -> bool {
    if (mWindow = std::make_unique<Display::SDLWindow>(mTitle.c_str(),
        mRect.top, mRect.left, mRect.width, mRect.height,
        SDL_WINDOW_HIDDEN);nullptr == mWindow) {
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

}  // namespace display
}  // namespace cgl