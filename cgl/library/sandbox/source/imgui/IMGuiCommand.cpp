/**
 * @file IMGuiCommand.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Source for IMGuiCommand
 * @version 0.1
 * @date 2022-01-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "imgui/IMGuiSDLRenderer.hpp"
#include <imgui/IMGuiCommand.hpp>

#include <error/CGLError.hpp>

namespace Error = ::cgl::error;

namespace cgl {
namespace application {
namespace sandbox {
namespace imgui {

IMGuiCommand::IMGuiCommand(::cgl::sandbox::imgui::IMGuiSDLRenderer& renderer) :
    mRenderer(renderer) {
}

auto IMGuiCommand::Execute() -> std::error_condition {
    mRenderer.OnUpdate();
    return Error::makeErrorCondition(Error::ErrorCode::NoError);
}

}  // namespace imgui
}  // namespace sandbox
}  // namespace application
}  // namespace cgl
