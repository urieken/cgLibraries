/**
 * @file L01Scene.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for lesson 01 scene
 * @version 0.1
 * @date 2022-01-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef CGL_LIBRARY_SANDBOX_INCLUDE_DISPLAY_L01SCENE_HPP_
#define CGL_LIBRARY_SANDBOX_INCLUDE_DISPLAY_L01SCENE_HPP_

#include <display/IScene.hpp>

#include <command/ICommand.hpp>
#include <display/IRenderer.hpp>
#include <display/IWindow.hpp>
#include <event/IEvent.hpp>

#include <cstdint>
#include <memory>
#include <queue>

#include <SDL2/SDL.h>

namespace cgl {
namespace display {
/**
 * @brief Scene class for lesson 01
 */
class L01Scene final : public IScene {
public:
    L01Scene();
    virtual ~L01Scene();
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
     * @brief Get the scene id.
     * 
     * @return std::uint32_t The scene id.
     */
    auto Id() const -> std::uint32_t override;
private:
    /**
     * @brief The window for the scene.
     */
    std::unique_ptr<::cgl::display::IWindow> mWindow;
    /**
     * @brief The window renderer.
     */
    std::unique_ptr<::cgl::display::IRenderer> mRenderer;
    /**
     * @brief The scene command queue.
     */
    std::queue<std::unique_ptr<::cgl::command::ICommand>> mCommandQueue;
    /**
     * @brief Setup the window and renderer.
     * 
     * @return true On success.
     * @return false On failure.
     */
    auto Setup() -> bool;
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

#endif//CGL_LIBRARY_SANDBOX_INCLUDE_DISPLAY_L01SCENE_HPP_