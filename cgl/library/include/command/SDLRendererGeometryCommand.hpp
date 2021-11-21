/**
 * @file SDLRendererGeometryCommand.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief SDLRendererGeometryCommand
 * @version 0.1
 * @date 2021-11-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_COMMAND_SDL_RENDERER_GEOMETRY_COMMAND_HPP_
#define CGL_LIBRARY_INCLUDE_COMMAND_SDL_RENDERER_GEOMETRY_COMMAND_HPP_

#include <command/SDLRendererCommand.hpp>

#include <memory>

#include <display/IRenderer.hpp>
#include <geometry/IGeometryElement.hpp>
#include <geometry/Line.hpp>
#include <geometry/Point.hpp>

namespace cgl {
namespace command {
/**
 * @brief SDLRenderer geometry commands.
 */
class SDLRendererGeometryCommand : public SDLRendererCommand {
public:
    /**
     * @brief Construct a new SDLRendererGeometryCommand object
     * 
     * @param renderer The renderer to operated upon.
     * @param operation The operation to be executed.
     * @param element The element to be used in the command.
     */
    SDLRendererGeometryCommand(::cgl::display::IRenderer& renderer,
        const Operation& operation,
        const ::cgl::geometry::Point& element);
    /**
     * @brief Construct a new SDLRendererGeometryCommand object
     * 
     * @param renderer The renderer to operated upon.
     * @param operation The operation to be executed.
     * @param element The element to be used in the command.
     */
    SDLRendererGeometryCommand(::cgl::display::IRenderer& renderer,
        const Operation& operation,
        const ::cgl::geometry::Line& element);
    /**
     * @brief Execute the command.
     * 
     * @return std::error_condition The operation result.
     */
    auto Execute() -> std::error_condition override;
private:
    /**
     * @brief The geometry element to be used.
     */
    std::unique_ptr<::cgl::geometry::IGeometryElement> mElement;
};

}  // namespace command
}  // namespace cgl

#endif /* CGL_LIBRARY_INCLUDE_COMMAND_SDL_RENDERER_GEOMETRY_COMMAND_HPP_ */
