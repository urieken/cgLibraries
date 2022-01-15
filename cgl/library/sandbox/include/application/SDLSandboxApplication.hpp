/**
 * @file SDLSandboxApplication.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for SDLSandboxApplication
 * @version 0.1
 * @date 2021-11-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_SANDBOX_INCLUDE_APPLICATION_SDL_SANDBOX_APPLICATION_HPP_
#define CGL_LIBRARY_SANDBOX_INCLUDE_APPLICATION_SDL_SANDBOX_APPLICATION_HPP_

#include <application/SDLApplication.hpp>

#include <command/ICommand.hpp>
#include <display/IWindow.hpp>
#include <display/IRenderer.hpp>
#include <display/ITexture.hpp>
#include <display/SDLTexture.hpp>
#include <error/CGLError.hpp>
#include <event/IEvent.hpp>
#include <log/SDLLog.hpp>
#include <system/Arguments.hpp>

#include <imgui/IMGuiSDLRenderer.hpp>

#include <cstdint>
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>

namespace cgl {
namespace application {
namespace sandbox {
/**
 * @brief The spritesheet structure.
 *
 * @note Might want to create a spritesheet generator.
 * (e.g) Use command in copying from source texture.
 */
struct SpriteSheet {
    ::cgl::display::SDLTexture texture;
    int width;
    int height;
    std::vector<int> indices;
};
/**
 * @brief Group for window, window id, renderer
 *
 * @note Might just need the window ID here.
 */
struct WindowGroup {
    /**
     * @brief The SDL window.
     */
    std::unique_ptr<::cgl::display::IWindow> mWindow;
    /**
     * @brief The SDL renderer.
     */
    std::unique_ptr<::cgl::display::IRenderer> mRenderer;
};
/**
 * @brief Alias for the window group map.
 *
 * @note Might just need to store the renderer instead of the entire group.
 */
using WindowGroupMap = std::unordered_map<std::uint32_t, WindowGroup>;

/**
 * @brief SDL application for sandbox.
 */
class SDLSandboxApplication : public ::cgl::application::SDLApplication {
public:
    /**
     * @brief Destroy the SDLSandboxApplication object
     */
    virtual ~SDLSandboxApplication();
    /**
     * @brief Construct a new SDLSandboxApplication object
     * 
     * @param args The processed arguments.
     */
    explicit SDLSandboxApplication(const ::cgl::system::Arguments& args);
    /**
     * @brief Handle events.
     * 
     * @param event The event to be handled.
     * @return true The event was processed.
     * @return false An error has occurred or quit the application.
     */
    auto OnEvent(const ::cgl::event::IEvent& event) -> bool override;
    /**
     * @brief Event handler for clear color change.
     * 
     * @param clearColor The clear color.
     */
    auto OnClearColorChange(std::vector<int>& clearColor) -> void;
    /**
     * @brief Event handler for modulation color change.
     * 
     * @param modulationColor The modulation color.
     */
    auto OnModulationColorChange(std::vector<int>& modulationColor) -> void;
private:
    std::uint32_t mMainWindow;
    /**
     * @brief SDL_Log wrapper
     */
    ::cgl::log::SDLLog mLog;
    /**
     * @brief Arguments for the application.
     */
    const ::cgl::system::Arguments& mArguments;
    /**
     * @brief The command queue for renderer operations.
     */
    std::queue<std::unique_ptr<::cgl::command::ICommand>> mCommandQueue;
    /**
     * @brief An update has been requested.
     */
    bool mUpdateRequested;
    /**
     * @brief Pointer to the texture.
     */
    std::unique_ptr<::cgl::display::ITexture> mTexture;
    /**
     * @brief Pointer to the background texture.
     */
    std::unique_ptr<::cgl::display::ITexture> mBackground;
    /**
     * @brief Spritesheet for Terra.
     */
    SpriteSheet mTerra;
    /**
     * @brief Pointer to the IMGUI wrapper.
     */
    std::unique_ptr<::cgl::sandbox::imgui::IMGuiSDLRenderer> mImGui;
    /**
     * @brief Window and renderer map.
     */
    WindowGroupMap mWindowGroupMap;
    /**
     * @brief Setup internal properties.
     * 
     * @return true Setup succeeded.
     * @return false Setup failed.
     */
    auto Setup() -> bool;
    /**
     * @brief Create window and renderer.
     * 
     * @return true Setup succeeded.
     * @return false Setup failed.
     */
    auto SetupWindowAndRenderer() -> bool;
    /**
     * @brief Load image resources.
     * 
     * @return true Setup succeeded.
     * @return false Setup failed.
     */
    auto LoadImages() -> bool;
    /**
     * @brief Handle keyboard press events
     * 
     * @param event The SDL keyboard event.
     * @return true The event was processed.
     * @return false An error has occurred or quit the application.
     */
    auto OnKeyDownEvent(const SDL_KeyboardEvent& event) -> bool;
    /**
     * @brief Handle keyboard release events
     * 
     * @param event The SDL keyboard event.
     * @return true The event was processed.
     * @return false An error has occurred or quit the application.
     */
    // auto OnKeyUpEvent(const SDL_KeyboardEvent& event) -> bool;
    /**
     * @brief Update renderer
     */
    auto OnUpdate() -> void;
    /**
     * @brief Update sprite.
     * 
     * @param index The spritesheet index.
     */
    auto UpdateSprite(int index) -> void;
};

}  // namespace sandbox
}  // namespace application
}  // namespace cgl

#endif /* CGL_LIBRARY_SANDBOX_INCLUDE_APPLICATION_SDL_SANDBOX_APPLICATION_HPP_ */
