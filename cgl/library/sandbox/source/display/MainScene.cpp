/**
 * @file MainScene.cpp
 * @author Ulyses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Source for main scene
 * @version 0.1
 * @date 2022-01-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <display/MainScene.hpp>

#include <command/SDLRendererCommand.hpp>
#include <display/SDLRenderer.hpp>
#include <display/SDLWindow.hpp>
#include <imgui/IMGuiCommand.hpp>
#include <imgui/IMGuiSDLRenderer.hpp>

#include <memory>
#include <stdexcept>

namespace Command = ::cgl::command;
namespace Display = ::cgl::display;
namespace Event = ::cgl::event;
namespace ImGui = ::cgl::sandbox::imgui;
namespace System = ::cgl::system;

using ImGuiCommand = ::cgl::application::sandbox::imgui::IMGuiCommand;
using ImGuiEvent = ImGui::IMGuiSDLRenderer::ImGuiEvent;
using RenderOperation = Command::SDLRendererCommand::Operation;

namespace cgl {
namespace display {

constexpr auto TITLE{"MAIN_SCENE"};
constexpr auto TOP{100};
constexpr auto LEFT{100};
constexpr auto WIDTH{150};
constexpr auto HEIGHT{150};

MainScene::MainScene(const std::uint32_t& event,
    const System::Arguments& args,
    std::vector<std::pair<std::string,
            ::cgl::event::CustomSDLEevent>> events) :
    mSceneEvent{event},
    mArguments{args},
    mWindow{nullptr},
    mRenderer{nullptr},
    mEvents{events} {
}

MainScene::~MainScene() {
}

auto MainScene::OnEvent(const Event::IEvent &event) -> bool {
    if (Event::EventSource::SDL == event.Source()) {
        auto data = static_cast<const SDL_Event*>(event.Data());
        if (nullptr != mImGui) {
            mImGui->OnEvent(data);
        }
        switch(data->type) {
            case SDL_KEYDOWN : {
                // return OnKeyDownEvent(data->key);
            }break;
            case SDL_WINDOWEVENT : {
                // return OnWindowEvent(data->window);
            }break;
            default: {
                // if (mSceneEvent == data->type) {
                if(mWindow->GetId() == data->window.windowID) {
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

auto MainScene::OnUpdate() -> void {
    mCommandQueue.push(
        std::make_unique<Command::SDLRendererCommand>(*mRenderer,
            Command::SDLRendererCommand::Operation::Clear));
        mCommandQueue.push(std::make_unique<ImGuiCommand>(*mImGui));
        mCommandQueue.push(
            std::make_unique<Command::SDLRendererCommand>(*mRenderer,
            RenderOperation::Present));
    while(!mCommandQueue.empty()) {
        mCommandQueue.front()->Execute();
        mCommandQueue.pop();
    }
}

auto MainScene::Id() const -> std::uint32_t {
    if (nullptr == mWindow) {
        throw std::runtime_error{
            std::string(__PRETTY_FUNCTION__) + ":Window = nullptr"};
    }
    return mWindow->GetId();
}

auto MainScene::Visible(bool visible) -> void {
    mWindow->Visible(visible);
}

auto MainScene::Setup() -> bool {
    if (mWindow = std::make_unique<Display::SDLWindow>(
        GetStringProperty("name", mArguments),
        GetIntegerProperty("top", mArguments),
        GetIntegerProperty("left", mArguments),
        GetIntegerProperty("width", mArguments),
        GetIntegerProperty("height", mArguments),
        SDL_WINDOW_HIDDEN);nullptr == mWindow) {
        ::SDL_Log("Failed to create window : %s", ::SDL_GetError());
        return false;
    }
    if (mRenderer = std::make_unique<Display::SDLRenderer>(mWindow->GetId(),
        -1, SDL_RENDERER_ACCELERATED); nullptr == mRenderer) {
        ::SDL_Log("Failed to create renderer : %s", ::SDL_GetError());
        return false;
    }
    mImGui = std::make_unique<::cgl::sandbox::imgui::IMGuiSDLRenderer>(
        mArguments, static_cast<SDL_Window*>(mWindow->Get()),
        static_cast<SDL_Renderer*>(mRenderer->Get()));
    for(auto& event : mEvents) {
        ::SDL_Log("Adding : %s", event.first.c_str());
        mImGui->AddCustomEvent(event.first, event.second);
    }
    return true;
}

auto MainScene::GetStringProperty(const std::string& key,
    const System::Arguments& args) -> const std::string {
    auto value = args.GetProperty(key);
    return value.value_or("");
}

auto MainScene::GetIntegerProperty(const std::string& key,
    const System::Arguments& args) -> const int {
    auto value = args.GetProperty(key);
    return std::stoi(value.value_or("0"));
}


}  // namespace display
}  // namespace cgl
