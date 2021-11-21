/**
 * @file Rectangle.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for Rectangle
 * @version 0.1
 * @date 2021-11-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_GEOMETRY_RECTANGLE_HPP_
#define CGL_LIBRARY_INCLUDE_GEOMETRY_RECTANGLE_HPP_

#include <geometry/IGeometryElement.hpp>

#include <display/Color.hpp>

#include <cstdint>
#include <utility>

namespace cgl {
namespace geometry {
/**
 * @brief Wrapper class for rectangle coordinates.
 */
class Rectangle : public IGeometryElement {
public:
    /**
     * @brief Construct a new Rectangle object
     */
    Rectangle();
    /**
     * @brief Construct a new Rectangle object
     * 
     * @param topLeft The top left corner of the Rectangle.
     * @param bottomRight The bottom right corder for the Rectangle.
     */
    Rectangle(const std::pair<int, int>& topLeft,
        const std::pair<int, int>& bottomRight);
    /**
     * @brief Construct a new Rectangle object
     * 
     * @param topLeft The top left corner of the Rectangle.
     * @param bottomRight The bottom right corder for the Rectangle.
     * @param colors The draw and fill colors.
     */
    Rectangle(const std::pair<int, int>& topLeft,
        const std::pair<int, int>& bottomRight,
        const std::pair<::cgl::display::Color,
            ::cgl::display::Color>& colors);
};

}  // namespace geometry
}  // namespace cgl

#endif /* CGL_LIBRARY_INCLUDE_GEOMETRY_RECTANGLE_HPP_ */
