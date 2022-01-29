/**
 * @file MainScene.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for main scene
 * @version 0.1
 * @date 2022-01-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef CGL_LIBRARY_SANDBOX_INCLUDE_DISPLAY_MAIN_SCENE_HPP_
#define CGL_LIBRARY_SANDBOX_INCLUDE_DISPLAY_MAIN_SCENE_HPP_

#include <display/IScene.hpp>

#include <command/ICommand.hpp>
#include <display/IRenderer.hpp>
#include <display/IWindow.hpp>
#include <event/IEvent.hpp>
#include <event/SDLEvent.hpp>
#include <imgui/IMGuiSDLRenderer.hpp>
#include <system/Arguments.hpp>

#include <cstdint>
#include <memory>
#include <queue>
#include <string>
#include <vector>

#include <SDL2/SDL.h>

namespace cgl {
namespace display {

class MainScene final : public IScene {
public:
    MainScene() = delete;
    /**
     * @brief Construct a new MainScene object
     * 
     * @param event Event type for this scene.
     * @param args The processed arguments.
     * @param events Custom events.
     */
    MainScene(const std::uint32_t& event,
        const ::cgl::system::Arguments& args,
        std::vector<std::pair<std::string,
            ::cgl::event::CustomSDLEevent>> events);
    /**
     * @brief Destroy the MainScene object
     */
    virtual ~MainScene();
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
     * @brief Arguments for the application.
     */
    const ::cgl::system::Arguments& mArguments;
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
     * @brief The IMGUI wrapper.
     */
    std::unique_ptr<::cgl::sandbox::imgui::IMGuiSDLRenderer> mImGui;
    /**
     * @brief Custom events.
     */
    std::vector<std::pair<std::string,
        ::cgl::event::CustomSDLEevent>> mEvents;
    /**
     * @brief Setup the window and renderer.
     * 
     * @return true On success.
     * @return false On failure.
     */
    auto Setup() -> bool;
    /**
    * @brief Get the string value of the given key.
    * 
    * @param key The key for the property.
    * @param args The Arguments instance containing the values.
    * @return const std::string The value for the key.
    */
    auto GetStringProperty(const std::string& key,
        const ::cgl::system::Arguments& args) -> const std::string;
    /**
    * @brief Get the integer value of the given key.
    * 
    * @param key The key for the property.
    * @param args The Arguments instance containing the values.
    * @return const int The value for the key.
    */
    auto GetIntegerProperty(const std::string& key,
        const ::cgl::system::Arguments& args) -> const int;
};

}  // namespace display
}  // namespace cgl

#endif//CGL_LIBRARY_SANDBOX_INCLUDE_DISPLAY_MAIN_SCENE_HPP_