/**
 * @file SDLRendererCopyCommand.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.co)
 * @brief Source` for SDLRendererCopyCommand
 * @version 0.1
 * @date 2021-10-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <command/SDLRendererCopyCommand.hpp>

#include <error/CGLError.hpp>

namespace Display = ::cgl::display;
namespace Error = ::cgl::error;

namespace cgl {
namespace command {

SDLRendererCopyCommand::SDLRendererCopyCommand(
    Display::IRenderer& renderer, const Operation& operation,
    Display::ITexture& texture) :
    SDLRendererCommand{renderer, operation},
    mTexture{texture} {
}

auto SDLRendererCopyCommand::Execute() -> std::error_condition {
    switch (mOperation) {
        case Operation::CopyTexture : {
            mRenderer.Copy(mTexture);
        } break;
        case Operation::Unknown : [[fallthrough]];
        default:break;
    }
    return Error::makeErrorCondition(Error::ErrorCode::NoError);
}

}  // namespace command
}  // namespace cgl

