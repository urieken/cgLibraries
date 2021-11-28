/**
 * @file Viewport.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Source for Viewport.
 * @version 0.1
 * @date 2021-11-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <display/Viewport.hpp>

namespace cgl {
namespace display {

Viewport::Viewport(const std::uint8_t& id, const Rect& rect) :
    mId{id}, mRect{rect} {}

auto Viewport::getId() const -> const std::uint8_t {
    return mId;
}

auto Viewport::getRect() const -> const Rect {
    return mRect;
}

}  // namespace display
}  // namespace cgl
