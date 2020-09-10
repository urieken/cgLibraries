// Copyright 2020. Ulysses Don Rieken

#include <sstream>

#include <compilers/compilers.hpp>

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
