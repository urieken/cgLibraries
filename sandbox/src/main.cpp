// Copyright 2020. Ulysses Don Rieken

#include <SDL2/SDL.h>

#include <cstdio>
#include <iostream>

#include <common/shapes.hpp>
#include <error/error_types.hpp>
#include <compilers/compilers.hpp>

#include <sandbox_app.hpp>

auto main(int argc, char** argv) -> int {
    cgl::sandbox::SandboxApp app;
    std::error_code cglError{
        static_cast<int>(cgl::error::CGL_ERROR::NO_ERROR),
        cgl::error::cglErrorCategory{}};
    int code{0};
    std::printf("BUILT WITH %s : %s\n",
        cgl::Compilers::name().c_str(),
        cgl::Compilers::versionString().c_str());
    std::printf("[ARGC : %d][APP : %s]\n", argc, argv[0]);
    std::cout << cglError << std::endl;
    std::cout << cglError.message() << std::endl;
    std::cout << cglError.value() << std::endl;

    if (0 == ::SDL_Init(SDL_INIT_VIDEO)) {
        std::printf("INITIAZED SDL\n");
        cgl::common::Rect<int> windowRect {
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            1280, 700};
        SDL_Window* window{nullptr};
        window  = ::SDL_CreateWindow("TEST",
            windowRect.top, windowRect.left,
            windowRect.width, windowRect.height,
            SDL_WINDOW_SHOWN);
        if (nullptr != window) {
            SDL_Renderer* renderer{nullptr};
            ::SDL_Delay(1000);
            renderer = ::SDL_CreateRenderer(window, -1,
                SDL_RENDERER_ACCELERATED);
            if (nullptr != renderer) {
                ::SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0xFF);
                ::SDL_RenderClear(renderer);
                ::SDL_RenderPresent(renderer);
                ::SDL_DestroyRenderer(renderer);
            } else {
                std::printf("FAILED TO GET RENDERER : %s\n",
                    ::SDL_GetError());
            }
            ::SDL_Delay(2000);
            ::SDL_DestroyWindow(window);
        }
        ::SDL_Quit();
    } else  {
        std::printf("FAILED TO INITIALIZE SDL : %s\n",
            ::SDL_GetError());
        code = -1;
    }

    return code;
}
