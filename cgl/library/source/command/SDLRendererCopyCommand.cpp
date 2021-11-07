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
    mTexture{texture},
    mSourceRect{},
    mDesinationRect{} {
}

SDLRendererCopyCommand::SDLRendererCopyCommand(
    ::cgl::display::IRenderer& renderer,
    const Operation& operation, Display::ITexture& texture,
    const Display::Rect& sourceRect, const Display::Rect& destinationRect)  :
    SDLRendererCommand{renderer, operation},
    mTexture{texture},
    mSourceRect{sourceRect},
    mDesinationRect{destinationRect} {
}

auto SDLRendererCopyCommand::Execute() -> std::error_condition {
    switch (mOperation) {
        case Operation::CopyTexture : {
            mRenderer.Copy(mTexture);
            // ::SDL_RenderCopy(static_cast<SDL_Renderer*>(mRenderer.Get()),
            //     static_cast<SDL_Texture*>(mTexture.Get()), nullptr, nullptr);
        } break;
        case Operation::CopyTextureRect : {
            mRenderer.Copy(mTexture, mSourceRect, mDesinationRect);
            // ::SDL_RenderCopy(static_cast<SDL_Renderer*>(mRenderer.Get()),
            //     static_cast<SDL_Texture*>(mTexture.Get()),
            //     &mSourceRect, &mDesinationRect);
        } break;
        case Operation::Unknown : [[fallthrough]];
        default:break;
    }
    return Error::makeErrorCondition(Error::ErrorCode::NoError);
}

}  // namespace command
}  // namespace cgl

