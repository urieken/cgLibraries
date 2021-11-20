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

#include <utility>

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
    Point(const int& x, const int& y);
    /**
     * @brief Retrieves the Point's x coortinate.
     * 
     * @return const int The x coordinate.
     */
    auto getX() const -> const int;
    /**
     * @brief Retrieves the Point's y coortinate.
     * 
     * @return const int The y coordinate.
     */
    auto getY() const -> const int;
    /**
     * @brief Get the x and y coordinates.
     * 
     * @return const std::pair<int, int> The x and y coordinates/
     */
    auto getCoordinates() const -> const std::pair<int, int>;
    /**
     * @brief Set the x coordinate.
     * 
     * @param x The x coordinate.
     */
    auto setX(const int& x) -> void;
    /**
     * @brief Set the y coordinate.
     * 
     * @param x The y coordinate.
     */
    auto setY(const int& y) -> void;
    /**
     * @brief Set the x and y coordinates.
     * 
     * @param x The x coordinate.
     * @param y The y coordinate.
     */
    auto setCoordinates(const int& x, const int& y) -> void;
private:
    /**
     * @brief The x coordinate.
     */
    int mX;
    /**
     * @brief The y coordinate.
     */
    int mY;
};

}  // namespace geometry
}  // namespace cgl

#endif /* CGL_LIBRARY_INCLUDE_GEOMETRY_POINT_HPP_ */
