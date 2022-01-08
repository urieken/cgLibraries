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

#include <SDL2/SDL_events.h>
#include <imgui/IMGuiSDLRenderer.hpp>
#include <application/SDLSandboxApplication.hpp>

#include <command/SDLRendererCommand.hpp>
#include <command/SDLRendererCopyCommand.hpp>
#include <command/SDLRendererGeometryCommand.hpp>
#include <command/SDLRendererViewportCommand.hpp>
#include <display/Color.hpp>
#include <display/SDLRenderer.hpp>
#include <display/SDLTexture.hpp>
#include <display/SDLWindow.hpp>
#include <geometry/Line.hpp>
#include <geometry/Point.hpp>
#include <geometry/Rectangle.hpp>
#include <error/CGLError.hpp>
#include <event/CoreEvent.hpp>

#include <memory>
#include <sstream>
#include <utility>
#include <vector>

namespace Command = ::cgl::command;
namespace Display = ::cgl::display;
namespace Error = ::cgl::error;
namespace Event = ::cgl::event;
namespace Geometry = ::cgl::geometry;
namespace System = ::cgl::system;

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
    SDLApplication{args},
    mArguments{args},
    mWindow{nullptr},
    mRenderer{nullptr},
    mRendererCommands{},
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
            mUpdateRequested = mImGui->OnEvent(data);
            mImGui->OnUpdate(static_cast<SDL_Window*>(mWindow->Get()));
            switch(data->type) {
                case SDL_KEYDOWN : {
                    result = OnKeyDownEvent(data->key);
                }break;
                case SDL_MOUSEMOTION:
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP: {
                    mUpdateRequested = true;
                }break;
                default : break;
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
    if (SetupWindowAndRenderer()) {
        mImGui = std::make_unique<::cgl::sandbox::imgui::IMGuiSDLRenderer>(
            mArguments,
            static_cast<SDL_Window*>(mWindow->Get()),
            static_cast<SDL_Renderer*>(mRenderer->Get()));
        if (LoadImages()) {
            auto dimensions = mTexture->GetDimensions();
            ::cgl::display::Rect src{0, 1, mTerra.width, mTerra.height};
            ::cgl::display::Rect dest{0, 1, mTerra.width, mTerra.height};
            mRendererCommands.push_back(   
                std::make_unique<Command::SDLRendererCopyCommand>(*mRenderer,
                    RenderOperation::CopyTexture, *mBackground));
            mRendererCommands.push_back(   
                std::make_unique<Command::SDLRendererCopyCommand>(*mRenderer,
                    RenderOperation::CopyTextureRect, *mTexture, src, dest));
            mUpdateRequested = true;
            mWindow->Visible(true);
        }
        return true;
    }
    return false;
}

auto SDLSandboxApplication::SetupWindowAndRenderer() -> bool {
    mWindow = std::make_unique<Display::SDLWindow>(
        GetStringProperty("name", mArguments),
        GetIntegerProperty("top", mArguments),
        GetIntegerProperty("left", mArguments),
        GetIntegerProperty("width", mArguments),
        GetIntegerProperty("height", mArguments),
        GetIntegerProperty("sdl_window_flags", mArguments));
    if (nullptr == mWindow) {
        return false;
    }
    mRenderer = std::make_unique<Display::SDLRenderer>(
        mWindow->GetId(), -1, SDL_RENDERER_ACCELERATED);
    return nullptr != mRenderer;
}

auto SDLSandboxApplication::LoadImages() -> bool {
    ::SDL_Log("Setting up SDLSandboxApplication");
    constexpr auto backgroundImage{"res/img/paper.png"};
    constexpr auto spriteImage{"res/img/Terra.png"};

    Display::Color colorKey{0x00, 0x80, 0x80, 0x00};

    mBackground = std::make_unique<Display::SDLTexture>();
    mTexture = std::make_unique<Display::SDLTexture>();
   
    if (static_cast<int>(Code::NoError) !=
        mBackground->Load(backgroundImage, *mRenderer, colorKey).value()) {
        return false;
    }
    if (static_cast<int>(Code::NoError) !=
        mTexture->Load(spriteImage, *mRenderer, colorKey).value()) {
        return false;
    }
    ::SDL_Log("Loaded %s", backgroundImage);
    auto dimensions = mBackground->GetDimensions();
    mWindow->SetSize(std::get<0>(dimensions), std::get<1>(dimensions));
    mTerra.texture.Load(spriteImage, *mRenderer, colorKey);
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
            mRendererCommands.push_back(
                std::make_unique<Command::SDLRendererCopyCommand>(*mRenderer,
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
    auto drawColor = mImGui->DrawColor();
    // ::SDL_SetRenderDrawColor(static_cast<SDL_Renderer*>(mRenderer->Get()),
    //     drawColor[0], drawColor[1], drawColor[2], 255);
    // ::SDL_RenderClear(static_cast<SDL_Renderer*>(mRenderer->Get()));
    // mImGui->OnUpdate(static_cast<SDL_Window*>(mWindow->Get()));
    if (mUpdateRequested) {
        mRendererCommands.push_back(
            std::make_unique<Command::SDLRendererCommand>(*mRenderer,
            RenderOperation::Present));
        mUpdateRequested = false;
        for (auto& command : mRendererCommands) {
            command->Execute();
        }
        mRendererCommands.clear();
    }
    // mImGui->OnUpdate(static_cast<SDL_Window*>(mWindow->Get()));
    // ::SDL_RenderPresent(static_cast<SDL_Renderer*>(mRenderer->Get()));
}

auto SDLSandboxApplication::UpdateSprite(int index) -> void {
    Display::Rect src{mTerra.indices[index], 1, mTerra.width, mTerra.height};
    Display::Rect dest{0, 1, mTerra.width, mTerra.height};
    
    mRendererCommands.push_back(   
        std::make_unique<Command::SDLRendererCopyCommand>(*mRenderer,
            RenderOperation::CopyTexture, *mBackground, src, dest));
    mRendererCommands.push_back(   
        std::make_unique<Command::SDLRendererCopyCommand>(*mRenderer,
            RenderOperation::CopyTextureRect, *mTexture, src, dest));
    mUpdateRequested = true;
}


}  // namespace sandbox
}  // namespace application
}  // namespace cgl
