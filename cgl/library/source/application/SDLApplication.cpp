/**
 * @file SDLApplication.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Source for SDL application base.
 * @version 0.1
 * @date 2021-10-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <SDL2/SDL_version.h>
#include <application/SDLApplication.hpp>

#include <error/CGLError.hpp>
#include <event/CoreEvent.hpp>

#include <regex>
#include <sstream>
#include <vector>

#include <SDL2/SDL_image.h>

namespace Error = ::cgl::error;
namespace Event = ::cgl::event;
namespace System = ::cgl::system;

using Code = Error::ErrorCode;

namespace cgl {
namespace application {

/**
 * @brief Get the string value of the given key.
 * 
 * @param key The key for the property.
 * @param args The Arguments instance containing the values.
 * @return const std::string The value for the key.
 */
auto GetStringProperty(const std::string& key,
    const System::Arguments& args) -> const std::string {
    auto value = args.GetProperty(key);
    return value.value_or("");
}

SDLApplication::SDLApplication(const System::Arguments& args) :
    mArguments{args} {
}

SDLApplication::~SDLApplication() {
    Cleanup();
}

auto SDLApplication::OnEvent(const Event::IEvent& event) -> bool {
    bool result{true};
    if (Event::EventSource::SDL == event.Source()) {
        auto data = static_cast<const SDL_Event*>(event.Data());
        switch(data->type) {
            case SDL_QUIT : {
                // Cleanup();
                result = false;
            }break;
            case SDL_KEYUP : {
                result = OnKeyUpEvent(data->key);
            }break;
            default:break;
        }
    } else {
        switch (event.Type()) {
            case Event::EventType::Init : {
                result = Setup();
            }break;
            default : break;
        }
    }
    return result;
}

auto SDLApplication::ProcessSDLFlags(const std::string& flags) const
    -> const std::int32_t {
    std::int32_t value{0};
    std::regex pattern{" "};
    std::vector<std::string> tokens{
        std::sregex_token_iterator(flags.begin(), flags.end(), pattern, -1),
        std::sregex_token_iterator()
    };
    for (auto& token : tokens) {
        std::int32_t tokenValue{0};
        std::stringstream ss;
        ss << std::hex << token;
        ss >> tokenValue;
        value |= tokenValue;
    }
    return value;
}

auto SDLApplication::OnIdle() -> void {
}

auto SDLApplication::Setup() -> bool {
    ::SDL_Log("Setting up SDLApplication");
    auto initFlags
        = ProcessSDLFlags(GetStringProperty("sdl_init_flags", mArguments));
    int imgFlags{IMG_INIT_PNG};
    if (0 != ::SDL_Init(initFlags) && (::IMG_Init(imgFlags) & imgFlags)) {
        ::SDL_LogCritical(SDL_LOG_CATEGORY_ERROR,
            "Failed to initialize SDL. Error = %s", ::SDL_GetError());
        return false;
    }
    SDL_version ver;
    ::SDL_GetVersion(&ver);
    ::SDL_Log("SDL Version : %d.%d.%d", ver.major, ver.minor, ver.patch);
    return true;
}

auto SDLApplication::Cleanup() -> void {
    ::SDL_Log("Shutting down SDL");
    ::SDL_Quit();
}

auto SDLApplication::OnKeyUpEvent(const SDL_KeyboardEvent& event) -> bool {
    bool result{true};
    switch(event.keysym.sym) {
        case SDLK_ESCAPE : {
            result = false;
        } break;
        default:break;
    }
    return result;
}

}  // namespace application
}  // namespace cgl
