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
    IGeometryElement{{}} {
    setColors({});
}

Point::Point(const std::int16_t& x, const std::int16_t& y) :
    IGeometryElement{{x, y}} {
    setColors({});
}

Point::Point(const std::int16_t& x, const std::int16_t& y,
    const Color& color) :
    IGeometryElement{{x, y}} {
    setColors(std::make_pair<Color, Color>({
        color.red, color.green, color.blue, color.alpha}, {}));
}

}  // namespace geometry
}  // namespace cgl
