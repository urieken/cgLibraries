/**
 * @file Arguments.cpp
 * @author Ulysses Don Rieken(ulysses.rieken@gmail.com)
 * @brief Source for Arguments.
 * @version 0.1
 * @date 2021-10-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <system/Arguments.hpp>

#include <error/CGLError.hpp>
#include <system/KeyPairString.hpp>

#include <stdexcept>

#include <SDL2/SDL.h>

namespace Error = ::cgl::error;

using Code = Error::ErrorCode;

namespace cgl {
namespace system {

auto Arguments::GetProperty(const std::string& key) const
    -> std::optional<std::string> {
    try {
        return std::string{mProperties.at(key)};
    } catch (const std::out_of_range& except) {
        ::SDL_Log("Exception occurred : %s", except.what());
        return {};
    }
}

auto Arguments::ProcessInputStream(std::istream& inputStream,
    const std::string& allowedCharacters, const std::string& delimeter,
    const std::string& commentStart)
    -> std::error_condition {
    std::string line{};
    KeyPairString keyPair{allowedCharacters, delimeter};

    while(std::getline(inputStream, line)) {
        if (line.rfind(commentStart) != 0UL) {
            if (keyPair.IsValid(line)) {
                auto keyValuePair = keyPair.Parse(line);
                mProperties[keyValuePair.key] = keyValuePair.value;
            } else {
                return Error::makeErrorCondition(Code::MalformedKeyPair);
            }
        }
    }
    return Error::makeErrorCondition(Code::NoError);
}

}  // namespace system
}  // namespace cgl
