/**
 * @file Arguments.hpp
 * @author Ulysses Don Rieken(ulysses.rieken@gmail.com)
 * @brief Header for Arguments
 * @version 0.1
 * @date 2021-10-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_SYSTEM_ARGUMENTS_HPP_
#define CGL_LIBRARY_INCLUDE_SYSTEM_ARGUMENTS_HPP_

#include <optional>
#include <sstream>
#include <string>
#include <system_error>
#include <unordered_map>

namespace cgl {
namespace system {

/**
 * @brief Wrapper for processed command line arguments.
 */
class Arguments final {
public:
    Arguments() = default;
    Arguments(const Arguments&) = default;
    Arguments(Arguments&&) = default;
    ~Arguments() = default;
    Arguments& operator=(const Arguments&) = default;
    Arguments& operator=(Arguments&&) = default;
    /**
     * @brief Process input stream.
     * 
     * @param inputStream The input stream.
     * @param allowedCharacters Allowed characters for key and value strings.
     * @param delimeter The delimeter for key and value strings.
     * @param commentStart The start for a comment line.
     * @return std::error_condition The error condition.
     */
    auto ProcessInputStream(std::istream& inputStream,
        const std::string& allowedCharacters = "([a-zA-Z0-9\\-]+)",
        // const std::string& allowedCharacters = "/^\\w+$/",
        const std::string& delimeter = ":",
        const std::string& commentStart = "#")
        -> std::error_condition;
    /**
     * @brief Get the named property.
     * 
     * @param key The key for the property.
     * @return std::optional<std::string> The property.
     */
    auto GetProperty(const std::string& key) const
        -> std::optional<std::string>;
private:
    /**
     * @brief The processed arguments.
     */
    std::unordered_map<std::string, std::string> mProperties;
};

}  // namespace system
}  // namespace cgl

#endif /* CGL_LIBRARY_INCLUDE_SYSTEM_ARGUMENTS_HPP_ */
