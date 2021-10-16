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

#include <display/SDLWindow.hpp>
#include <display/SDLRenderer.hpp>

#include <event/IEvent.hpp>

#include <memory>

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
     * @param argc Command line argument count.
     * @param argv Command line arguments.
     * 
     * @note Might want to use std::forward here.
     */
    SDLApplication(int argc, char** argv);
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
     * @brief The SDL window.
     */
    std::unique_ptr<::cgl::display::IWindow> mWindow;
    /**
     * @brief The SDL renderer.
     */
    std::unique_ptr<::cgl::display::IRenderer> mRenderer;
    /**
     * @brief An update has been requested.
     */
    bool mUpdateRequested;
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
