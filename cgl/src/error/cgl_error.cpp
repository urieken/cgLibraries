// Copyright 2020. Ulysses Don Rieken

#include <error/error_types.hpp>

namespace cgl {
namespace error {

constexpr auto UNKNOWN = "UNKNOWN";
constexpr auto NO_ERROR = "NO_ERROR";
constexpr auto CGL_ERROR_CATEGORY = "CGL_ERROR";

auto cglErrorCategory::name() const noexcept -> const char* {
    return CGL_ERROR_CATEGORY;
}

auto cglErrorCategory::equivalent(const std::error_code& code,
    int condition) const noexcept -> bool {
    return *this == code.category() &&
        static_cast<int>(
            default_error_condition(code.value()).value()) == condition;
}

auto cglErrorCategory::message(int code) const -> std::string {
    std::string msg{UNKNOWN};
    switch (static_cast<CGL_ERROR>(code)) {
        case CGL_ERROR::NO_ERROR : msg = NO_ERROR; break;
        default : {
            msg = UNKNOWN;
        } break;
    }
    return msg;
}

}  // namespace error
}  // namespace cgl

namespace {
cgl::error::cglErrorCategory cglErrorCategoryObj{};
}  // anonymous namespace

auto cgl::error::make_error_code(
    const cgl::error::CGL_ERROR& code) -> std::error_condition {
    return {static_cast<int>(code), cglErrorCategoryObj};
}
