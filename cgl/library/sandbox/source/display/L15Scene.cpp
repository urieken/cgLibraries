/**
 * @file L15Scene.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Source for lesson 15
 * @version 0.1
 * @date 2022-01-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "display/Rect.hpp"
#include <SDL2/SDL_error.h>
#include <display/L15Scene.hpp>

#include <command/SDLRendererCommand.hpp>
#include <command/SDLRendererCopyCommand.hpp>
#include <display/SDLRenderer.hpp>
#include <display/SDLTexture.hpp>
#include <display/SDLWindow.hpp>
#include <error/CGLError.hpp>
#include <imgui/IMGuiSDLRenderer.hpp>

#include <memory>
#include <stdexcept>

namespace Command = ::cgl::command;
namespace Display = ::cgl::display;
namespace Error = ::cgl::error;
namespace Event = ::cgl::event;
namespace ImGui = ::cgl::sandbox::imgui;

using Code = Error::ErrorCode;
using ImGuiEvent = ImGui::IMGuiSDLRenderer::ImGuiEvent;
using RenderOperation = Command::SDLRendererCommand::Operation;

namespace cgl {
namespace display {

constexpr auto TITLE{"LESSON_15"};
constexpr auto TOP{421};
constexpr auto LEFT{1281};
constexpr auto WIDTH{150};
constexpr auto HEIGHT{150};

L15Scene::L15Scene(const std::uint32_t& event) :
    L15Scene{event, TITLE, {TOP, LEFT, WIDTH, HEIGHT}}{
}

L15Scene::L15Scene(const std::uint32_t& event,
    const std::string& title, const Rect& rect) :
    SandboxScene{event, title, rect},
    mTexture{nullptr} {}


auto L15Scene::OnEvent(const Event::IEvent &event) -> bool {
    if (Event::EventSource::SDL == event.Source()) {
        auto data = static_cast<const SDL_Event*>(event.Data());
        switch(data->type) {
            default:{
                if ((EventType() == data->type) &&
                   (Id() == data->window.windowID)) {
                    switch(static_cast<ImGuiEvent>(data->user.code)) {
                        case ImGuiEvent::LoadImages : {
                            ::SDL_Log("Load images recieved");
                            constexpr auto spriteImageFile{"res/img/Terra.png"};
                            Display::Color colorKey{0x00, 0x80, 0x80, 0x00};

                            mTexture = std::make_unique<Display::SDLTexture>();
                            auto error = mTexture->Load(spriteImageFile,
                                *GetRenderer(), colorKey);
                            if(static_cast<int>(Code::NoError) == error.value()){
                                auto commands = CommandQueue();
                                // Display::Rect src{0, 1,
                                //     std::get<0>(mTexture->GetDimensions()),
                                //     std::get<1>(mTexture->GetDimensions())};
                                // Display::Rect dest{0, 1,
                                //     std::get<0>(mTexture->GetDimensions()),
                                //     std::get<1>(mTexture->GetDimensions())};
                                Display::Rect src{0, 1, 30, 48};
                                Display::Rect dest{0, 1, 30, 48};
                                ::SDL_Log("Rect %d:%d:%d:%d",
                                    src.top, src.left, src.width, src.height);
                                commands->push(
                                    std::make_unique<Command::SDLRendererCopyCommand>(
                                        *GetRenderer(),
                                        RenderOperation::CopyTextureRect, *mTexture,
                                        src, dest));
                                commands->push(
                                    std::make_unique<Command::SDLRendererCommand>(
                                        *GetRenderer(),
                                        RenderOperation::Present));
                            } else {
                                ::SDL_Log("Failed to load %s - %s - %s",
                                    spriteImageFile, ::SDL_GetError(),
                                    error.message().c_str());
                            }
                        } break;
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

}  // namespace display
}  // namespace cgl
