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
    const GeometryElement& element) :
    SDLRendererCommand{renderer, operation} {
    mElement =
        std::make_unique<GeometryElement>(element.getCoordinates());
    mElement->setDrawColor(element.getDrawColor());
}

auto SDLRendererGeometryCommand::Execute() -> std::error_condition {
    auto coordinates = mElement->getCoordinates();
    switch (mOperation) {
        case Operation::DrawPoint : {
            auto drawColor = mElement->getDrawColor();
            ::SDL_SetRenderDrawColor(static_cast<SDL_Renderer*>(mRenderer.Get()),
                drawColor.red, drawColor.green, drawColor.blue,
                drawColor.alpha);
            ::SDL_RenderDrawPoint(static_cast<SDL_Renderer*>(mRenderer.Get()),
                coordinates[0], coordinates[1]);
        } break;
        case Operation::DrawLine : {
            auto drawColor = mElement->getDrawColor();
            ::SDL_SetRenderDrawColor(static_cast<SDL_Renderer*>(mRenderer.Get()),
                drawColor.red, drawColor.green, drawColor.blue,
                drawColor.alpha);
            ::SDL_RenderDrawLine(static_cast<SDL_Renderer*>(mRenderer.Get()),
                coordinates[0], coordinates[1], coordinates[2], coordinates[3]);
        } break;
        case Operation::DrawRect : {
            auto drawColor = mElement->getDrawColor();
            ::SDL_SetRenderDrawColor(static_cast<SDL_Renderer*>(mRenderer.Get()),
                drawColor.red, drawColor.green, drawColor.blue,
                drawColor.alpha);
            // ::SDL_Log("DRAW COLOR:\nR:%d\nG:%d\nB:%d\nA:%d\n",
            //     drawColor.red, drawColor.green, drawColor.blue,
            //     drawColor.alpha);
            SDL_Rect rect{coordinates[0],coordinates[1],coordinates[2],
                coordinates[3]};
            ::SDL_RenderDrawRect(static_cast<SDL_Renderer*>(mRenderer.Get()),
                &rect);
        } break;
        case Operation::DrawFillRect : {
            auto fillColor = mElement->getFillColor();
            ::SDL_SetRenderDrawColor(static_cast<SDL_Renderer*>(mRenderer.Get()),
                fillColor.red, fillColor.green, fillColor.blue,
                fillColor.alpha);
            // ::SDL_Log("FILL COLOR:\nR:%d\nG:%d\nB:%d\nA:%d\n",
            //     fillColor.red, fillColor.green, fillColor.blue,
            //     fillColor.alpha);
            SDL_Rect rect{coordinates[0],coordinates[1],coordinates[2],
                coordinates[3]};
            ::SDL_RenderFillRect(static_cast<SDL_Renderer*>(mRenderer.Get()),
                &rect);
        } break;
        case Operation::Unknown : [[fallthrough]];
        default:break;
    }
    return Error::makeErrorCondition(Error::ErrorCode::NoError);
}

}  // namespace command
}  // namespace cgl
