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
            auto coordinates = 
                static_cast<::Geometry::Point*>(mElement.get())
                    ->getCoordinates();
            auto drawColor = mElement->getDrawColor();
            ::SDL_SetRenderDrawColor(
                static_cast<SDL_Renderer*>(mRenderer.Get()),
                drawColor.red, drawColor.green, drawColor.blue,
                drawColor.alpha);
            ::SDL_RenderDrawPoint(
                static_cast<SDL_Renderer*>(mRenderer.Get()),
                coordinates.first, coordinates.second);
        } break;
        case Operation::DrawLine : {
            auto begin =
                static_cast<::Geometry::Line*>(mElement.get())->getBegin();
            auto end =
                static_cast<::Geometry::Line*>(mElement.get())->getEnd();
            auto drawColor = mElement->getDrawColor();
            ::SDL_Log("BEGIN : %d, %d\nEND : %d, %d",
                begin.first, begin.second, end.first, end.second);
            ::SDL_SetRenderDrawColor(
                static_cast<SDL_Renderer*>(mRenderer.Get()),
                drawColor.red, drawColor.green, drawColor.blue,
                drawColor.alpha);
            ::SDL_RenderDrawLine(static_cast<SDL_Renderer*>(mRenderer.Get()),
                begin.first, begin.second, end.first, end.second);
        } break;
        case Operation::Unknown : [[fallthrough]];
        default:break;
    }
    return Error::makeErrorCondition(Error::ErrorCode::NoError);
}

}  // namespace command
}  // namespace cgl
