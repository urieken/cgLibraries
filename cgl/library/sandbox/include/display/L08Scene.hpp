/**
 * @file L08Scene.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for lesson 08 scene
 * @version 0.1
 * @date 2022-01-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef CGL_LIBRARY_SANDBOX_INCLUDE_DISPLAY_L08SCENE_HPP_
#define CGL_LIBRARY_SANDBOX_INCLUDE_DISPLAY_L08SCENE_HPP_

#include "command/SDLRendererCommand.hpp"
#include "display/Color.hpp"
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
 * @brief Scene class for lesson 08
 */
class L08Scene final : public IScene {
public:
    L08Scene() = delete;
    /**
     * @brief Construct a new L08Scene object
     * 
     * @param event Event type for this scene.
     */
    explicit L08Scene(const std::uint32_t& event);
    /**
     * @brief Destroy the L08Scene object
     */
    virtual ~L08Scene();
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
     * @brief The clear color.
     */
    SDL_Color mClearColor;
    /**
     * @brief The draw color.
     */
    SDL_Color mDrawColor;
    /**
     * @brief The fill color.
     */
    SDL_Color mFillColor;
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
     * @brief Append set draw color commands to the command queue.
     */
    auto AppendSetDrawColorCommand() -> void;
    /**
     * @brief Append draw commands to the command queue.
     * 
     * @param operation The draw operation.
     */
    auto AppendDrawCommand(
        const ::cgl::command::SDLRendererCommand::Operation& operation)
        -> void;
};
}  // namespace display
}  // namespace cgl

#endif//CGL_LIBRARY_SANDBOX_INCLUDE_DISPLAY_L08SCENE_HPP_
