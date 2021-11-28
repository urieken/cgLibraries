/**
 * @file SDLRendererViewportCommand.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for SDLRendererViewportCommand
 * @version 0.1
 * @date 2021-11-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_COMMAND_SDL_VIEWPORT_COMMAND_HPP_
#define CGL_LIBRARY_INCLUDE_COMMAND_SDL_VIEWPORT_COMMAND_HPP_

#include <command/SDLRendererCommand.hpp>

#include <display/IRenderer.hpp>
#include <display/Viewport.hpp>

#include <memory>
#include <system_error>

namespace cgl {
namespace command {
/**
 * @brief SDLRenderer viewport commands.
 */
class SDLRendererViewportCommand : public SDLRendererCommand {
public:
    /**
     * @brief Construct a new SDLRendererViewportCommand object
     * 
     * @param renderer The renderer to operated upon.
     * @param operation The operation to be executed.
     * @param viewport The viewport to be used.
     */
    SDLRendererViewportCommand(::cgl::display::IRenderer& renderer,
        const Operation& operation,
        const ::cgl::display::Viewport& viewport);
    /**
     * @brief Execute the command.
     * 
     * @return std::error_condition The operation result.
     */
    auto Execute() -> std::error_condition override;
private:
    /**
     * @brief The viewport to be used.
     */
    std::unique_ptr<::cgl::display::Viewport> mViewport;
};

}  // namespace command
}  // namespace cgl

#endif /* CGL_LIBRARY_INCLUDE_COMMAND_SDL_VIEWPORT_COMMAND_HPP_ */
