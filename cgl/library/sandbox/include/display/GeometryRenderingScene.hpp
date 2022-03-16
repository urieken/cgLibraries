/**
 * @file GeometryRenderingScene.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for geometry rendering scene
 * @version 0.1
 * @date 2022-01-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef CGL_LIBRARY_SANDBOX_INCLUDE_DISPLAY_L08SCENE_HPP_
#define CGL_LIBRARY_SANDBOX_INCLUDE_DISPLAY_L08SCENE_HPP_

#include <display/SandboxScene.hpp>

#include <command/ICommand.hpp>
#include <command/SDLRendererCommand.hpp>
#include <display/IRenderer.hpp>
#include <display/IWindow.hpp>
#include <event/IEvent.hpp>

#include <cstdint>
#include <memory>
#include <queue>

#include <SDL2/SDL.h>

constexpr auto GEOMETRY_RENDERING_SCENE_TITLE{"Geometry rendering scene"};

namespace cgl {
namespace display {
/**
 * @brief Scene class for geometry rendering
 */
class GeometryRenderingScene final : public SandboxScene {
public:
    GeometryRenderingScene() = delete;
    /**
     * @brief Construct a new GeometryRenderingScene object
     * 
     * @param event Event type for this scene.
     */
    explicit GeometryRenderingScene(const std::uint32_t& event);
    /**
     * @brief Construct a new GeometryRenderingScene object
     * 
     * @param event Event type for this scene.
     * @param title The scene title.
     * @param rect The scene dimensions.
     */
    GeometryRenderingScene(const std::uint32_t& event,
        const std::string& title, const Rect& rect);
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
