/**
 * @file IMGuiCommand.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for IMGuiCommand
 * @version 0.1
 * @date 2022-01-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef CGL_LIBRARY_SANDBOX_INCLUDE_IMGUI_IMGUI_COMMAND_HPP
#define CGL_LIBRARY_SANDBOX_INCLUDE_IMGUI_IMGUI_COMMAND_HPP

#include <command/ICommand.hpp>

#include <imgui/IMGuiSDLRenderer.hpp>

#include <system_error>

namespace cgl {
namespace application {
namespace sandbox {
namespace imgui {
/**
 * @brief Wrapper class for IMGui commands
 */
class IMGuiCommand final : public ::cgl::command::ICommand {
public:
    /**
     * @brief Construct a new IMGuiCommand object
     * 
     * @param renderer The IMGuiSDLRenderer instance.
     */
    IMGuiCommand(::cgl::sandbox::imgui::IMGuiSDLRenderer& renderer);
    /**
     * @brief Execute tthe command.
     * 
     * @return std::error_condition The command result. 
     */
    auto Execute() -> std::error_condition override;
public:
    /**
     * @brief Reference to the IMGuiRenderer instance.
     */
    ::cgl::sandbox::imgui::IMGuiSDLRenderer& mRenderer;
};

}  // namespace imgui
}  // namespace sandbox
}  // namespace application
}  // namespace cgl

#endif  // CGL_LIBRARY_SANDBOX_INCLUDE_IMGUI_IMGUI_COMMAND_HPP