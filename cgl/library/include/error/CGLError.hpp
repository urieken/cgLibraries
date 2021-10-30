/**
 * @file CGLError.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for CGLError
 * @version 0.1
 * @date 2021-10-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_ERROR_CGL_ERROR_HPP_
#define CGL_LIBRARY_INCLUDE_ERROR_CGL_ERROR_HPP_

#include <string>
#include <system_error>
#include <type_traits>

namespace cgl {
namespace error {
/**
 * @brief The error code enumeration.
 */
enum class ErrorCode {
    NoError = 0UL,
    MalformedKeyPair,
    ImageLoadFailure,
    TextureCreationFailure,
    /**
     * @brief The max value for error code.
     * 
     * @note New entries for error code should be added
     * before this.
     */
    Unknown
};

}  // namespace error
}  // namespace cgl

namespace std {
/**
 * @brief Verify if a value is of ErrorCode.
 */
template<>
struct is_error_code_enum<::cgl::error::ErrorCode> : true_type {
};
}  // namespace std

namespace cgl {
namespace error {
/**
 * @brief Create an instance of std::error_condition.
 * 
 * @param code The ErrorCode value to be used.
 * @return std::error_condition The std::error_condition instance.
 */
auto makeErrorCondition(const ::cgl::error::ErrorCode& code)
    -> std::error_condition;
/**
 * @brief Error category for common errors.
 */
class CGLError final : public std::error_category {
public:
    /**
     * @brief Gets the error condition name.
     * 
     * @return const char* The condition name.
     */
    auto name() const noexcept -> const char* override;
    /**
     * @brief Gets the error message for the error code.
     * 
     * @param code The error code.
     * @return std::string The erroe message.
     */
    auto message(int code) const -> std::string override;
};

}  // namespace error
}  // namespace cgl

#endif /* CGL_LIBRARY_INCLUDE_ERROR_CGL_ERROR_HPP_ */
