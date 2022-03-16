/**
 * @file SpriteRenderingScene.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Source for sprite rendering scene
 * @version 0.1
 * @date 2022-01-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <display/SpriteRenderingScene.hpp>

#include <command/SDLRendererCommand.hpp>
#include <command/SDLRendererCopyCommand.hpp>
#include <display/SDLRenderer.hpp>
#include <display/SDLTexture.hpp>
#include <display/SDLWindow.hpp>
#include <error/CGLError.hpp>
#include <event/SDLTimer.hpp>
#include <imgui/IMGuiSDLRenderer.hpp>

#include <bitset>
#include <memory>
#include <stdexcept>
#include <system_error>

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

constexpr auto TOP{421};
constexpr auto LEFT{1281};
constexpr auto WIDTH{150};
constexpr auto HEIGHT{150};

auto callBack(std::uint32_t interval, void* arg) -> std::uint32_t {
    reinterpret_cast<SpriteRenderingScene*>(arg)->OnTimer();
    return 0;
}

auto SpriteRenderingScene::OnTimer() -> void {
    ::SDL_Log("%s", __PRETTY_FUNCTION__);
}

SpriteRenderingScene::SpriteRenderingScene(const std::uint32_t& event) :
    SpriteRenderingScene{event, SPRITE_RENDERING_SCENE_TITLE,
        {TOP, LEFT, WIDTH, HEIGHT}}{
    ::SDL_Log("STOPPED : %d",
        static_cast<int>(::cgl::event::TimerState::Stopped));
    ::SDL_Log("STOPPED : %d",
        static_cast<int>(::cgl::event::TimerState::Started));
    ::SDL_Log("STOPPED : %d",
        static_cast<int>(::cgl::event::TimerState::Paused));
    ::SDL_Log("UNKNWON : %d",
        static_cast<int>(::cgl::event::TimerState::Unknown));
}

SpriteRenderingScene::SpriteRenderingScene(const std::uint32_t& event,
    const std::string& title, const Rect& rect) :
    SandboxScene{event, title, rect},
    mTexture{nullptr},
    mTimer{std::make_unique<Event::SDLTimer>()},
    mFrameCount{0}, mFPS{0.0f}, mFrame{0} {}

SpriteRenderingScene::~SpriteRenderingScene() {
    mTimer->Stop();
}

auto SpriteRenderingScene::OnEvent(const Event::IEvent &event) -> bool {
    ::SDL_Log("%s", __PRETTY_FUNCTION__);
    if (Event::EventSource::SDL == event.Source()) {
        auto data = static_cast<const SDL_Event*>(event.Data());
        switch(data->type) {
            case SDL_KEYDOWN : {
                switch(data->key.keysym.sym) {
                    case  SDLK_SPACE : {
                        ::SDL_Log("SPACE");
                        // ::SDL_Log("SECONDS : %f",
                        //     mTimer->GetTicks() / 1000.0f);
                            // mFPS = mFrameCount / (mTimer->GetTicks() / 1000.0f);
                            // if (mFPS > 2000000) {
                            //     mFPS = 0.0f;
                            // }
                            // ::SDL_Log("FRAME COUNT : %d, FRAME RATE : %f",
                            //     mFrameCount, mFPS);
                    }break;
                    default:break;
                }
            }break;
            default:{
                if ((EventType() == data->type) &&
                   (Id() == data->window.windowID)) {
                    switch(static_cast<ImGuiEvent>(data->user.code)) {
                        case ImGuiEvent::LoadImages : {
                            ::SDL_Log("Load images recieved");
                            constexpr auto spriteImageFile{"res/img/Terra.png"};
                            Display::Color colorKey{0x00, 0x80, 0x80, 0x00};

                            mTexture =
                                std::make_unique<Display::SDLTexture>(spriteImageFile);
                            auto error = mTexture->Create(*GetRenderer(), colorKey);
                            if(static_cast<int>(Code::NoError) == error.value()){
                                auto commands = CommandQueue();
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
                        case ImGuiEvent::StartTimer : {
                            ::SDL_Log("%s", __PRETTY_FUNCTION__);
                            ::SDL_Log("Start timer");
                            // mFrameCount = 0;
                            mTimer->Start();
                            mStartTime = std::chrono::steady_clock::now();
                        }break;
                        case ImGuiEvent::StopTimer : {
                            ::SDL_Log("%s", __PRETTY_FUNCTION__);
                            ::SDL_Log("Stop timer");
                            mTimer->Stop();
                        }break;
                        case ImGuiEvent::PauseTimer : {
                            ::SDL_Log("%s", __PRETTY_FUNCTION__);
                            ::SDL_Log("Pause timer");
                            // if(mTimer->IsStarted()) {
                            //     mTimer->Pause();
                            // }
                        }break;
                        case ImGuiEvent::ResumeTimer : {
                            ::SDL_Log("%s", __PRETTY_FUNCTION__);
                            ::SDL_Log("Resume timer");
                            // if(mTimer->IsStarted()) {
                            //     mTimer->Resume();
                            // }
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

auto SpriteRenderingScene::OnUpdate() -> void {
    // ::SDL_Log("%s", __PRETTY_FUNCTION__);
    auto time = mTimer->GetTicks() / 1000.0f;
    mEndTime = std::chrono::steady_clock::now();
    auto diff = mEndTime - mStartTime;
    auto seconds = diff / std::chrono::seconds(1);
    // 0.041 - 24
    // 0.016 - 60
    if (mTimer->IsStarted()) {
        // auto frame = diff / std::chrono::milliseconds(410);
        // auto frame = diff / std::chrono::milliseconds(1);
        auto frame = diff / std::chrono::seconds(1);
        if (frame != mFrame) {
            mFrame = frame;
            mFrameCount++;
            ::SDL_Log("mFrameCount : %d", mFrameCount);
            // if (410 >= mFrame) {
            //     ::SDL_Log("frame : %ld, mFrame : %ld",
            //         frame, mFrame);
            // }
            if(24 <= mFrameCount) {
                mFrameCount = 0;
            }
        }
        // if (10 > seconds) {
        //     // mStartTime = std::chrono::steady_clock::now();
        //     ::SDL_Log("%ld", diff / std::chrono::milliseconds(1));
        //     ::SDL_Log("%ld", diff / std::chrono::milliseconds(410));
        //     ::SDL_Log("%ld", diff / std::chrono::milliseconds(160));
        //     ::SDL_Log("%ld", diff / std::chrono::seconds(1));
        // }
    }
    
    // mFrameCount++;
    // if (50000 < mFrameCount) {
    //     mFrameCount = 0;
    // }
    // mFPS = mFrameCount / (mTimer->GetTicks() / 1000.0f);
    // if (mFPS > 2000000) {
    //     mFPS = 0.0f;
    // }
    // ::SDL_Log("FRAME COUNT : %d, FRAME RATE : %f", mFrameCount, mFPS);
    // ::SDL_Log("SECONDS : %f", mTimer->GetTicks() / 1000.0f);
}

}  // namespace display
}  // namespace cgl
