/**
 * @file SDLRendererViewportCommand.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Source for SDLRendererViewportCommand
 * @version 0.1
 * @date 2021-11-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <command/SDLRendererViewportCommand.hpp>

#include <error/CGLError.hpp>

#include <SDL2/SDL.h>

namespace Error = ::cgl::error;
namespace Display = ::cgl::display;

using Viewport = Display::Viewport;

namespace cgl {
namespace command {

SDLRendererViewportCommand::SDLRendererViewportCommand(
    ::cgl::display::IRenderer& renderer, const Operation& operation,
    const Viewport& viewport) :
    SDLRendererCommand{renderer, operation} {
    mViewport =
        std::make_unique<Viewport>(viewport.getId(), viewport.getRect());
}

auto SDLRendererViewportCommand::Execute() -> std::error_condition {
    switch(mOperation) {
        case Operation::SetViewport : {
            SDL_Rect rect{
                mViewport->getRect().top,
                mViewport->getRect().left,
                mViewport->getRect().width,
                mViewport->getRect().height,
            };
            ::SDL_RenderSetViewport(getRenderer(), &rect);
        } break;
        case Operation::Unknown : [[fallthrough]];
        default:break;
    }
    return Error::makeErrorCondition(Error::ErrorCode::NoError);
}

}  // namespace command
}  // namespace cgl
