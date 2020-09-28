// Copyright 2020. Ulysses Don Rieken

#ifndef CGL_INC_ERROR_CGL_ERROR_HPP_
#define CGL_INC_ERROR_CGL_ERROR_HPP_

#include <string>
#include <type_traits>
#include <system_error>

namespace cgl {
namespace error {

enum class CGL_ERROR {
    UNKNOWN = -1,
    NO_ERROR
};

}  // namespace error
}  // namespace cgl

namespace std {
template<>
struct is_error_code_enum<cgl::error::CGL_ERROR> : true_type {};
}  // namespace std

namespace cgl {
namespace error {

auto make_error_code(const cgl::error::CGL_ERROR& code)
    -> std::error_condition;

class cglErrorCategory : public std::error_category {
 public:
    virtual auto name() const noexcept -> const char*;
    virtual auto equivalent(const std::error_code& code,
        int condition) const noexcept -> bool;
    virtual auto message(int code) const -> std::string;
};

}  // namespace error
}  // namespace cgl

#endif  // CGL_INC_ERROR_CGL_ERROR_HPP_
