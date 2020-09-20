// Copyright 2020. Ulysses Don Rieken

#include <SDL2/SDL.h>

#include <cstdio>

#include <common/shapes.hpp>
#include <sandbox_app.hpp>

auto main(int argc, char** argv) -> int {
    int code{0};
    cgl::sandbox::SandboxApp app;
    std::printf("[ARGC : %d][APP : %s]\n", argc, argv[0]);

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
