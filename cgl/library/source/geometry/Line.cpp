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

#include <SDL2/SDL.h>

using Color = ::cgl::display::Color;

namespace cgl {
namespace geometry {

Line::Line() : mBegin{}, mEnd{} {
    setColors({});
}

Line::Line(std::pair<std::int16_t, std::int16_t> begin,
    std::pair<std::int16_t, std::int16_t> end) :
    mBegin{begin}, mEnd{} {
    setColors({});
}

Line::Line(std::pair<std::int16_t, std::int16_t> begin,
    std::pair<std::int16_t, std::int16_t> end, const Color& color) :
    mBegin{begin}, mEnd{end} {
    setColors(std::make_pair<Color, Color>({
        color.red, color.green, color.blue, color.alpha}, {}));
    ::SDL_Log("METHOD : %s\n", __PRETTY_FUNCTION__);
    ::SDL_Log("BEGIN : %d, %d\nEND : %d, %d",
        mBegin.first, mBegin.second, mEnd.first, mEnd.second);
}

auto Line::setBegin(const std::pair<std::int16_t,
        std::int16_t>& begin) -> void {
    mBegin = begin;
}

auto Line::getBegin() const -> std::pair<std::int16_t, std::int16_t> {
    ::SDL_Log("METHOD : %s\n", __PRETTY_FUNCTION__);
    ::SDL_Log("BEGIN : %d, %d\nEND : %d, %d",
        mBegin.first, mBegin.second, mEnd.first, mEnd.second);
    return mBegin;
}

auto Line::setEnd(const std::pair<std::int16_t,
        std::int16_t>& end) -> void {
    mEnd = end;
}

auto Line::getEnd() const -> std::pair<std::int16_t, std::int16_t> {
    ::SDL_Log("METHOD : %s\n", __PRETTY_FUNCTION__);
    ::SDL_Log("BEGIN : %d, %d\nEND : %d, %d",
        mBegin.first, mBegin.second, mEnd.first, mEnd.second);
    return mEnd;
}

}  // namespace geometry
}  // namespace cgl
