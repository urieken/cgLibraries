/**
 * @file Line.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for Line
 * @version 0.1
 * @date 2021-11-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_GEOMETRY_LINE_HPP_
#define CGL_LIBRARY_INCLUDE_GEOMETRY_LINE_HPP_

#include <geometry/IGeometryElement.hpp>

#include <display/Color.hpp>

#include <cstdint>
#include <utility>

namespace cgl {
namespace geometry {
/**
 * @brief Wrapper class for line coordinates.
 */
class Line : public IGeometryElement {
public:
    /**
     * @brief Construct a new Line object
     */
    Line();
    /**
     * @brief Construct a new Line object
     * 
     * @param begin The starting point of the line.
     * @param end The ending point of the line.
     */
    Line(std::pair<std::int16_t, std::int16_t> begin,
        std::pair<std::int16_t, std::int16_t> end);
    /**
     * @brief Construct a new Line object
     * 
     * @param begin The starting point of the line.
     * @param end The ending point of the line.
     * @param color The draw color.
     */
    Line(std::pair<std::int16_t, std::int16_t> begin,
        std::pair<std::int16_t, std::int16_t> end,
        const ::cgl::display::Color& color);
};

}  // namespace geometry
}  // namespace cgl

#endif /* CGL_LIBRARY_INCLUDE_GEOMETRY_LINE_HPP_ */
