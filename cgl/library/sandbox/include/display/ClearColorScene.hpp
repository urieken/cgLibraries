/**
 * @file ClearColorScene.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for lesson 01 scene
 * @version 0.1
 * @date 2022-01-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef CGL_LIBRARY_SANDBOX_INCLUDE_DISPLAY_CLEAR_COLOR_SCENE_HPP_
#define CGL_LIBRARY_SANDBOX_INCLUDE_DISPLAY_CLEAR_COLOR_SCENE_HPP_

#include <display/SandboxScene.hpp>

#include <command/ICommand.hpp>
#include <display/IRenderer.hpp>
#include <display/IWindow.hpp>
#include <event/IEvent.hpp>

#include <cstdint>
#include <memory>
#include <queue>

#include <SDL2/SDL.h>

constexpr auto CLEAR_COLOR_SCENE_TITLE{"Clear color scene"};

namespace cgl {
namespace display {
/**
 * @brief Scene class for lesson 01
 */
class ClearColorScene final : public SandboxScene {
public:
    ClearColorScene() = delete;
    /**
     * @brief Construct a new ClearColorScene object
     * 
     * @param event Event type for this scene.
     */
    explicit ClearColorScene(const std::uint32_t& event);
    /**
     * @brief Construct a new ClearColorScene object
     * 
     * @param event Event type for this scene.
     * @param title The scene title.
     * @param rect The scene dimensions.
     */
    ClearColorScene(const std::uint32_t& event, const std::string& title,
        const Rect& rect);
    /**
     * @brief Handle events.
     * 
     * @param event The event to be handled.
     * @return true The event was processed.
     * @return false An error has occurred or quit the application.
     */
    auto OnEvent(const ::cgl::event::IEvent& event) -> bool override;
private:
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

#endif//CGL_LIBRARY_SANDBOX_INCLUDE_DISPLAY_CLEAR_COLOR_SCENE_HPP_