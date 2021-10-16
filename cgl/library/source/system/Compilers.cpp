/**
 * @file Compilers.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Source code Compilers.
 * @version 0.1
 * @date 2021-09-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <system/Compilers.hpp>

#include <sstream>


#if defined(__clang__)
constexpr auto compilerName{"CLANG"};
constexpr auto compilerMajor{__clang_major__};
constexpr auto compilerMinor{__clang_minor__};
constexpr auto compilerPatchLevel{__clang_patchlevel__};
#define FUNCTION_NAME __PRETTY_FUNCTION__
#elif defined(__GNUC___) || defined(__GNUG__)
constexpr auto compilerName{"GNU"};
constexpr auto compilerMajor{__GNUC__};
constexpr auto compilerMinor{__GNUC_MINOR__};
constexpr auto compilerPatchLevel{__GNUC_PATCHLEVEL__};
#define FUNCTION_NAME __PRETTY_FUNCTION__
#elif defined(__MINGW32__)
constexpr auto compilerName{"MINGW32"};
constexpr auto compilerMajor{__MINGW32_MAJOR_VERSION};
constexpr auto compilerMinor{__MINGW32_MINOR_VERSION};
constexpr auto compilerPatchLevel{0};
#define FUNCTION_NAME __PRETTY_FUNCTION__
#elif defined(__MINGW64__)
constexpr auto compilerName{"MINGW64"};
constexpr auto compilerMajor{__MINGW64_MAJOR_VERSION};
constexpr auto compilerMinor{__MINGW64_MINOR_VERSION};
constexpr auto compilerPatchLevel{0};
#define FUNCTION_NAME __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
constexpr auto compilerName{"MSC"};
constexpr auto compilerMajor{_MSC_VER};
constexpr auto compilerMinor{_MSC_VER};
constexpr auto compilerPatchLevel{_MSC_VER};
#define FUNCTION_NAME ___FUNC__
#endif

namespace cgl {
namespace system {

auto Compilers::name() const -> const std::string {
    return std::string{compilerName};
}

auto Compilers::versionString() const -> const std::string {
    std::stringstream ss;
    ss << compilerMajor << "." << compilerMinor << "." << compilerPatchLevel;
    return ss.str();
}

auto Compilers::majorVersion() const -> const std::uint8_t {
    return compilerMajor;
}

auto Compilers::minorVersion() const -> const std::uint8_t {
    return compilerMinor;
}

auto Compilers::patchLevel() const -> const std::uint8_t {
    return compilerPatchLevel;
}

}  // namespace system
}  // namespace cgl
