/**
 * @file KeyPairString.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Source for KeyPair
 * @version 0.1
 * @date 2021-10-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <system/KeyPairString.hpp>

#include <regex>

namespace cgl {
namespace system {

KeyPairString::KeyPairString(const std::string& allowedCharacters,
    const std::string& delimeter) :
    mAllowedCharacters{allowedCharacters},
    mDelimeter{delimeter} {
}

auto KeyPairString::IsValid(const std::string& inputString) const -> bool {
    const std::regex expression{std::string(mAllowedCharacters)
        .append(mDelimeter).append(mAllowedCharacters)};
    return std::regex_match(inputString, expression);
}

auto KeyPairString::Parse(const std::string& inputString) const
    -> KeyValuePair {
    const std::regex expression{std::string(mAllowedCharacters)
        .append(mDelimeter).append(mAllowedCharacters)};
    std::smatch pieces;
    if (std::regex_match(inputString, pieces, expression)) {
        return { pieces[1].str(), pieces[2].str() };
    }
    return {};
}

}  // namespace system
}  // namespace cgl
