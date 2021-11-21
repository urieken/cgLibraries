/**
 * @file Rectangle.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.co)
 * @brief Source for Rectangle
 * @version 0.1
 * @date 2021-11-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <geometry/Rectangle.hpp>

using Color = ::cgl::display::Color;

namespace cgl {
namespace geometry {

Rectangle::Rectangle() : IGeometryElement{{}} {
    setColors({});
}

Rectangle::Rectangle(const std::pair<int, int>& topLeft,
    const std::pair<int, int>& bottomRight) :
    IGeometryElement{{
        topLeft.first,
        topLeft.second,
        bottomRight.first,
        bottomRight.second
    }} {
    setColors({});
}

Rectangle::Rectangle(const std::pair<int, int>& topLeft,
    const std::pair<int, int>& bottomRight,
    const std::pair<::cgl::display::Color,
        ::cgl::display::Color>& colors) :
    IGeometryElement{{
        topLeft.first,
        topLeft.second,
        bottomRight.first,
        bottomRight.second
    }} {
    setColors(colors);
}

}  // namespace geometry
}  // namespace cgl
