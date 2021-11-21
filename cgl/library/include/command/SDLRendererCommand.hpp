/**
 * @file SDLRendererCommand.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for SDLRendererCommand
 * @version 0.1
 * @date 2021-10-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_COMMAND_SDL_RENDERER_COMMAND_HPP_
#define CGL_LIBRARY_INCLUDE_COMMAND_SDL_RENDERER_COMMAND_HPP_

#include <command/ICommand.hpp>

#include <display/IRenderer.hpp>
#include <display/ITexture.hpp>

#include <cstdint>
#include <system_error>

#include <SDL2/SDL.h>

namespace cgl {
namespace command {
/**
 * @brief Wrapper for SDL_Renderer command
 */
class SDLRendererCommand : public ICommand {
public:
    /**
     * @brief SDL_Renderer operations
     */
    enum class Operation {
        Clear = 0UL,
        Present,
        SetDrawColor,
        CopyTexture,
        CopyTextureRect,
        DrawPoint,
        DrawLine,
        DrawRect,
        DrawFillRect,
        Unknown
    };
    SDLRendererCommand() = delete;
    virtual ~SDLRendererCommand() = default;
    /**
     * @brief Construct a new SDLRendererCommand object
     * 
     * @param renderer The renderer to operated upon.
     * @param operation The operation to be executed.
     */
    SDLRendererCommand(::cgl::display::IRenderer& renderer,
        const Operation& operation);
    /**
     * @brief Construct a new SDLRendererCommand object
     * 
     * @param renderer The renderer to operated upon.
     * @param operation The operation to be executed.
     * @param color The color for the operation.
     */
    SDLRendererCommand(::cgl::display::IRenderer& renderer,
        const Operation& operation, const SDL_Color& color);
    /**
     * @brief Execute the command.
     * 
     * @return std::error_condition The operation result.
     */
    auto Execute() -> std::error_condition override;
protected:
    /**
     * @brief The operation to be executed in this command.
     */
    Operation mOperation;
    /**
     * @brief Reference to the renderer instance.
     */
    ::cgl::display::IRenderer& mRenderer;
private:
    /**
     * @brief The render color.
     */
    SDL_Color mRenderColor;
};

}  // namespace command
}  // namespace cgl

#endif /* CGL_LIBRARY_INCLUDE_COMMAND_SDL_RENDERER_COMMAND_HPP_ */
