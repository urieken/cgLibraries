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
    /**
     * @brief Set the starting point of the line.
     * 
     * @param begin The starting point of the line.
     */
    auto setBegin(const std::pair<std::int16_t,
        std::int16_t>& begin) -> void;
    /**
     * @brief Get the starting point of the line.
     * 
     * @return std::pair<std::int16_t, std::int16_t>
     * The starting point of the line.
     */
    auto getBegin() const -> std::pair<std::int16_t, std::int16_t>;
    /**
     * @brief Set the ending point of the line.
     * 
     * @param end The ending point of the line.
     */
    auto setEnd(const std::pair<std::int16_t,
        std::int16_t>& end) -> void;
    /**
     * @brief Get the ending point of the line.
     * 
     * @return std::pair<std::int16_t, std::int16_t>
     * The ending point of the line.
     */
    auto getEnd() const -> std::pair<std::int16_t, std::int16_t>;
private:
    /**
     * @brief The starting point of the line.
     */
    std::pair<std::int16_t, std::int16_t> mBegin;
    /**
     * @brief The ending point of the line.
     */
    std::pair<std::int16_t, std::int16_t> mEnd;
};

}  // namespace geometry
}  // namespace cgl

#endif /* CGL_LIBRARY_INCLUDE_GEOMETRY_LINE_HPP_ */
