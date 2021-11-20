/**
 * @file Point.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Source for Point
 * @version 0.1
 * @date 2021-11-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <geometry/Point.hpp>

#include <utility>

using Color = ::cgl::display::Color;

namespace cgl {
namespace geometry {

Point::Point() :
    mX{0}, mY{0} {
    setColors({});
}

Point::Point(const int& x, const int& y) :
    mX{x}, mY{y} {
    setColors({});
}

Point::Point(const int& x, const int& y,
    const Color& color) :
    mX{x}, mY{y} {
    setColors(std::make_pair<Color, Color>({
        color.red, color.green, color.blue, color.alpha}, {}));
}

auto Point::getX() const -> const int {
    return mX;
}

auto Point::getY() const -> const int {
    return mY;
}

auto Point::getCoordinates() const -> const std::pair<int, int> {
    return {mX, mY};
}

auto Point::setX(const int& x) -> void {
    mX = x;
}

auto Point::setY(const int& y) -> void {
    mY = y;
}

auto Point::setCoordinates(const int& x, const int& y) -> void {
    mX = x;
    mY = y;
}

}  // namespace geometry
}  // namespace cgl
