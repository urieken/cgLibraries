/**
 * @file SandboxScene.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for base lesson scene.
 * @version 0.1
 * @date 2022-01-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef CGL_LIBRARY_SANDBOX_INCLUDE_DISPLAY_SANDBOX_SCENE_HPP_
#define CGL_LIBRARY_SANDBOX_INCLUDE_DISPLAY_SANDBOX_SCENE_HPP_

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
 * @brief Base class for common scene operations
 */
class SandboxScene : public IScene {
public:
    virtual ~SandboxScene() = default;
    /**
     * @brief Construct a new SandboxScene object
     * 
     * @param event Event type for this scene.
     */
    explicit SandboxScene(const std::uint32_t& event);
    /**
     * @brief Construct a new SandboxScene object
     * 
     * @param event Event type for this scene.
     * @param title The scene title.
     * @param rect The scene dimensions.
     */
    SandboxScene(const std::uint32_t& event, const std::string& title,
        const Rect& rect);
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
    auto Visible(bool visible) -> void override;
protected:
    /**
     * @brief Get a raw pointer to the window instance.
     * 
     * @return ::cgl::display::IWindow* The window instance pointer.
     */
    auto GetWindow() -> ::cgl::display::IWindow*;
    /**
     * @brief Get a raw pointer to the renderer instance.
     * 
     * @return ::cgl::display::IRenderer* The renderer instance pointer.
     */
    auto GetRenderer() -> ::cgl::display::IRenderer*;
    /**
     * @brief Get the scene event type.
     * 
     * @return std::uint32_t const The scene event type.
     */
    auto EventType() const -> std::uint32_t const;
    /**
     * @brief Return a pointer to the command queue.
     * 
     * @return std::queue<std::unique_ptr<::cgl::command::ICommand>>*
     */
    auto CommandQueue()
        -> std::queue<std::unique_ptr<::cgl::command::ICommand>>*;
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
     * @brief The scene title.
     */
    std::string mTitle;
    /**
     * @brief The scene dimensions.
     */
    Rect mRect;
    /**
     * @brief Setup the window and renderer.
     * 
     * @return true On success.
     * @return false On failure.
     */
    auto Setup() -> bool;
};
}  // namespace display
}  // namespace cgl

#endif//CGL_LIBRARY_SANDBOX_INCLUDE_DISPLAY_SANDBOX_SCENE_HPP_