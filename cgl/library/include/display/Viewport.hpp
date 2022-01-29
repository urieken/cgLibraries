/**
 * @file Viewport.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for Viewport.
 * @version 0.1
 * @date 2021-11-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_DISPLAY_VIEWPORT_HPP_
#define CGL_LIBRARY_INCLUDE_DISPLAY_VIEWPORT_HPP_

#include <display/Rect.hpp>

#include <cstdint>

namespace cgl {
namespace display {
/**
 * @brief The viewport class.
 */
class Viewport {
public:
    Viewport() = delete;
    virtual ~Viewport() = default;
    /**
     * @brief Construct a new Viewport object
     * 
     * @param id The viewport id.
     * @param rect The viewport coordinates.
     */
    Viewport(const std::uint8_t& id, const Rect& rect);
    /**
     * @brief Get the viewport id.
     * 
     * @return const std::uint8_t The viewport id.
     */
    auto getId() const -> const std::uint8_t;
    /**
     * @brief Get the viewport coordinates.
     * 
     * @return const Rect The viewport coordinates.
     */
    auto getRect() const -> const Rect;
private:
    /**
     * @brief The viewport coordinates.
     */
    Rect mRect;
    /**
     * @brief The viewport ID.
     */
    std::uint8_t mId;
};

}  // namespace display
}  // namespace cgl

#endif /* CGL_LIBRARY_INCLUDE_DISPLAY_VIEWPORT_HPP_ */
