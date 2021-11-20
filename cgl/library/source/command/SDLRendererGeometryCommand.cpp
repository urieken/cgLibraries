/**
 * @file SDLRendererGeometryCommand.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for SDLRendererGeometryCommand
 * @version 0.1
 * @date 2021-11-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <command/SDLRendererGeometryCommand.hpp>

#include <error/CGLError.hpp>

#include <SDL2/SDL.h>

namespace Error = ::cgl::error;
namespace Geometry = ::cgl::geometry;

namespace cgl {
namespace command {

SDLRendererGeometryCommand::SDLRendererGeometryCommand(
    ::cgl::display::IRenderer& renderer, const Operation& operation,
    const Geometry::Point& element) :
    SDLRendererCommand{renderer, operation} {
    mElement = std::make_unique<Geometry::Point>(element.getX(),
        element.getY());
}

auto SDLRendererGeometryCommand::Execute() -> std::error_condition {
    switch (mOperation) {
        case Operation::DrawPoint : {
            auto coordinates = 
                static_cast<::Geometry::Point*>(mElement.get())
                    ->getCoordinates();
            ::SDL_RenderDrawPoint(static_cast<SDL_Renderer*>(mRenderer.Get()),
                coordinates.first, coordinates.second);
        } break;
        case Operation::Unknown : [[fallthrough]];
        default:break;
    }
    return Error::makeErrorCondition(Error::ErrorCode::NoError);
}

}  // namespace command
}  // namespace cgl
