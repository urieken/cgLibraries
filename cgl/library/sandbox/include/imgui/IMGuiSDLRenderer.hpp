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

#include <event/SDLEvent.hpp>
#include <system/Arguments.hpp>

#include <unordered_map>
#include <vector>

#include <SDL2/SDL.h>

namespace cgl {
namespace application {
namespace sandbox {
class SDLSandboxApplication;
}  // namespace sandbox
}  // namespace application
namespace sandbox {
namespace imgui {
/**
 * @brief Wrapper class for imgui SDL and SDL_Renderer
 */
class IMGuiSDLRenderer {
public:
    /**
     * @brief ImGui event type
     */
    enum class ImGuiEvent {
        ClearColorChange = 0,
        DrawColorChange,
        FillColorChange,
        ModulationColorChange,
        Unknown
    };
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
     */
    auto OnUpdate() -> void;
    /**
     * @brief Retrieve the draw color.
     * 
     * @return std::vector<int> The draw color.
     */
    auto DrawColor() -> std::vector<int>;
    /**
     * @brief Retrieve the modulation color.
     * 
     * @return std::vector<int> The modulation color.
     */
    auto ModulationColor() -> std::vector<int>;
    /**
     * @brief Add custom event details.
     * 
     * @param key The event key.
     * @param event The custom event details.
     */
    auto AddCustomEvent(const std::string& key,
        const ::cgl::event::CustomSDLEevent& event) -> void;
private:
    /**
     * @brief Pointer to the window instance
     */
    SDL_Window* mWindow;
    /**
     * @brief Pointer to the renderer instance.
     */
    SDL_Renderer* mRenderer;
    /**
     * @brief The draw color
     */
    std::vector<int> mDrawColor;
    /**
     * @brief The modulation color
     */
    std::vector<int> mModulationColor;
    /**
     * @brief The application arguments.
     */
    const ::cgl::system::Arguments& mArguments;
    /**
     * @brief Clear color.
     */
    std::vector<float> mClearColors;
    /**
     * @brief Draw color.
     */
    std::vector<float> mDrawColors;
    /**
     * @brief Fill color.
     */
    std::vector<float> mFillColors;
    /**
     * @brief Custom SDL events
     */
    std::unordered_map<std::string,
        ::cgl::event::CustomSDLEevent> mUserEvents;
    /**
     * @brief Display system information.
     */
    auto SystemInformation() -> void;
    /**
     * @brief Video display information details.
     */
    auto DisplayInformation() -> void;
    /**
     * @brief Details for the current display.
     * 
     * @param index The current display index.
     */
    auto DisplayDetails(const int& index) -> void;
    /**
     * @brief Bounds for the current display.
     * 
     * @param index The current display index.
     */
    auto DisplayBounds(const int& index) -> void;
    /**
     * @brief Display modes for the current display.
     * 
     * @param index The current display index.
     */
    auto DisplayModes(const int& index) -> void;
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
    /**
     * @brief Display lesson 01 details.
     *
     * @note Some trivial lessons are incorporated.
     */
    auto Lesson01() -> void;
    /**
     * @brief Display lesson 08 details.
     *
     * @note Some trivial lessons are incorporated.
     */
    auto Lesson08() -> void;
};

}  // namespace imgui
}  // namespace sandbox
}  // namespace cgl

#endif  // CGL_LIBRARY_SANDBOX_INCLUDE_IMGUI_SDL_RENDERER_HPP_
