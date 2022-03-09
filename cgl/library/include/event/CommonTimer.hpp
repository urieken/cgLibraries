/**
 * @file CommonTimer.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for common(std::chrono) timer.
 * @version 0.1
 * @date 2022-03-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_EVENT_COMMON_TIMER_HPP_
#define CGL_LIBRARY_INCLUDE_EVENT_COMMON_TIMER_HPP_

#include <event/ITimer.hpp>

#include <chrono>
#include <cstddef>
#include <cstdint>

namespace cgl {
namespace event {
/**
 * @brief Wrapper for std::chrono time utilities.
 */
class CommonTimer : public ITimer {
public:
    virtual ~CommonTimer() = default;
    /**
     * @brief Construct a new CommonTimer object
     */
    CommonTimer();
    /**
     * @brief Start the timer.
     */
    auto Start() -> void override;
    /**
     * @brief Stop the timer.
     */
    auto Stop() -> void override;
    /**
     * @brief Pause the timer.
     */
    auto Pause() -> void override;
    /**
     * @brief Resume the timer.
     */
    auto Resume() -> void override;
    /**
     * @brief Get the timer ticks.
     * 
     * @return std::uint32_t The timer ticks.
     */
    auto GetTicks() -> std::uint32_t override;
    /**
     * @brief Check if the timer is started.
     * 
     * @return true The timer is started.
     * @return false The timer is not started.
     */
    auto IsStarted() -> bool override;
    /**
     * @brief Check if timer is paused.
     * 
     * @return true The timer is paused.
     * @return false The timer is not paused. 
     */
    auto IsPaused() -> bool override;
private:
    /**
     * @brief The time at start.
     */
    std::chrono::time_point<std::chrono::steady_clock> mStartTime;
    /**
     * @brief The time at pause.
     */
    std::chrono::time_point<std::chrono::steady_clock> mPausedTime;
    /**
     * @brief The timer state.
     *
     * @note Experiment with bit field instead of bool(s). 
     */
    TimerState mState;
};
}  // namespace event
}  // namespace cgl

#endif//CGL_LIBRARY_INCLUDE_EVENT_COMMON_TIMER_HPP_
