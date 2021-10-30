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

#include <application/SDLApplication.hpp>

#include <display/SDLWindow.hpp>
#include <display/SDLRenderer.hpp>
#include <event/CoreEvent.hpp>

#include <regex>
#include <sstream>
#include <vector>

namespace Display = ::cgl::display;
namespace Event = ::cgl::event;
namespace System = ::cgl::system;

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
/**
 * @brief Get the integer value of the given key.
 * 
 * @param key The key for the property.
 * @param args The Arguments instance containing the values.
 * @return const int The value for the key.
 */
auto GetIntegerProperty(const std::string& key,
    const System::Arguments& args) -> const int {
    auto value = args.GetProperty(key);
    return std::stoi(value.value_or("0"));
}

SDLApplication::SDLApplication(const System::Arguments& args) :
    mArguments{args}, mWindow{nullptr}, mRenderer{nullptr},
    mUpdateRequested{false} {
}

SDLApplication::~SDLApplication() {
}

auto SDLApplication::OnEvent(const Event::IEvent& event) -> bool {
    bool result{true};
    if (Event::EventSource::SDL == event.Source()) {
        auto data = static_cast<const SDL_Event*>(event.Data());
        switch(data->type) {
            case SDL_QUIT : {
                Cleanup();
                result = false;
            }break;
            case SDL_KEYDOWN : {
                result = OnKeyDownEvent(data->key);
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
    OnUpdate();
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

auto SDLApplication::Setup() -> bool {
    ::SDL_Log("Setting up SDLApplication");
    auto initFlags
        = ProcessSDLFlags(GetStringProperty("sdl_init_flags", mArguments));
    if (0 != ::SDL_Init(initFlags)) {
        ::SDL_LogCritical(SDL_LOG_CATEGORY_ERROR,
            "Failed to initialize SDL. Error = %s", ::SDL_GetError());
        return false;
    }
    mWindow = std::make_unique<Display::SDLWindow>(
        GetStringProperty("name", mArguments),
        GetIntegerProperty("top", mArguments),
        GetIntegerProperty("left", mArguments),
        GetIntegerProperty("width", mArguments),
        GetIntegerProperty("height", mArguments),
        GetIntegerProperty("sdl_window_flags", mArguments));
    mRenderer = std::make_unique<Display::SDLRenderer>(
        mWindow->GetId(), -1, SDL_RENDERER_ACCELERATED);
    return nullptr != mRenderer;
}

auto SDLApplication::Cleanup() -> void {
    ::SDL_Log("Shutting down SDL");
    ::SDL_Quit();
}

auto SDLApplication::OnKeyDownEvent(const SDL_KeyboardEvent& event) -> bool {
    switch(event.keysym.sym) {
        case SDLK_r : {
            mRenderer->SetDrawColor(255UL, 0UL, 0UL, 255UL);
            mUpdateRequested = true;
        } break;
        case SDLK_g : {
            mRenderer->SetDrawColor(0UL, 255UL, 0UL, 255UL);
            mUpdateRequested = true;
        } break;
        case SDLK_b : {
            mRenderer->SetDrawColor(0UL, 0UL, 255UL, 255UL);
            mUpdateRequested = true;
        } break;
        default:break;
    }
    return true;
}

auto SDLApplication::OnKeyUpEvent(const SDL_KeyboardEvent& event) -> bool {
    bool result{true};
    switch(event.keysym.sym) {
        case SDLK_ESCAPE : {
            Cleanup();
            result = false;
        } break;
        default:break;
    }
    return result;
}

auto SDLApplication::OnUpdate() -> void {
    if (mUpdateRequested) {
        mRenderer->Clear();
        mRenderer->Present();
        mUpdateRequested = false;
    }
}

}  // namespace application
}  // namespace cgl
