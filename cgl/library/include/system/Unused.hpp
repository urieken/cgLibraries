/**
 * @file Unused.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for Unused
 * @version 0.1
 * @date 2021-10-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_SYSTEM_UNUSED_HPP_
#define CGL_LIBRARY_INCLUDE_SYSTEM_UNUSED_HPP_

namespace cgl {
namespace system {

template <typename...Args> 
auto unused(const Args&...) -> void { /* no-op */ } 

}  // namespace system
}  // namespace cgl

#endif /* CGL_LIBRARY_INCLUDE_SYSTEM_UNUSED_HPP_ */
