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

#include <memory>
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
        LoadImages,
        StartTimer,
        StopTimer,
        PauseTimer,
        ResumeTimer,
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
     * @brief The Lesson task interface.
     */
    class ILessonTask {
    public:
        /**
         * @brief Construct a new ILessonTask object
         *
         * @param event The task custom event.
         */
        explicit ILessonTask(
            const ::cgl::event::CustomSDLEevent& event);
        /**
         * @brief Execute the task.
         */
        virtual auto Execute() -> void = 0;
    protected:
        /**
         * @brief The lesson event.
         */
        ::cgl::event::CustomSDLEevent mEvent;
    };
    /**
     * @brief Wrapper for clear color task.
     */
    class ClearColorTask : public ILessonTask {
    public:
        /**
         * @brief Construct a new ClearColorTask object
         *
         * @param event The clear color custom event.
         */
        explicit ClearColorTask(
            const ::cgl::event::CustomSDLEevent& event);
        /**
         * @brief Execute the task.
         */
         auto Execute() -> void override;
    private:
        /**
         * @brief The draw color.
         */
        std::vector<int> mDrawColor;
    };
    /**
     * @brief Wrapper for lesson 08 task.
     */
    class Lesson08Task : public ILessonTask {
    public:
        /**
         * @brief Construct a new Lesson08Task object
         *
         * @param event The lesson 08 custom event.
         */
        explicit Lesson08Task(
            const ::cgl::event::CustomSDLEevent& event);
        /**
         * @brief Execute the task.
         */
         auto Execute() -> void override;
    private:
        /**
         * @brief The clear, draw, and fill colors.
         */
        std::vector<std::vector<float>> mColors;
    };
    /**
     * @brief Wrapper for lesson 15 task.
     */
    class Lesson15Task : public ILessonTask {
    public:
        /**
         * @brief Construct a new Lesson15Task object
         *
         * @param event The lesson 08 custom event.
         */
        explicit Lesson15Task(
            const ::cgl::event::CustomSDLEevent& event);
        /**
         * @brief Execute the task.
         */
         auto Execute() -> void override;
    private:
        /**
         * @brief The timer status flag.
         */
        bool mTimerStarted;
        /**
         * @brief The timer pause/resume flag.
         */
        bool mTimerPaused;
    };
    /**
     * @brief Pointer to the window instance
     */
    SDL_Window* mWindow;
    /**
     * @brief Pointer to the renderer instance.
     */
    SDL_Renderer* mRenderer;
    /**
     * @brief The modulation color
     */
    std::vector<int> mModulationColor;
    /**
     * @brief The application arguments.
     */
    const ::cgl::system::Arguments& mArguments;
    /**
     * @brief Custom SDL events
     */
    std::unordered_map<std::string,
        ::cgl::event::CustomSDLEevent> mUserEvents;
    /**
     * @brief Lessons.
     */
    std::vector<std::unique_ptr<ILessonTask>> mLessons;
    /**
     * @brief Timer started flag.
     */
    bool mTimerStarted;
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
     * @brief Display lesson 15 details.
     *
     * @note Some trivial lessons are incorporated.
     */
    auto Lesson15() -> void;
};

}  // namespace imgui
}  // namespace sandbox
}  // namespace cgl

#endif  // CGL_LIBRARY_SANDBOX_INCLUDE_IMGUI_SDL_RENDERER_HPP_
