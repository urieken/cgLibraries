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

#include <application/SDLApplication.hpp>
#include <event/SDLEventListener.hpp>

#include <system/Compilers.hpp>

#include <cstdio>
#include <string>

namespace Application = ::cgl::application;
namespace Event = ::cgl::event;
namespace System = ::cgl::system;

auto main(int argc, char** argv) -> int {
    auto compiler = System::Compilers{};
    std::printf("Compiled with : %s %s\n",compiler.name().c_str(),
        compiler.versionString().c_str());
    Application::AppRunner<Application::SDLApplication,
        Event::SDLEventListener> appRunner{argc, argv};
    return appRunner.Run();
}