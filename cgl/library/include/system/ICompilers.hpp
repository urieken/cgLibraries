/**
 * @file ICompilers.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for Compilers interface
 * @version 0.1
 * @date 2021-09-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_SYSTEM_ICOMPILERS_HPP_
#define CGL_LIBRARY_INCLUDE_SYSTEM_ICOMPILERS_HPP_

#include <cstdint>
#include <string>

namespace cgl {
namespace system {
/**
 * @brief Interface for Compilers. 
 */
class ICompilers {
public:
    virtual ~ICompilers() = default;
    /**
     * @brief Returns the compiler name string.
     * 
     * @return const std::string The compiler name string.
     */
    virtual auto name() const -> const std::string = 0;   
    /**
     * @brief Returns the compiler version string.
     * 
     * @return const std::string The compiler version string.
     */
    virtual auto versionString() const -> const std::string = 0;
    /**
     * @brief Returns the compiler major version.
     * 
     * @return std::uint8_t The compiler major version.
     */
    virtual auto majorVersion() const -> const std::uint8_t = 0;
    /**
     * @brief Returns the compiler minor version.
     * 
     * @return std::uint8_t The compiler minor version.
     */
    virtual auto minorVersion() const -> const std::uint8_t = 0;
    /**
     * @brief Returns the compiler patch level.
     * 
     * @return std::uint8_t The compiler patch level.
     */
    virtual auto patchLevel() const -> const std::uint8_t = 0;
};

}  // namespaced system
}  // namespace cgl


#endif /* CGL_LIBRARY_INCLUDE_SYSTEM_ICOMPILERS_HPP_ */
