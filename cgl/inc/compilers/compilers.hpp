// Copyright 2020. Ulysses Don Rieken

#ifndef COMMON_INCLUDE_COMPILERS_COMPILERS_HPP_
#define COMMON_INCLUDE_COMPILERS_COMPILERS_HPP_

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
