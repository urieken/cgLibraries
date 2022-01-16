/**
 * @file IScene.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for scene interface.
 * @version 0.1
 * @date 2022-01-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_DISPLAY_ISCENE_HPP_
#define CGL_LIBRARY_INCLUDE_DISPLAY_ISCENE_HPP_

#include <event/IEvent.hpp>

#include <cstdint>

namespace cgl {
namespace display {
/**
 * @brief Interface for scene classes.
 */
class IScene {
public:
    virtual ~IScene() = default;
    /**
     * @brief Handle events.
     * 
     * @param event The event to be handled.
     * @return true The event was processed.
     * @return false An error has occurred or quit the application.
     */
    virtual auto OnEvent(const ::cgl::event::IEvent& event) -> bool = 0;
    /**
     * @brief Update the scene.
     */
    virtual auto OnUpdate() -> void = 0;
    /**
     * @brief Get the scene id.
     * 
     * @return std::uint32_t The scene id.
     */
    virtual auto Id() const -> std::uint32_t = 0;
};
}  // namespace display
}  // namespace cgl

#endif//CGL_LIBRARY_INCLUDE_DISPLAY_ISCENE_HPP_