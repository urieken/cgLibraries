/**
 * @file main.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Entry point for sanbox
 * @version 0.1
 * @date 2021-09-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <application/AppRunner.hpp>

#include <application/SDLSandboxApplication.hpp>
#include <application/SDLApplication.hpp>

#include <display/SDLRenderer.hpp>
#include <display/SDLWindow.hpp>

#include <error/CGLError.hpp>

#include <event/SDLEventListener.hpp>

#include <system/Arguments.hpp>
#include <system/Compilers.hpp>

#include <cstdio>
#include <fstream>
#include <string>
#include <sstream>

namespace Application = ::cgl::application;
namespace Display = ::cgl::display;
namespace Error = ::cgl::error;
namespace Event = ::cgl::event;
namespace System = ::cgl::system;

namespace SandboxApplication = ::cgl::application::sandbox;

using Code = Error::ErrorCode;

constexpr auto default_config{"res/config/default_config"};

auto main(int argc, char** argv) -> int {
    auto compiler = System::Compilers{};
    std::printf("Compiled with : %s %s\n",compiler.name().c_str(),
        compiler.versionString().c_str());
    std::ifstream configFile{default_config};
    if (configFile.is_open()) {
        System::Arguments args{};
        auto parseResult = args.ProcessInputStream(configFile,
            "([a-zA-Z0-9 \\_\\-]+)");
        if (static_cast<int>(Code::NoError) == parseResult.value()) {
            Application::AppRunner<SandboxApplication::SDLSandboxApplication,
                Event::SDLEventListener>appRunner{args};
            return appRunner.Run();
        } else {
            std::printf("Failed to parse input stream : %s\n",
                parseResult.message().c_str());
        }
    } else {
        std::printf("Failed to open file : %s\n", default_config);
    }
    return -1;
}