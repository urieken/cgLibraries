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
#include <display/SDLRenderer.hpp>
#include <display/SDLTexture.hpp>
#include <display/SDLWindow.hpp>
#include <geometry/Line.hpp>
#include <geometry/Point.hpp>
#include <geometry/Rectangle.hpp>
#include <error/CGLError.hpp>
#include <event/CoreEvent.hpp>

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
    mTexture{nullptr} {
}

auto SDLSandboxApplication::OnEvent(
    const ::cgl::event::IEvent& event) -> bool {
    bool result{true};
    if (result = SDLApplication::OnEvent(event); true == result) {
        if (Event::EventSource::SDL == event.Source()) {
            auto data = static_cast<const SDL_Event*>(event.Data());
            switch(data->type) {
                case SDL_KEYDOWN : {
                    result = OnKeyDownEvent(data->key);
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
    ::SDL_Log("Setting up SDLSandboxApplication");
    // constexpr auto file{"res/img/2387345452.png"};
    // constexpr auto file{"res/img/paper.png"};
    // constexpr auto file{"res/img/Terra.png"};
    constexpr auto file{"res/img/Celes_Chere.png"};
    mWindow = std::make_unique<Display::SDLWindow>(
        GetStringProperty("name", mArguments),
        GetIntegerProperty("top", mArguments),
        GetIntegerProperty("left", mArguments),
        GetIntegerProperty("width", mArguments),
        GetIntegerProperty("height", mArguments),
        GetIntegerProperty("sdl_window_flags", mArguments));
    mRenderer = std::make_unique<Display::SDLRenderer>(
        mWindow->GetId(), -1, SDL_RENDERER_ACCELERATED);
    mTexture = std::make_unique<Display::SDLTexture>();
    if (static_cast<int>(Code::NoError) !=
        mTexture->Load(file, *mRenderer, {0x00, 0x80, 0x80, 0x00}).value()) {
        return false;
    }
    ::SDL_Log("Loaded %s", file);
    auto dimensions = mTexture->GetDimensions();
    mWindow->SetSize(std::get<0>(dimensions), std::get<1>(dimensions));
    return true;
}

auto SDLSandboxApplication::OnKeyDownEvent(const SDL_KeyboardEvent& event)
     -> bool {
    switch(event.keysym.sym) {
        case SDLK_v : {
            ::SDL_Log("Setting viewport");
            mRendererCommands.push_back(
                std::make_unique<Command::SDLRendererViewportCommand>(*mRenderer,
                RenderOperation::SetViewport,
                Display::Viewport{010, Display::Rect{100, 100, 200, 200}}));
        } break;
        case SDLK_r : {
            mRendererCommands.push_back(
                std::make_unique<Command::SDLRendererCommand>(*mRenderer,
                RenderOperation::SetDrawColor,
                SDL_Color{255, 0, 0, 255}));
            mRendererCommands.push_back(
                std::make_unique<Command::SDLRendererCommand>(*mRenderer,
                RenderOperation::Clear));
            mUpdateRequested = true;
        } break;
        case SDLK_g : {
            mRendererCommands.push_back(
                std::make_unique<Command::SDLRendererCommand>(*mRenderer,
                RenderOperation::SetDrawColor,
                SDL_Color{0, 255, 0, 255}));
            mRendererCommands.push_back(
                std::make_unique<Command::SDLRendererCommand>(*mRenderer,
                RenderOperation::Clear));
            mUpdateRequested = true;
        } break;
        case SDLK_b : {
            mRendererCommands.push_back(
                std::make_unique<Command::SDLRendererCommand>(*mRenderer,
                RenderOperation::SetDrawColor,
                SDL_Color{0, 0, 255, 255}));
            mRendererCommands.push_back(
                std::make_unique<Command::SDLRendererCommand>(*mRenderer,
                RenderOperation::Clear));
            mUpdateRequested = true;
        } break;
        case SDLK_c : {
            mRendererCommands.push_back(
                std::make_unique<Command::SDLRendererCopyCommand>(*mRenderer,
                RenderOperation::CopyTexture, *mTexture));
            mUpdateRequested = true;
        } break;
        case SDLK_UP : {
            ::SDL_Log("UP");
            mRendererCommands.push_back(
                std::make_unique<Command::SDLRendererCommand>(*mRenderer,
                RenderOperation::Clear));
            Display::Rect rect{390, 0, 500, 500};
            mRendererCommands.push_back(
                std::make_unique<Command::SDLRendererCopyCommand>(*mRenderer,
                RenderOperation::CopyTextureRect, *mTexture, rect, rect));
            mUpdateRequested = true;
        } break;
        case SDLK_DOWN : {
            ::SDL_Log("DOWN");
            mRendererCommands.push_back(
                std::make_unique<Command::SDLRendererCommand>(*mRenderer,
                RenderOperation::Clear));
            Display::Rect rect{390, 220, 500, 500};
            mRendererCommands.push_back(
                std::make_unique<Command::SDLRendererCopyCommand>(*mRenderer,
                RenderOperation::CopyTextureRect, *mTexture, rect, rect));
            mUpdateRequested = true;
        } break;
        case SDLK_LEFT : {
            ::SDL_Log("LEFT");
            mRendererCommands.push_back(
                std::make_unique<Command::SDLRendererCommand>(*mRenderer,
                RenderOperation::Clear));
            Display::Rect rect{0, 110, 500, 500};
            mRendererCommands.push_back(
                std::make_unique<Command::SDLRendererCopyCommand>(*mRenderer,
                RenderOperation::CopyTextureRect, *mTexture, rect, rect));
            mUpdateRequested = true;
        } break;
        case SDLK_RIGHT : {
            ::SDL_Log("RIGHT");
            mRendererCommands.push_back(
                std::make_unique<Command::SDLRendererCommand>(*mRenderer,
                RenderOperation::Clear));
            Display::Rect rect{780, 110, 500, 500};
            mRendererCommands.push_back(
                std::make_unique<Command::SDLRendererCopyCommand>(*mRenderer,
                RenderOperation::CopyTextureRect, *mTexture, rect, rect));
            mUpdateRequested = true;
        } break;
        case SDLK_p : {
            mRendererCommands.push_back(
                std::make_unique<Command::SDLRendererCommand>(*mRenderer,
                RenderOperation::SetDrawColor,
                SDL_Color{0, 0, 0, 0}));
            mRendererCommands.push_back(
                std::make_unique<Command::SDLRendererCommand>(*mRenderer,
                RenderOperation::Clear));
            Geometry::Point point{100, 100, {255, 255, 255, 255}};
            mRendererCommands.push_back(
                std::make_unique<Command::SDLRendererGeometryCommand>(
                *mRenderer, RenderOperation::DrawPoint, point));
            mUpdateRequested = true;
        } break;
        case SDLK_l : {
            mRendererCommands.push_back(
                std::make_unique<Command::SDLRendererCommand>(*mRenderer,
                RenderOperation::SetDrawColor,
                SDL_Color{0, 0, 0, 0}));
            mRendererCommands.push_back(
                std::make_unique<Command::SDLRendererCommand>(*mRenderer,
                RenderOperation::Clear));
            Geometry::Line line{{100, 100}, {300, 300},
                {25, 50, 255, 255}};
            mRendererCommands.push_back(
                std::make_unique<Command::SDLRendererGeometryCommand>(
                *mRenderer, RenderOperation::DrawLine, line));
            mUpdateRequested = true;
        } break;
        case SDLK_f : {
            mRendererCommands.push_back(
                std::make_unique<Command::SDLRendererCommand>(*mRenderer,
                RenderOperation::SetDrawColor,
                SDL_Color{0, 50, 0, 255}));
            mRendererCommands.push_back(
                std::make_unique<Command::SDLRendererCommand>(*mRenderer,
                RenderOperation::Clear));

            Geometry::Rectangle rect{{780, 110}, {500, 500},
                {{25, 50, 255, 255}, {50, 150, 255, 255}}};
            mRendererCommands.push_back(
                std::make_unique<Command::SDLRendererGeometryCommand>(
                *mRenderer, RenderOperation::DrawFillRect, rect));
            mUpdateRequested = true;
        } break;
        case SDLK_d : {
            mRendererCommands.push_back(
                std::make_unique<Command::SDLRendererCommand>(*mRenderer,
                RenderOperation::SetDrawColor,
                SDL_Color{0, 50, 0, 255}));
            mRendererCommands.push_back(
                std::make_unique<Command::SDLRendererCommand>(*mRenderer,
                RenderOperation::Clear));

            Geometry::Rectangle rect{{0, 110}, {500, 500},
                {{50, 150, 255, 255}, {25, 50, 255, 255}}};
            mRendererCommands.push_back(
                std::make_unique<Command::SDLRendererGeometryCommand>(
                *mRenderer, RenderOperation::DrawRect, rect));
            mUpdateRequested = true;
        } break;
        default:break;
    }
    return true;
}

auto SDLSandboxApplication::OnUpdate() -> void {
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
}

}  // namespace sandbox
}  // namespace application
}  // namespace cgl
