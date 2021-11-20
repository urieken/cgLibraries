/**
 * @file Color.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for Color
 * @version 0.1
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_DISPLAY_COLOR_HPP_
#define CGL_LIBRARY_INCLUDE_DISPLAY_COLOR_HPP_

#include <cstdint>

namespace cgl {
namespace display {

/**
 * @brief The color structure.
 */
struct Color {
    std::uint8_t red;
    std::uint8_t green;
    std::uint8_t blue;
    std::uint8_t alpha;
};

}  // namespace display
}  // namespace cgl

#endif /* CGL_LIBRARY_INCLUDE_DISPLAY_COLOR_HPP_ */
