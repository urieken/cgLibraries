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


#include "event/SDLEvent.hpp"
#include <application/SDLSandboxApplication.hpp>

#include <command/SDLRendererCommand.hpp>
#include <command/SDLRendererCopyCommand.hpp>
#include <command/SDLRendererGeometryCommand.hpp>
#include <command/SDLRendererViewportCommand.hpp>
#include <display/Color.hpp>
#include <display/L01Scene.hpp>
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
    // mWindow{nullptr},
    // mRenderer{nullptr},
    // mRendererCommands{},
    mCommandQueue{},
    mImGui{nullptr},
    mScenes{} {
    // mUpdateRequested{false},
    // mTexture{nullptr},
    // mBackground{nullptr} {
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
                default : break;
            }
        }
    }
    OnUpdate();
    return result;
}

auto SDLSandboxApplication::Setup() -> bool {
    // if (SetupWindowAndRenderer()) {

    mCustomEventStart = ::SDL_RegisterEvents(3);
    auto scene01 = std::make_unique<Display::L01Scene>(mCustomEventStart + 1);
    auto scene08 = std::make_unique<Display::L08Scene>(mCustomEventStart + 2);
    auto scene15 = std::make_unique<Display::L15Scene>(mCustomEventStart + 3);

    auto event = Event::CoreEvent{
        Event::EventType::Init,
        Event::EventSource::None
    };

    scene01->OnEvent(event);
    scene08->OnEvent(event);
    scene15->OnEvent(event);

    std::vector<std::pair<std::string,
        ::cgl::event::CustomSDLEevent>> events {
        {
            "LESSON_01",
            {
                mCustomEventStart + 1,
                scene01->Id(),
                0
                // static_cast<Sint32>(ImGuiEvent::ClearColorChange)
            }
        },
        {
            "LESSON_08",
            {
                mCustomEventStart + 2,
                scene08->Id(),
                0
                // static_cast<Sint32>(ImGuiEvent::ClearColorChange)
            }
        },
        {
            "LESSON_15",
            {
                mCustomEventStart + 3,
                scene15->Id(),
                0
                // static_cast<Sint32>(ImGuiEvent::ClearColorChange)
            }
        }
    };

    auto mainScene = std::make_unique<Display::MainScene>(mCustomEventStart,
        mArguments, events);
    mainScene->OnEvent(event);

    mScenes[mainScene->Id()] = std::move(mainScene);
    mScenes[scene01->Id()] = std::move(scene01);
    mScenes[scene08->Id()] = std::move(scene08);
    mScenes[scene15->Id()] = std::move(scene15);

    for(auto& scene : mScenes) {
        scene.second->Visible(true);
    }

        // if (LoadImages()) {
        //     auto dimensions = mTexture->GetDimensions();
        //     ::cgl::display::Rect src{0, 1, mTerra.width, mTerra.height};
        //     ::cgl::display::Rect dest{0, 1, mTerra.width, mTerra.height};
        //     mCommandQueue.push(
        //         std::make_unique<Command::SDLRendererCopyCommand>(
        //         *mWindowGroupMap[mMainWindow].mRenderer,
        //         RenderOperation::CopyTexture, *mBackground));
        //     mCommandQueue.push(
        //         std::make_unique<Command::SDLRendererCopyCommand>(
        //         *mWindowGroupMap[mMainWindow].mRenderer,
        //         RenderOperation::CopyTextureRect, *mTexture, src, dest));
        //     mUpdateRequested = true;
        //     mWindowGroupMap[mMainWindow].mWindow->Visible(true);
        //     mScene = std::make_unique<Display::L01Scene>(mCustomEventStart);
        //     mImGui->Register(this);
        //     return true;
        // }
    return true;
    // }
    // return false;
}

// auto SDLSandboxApplication::SetupWindowAndRenderer() -> bool {
//     auto displayCount = ::SDL_GetNumVideoDisplays();
//     ::SDL_Log("DISPLAY COUNT : %d", displayCount);
//     for(auto i = 0; i < displayCount; i++) {
//         SDL_Rect rect;
//         if(0 == ::SDL_GetDisplayBounds(i, &rect)) {
//             ::SDL_Log("Display %i-[%d:%d:%d:%d]", i,
//             rect.x, rect.y, rect.w, rect.h);
//         } else {
//             ::SDL_Log("Failed to get display bounds for %d-%s",
//                 i, ::SDL_GetError());
//         }
//     }
//     return true;
// }

// auto SDLSandboxApplication::LoadImages() -> bool {
//     // mLog.Push(::cgl::log::ILog::Severity::Debug,
//     //     ::cgl::log::ILog::Category::Input,
//     //     "Setting up SDLSandboxApplication");
//     mLog.Push("Setting up SDLSandboxApplication");
//     constexpr auto backgroundImage{"res/img/paper.png"};
//     constexpr auto spriteImage{"res/img/Terra.png"};

//     Display::Color colorKey{0x00, 0x80, 0x80, 0x00};

//     mBackground = std::make_unique<Display::SDLTexture>();
//     mTexture = std::make_unique<Display::SDLTexture>();

   
//     if (static_cast<int>(Code::NoError) !=
//         mBackground->Load(backgroundImage,
//             *mWindowGroupMap[mMainWindow].mRenderer,
//             colorKey).value()) {
//         return false;
//     }
//     if (static_cast<int>(Code::NoError) !=
//         mTexture->Load(spriteImage,
//             *mWindowGroupMap[mMainWindow].mRenderer,
//             colorKey).value()) {
//         return false;
//     }
//     // mLog.Push(::cgl::log::ILog::Severity::Debug,
//     //     ::cgl::log::ILog::Category::Input,
//     //     std::string("Loaded : ") + backgroundImage);
//     mLog.Push(std::string("Loaded : ") + backgroundImage);
//     auto dimensions = mBackground->GetDimensions();
//     mWindowGroupMap[mMainWindow].mWindow->SetSize(
//         std::get<0>(dimensions), std::get<1>(dimensions));
//     mTerra.texture.Load(spriteImage,
//         *mWindowGroupMap[mMainWindow].mRenderer,
//         colorKey);
//     mTerra.width = 30;
//     mTerra.height = 48;
//     mTerra.indices = {0, 32, 64, 96, 128, 160, 192, 224};
//     return true;
// }

auto SDLSandboxApplication::OnUpdate() -> void {
    // if (mUpdateRequested) {
        // mCommandQueue.push(
        //     std::make_unique<Command::SDLRendererCommand>(
        //         *mWindowGroupMap[mMainWindow].mRenderer,
        //         Command::SDLRendererCommand::Operation::Clear));
        // mCommandQueue.push(
        //     std::make_unique<::cgl::application::sandbox::imgui::IMGuiCommand>(*mImGui));
        // mCommandQueue.push(
        //     std::make_unique<Command::SDLRendererCommand>(
        //         *mWindowGroupMap[mMainWindow].mRenderer,
        //     RenderOperation::Present));
        while(!mCommandQueue.empty()) {
            mCommandQueue.front()->Execute();
            mCommandQueue.pop();
        }
        // mScene->OnUpdate();
        for(auto& pair : mScenes) {
            pair.second->OnUpdate();
        }
        mUpdateRequested = false;
    // }
}

// auto SDLSandboxApplication::UpdateSprite(int index) -> void {
//     Display::Rect src{mTerra.indices[index], 1, mTerra.width, mTerra.height};
//     Display::Rect dest{0, 1, mTerra.width, mTerra.height};
    
//     mCommandQueue.push(
//         std::make_unique<Command::SDLRendererCopyCommand>(
//             *mWindowGroupMap[mMainWindow].mRenderer,
//             RenderOperation::CopyTexture, *mBackground, src, dest));
//     mCommandQueue.push(
//         std::make_unique<Command::SDLRendererCopyCommand>(
//             *mWindowGroupMap[mMainWindow].mRenderer,
//             RenderOperation::CopyTextureRect, *mTexture, src, dest));
//     mUpdateRequested = true;
// }

// auto SDLSandboxApplication::OnClearColorChange(std::vector<int>& clearColor)
//     -> void {
//     ::SDL_Log("Clear color : %d-%d-%d",
//         clearColor[0], clearColor[1], clearColor[2]);
//     mCommandQueue.push(
//         std::make_unique<Command::SDLRendererCommand>(
//             *mWindowGroupMap[mMainWindow].mRenderer,
//         RenderOperation::SetDrawColor,
//         SDL_Color{
//             static_cast<std::uint8_t>(clearColor[0]),
//             static_cast<std::uint8_t>(clearColor[1]),
//             static_cast<std::uint8_t>(clearColor[2]),
//             255}));
//     mCommandQueue.push(
//         std::make_unique<Command::SDLRendererCommand>(
//             *mWindowGroupMap[mMainWindow].mRenderer,
//         RenderOperation::Clear));
//     mUpdateRequested = true;
// }

// auto SDLSandboxApplication::OnModulationColorChange(std::vector<int>& modulationColor)
//     -> void {
//     ::SDL_Log("Modulation color : %d-%d-%d",
//         modulationColor[0], modulationColor[1], modulationColor[2]);
//     mTexture->SetColorModulation(modulationColor[0],
//         modulationColor[1], modulationColor[2]);
//     UpdateSprite(0);
//     mUpdateRequested = true;
// }

}  // namespace sandbox
}  // namespace application
}  // namespace cgl
