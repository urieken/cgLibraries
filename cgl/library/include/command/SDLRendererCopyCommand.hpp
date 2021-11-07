/**
 * @file SDLRendererCopyCommand.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.co)
 * @brief Header for SDLRendererCopyCommand
 * @version 0.1
 * @date 2021-10-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_COMMAND_SDL_RENDERER_COPY_COMMAND_HPP_
#define CGL_LIBRARY_INCLUDE_COMMAND_SDL_RENDERER_COPY_COMMAND_HPP_

#include <command/SDLRendererCommand.hpp>

#include <display/ITexture.hpp>
#include <display/Rect.hpp>

#include <SDL2/SDL.h>

namespace cgl {
namespace command {
/**
 * @brief SDLRenderer copy commands.
 */
class SDLRendererCopyCommand : public SDLRendererCommand {
public:
    /**
     * @brief Construct a new SDLRendererCopyCommand object
     * 
     * @param renderer The renderer to operated upon.
     * @param operation The operation to be executed.
     * @param texture The texture for the operation.
     */
    SDLRendererCopyCommand(::cgl::display::IRenderer& renderer,
        const Operation& operation, ::cgl::display::ITexture& texture);
    /**
     * @brief Construct a new SDLRendererCopyCommand object
     * 
     * @param renderer The renderer to operated upon.
     * @param operation The operation to be executed.
     * @param texture The texture for the operation.
     * @param sourceRect The source rectangle.
     * @param destinationRect The destination rectangle.
     */
    SDLRendererCopyCommand(::cgl::display::IRenderer& renderer,
        const Operation& operation, ::cgl::display::ITexture& texture,
        const ::cgl::display::Rect& sourceRect,
        const ::cgl::display::Rect& destinationRect);
    /**
     * @brief Execute the command.
     * 
     * @return std::error_condition The operation result.
     */
    auto Execute() -> std::error_condition override;
private:
    /**
     * @brief The texture to be used for the copy operation.
     */
    ::cgl::display::ITexture& mTexture;
    /**
     * @brief The source rectangle.
     */
    ::cgl::display::Rect mSourceRect;
    /**
     * @brief The desination rectangle.
     */
    ::cgl::display::Rect mDesinationRect;
};

}  // namespace command
}  // namespace cgl

#endif /* CGL_LIBRARY_INCLUDE_COMMAND_SDL_RENDERER_COPY_COMMAND_HPP_ */
