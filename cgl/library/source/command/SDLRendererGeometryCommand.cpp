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
    mElement->setColors(element.getColors());
}

auto SDLRendererGeometryCommand::Execute() -> std::error_condition {
    auto coordinates = mElement->getCoordinates();
    switch (mOperation) {
        case Operation::DrawPoint : {
            auto drawColor = mElement->getDrawColor();
            mRenderer.SetDrawColor(drawColor.red, drawColor.green,
                drawColor.blue, drawColor.alpha);
            // ::SDL_SetRenderDrawColor(getRenderer(), drawColor.red,
            //     drawColor.green, drawColor.blue, drawColor.alpha);
            ::SDL_RenderDrawPoint(getRenderer(),
                coordinates[0], coordinates[1]);
        } break;
        case Operation::DrawLine : {
            auto drawColor = mElement->getDrawColor();
            mRenderer.SetDrawColor(drawColor.red, drawColor.green,
                drawColor.blue, drawColor.alpha);
            // ::SDL_SetRenderDrawColor(getRenderer(), drawColor.red,
            //     drawColor.green, drawColor.blue, drawColor.alpha);
            ::SDL_RenderDrawLine(getRenderer(),
                coordinates[0], coordinates[1], coordinates[2], coordinates[3]);
        } break;
        case Operation::DrawRect : {
            auto drawColor = mElement->getDrawColor();
            mRenderer.SetDrawColor(drawColor.red, drawColor.green,
                drawColor.blue, drawColor.alpha);
            // ::SDL_SetRenderDrawColor(getRenderer(), drawColor.red,
            //     drawColor.green, drawColor.blue, drawColor.alpha);
            SDL_Rect rect{coordinates[0],coordinates[1],coordinates[2],
                coordinates[3]};
            ::SDL_RenderDrawRect(getRenderer(),
                &rect);
        } break;
        case Operation::DrawFillRect : {
            auto fillColor = mElement->getFillColor();
            mRenderer.SetDrawColor(fillColor.red, fillColor.green,
                fillColor.blue, fillColor.alpha);
            // ::SDL_SetRenderDrawColor(getRenderer(), fillColor.red,
            //     fillColor.green, fillColor.blue, fillColor.alpha);
            SDL_Rect rect{coordinates[0],coordinates[1],coordinates[2],
                coordinates[3]};
            ::SDL_RenderFillRect(getRenderer(),
                &rect);
        } break;
        case Operation::Unknown : [[fallthrough]];
        default:break;
    }
    return Error::makeErrorCondition(Error::ErrorCode::NoError);
}

}  // namespace command
}  // namespace cgl
