/**
 * @file Compilers.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for Compilers
 * @version 0.1
 * @date 2021-09-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_SYSTEM_COMPILERS_HPP_
#define CGL_LIBRARY_INCLUDE_SYSTEM_COMPILERS_HPP_

#include <system/ICompilers.hpp>

namespace cgl {
namespace system {
/**
 * @brief Interface for Compilers. 
 */
class Compilers final : public ICompilers {
public:
    virtual ~Compilers() = default;
    /**
     * @brief Returns the compiler name string.
     * 
     * @return const std::string The compiler name string.
     */
    auto name() const -> const std::string override;   
    /**
     * @brief Returns the compiler version string.
     * 
     * @return const std::string The compiler version string.
     */
    auto versionString() const -> const std::string override;
    /**
     * @brief Returns the compiler major version.
     * 
     * @return std::uint8_t The compiler major version.
     */
    auto majorVersion() const -> const std::uint8_t override;
    /**
     * @brief Returns the compiler minor version.
     * 
     * @return std::uint8_t The compiler minor version.
     */
    auto minorVersion() const -> const std::uint8_t override;
    /**
     * @brief Returns the compiler patch level.
     * 
     * @return std::uint8_t The compiler patch level.
     */
    auto patchLevel() const -> const std::uint8_t override;
};

}  // namespaced system
}  // namespace cgl


#endif /* CGL_LIBRARY_INCLUDE_SYSTEM_COMPILERS_HPP_ */
