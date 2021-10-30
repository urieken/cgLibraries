/**
 * @file SDLRendererCommand.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Source for SDLRendererCommand
 * @version 0.1
 * @date 2021-10-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <command/SDLRendererCommand.hpp>

#include <error/CGLError.hpp>

namespace Display = ::cgl::display;
namespace Error = ::cgl::error;

namespace cgl {
namespace command {

SDLRendererCommand::SDLRendererCommand(Display::SDLRenderer& renderer,
    const Operation& operation) :
    mRenderer{renderer}, mOperation{operation} {
}

auto SDLRendererCommand::Execute() -> std::error_condition {
    switch (mOperation) {
        case Operation::Clear : {
            mRenderer.Clear();
        }break;
        case Operation::Present : {
            mRenderer.Present();
        }break;
        default:break;
    }
    return Error::makeErrorCondition(Error::ErrorCode::NoError);
}

}  // namespace command
}  // namespace cgl
