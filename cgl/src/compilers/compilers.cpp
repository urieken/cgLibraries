// Copyright 2020. Ulysses Don Rieken

#include <sstream>

#include <compilers/compilers.hpp>

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

namespace cgl {
const std::string Compilers::name() {
    return std::string(COMPILER_NAME);
}

const std::string Compilers::versionString() {
    std::stringstream stream;
    stream << COMPILER_MAJOR << "." << COMPILER_MINOR
           << "." << COMPILER_PATCHLEVEL;
    return stream.str();
}

const std::uint8_t Compilers::majorVersion() {
    return COMPILER_MAJOR;
}

const std::uint8_t Compilers::minorVersion() {
    return COMPILER_MINOR;
}

const std::uint8_t Compilers::patchLevel() {
    return COMPILER_PATCHLEVEL;
}
}  // namespace cgl
