/**
 * @file IWindow.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.co)
 * @brief Header for Window interface
 * @version 0.1
 * @date 2021-10-11
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_DISPLAY_IWINDOW_HPP_
#define CGL_LIBRARY_INCLUDE_DISPLAY_IWINDOW_HPP_

#include <cstdint>

namespace cgl {
namespace display {

/**
 * @brief The Window interface
 */
class IWindow {
public:
    virtual ~IWindow() = default;
    /**
     * @brief Get the window ID.
     * 
     * @return const std::uint32_t The the window ID.
     */
    virtual auto GetId() const -> const std::uint32_t = 0;
    /**
     * @brief Resize the window.
     * 
     * @param width The new window width.
     * @param height The new window height.
     */
    virtual auto SetSize(const int& width, const int& height) -> void = 0;
    /**
     * @brief Set the window visibility
     * 
     * @param flag True to show the window. False otherwise.
     */
    virtual auto Visible(bool flag) -> void = 0;
    /**
     * @brief Retrieve the window raw pointer.
     * 
     * @return void* The window raw pointer.
     */
    virtual auto Get() -> void* = 0;
};

}  // namespace display
}  // namespace cgl

#endif /* CGL_LIBRARY_INCLUDE_DISPLAY_IWINDOW_HPP_ */
