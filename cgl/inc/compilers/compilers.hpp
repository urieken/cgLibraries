// Copyright 2020. Ulysses Don Rieken

#ifndef COMMON_INCLUDE_COMPILERS_COMPILERS_HPP_
#define COMMON_INCLUDE_COMPILERS_COMPILERS_HPP_
#if defined(__clang__)
#define COMPILER_NAME "CLANG"
#define COMPILER_MAJOR __clang_major__
#define COMPILER_MINOR __clang_minor__
#define COMPILER_PATCHLEVEL __clang_patchlevel__
#define FUNCTION_NAME __PRETTY_FUNCTION__
#elif defined(__GNUC___) || defined(__GNUG__)
#define COMPILER_NAME "GNU"
#define COMPILER_MAJOR __GNUC__
#define COMPILER_MINOR __GNUC_MINOR__
#define COMPILER_PATCHLEVEL __GNUC_PATCHLEVEL__
#define FUNCTION_NAME __PRETTY_FUNCTION__
#elif defined(__MINGW32__)
#define COMPILER_NAME "MINGW32"
#define COMPILER_MAJOR __MINGW32_MAJOR_VERSION
#define COMPILER_MINOR __MINGW32_MINOR_VERSION
#define COMPILER_PATCHLEVEL 0
#define FUNCTION_NAME __PRETTY_FUNCTION__
#elif defined(__MINGW64__)
#define COMPILER_NAME "MINGW64"
#define COMPILER_MAJOR __MINGW64_MAJOR_VERSION
#define COMPILER_MINOR __MINGW64_MINOR_VERSION
#define COMPILER_PATCHLEVEL 0
#define FUNCTION_NAME __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
#define COMPILER_NAME "MSC"
#define COMPILER_MAJOR _MSC_VER
#define COMPILER_MINOR _MSC_VER
#define COMPILER_PATCHLEVEL _MSC_VER
#define FUNCTION_NAME __FUNC__
#endif
#include <string>
#include <cstdint>
namespace cgl {
class Compilers {
    Compilers() = default;
    ~Compilers() = default;
    Compilers(const Compilers&) = delete;
    Compilers(Compilers&&) = delete;
    Compilers& operator = (const Compilers&) = delete;
    Compilers& operator = (Compilers&&) = delete;

 public:
    static const std::string name();
    static const std::string versionString();
    static const std::uint8_t majorVersion();
    static const std::uint8_t minorVersion();
    static const std::uint8_t patchLevel();
};
}  // namespace cgl
#endif  // COMMON_INCLUDE_COMPILERS_COMPILERS_HPP_
