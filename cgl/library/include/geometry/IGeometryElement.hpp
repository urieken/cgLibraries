/**
 * @file IGeometryElement.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com4)
 * @brief Header for geometry element interface.
 * @version 0.1
 * @date 2021-11-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_SOURCE_GEOMETRY_IGEOMETRY_ELEMENT_HPP_
#define CGL_LIBRARY_SOURCE_GEOMETRY_IGEOMETRY_ELEMENT_HPP_

#include <display/Color.hpp>

#include <utility>
#include <vector>

namespace cgl {
namespace geometry {
/**
 * @brief Interface for geometry elements.
 */
class IGeometryElement {
public:
    IGeometryElement() = delete;
    virtual ~IGeometryElement() = default;
    /**
     * @brief Construct a new IGeometryElement object
     * 
     * @param coordinates The coordinate set for the element.
     */
    explicit IGeometryElement(const std::vector<int>& coordinates) :
        mCoordinates{coordinates} {}
    /**
     * @brief Set the draw and fill colors.
     * 
     * @param colors The draw and fill colors.
     */
    auto setColors(const std::pair<::cgl::display::Color,
        ::cgl::display::Color>& colors) -> void {
        mColors.first = colors.first;
        mColors.second = colors.second;
    }
    /**
     * @brief Get the draw and fill colors.
     * 
     * @return std::pair<::cgl::display::Color,
     * ::cgl::display::Color> The draw and fill colors.
     */
    auto getColors() const -> std::pair<::cgl::display::Color,
        ::cgl::display::Color> {
        return mColors;
    }
    /**
     * @brief Set the draw color.
     * 
     * @param color The draw color.
     */
    auto setDrawColor(const ::cgl::display::Color& color) -> void {
        mColors.first = color;
    }
    /**
     * @brief Get the draw color.
     * 
     * @return ::cgl::display::Color The draw color.
     */
    auto getDrawColor() const -> ::cgl::display::Color {
        return mColors.first;
    }
    /**
     * @brief Set the fill color.
     * 
     * @param color The fill color.
     */
    auto setFillColor(const ::cgl::display::Color& color) -> void {
        mColors.second = color;
    }
    /**
     * @brief Get the fill color.
     * 
     * @return ::cgl::display::Color The fill color.
     */
    auto getFillColor() const -> ::cgl::display::Color {
        return mColors.second;
    }
    /**
     * @brief Set the coordinate set for the element.
     * 
     * @param coordinates The coordinate set for the element.
     */
    auto setCoordinates(const std::vector<int>& coordinates) -> void {
        mCoordinates = coordinates;
    }
    /**
     * @brief Get the coordinate set for the element.
     * 
     * @return std::vector<int> The coordinate set for the element.
     */
    auto getCoordinates() const -> std::vector<int> {
        return mCoordinates;
    }
private:
    /**
     * @brief The coordinate set for the element.
     */
    std::vector<int> mCoordinates;
    /**
     * @brief The draw(first) and fill(second) colors.
     */
    std::pair<::cgl::display::Color,
        ::cgl::display::Color> mColors;
};

}  // namespace geometry
}  // namespace cgl

#endif /* CGL_LIBRARY_SOURCE_GEOMETRY_IGEOMETRY_ELEMENT_HPP_ */
