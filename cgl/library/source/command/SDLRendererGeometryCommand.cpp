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

using GeometryElement = Geometry::IGeometryElement;

namespace cgl {
namespace command {

SDLRendererGeometryCommand::SDLRendererGeometryCommand(
    ::cgl::display::IRenderer& renderer, const Operation& operation,
    const Geometry::Point& element) :
    SDLRendererCommand{renderer, operation} {
    mElement =
        std::make_unique<GeometryElement>(element.getCoordinates());
    mElement->setDrawColor(element.getDrawColor());
}

SDLRendererGeometryCommand::SDLRendererGeometryCommand(
    ::cgl::display::IRenderer& renderer, const Operation& operation,
    const Geometry::Line& element) :
    SDLRendererCommand{renderer, operation} {
    mElement =
        std::make_unique<GeometryElement>(element.getCoordinates());
    mElement->setDrawColor(element.getDrawColor());
}

SDLRendererGeometryCommand::SDLRendererGeometryCommand(
    ::cgl::display::IRenderer& renderer, const Operation& operation,
    const Geometry::Line& element) :
    SDLRendererCommand{renderer, operation} {
    mElement = std::make_unique<Geometry::Line>(element.getBegin(),
        element.getEnd());
    mElement->setDrawColor(element.getDrawColor());
}

auto SDLRendererGeometryCommand::Execute() -> std::error_condition {
    ::SDL_Log("METHOD : %s\n", __PRETTY_FUNCTION__);
    switch (mOperation) {
        case Operation::DrawPoint : {
            auto coordinates = mElement->getCoordinates();
            auto drawColor = mElement->getDrawColor();
            ::SDL_SetRenderDrawColor(
                static_cast<SDL_Renderer*>(mRenderer.Get()),
                drawColor.red, drawColor.green, drawColor.blue,
                drawColor.alpha);
            ::SDL_RenderDrawPoint(
                static_cast<SDL_Renderer*>(mRenderer.Get()),
                coordinates[0], coordinates[1]);
        } break;
        case Operation::DrawLine : {
            auto coordinates = mElement->getCoordinates();
            auto drawColor = mElement->getDrawColor();
            ::SDL_SetRenderDrawColor(
                static_cast<SDL_Renderer*>(mRenderer.Get()),
                drawColor.red, drawColor.green, drawColor.blue,
                drawColor.alpha);
            ::SDL_RenderDrawLine(static_cast<SDL_Renderer*>(mRenderer.Get()),
                coordinates[0], coordinates[1], coordinates[2], coordinates[3]);
        } break;
        case Operation::Unknown : [[fallthrough]];
        default:break;
    }
    return Error::makeErrorCondition(Error::ErrorCode::NoError);
}

}  // namespace command
}  // namespace cgl
