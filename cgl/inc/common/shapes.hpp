// Copyright 2020, Ulysses Don Rieken
/*! \file shapes.hpp
    \brief Header for shapes structures.

    Basic shapes.
 */
#ifndef CGL_INC_COMMON_SHAPES_HPP_
#define CGL_INC_COMMON_SHAPES_HPP_

#include <cstdint>

//! Crazy Galen's Libraries
namespace cgl {
    /*!
 * \addtogroup cgl
 * @{
 */
//! Crazy Galen's common classes.
namespace common {
/*!
 * \addtogroup common
 * @{
 */
//! Point struture
template <typename T>
struct Point {
    //! X coordinate.
    T x;
    //! Y coordinate.
    T y;
};
//! Rect structure
template <typename T>
struct Rect {
    //! Top of the window.
    T top;
    //! Left side of the window.
    T left;
    //! Width of the shape.
    T width;
    //! Height of the shape.
    T height;
};

/*! @} End of Doxygen Groups*/
}  // namespace common
/*! @} End of Doxygen Groups*/
}  // namespace cgl

#endif  // CGL_INC_COMMON_SHAPES_HPP_
