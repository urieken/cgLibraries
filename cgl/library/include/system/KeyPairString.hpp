/**
 * @file KeyPairString.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for KeyPair
 * @version 0.1
 * @date 2021-10-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#ifndef CGL_LIBRARY_INCLUDE_SYSTEM_KEYPAIR_STRING_HPP_
#define CGL_LIBRARY_INCLUDE_SYSTEM_KEYPAIR_STRING_HPP_

#include <string>

namespace cgl {
namespace system {

/**
 * @brief Key-value pair structure.
 */
struct KeyValuePair {
    /**
     * @brief The key string.
     */
    std::string key;
    /**
     * @brief The value string.
     */
    std::string value;
};

/**
 * @brief Wrapper class for key-pair string.
 */
class KeyPairString final {
public:
    KeyPairString() = delete;
    KeyPairString(const KeyPairString&) = delete;
    KeyPairString(KeyPairString&&) = delete;
    KeyPairString& operator=(const KeyPairString&) = delete;
    KeyPairString& operator=(KeyPairString&&) = delete;
    ~KeyPairString() = default;
    /**
     * @brief Construct a new KeyPair object
     * 
     * @param allowedCharacters Allowed characters for key and value strings.
     * @param delimeter The delimeter for key and value strings.
     */
    KeyPairString(const std::string& allowedCharacters,
        const std::string& delimeter);
    /**
     * @brief Check of the input string is valid.
     * 
     * @param inputString The input string.
     * @return true Input string is valid.
     * @return false Input string is not valid.
     */
    auto IsValid(const std::string& inputString) const -> bool;
    /**
     * @brief Parse the valid input string.
     * 
     * @param inputString The input string.
     * @return KeyValuePair The key-value pair.
     * @sa KeyValuePair
     */
    auto Parse(const std::string& inputString) const -> KeyValuePair;
private:
    /**
     * @brief The input string.
     */
    std::string mAllowedCharacters;
    /**
     * @brief The delimeter for key and value.
     */
    std::string mDelimeter;
};

}  // namespace system
}  // namespace cgl

#endif /* CGL_LIBRARY_INCLUDE_SYSTEM_KEYPAIR_STRING_HPP_ */
