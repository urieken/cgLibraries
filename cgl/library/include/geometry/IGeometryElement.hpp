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

namespace cgl {
namespace geometry {
/**
 * @brief Interface for geometry elements.
 */
class IGeometryElement {
public:
    virtual ~IGeometryElement() = default;
};

}  // namespace geometry
}  // namespace cgl

#endif /* CGL_LIBRARY_SOURCE_GEOMETRY_IGEOMETRY_ELEMENT_HPP_ */
