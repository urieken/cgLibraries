/**
 * @file Rect.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Source for Rect
 * @version 0.1
 * @date 2021-11-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_DISPLAY_IRECT_HPP_
#define CGL_LIBRARY_INCLUDE_DISPLAY_IRECT_HPP_

namespace cgl {
namespace display {

/**
 * @brief The rectangle structure.
 */
struct Rect {
    /**
     * @brief The top coordinate.
     */
    int top;
    /**
     * @brief The left coordinate.
     */
    int left;
    /**
     * @brief The rectnagle's width
     */
    int width;
    /**
     * @brief The rectnagle's height
     */
    int height;
};

}  // namespace display
}  // namespace cgl

#endif /* CGL_LIBRARY_INCLUDE_DISPLAY_IRECT_HPP_ */
