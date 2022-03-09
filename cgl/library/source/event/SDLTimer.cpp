/**
 * @file SDLTimer.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-02-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <SDL2/SDL_timer.h>
#include <event/SDLTimer.hpp>

#include <cstdint>

#include <SDL2/SDL.h>

namespace cgl {
namespace event {

SDLTimer::SDLTimer() :
    mStartTicks{0},
    mPausedTicks{0},
    mPaused{false},
    mStarted{false} {
}

auto SDLTimer::Start() -> void {
    mStarted = true;
    mPaused = false;
    mPausedTicks = 0;
    // Get the current clock time.
    mStartTicks = ::SDL_GetTicks();
}

auto SDLTimer::Stop() -> void {
    mStarted = false;
    mPaused = false;
    // Clear counters.
    mStartTicks = 0;
    mPausedTicks = 0;
}

auto SDLTimer::Pause() -> void {
    // Timer is running and not paused.
    if(mStarted && !mPaused) {
        mPaused = true;
        // Calculate the paused ticks.
        mPausedTicks = ::SDL_GetTicks() - mStartTicks;
        mStartTicks = 0;
    }
}

auto SDLTimer::Resume() -> void {
    // Timer is running and paused.
    if(mStarted && mPaused) {
        mPaused = false;
        // Reset counters.
        mStartTicks = ::SDL_GetTicks() - mPausedTicks;
        mPausedTicks = 0;
    }
}

auto SDLTimer::GetTicks() -> std::uint32_t {
    std::uint32_t time{0};
    if(mStarted) {
        if(mPaused) {
            // Tick count from pause.
            time = mPausedTicks;
        } else {
            // Time since start time.
            time = ::SDL_GetTicks() - mStartTicks;
        }
    }
    return time;
}

auto SDLTimer::IsStarted() -> bool {
    return mStarted;
}

auto SDLTimer::IsPaused() -> bool {
    return mPaused;
}

}  // namespace event
}  // namespace cgl