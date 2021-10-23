/**
 * @file CGLError.cpp
 * @author Ulysses Don Rieken(ulysses.rieken@gmail.com)
 * @brief Source for CGLError
 * @version 0.1
 * @date 2021-10-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <error/CGLError.hpp>

namespace cgl {
namespace error {

constexpr auto NoError{"NoError"};
constexpr auto MalformedKeyPair{"MalformedKeyPair"};
constexpr auto Unknown{"Unknown"};
constexpr auto CGLErrorCategory{"CGLErrorCategory"};

auto CGLError::name() const noexcept -> const char* {
    return CGLErrorCategory;
}

auto CGLError::message(int code) const -> std::string {
    std::string message{Unknown};
    switch (static_cast<ErrorCode>(code)) {
    case ErrorCode::NoError : message =  NoError; break;
    case ErrorCode::MalformedKeyPair : message = MalformedKeyPair; break;
    case ErrorCode::Unknown : message = Unknown;[[fallthrough]];
    default:break;
    }
    return message;
}

auto makeErrorCondition(const ErrorCode& code) -> std::error_condition {
    static CGLError cglError{};
    return {static_cast<int>(code), cglError};
}

}  // namespace error
}  // namespace cgl
