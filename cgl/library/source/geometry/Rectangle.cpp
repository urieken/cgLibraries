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

#include <SDL2/SDL.h>

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
    ::SDL_Log("DRAW COLOR: R:%d nG:%d B:%d A:%d\n",
        colors.first.red, colors.first.green,
        colors.first.blue, colors.first.alpha);
    ::SDL_Log("FILL COLOR: R:%d G:%d B:%d A:%d\n",
        colors.second.red, colors.second.green,
        colors.second.blue, colors.second.alpha);
    auto clr = getColors();
    ::SDL_Log("DRAW COLOR: R:%d G:%d B:%d A:%d\n",
        clr.first.red, clr.first.green,
        clr.first.blue, clr.first.alpha);
    ::SDL_Log("FILL COLOR: R:%d G:%d B:%d A:%d\n",
        clr.second.red, clr.second.green,
        clr.second.blue, clr.second.alpha);
}

}  // namespace geometry
}  // namespace cgl
