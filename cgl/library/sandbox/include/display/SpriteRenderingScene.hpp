/**
 * @file SpriteRenderingScene.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for sprite rendering scene
 * @version 0.1
 * @date 2022-01-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef CGL_LIBRARY_SANDBOX_INCLUDE_DISPLAY_SPRITE_RENDERING_SCENE_HPP_
#define CGL_LIBRARY_SANDBOX_INCLUDE_DISPLAY_SPRITE_RENDERING_SCENE_HPP_

#include <display/SandboxScene.hpp>

#include <command/ICommand.hpp>
#include <command/SDLRendererCommand.hpp>
#include <display/IRenderer.hpp>
#include <display/ITexture.hpp>
#include <display/IWindow.hpp>
#include <display/SDLTexture.hpp>
#include <display/Rect.hpp>
#include <event/IEvent.hpp>
#include <event/ITimer.hpp>

#include <chrono>
#include <cstdint>
#include <memory>
#include <queue>
#include <vector>

#include <SDL2/SDL.h>

constexpr auto SPRITE_RENDERING_SCENE_TITLE{"Sprite rendering scene"};

namespace cgl {
namespace display {
/**
 * @brief The spritesheet wrapper.
 */
struct SpriteSheet {
    /**
     * @brief The spritesheet texture.
     */
    SDLTexture texture;
    /**
     * @brief The sprite rectangles.
     */
    std::vector<Rect> rectangles;
};
/**
 * @brief Scene class for sprite rendering
 */
class SpriteRenderingScene final : public SandboxScene {
public:
    SpriteRenderingScene() = delete;
    /**
     * @brief Construct a new SpriteRenderingScene object
     * 
     * @param event Event type for this scene.
     */
    explicit SpriteRenderingScene(const std::uint32_t& event);
    /**
     * @brief Construct a new SpriteRenderingScene object
     * 
     * @param event Event type for this scene.
     * @param title The scene title.
     * @param rect The scene dimensions.
     */
    SpriteRenderingScene(const std::uint32_t& event, const std::string& title,
        const Rect& rect);
    /**
     * @brief Destroy the SpriteRenderingScene object
     */
    virtual ~SpriteRenderingScene();
    /**
     * @brief Handle events.
     * 
     * @param event The event to be handled.
     * @return true The event was processed.
     * @return false An error has occurred or quit the application.
     */
    auto OnEvent(const ::cgl::event::IEvent& event) -> bool override;
    /**
     * @brief Timer callback
     */
    auto OnTimer() -> void;
    /**
     * @brief Update the scene.
     */
    auto OnUpdate() -> void override;
private:
    /**
     * @brief The test texture.
     */
    std::unique_ptr<::cgl::display::ITexture> mTexture;
    /**
     * @brief The test timer.
     */
    std::unique_ptr<::cgl::event::ITimer> mTimer;
    /**
     * @brief The frame counter.
     */
    int mFrameCount;
    /**
     * @brief Frames per second.
     */
    float mFPS;
    /**
     * @brief The current frame.
     */
    int mFrame;
    /**
     * @brief The step to the next frame.
     */
    int mStep;
    /**
     * @brief The initial spritesheet.
     */
    SpriteSheet mSpriteSheet;
    /**
     * @brief The start time.
     */
    std::chrono::time_point<std::chrono::steady_clock> mStartTime;
    /**
     * @brief The end time.
     */
    std::chrono::time_point<std::chrono::steady_clock> mEndTime;
    /**
     * @brief Handle keyboard press events
     * 
     * @param event The SDL keyboard event.
     * @return true The event was processed.
     * @return false An error has occurred or quit the application.
     */
    auto OnKeyDownEvent(const SDL_KeyboardEvent& event) -> bool;
};
}  // namespace display
}  // namespace cgl

#endif//CGL_LIBRARY_SANDBOX_INCLUDE_DISPLAY_SPRITE_RENDERING_SCENE_HPP_