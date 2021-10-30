/**
 * @file SDLApplication.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for SDL application base.
 * @version 0.1
 * @date 2021-10-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_APPLICATION_SDL_APPLICATION_HPP_
#define CGL_LIBRARY_INCLUDE_APPLICATION_SDL_APPLICATION_HPP_

#include <application/IApplication.hpp>

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

#include <SDL2/SDL.h>

namespace cgl {
namespace application {

/**
 * @brief Base class for SDL applications.
 */
class SDLApplication : public IApplication {
public:
    /**
     * @brief Destroy the SDLApplication object
     */
    virtual ~SDLApplication();
    /**
     * @brief Construct a new SDLApplication object
     * 
     * @param args The processed arguments.
     */
    explicit SDLApplication(const ::cgl::system::Arguments& args);
    // Add std::error_condition for some handlers.
    // Add pure virtual init, update, event, render handers, etc.
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
     * @brief Process the std::string flags.
     * 
     * @param flags The flags in std::string format.
     * @return const std::int32_t The integral value of the flags.
     */
    auto ProcessSDLFlags(const std::string& flags) const
        -> const std::int32_t;
    /**
     * @brief Setup the application
     * 
     * @return true Initialization succeeded.
     * @return false Initialization failed.
     */
    auto Setup() -> bool;
    /**
     * @brief Cleanup the appication resources.
     */
    auto Cleanup() -> void;
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
    auto OnKeyUpEvent(const SDL_KeyboardEvent& event) -> bool;
    /**
     * @brief Update renderer
     */
    auto OnUpdate() -> void;
};


}  // namespace application
}  // namespace cgl

#endif /* CGL_LIBRARY_INCLUDE_APPLICATION_SDL_APPLICATION_HPP_ */
