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

#include <display/SDLRenderer.hpp>
#include <error/CGLError.hpp>

namespace Display = ::cgl::display;
namespace Error = ::cgl::error;

namespace cgl {
namespace command {

SDLRendererCommand::SDLRendererCommand(Display::IRenderer& renderer,
    const Operation& operation) :
    mRenderer{renderer},
    mOperation{operation},
    mRenderColor{0UL, 0UL, 0UL, 0UL} {
}

SDLRendererCommand::SDLRendererCommand(Display::IRenderer& renderer,
    const Operation& operation, const SDL_Color& color) :
    mRenderer{renderer},
    mOperation{operation},
    mRenderColor{color} {
}

auto SDLRendererCommand::Execute() -> std::error_condition {
    switch (mOperation) {
        case Operation::Clear : {
            mRenderer.Clear();
        }break;
        case Operation::Present : {
            mRenderer.Present();
        }break;
        case Operation::SetDrawColor : {
            mRenderer.SetDrawColor(mRenderColor.r, mRenderColor.g,
                mRenderColor.b, mRenderColor.a);
        }break;
        case Operation::Unknown : [[fallthrough]];
        default:break;
    }
    return Error::makeErrorCondition(Error::ErrorCode::NoError);
}

}  // namespace command
}  // namespace cgl
