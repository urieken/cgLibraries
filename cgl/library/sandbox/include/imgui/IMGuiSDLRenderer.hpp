/**
 * @file IMGuiSDLRenderer.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for IMGuiSDLRenderer
 * @version 0.1
 * @date 2021-12-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_SANDBOX_INCLUDE_IMGUI_SDL_RENDERER_HPP_
#define CGL_LIBRARY_SANDBOX_INCLUDE_IMGUI_SDL_RENDERER_HPP_

#include <system/Arguments.hpp>

#include <vector>

#include <SDL2/SDL.h>

namespace cgl {
namespace sandbox {
namespace imgui {

/**
 * @brief Wrapper class for imgui SDL and SDL_Renderer
 */
class IMGuiSDLRenderer {
public:
    IMGuiSDLRenderer() = delete;
    /**
     * @brief Construct a new IMGuiSDLRenderer object
     * 
     * @param arguments The application arguments.
     * @param window Pointer to SDL_Window object.
     * @param renderer Pointer to SDL_Renderer object.
     */
    IMGuiSDLRenderer(const ::cgl::system::Arguments& arguments,
        SDL_Window* window, SDL_Renderer* renderer);
    /**
     * @brief Destroy the IMGuiSDLRenderer object
     */
    virtual ~IMGuiSDLRenderer();
    /**
     * @brief Handle SDL events.
     * 
     * @param event The SDL event data.
     * @return true On success.
     * @return false On failure.
     */
    auto OnEvent(const SDL_Event* event) -> bool;
    /**
     * @brief Update user interface.
     *
     * @param window The window to update
     */
    auto OnUpdate(SDL_Window* window) -> void;
    /**
     * @brief Retrieve the draw color.
     * 
     * @return std::vector<int> The draw color.
     */
    auto DrawColor() -> std::vector<int>;
private:
    /**
     * @brief The draw color
     */
    std::vector<int> mDrawColor;
    /**
     * @brief The application arguments.
     */
    const ::cgl::system::Arguments& mArguments;
    /**
     * @brief Display system information.
     */
    auto SystemInformation() -> void;
    /**
     * @brief Display application arguments.
     */
    auto Arguments() -> void;
    /**
     * @brief Display draw color
     */
    auto DrawColorInformation() -> void;
    /**
     * @brief Display event details.
     */
    auto Events() -> void;
};

}  // namespace imgui
}  // namespace sandbox
}  // namespace cgl

#endif  // CGL_LIBRARY_SANDBOX_INCLUDE_IMGUI_SDL_RENDERER_HPP_
