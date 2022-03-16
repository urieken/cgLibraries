/**
 * @file SDLSandboxApplication.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for SDLSandboxApplication
 * @version 0.1
 * @date 2021-11-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_SANDBOX_INCLUDE_APPLICATION_SDL_SANDBOX_APPLICATION_HPP_
#define CGL_LIBRARY_SANDBOX_INCLUDE_APPLICATION_SDL_SANDBOX_APPLICATION_HPP_

#include <application/SDLApplication.hpp>

#include <command/ICommand.hpp>
#include <display/IWindow.hpp>
#include <display/IRenderer.hpp>
#include <display/ITexture.hpp>
#include <display/IScene.hpp>
#include <display/SDLTexture.hpp>
#include <error/CGLError.hpp>
#include <event/IEvent.hpp>
#include <log/SDLLog.hpp>
#include <system/Arguments.hpp>

#include <imgui/IMGuiSDLRenderer.hpp>

#include <cstdint>
#include <functional>
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>

namespace cgl {
namespace application {
namespace sandbox {
/**
 * @brief The spritesheet structure.
 *
 * @note Might want to create a spritesheet generator.
 * (e.g) Use command in copying from source texture.
 */
struct SpriteSheet {
    ::cgl::display::SDLTexture texture;
    int width;
    int height;
    std::vector<int> indices;
};

/**
 * @brief SDL application for sandbox.
 */
class SDLSandboxApplication : public ::cgl::application::SDLApplication {
public:
    /**
     * @brief Destroy the SDLSandboxApplication object
     */
    virtual ~SDLSandboxApplication();
    /**
     * @brief Construct a new SDLSandboxApplication object
     * 
     * @param args The processed arguments.
     */
    explicit SDLSandboxApplication(const ::cgl::system::Arguments& args);
    /**
     * @brief Handle events.
     * 
     * @param event The event to be handled.
     * @return true The event was processed.
     * @return false An error has occurred or quit the application.
     */
    auto OnEvent(const ::cgl::event::IEvent& event) -> bool override;
    /**
     * @brief Called when the event queue is empty.
     */
    auto OnIdle() -> void override;
private:
    /**
     * @brief Starting value for custom event type.
     */
    std::uint32_t mCustomEventStart;

    std::uint32_t mMainWindow;
    /**
     * @brief SDL_Log wrapper
     */
    ::cgl::log::SDLLog mLog;
    /**
     * @brief Arguments for the application.
     */
    const ::cgl::system::Arguments& mArguments;
    /**
     * @brief The command queue for renderer operations.
     */
    std::queue<std::unique_ptr<::cgl::command::ICommand>> mCommandQueue;
    /**
     * @brief An update has been requested.
     */
    bool mUpdateRequested;
    /**
     * @brief Pointer to the IMGUI wrapper.
     */
    std::shared_ptr<::cgl::sandbox::imgui::IMGuiSDLRenderer> mImGui;
    /**
     * @brief Event handlers for scene instances.
     * 
     * @note Attempt to change to std::function instead of pointer
     * to the scene instance.
     */
    std::unordered_map<std::uint32_t,
        std::unique_ptr<::cgl::display::IScene>> mScenes;

    /**
     * @brief Setup internal properties.
     * 
     * @return true Setup succeeded.
     * @return false Setup failed.
     */
    auto Setup() -> bool;
    /**
     * @brief Update renderer
     */
    auto OnUpdate() -> void;
};

}  // namespace sandbox
}  // namespace application
}  // namespace cgl

#endif /* CGL_LIBRARY_SANDBOX_INCLUDE_APPLICATION_SDL_SANDBOX_APPLICATION_HPP_ */
