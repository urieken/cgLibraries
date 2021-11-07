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
#include <error/CGLError.hpp>
#include <event/IEvent.hpp>
#include <system/Arguments.hpp>

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace cgl {
namespace application {
namespace sandbox {
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
private:
    /**
     * @brief Arguments for the application.
     */
    const ::cgl::system::Arguments& mArguments;
    /**
     * @brief The SDL window.
     */
    std::unique_ptr<::cgl::display::IWindow> mWindow;
    /**
     * @brief The SDL renderer.
     */
    std::unique_ptr<::cgl::display::IRenderer> mRenderer;
    /**
     * @brief The command queue for renderer operations.
     */
    std::vector<std::unique_ptr<::cgl::command::ICommand>> mRendererCommands;
    /**
     * @brief An update has been requested.
     */
    bool mUpdateRequested;
    /**
     * @brief Pointer to the texture.
     */
    std::unique_ptr<::cgl::display::ITexture> mTexture;
    /**
     * @brief Setup internal properties.
     * 
     * @return true Setup succeeded.
     * @return false Setup failed.
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
     * @brief Handle keyboard release events
     * 
     * @param event The SDL keyboard event.
     * @return true The event was processed.
     * @return false An error has occurred or quit the application.
     */
    // auto OnKeyUpEvent(const SDL_KeyboardEvent& event) -> bool;
    /**
     * @brief Update renderer
     */
    auto OnUpdate() -> void;
};

}  // namespace sandbox
}  // namespace application
}  // namespace cgl

#endif /* CGL_LIBRARY_SANDBOX_INCLUDE_APPLICATION_SDL_SANDBOX_APPLICATION_HPP_ */
