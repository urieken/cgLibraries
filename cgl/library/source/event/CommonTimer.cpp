/**
 * @file CommonTimer.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Source for common(std::chrono) timer.
 * @version 0.1
 * @date 2022-03-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "event/ITimer.hpp"
#include <event/CommonTimer.hpp>

namespace cgl {
namespace event {

CommonTimer::CommonTimer() :
    mState{TimerState::Stopped} {
}

auto CommonTimer::Start() -> void {
    mStartTime = std::chrono::steady_clock::now();
    mState = TimerState::Started;
}

auto CommonTimer::Stop() -> void {
    mState = TimerState::Stopped;
}

auto CommonTimer::Pause() -> void {
    mState = TimerState::Paused;
    mPausedTime = std::chrono::steady_clock::now();
}

auto CommonTimer::Resume() -> void {
    mState = TimerState::Started;
}

auto CommonTimer::GetTicks() -> std::uint32_t {
    return 0;
}

auto CommonTimer::IsStarted() -> bool {
    return mState == TimerState::Started;
}

auto CommonTimer::IsPaused() -> bool {
    return mState == TimerState::Paused;
}

}  // namespace event
}  // namespace cgl
