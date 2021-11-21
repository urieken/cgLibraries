/**
 * @file Line.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for Line
 * @version 0.1
 * @date 2021-11-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <geometry/Line.hpp>

using Color = ::cgl::display::Color;

namespace cgl {
namespace geometry {

Line::Line() : IGeometryElement{{}} {
    setColors({});
}

Line::Line(std::pair<int, int> begin,
    std::pair<int, int> end) :
    IGeometryElement{{
        begin.first,
        begin.second,
        end.first,
        end.second
    }} {
    setColors({});
}

Line::Line(std::pair<int, int> begin,
    std::pair<int, int> end, const Color& color) :
    IGeometryElement{{
        begin.first,
        begin.second,
        end.first,
        end.second
    }} {
    setColors(std::make_pair<Color, Color>({
        color.red, color.green, color.blue, color.alpha}, {}));
}

}  // namespace geometry
}  // namespace cgl
