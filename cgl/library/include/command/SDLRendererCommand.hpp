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

#include <display/SDLRenderer.hpp>

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
    SDLRendererCommand(::cgl::display::SDLRenderer& renderer,
        const Operation& operation);

    auto Execute() -> std::error_condition override;
private:
    /**
     * @brief Reference to the renderer instance.
     */
    ::cgl::display::SDLRenderer& mRenderer;
    /**
     * @brief The operation to be executed in this command.
     */
    Operation mOperation;
};

}  // namespace command
}  // namespace cgl

#endif /* CGL_LIBRARY_INCLUDE_COMMAND_SDL_RENDERER_COMMAND_HPP_ */
