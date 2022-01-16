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


#include "imgui/IMGuiCommand.hpp"
#include "log/ILog.hpp"
#include <application/SDLSandboxApplication.hpp>

#include <command/SDLRendererCommand.hpp>
#include <command/SDLRendererCopyCommand.hpp>
#include <command/SDLRendererGeometryCommand.hpp>
#include <command/SDLRendererViewportCommand.hpp>
#include <display/Color.hpp>
#include <display/L01Scene.hpp>
#include <display/SDLRenderer.hpp>
#include <display/SDLTexture.hpp>
#include <display/SDLWindow.hpp>
#include <error/CGLError.hpp>
#include <event/CoreEvent.hpp>
#include <functional>
#include <geometry/Line.hpp>
#include <geometry/Point.hpp>
#include <geometry/Rectangle.hpp>

#include <memory>
#include <sstream>
#include <utility>

namespace Command = ::cgl::command;
namespace Display = ::cgl::display;
namespace Error = ::cgl::error;
namespace Event = ::cgl::event;
// namespace Geometry = ::cgl::geometry;
namespace System = ::cgl::system;
// namespace ImGui = ::cgl::sandbox::imgui;

using Code = Error::ErrorCode;
using Color = Display::Color;
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
    mMainWindow{0},
    SDLApplication{args},
    mArguments{args},
    // mWindow{nullptr},
    // mRenderer{nullptr},
    // mRendererCommands{},
    mCommandQueue(),
    mUpdateRequested{false},
    mTexture{nullptr},
    mBackground{nullptr} {
}

auto SDLSandboxApplication::OnEvent(
    const ::cgl::event::IEvent& event) -> bool {
    bool result{true};
    if (result = SDLApplication::OnEvent(event); true == result) {
        if (Event::EventSource::SDL == event.Source()) {
            auto data = static_cast<const SDL_Event*>(event.Data());
            auto windowId = data->window.windowID;
            mUpdateRequested = mImGui->OnEvent(data);
            switch(data->type) {
                case SDL_KEYDOWN : {                    
                    result = OnKeyDownEvent(data->key);
                }break;
                default : break;
            }
            // if (mScene->Id() == data->window.windowID) {
            //     mScene->OnEvent(event);
            // }
            // if (mHandlers.end() != mHandlers.find(data->window.windowID)) {
            //     mHandlers.at(data->window.windowID)->OnEvent(event);
            // }
            if(auto iter = mHandlers.find(data->window.windowID);
                mHandlers.end() != iter) {
                iter->second->OnEvent(event);
            }
        } else {
            switch (event.Type()) {
                case Event::EventType::Init : {
                    result = Setup();
                    mScene->OnEvent(event);
                    mHandlers[mScene->Id()] = mScene.get();
                }break;
                default : break;
            }
        }
    }
    OnUpdate();
    return result;
}

auto SDLSandboxApplication::Setup() -> bool {
    if (SetupWindowAndRenderer()) {
        mImGui = std::make_unique<::cgl::sandbox::imgui::IMGuiSDLRenderer>(
            mArguments,
            static_cast<SDL_Window*>(
                mWindowGroupMap[mMainWindow].mWindow->Get()),
            static_cast<SDL_Renderer*>(
                mWindowGroupMap[mMainWindow].mRenderer->Get()));
        if (LoadImages()) {
            auto dimensions = mTexture->GetDimensions();
            ::cgl::display::Rect src{0, 1, mTerra.width, mTerra.height};
            ::cgl::display::Rect dest{0, 1, mTerra.width, mTerra.height};
            mCommandQueue.push(
                std::make_unique<Command::SDLRendererCopyCommand>(
                *mWindowGroupMap[mMainWindow].mRenderer,
                RenderOperation::CopyTexture, *mBackground));
            mCommandQueue.push(
                std::make_unique<Command::SDLRendererCopyCommand>(
                *mWindowGroupMap[mMainWindow].mRenderer,
                RenderOperation::CopyTextureRect, *mTexture, src, dest));
            mUpdateRequested = true;
            mWindowGroupMap[mMainWindow].mWindow->Visible(true);
            mScene = std::make_unique<Display::L01Scene>();
            mImGui->Register(this);
            return true;
        }
        return false;
    }
    return false;
}

auto SDLSandboxApplication::SetupWindowAndRenderer() -> bool {
    auto window = std::make_unique<Display::SDLWindow>(
        GetStringProperty("name", mArguments),
        GetIntegerProperty("top", mArguments),
        GetIntegerProperty("left", mArguments),
        GetIntegerProperty("width", mArguments),
        GetIntegerProperty("height", mArguments),
        GetIntegerProperty("sdl_window_flags", mArguments));
    // auto windowId = window->GetId();
    mMainWindow = window->GetId();
    mWindowGroupMap[mMainWindow].mWindow = std::move(window);
    mWindowGroupMap[mMainWindow].mRenderer =
        std::make_unique<Display::SDLRenderer>(
            mMainWindow, -1, SDL_RENDERER_ACCELERATED);
    return ((nullptr != mWindowGroupMap[mMainWindow].mRenderer) &&
        (nullptr != mWindowGroupMap[mMainWindow].mWindow));
}

auto SDLSandboxApplication::LoadImages() -> bool {
    // mLog.Push(::cgl::log::ILog::Severity::Debug,
    //     ::cgl::log::ILog::Category::Input,
    //     "Setting up SDLSandboxApplication");
    mLog.Push("Setting up SDLSandboxApplication");
    constexpr auto backgroundImage{"res/img/paper.png"};
    constexpr auto spriteImage{"res/img/Terra.png"};

    Display::Color colorKey{0x00, 0x80, 0x80, 0x00};

    mBackground = std::make_unique<Display::SDLTexture>();
    mTexture = std::make_unique<Display::SDLTexture>();

   
    if (static_cast<int>(Code::NoError) !=
        mBackground->Load(backgroundImage,
            *mWindowGroupMap[mMainWindow].mRenderer,
            colorKey).value()) {
        return false;
    }
    if (static_cast<int>(Code::NoError) !=
        mTexture->Load(spriteImage,
            *mWindowGroupMap[mMainWindow].mRenderer,
            colorKey).value()) {
        return false;
    }
    // mLog.Push(::cgl::log::ILog::Severity::Debug,
    //     ::cgl::log::ILog::Category::Input,
    //     std::string("Loaded : ") + backgroundImage);
    mLog.Push(std::string("Loaded : ") + backgroundImage);
    auto dimensions = mBackground->GetDimensions();
    mWindowGroupMap[mMainWindow].mWindow->SetSize(
        std::get<0>(dimensions), std::get<1>(dimensions));
    mTerra.texture.Load(spriteImage,
        *mWindowGroupMap[mMainWindow].mRenderer,
        colorKey);
    mTerra.width = 30;
    mTerra.height = 48;
    mTerra.indices = {0, 32, 64, 96, 128, 160, 192, 224};
    return true;
}

auto SDLSandboxApplication::OnKeyDownEvent(const SDL_KeyboardEvent& event)
     -> bool {
    int index{0};
    switch(event.keysym.sym) {
        case  SDLK_SPACE : {
            ::SDL_Log("SPACE");
            auto dimensions = mTexture->GetDimensions();
            ::cgl::display::Rect src{0, 1, mTerra.width, mTerra.height};
            ::cgl::display::Rect dest{0, 1, mTerra.width, mTerra.height};
            mCommandQueue.push(
                std::make_unique<Command::SDLRendererCopyCommand>(
                *mWindowGroupMap[mMainWindow].mRenderer,
                RenderOperation::CopyTexture, *mBackground, src, dest));
            mUpdateRequested = true;
        }break;
        case  SDLK_1 : {
            index = 0;
            ::SDL_Log("INDEX %d", index);
            UpdateSprite(index);
        } break;
        case  SDLK_2 : {
            index = 1;
            ::SDL_Log("INDEX %d", index);
            UpdateSprite(index);
        } break;
        case  SDLK_3 : {
            index = 2;
            ::SDL_Log("INDEX %d", index);
            UpdateSprite(index);
        } break;
        case  SDLK_4 : {
            index = 3;
            ::SDL_Log("INDEX %d", index);
            UpdateSprite(index);
        } break;
        case  SDLK_5 : {
            index = 4;
            ::SDL_Log("INDEX %d", index);
            UpdateSprite(index);
        } break;
        case  SDLK_6 : {
            index = 5;
            ::SDL_Log("INDEX %d", index);
            UpdateSprite(index);
        } break;
        case  SDLK_7 : {
            index = 6;
            ::SDL_Log("INDEX %d", index);
            UpdateSprite(index);
        } break;
        case  SDLK_8 : {
            index = 7;
            ::SDL_Log("INDEX %d", index);
            UpdateSprite(index);
        } break;
        default:break;
    }
    return true;
}

auto SDLSandboxApplication::OnUpdate() -> void {
    // if (mUpdateRequested) {
        mCommandQueue.push(
            std::make_unique<::cgl::application::sandbox::imgui::IMGuiCommand>(*mImGui));
        mCommandQueue.push(
            std::make_unique<Command::SDLRendererCommand>(
                *mWindowGroupMap[mMainWindow].mRenderer,
            RenderOperation::Present));
        while(!mCommandQueue.empty()) {
            mCommandQueue.front()->Execute();
            mCommandQueue.pop();
        }
        mScene->OnUpdate();
        mUpdateRequested = false;
    // }
}

auto SDLSandboxApplication::UpdateSprite(int index) -> void {
    Display::Rect src{mTerra.indices[index], 1, mTerra.width, mTerra.height};
    Display::Rect dest{0, 1, mTerra.width, mTerra.height};
    
    mCommandQueue.push(
        std::make_unique<Command::SDLRendererCopyCommand>(
            *mWindowGroupMap[mMainWindow].mRenderer,
            RenderOperation::CopyTexture, *mBackground, src, dest));
    mCommandQueue.push(
        std::make_unique<Command::SDLRendererCopyCommand>(
            *mWindowGroupMap[mMainWindow].mRenderer,
            RenderOperation::CopyTextureRect, *mTexture, src, dest));
    mUpdateRequested = true;
}

auto SDLSandboxApplication::OnClearColorChange(std::vector<int>& clearColor)
    -> void {
    ::SDL_Log("Clear color : %d-%d-%d",
        clearColor[0], clearColor[1], clearColor[2]);
    mCommandQueue.push(
        std::make_unique<Command::SDLRendererCommand>(
            *mWindowGroupMap[mMainWindow].mRenderer,
        RenderOperation::SetDrawColor,
        SDL_Color{
            static_cast<std::uint8_t>(clearColor[0]),
            static_cast<std::uint8_t>(clearColor[1]),
            static_cast<std::uint8_t>(clearColor[2]),
            255}));
    mCommandQueue.push(
        std::make_unique<Command::SDLRendererCommand>(
            *mWindowGroupMap[mMainWindow].mRenderer,
        RenderOperation::Clear));
    mUpdateRequested = true;
}

auto SDLSandboxApplication::OnModulationColorChange(std::vector<int>& modulationColor)
    -> void {
    ::SDL_Log("Modulation color : %d-%d-%d",
        modulationColor[0], modulationColor[1], modulationColor[2]);
    mTexture->SetColorModulation(modulationColor[0],
        modulationColor[1], modulationColor[2]);
    UpdateSprite(0);
    mUpdateRequested = true;
}

}  // namespace sandbox
}  // namespace application
}  // namespace cgl
