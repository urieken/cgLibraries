/**
 * @file Point.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for Point
 * @version 0.1
 * @date 2021-11-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_GEOMETRY_POINT_HPP_
#define CGL_LIBRARY_INCLUDE_GEOMETRY_POINT_HPP_

#include <geometry/IGeometryElement.hpp>

#include <display/Color.hpp>

#include <cstdint>

namespace cgl {
namespace geometry {

/**
 * @brief Wrapper class for point coordinates.
 */
class Point : public IGeometryElement {
public:
    /**
     * @brief Construct a new Point object
     */
    Point();
    /**
     * @brief Construct a new Point object
     * 
     * @param x The x coordinate.
     * @param y The y coordinate.
     */
    Point(const std::int16_t& x,const std::int16_t& y);
    /**
     * @brief Construct a new Point object
     * 
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @param drawColor The draw color.
     */
    Point(const std::int16_t& x, const std::int16_t& y,
        const ::cgl::display::Color& drawColor);
};

}  // namespace geometry
}  // namespace cgl

#endif /* CGL_LIBRARY_INCLUDE_GEOMETRY_POINT_HPP_ */
