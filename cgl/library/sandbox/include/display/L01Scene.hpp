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
    L01Scene() = delete;
    /**
     * @brief Construct a new L01Scene object
     * 
     * @param event Event type for this scene.
     */
    explicit L01Scene(const std::uint32_t& event);
    /**
     * @brief Destroy the L01Scene object
     */
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
    /**
     * @brief Show or hide the scene.
     * 
     * @param visible Scene visibility flag.
     */
    virtual auto Visible(bool visible) -> void override;
private:
    /**
     * @brief The scene event
     */
    std::uint32_t mSceneEvent;
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
    /**
     * @brief Handle window events
     * 
     * @param event The SDL window event.
     * @return true The event was processed.
     * @return false An error has occurred or quit the application.
     */
    auto OnWindowEvent(const SDL_WindowEvent& event) -> bool;
    /**
     * @brief Append a set draw color command to the command queue.
     * 
     * @param color Draw color for the command.
     */
    auto AppendSetDrawColorCommand(const SDL_Color& color) -> void;
};
}  // namespace display
}  // namespace cgl

#endif//CGL_LIBRARY_SANDBOX_INCLUDE_DISPLAY_L01SCENE_HPP_