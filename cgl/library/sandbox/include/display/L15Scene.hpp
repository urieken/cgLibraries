/**
 * @file L15Scene.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for lesson 15 scene
 * @version 0.1
 * @date 2022-01-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef CGL_LIBRARY_SANDBOX_INCLUDE_DISPLAY_L15SCENE_HPP_
#define CGL_LIBRARY_SANDBOX_INCLUDE_DISPLAY_L15SCENE_HPP_

#include <display/SandboxScene.hpp>

#include <command/ICommand.hpp>
#include <command/SDLRendererCommand.hpp>
#include <display/IRenderer.hpp>
#include <display/ITexture.hpp>
#include <display/IWindow.hpp>
#include <event/IEvent.hpp>
#include <event/ITimer.hpp>

#include <chrono>
#include <cstdint>
#include <memory>
#include <queue>

#include <SDL2/SDL.h>

namespace cgl {
namespace display {
/**
 * @brief Scene class for lesson 15
 */
class L15Scene final : public SandboxScene {
public:
    L15Scene() = delete;
    /**
     * @brief Construct a new L15Scene object
     * 
     * @param event Event type for this scene.
     */
    explicit L15Scene(const std::uint32_t& event);
    /**
     * @brief Construct a new L15Scene object
     * 
     * @param event Event type for this scene.
     * @param title The scene title.
     * @param rect The scene dimensions.
     */
    L15Scene(const std::uint32_t& event, const std::string& title,
        const Rect& rect);
    /**
     * @brief Destroy the L15Scene object
     */
    virtual ~L15Scene();
    /**
     * @brief Handle events.
     * 
     * @param event The event to be handled.
     * @return true The event was processed.
     * @return false An error has occurred or quit the application.
     */
    auto OnEvent(const ::cgl::event::IEvent& event) -> bool override;
    /**
     * @brief Update the scene.
     */
    auto OnUpdate() -> void override;
    /**
     * @brief Timer callback
     */
    auto OnTimer() -> void;
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
    std::int64_t mFrame;
    /**
     * @brief The start time.
     */
    std::chrono::time_point<std::chrono::steady_clock> mStartTime;
    /**
     * @brief The end time.
     */
    std::chrono::time_point<std::chrono::steady_clock> mEndTime;
};
}  // namespace display
}  // namespace cgl

#endif//CGL_LIBRARY_SANDBOX_INCLUDE_DISPLAY_L15SCENE_HPP_