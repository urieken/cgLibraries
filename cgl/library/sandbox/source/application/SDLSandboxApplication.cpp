/**
 * @file SDLSandboxApplication.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Source for SDLSandboxApplication
 * @version 0.1
 * @date 2021-11-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include <application/SDLSandboxApplication.hpp>

#include <command/SDLRendererCommand.hpp>
#include <command/SDLRendererCopyCommand.hpp>
#include <command/SDLRendererGeometryCommand.hpp>
#include <command/SDLRendererViewportCommand.hpp>
#include <display/Color.hpp>
#include <display/ClearColorScene.hpp>
#include <display/L08Scene.hpp>
#include <display/L15Scene.hpp>
#include <display/MainScene.hpp>
#include <display/SandboxScene.hpp>
#include <display/SDLRenderer.hpp>
#include <display/SDLTexture.hpp>
#include <display/SDLWindow.hpp>
#include <error/CGLError.hpp>
#include <event/CoreEvent.hpp>
#include <geometry/Line.hpp>
#include <geometry/Point.hpp>
#include <geometry/Rectangle.hpp>
#include <imgui/IMGuiCommand.hpp>

#include <memory>
#include <sstream>
#include <utility>
#include <vector>

namespace Command = ::cgl::command;
namespace Display = ::cgl::display;
namespace Error = ::cgl::error;
namespace Event = ::cgl::event;
// namespace Geometry = ::cgl::geometry;
namespace ImGui = ::cgl::sandbox::imgui;
namespace System = ::cgl::system;

using Code = Error::ErrorCode;
using Color = Display::Color;
using ImGuiEvent = ImGui::IMGuiSDLRenderer::ImGuiEvent;
using RenderOperation = Command::SDLRendererCommand::Operation;

namespace cgl {
namespace application {
namespace sandbox {

/**
 * @brief Get the string value of the given key.
 * 
 * @param key The key for the property.
 * @param args The Arguments instance containing the values.
 * @return const std::string The value for the key.
 */
auto GetStringProperty(const std::string& key,
    const System::Arguments& args) -> const std::string {
    auto value = args.GetProperty(key);
    return value.value_or("");
}
/**
 * @brief Get the integer value of the given key.
 * 
 * @param key The key for the property.
 * @param args The Arguments instance containing the values.
 * @return const int The value for the key.
 */
auto GetIntegerProperty(const std::string& key,
    const System::Arguments& args) -> const int {
    auto value = args.GetProperty(key);
    return std::stoi(value.value_or("0"));
}

SDLSandboxApplication::~SDLSandboxApplication() {
}

SDLSandboxApplication::SDLSandboxApplication(
    const ::cgl::system::Arguments& args) :
    mCustomEventStart{0},
    mMainWindow{0},
    SDLApplication{args},
    mArguments{args},
    mCommandQueue{},
    mImGui{nullptr},
    mScenes{} {
}

auto SDLSandboxApplication::OnEvent(
    const ::cgl::event::IEvent& event) -> bool {
    bool result{true};
    if (result = SDLApplication::OnEvent(event); true == result) {
        if (Event::EventSource::SDL == event.Source()) {
            auto data = static_cast<const SDL_Event*>(event.Data());
            auto windowId = data->window.windowID;
            if (auto iter = mScenes.find(data->window.windowID);
                mScenes.end() != iter) {
                iter->second->OnEvent(event);
            }
        } else {
            switch (event.Type()) {
                case Event::EventType::Init : {
                    result = Setup();
                }break;
                case Event::EventType::Update : {
                    // OnUpdate();
                    // mUpdateRequested = true;
                    result = true;
                } break;
                default : break;
            }
        }
    }
    return result;
}

auto SDLSandboxApplication::OnIdle() -> void {
    // if(mUpdateRequested) {
        OnUpdate();
        // mUpdateRequested = false;
    // }
}

auto SDLSandboxApplication::Setup() -> bool {
    // mCustomEventStart = ::SDL_RegisterEvents(1);
    mCustomEventStart = ::SDL_RegisterEvents(3);
    auto clearColorScene =
        std::make_unique<Display::ClearColorScene>(mCustomEventStart + 1);
    // auto scene08 = std::make_unique<Display::L08Scene>(mCustomEventStart + 2);
    // auto scene15 = std::make_unique<Display::L15Scene>(mCustomEventStart + 3);

    auto event = Event::CoreEvent{
        Event::EventType::Init,
        Event::EventSource::None
    };

    clearColorScene->OnEvent(event);
    // scene08->OnEvent(event);
    // scene15->OnEvent(event);

    std::vector<std::pair<std::string,
        ::cgl::event::CustomSDLEevent>> events {
            {
               CLEAR_COLOR_SCENE_TITLE,
                {mCustomEventStart + 1, clearColorScene->Id(), 0}
            }//,
            // {
            //     "LESSON_08", {mCustomEventStart + 2, scene08->Id(), 0}
            // },
            // {
            //     "LESSON_15", {mCustomEventStart + 3, scene15->Id(), 0}
            // }
        };
    auto mainScene = std::make_unique<Display::MainScene>(mCustomEventStart,
        mArguments, events);
    mainScene->OnEvent(event);

    mScenes[mainScene->Id()] = std::move(mainScene);
    mScenes[clearColorScene->Id()] = std::move(clearColorScene);
    // mScenes[scene08->Id()] = std::move(scene08);
    // mScenes[scene15->Id()] = std::move(scene15);

    for(auto& scene : mScenes) {
        scene.second->Visible(true);
    }
    return true;
}

auto SDLSandboxApplication::OnUpdate() -> void {
    while(!mCommandQueue.empty()) {
        mCommandQueue.front()->Execute();
        mCommandQueue.pop();
    }
    for(auto& pair : mScenes) {
        pair.second->OnUpdate();
    }
    mUpdateRequested = false;
}

}  // namespace sandbox
}  // namespace application
}  // namespace cgl
