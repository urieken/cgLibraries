/**
 * @file ITimer.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for timer interface
 * @version 0.1
 * @date 2022-02-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_EVENT_ITIMER_HPP_
#define CGL_LIBRARY_INCLUDE_EVENT_ITIMER_HPP_

#include <cstdint>

namespace cgl {
namespace event {
/**
 * @brief Timer state flags.
 */
enum class TimerState {
    /**
     * @brief Timer is stopped or in the initial state.
     */
    Stopped = 0b00000000,
    /**
     * @brief Timer is started.
     */
    Started,
    /**
     * @brief Timer is paused.
     */
    Paused,
    /**
     * @brief Timer is in an unknown state.
     *
     * @note New entries in this enumeration should be added before this entry.
     */
    Unknown
};
/**
 * @brief The timer interface
 */
class ITimer {
public:
    virtual ~ITimer() = default;
    /**
     * @brief Start the timer.
     */
    virtual auto Start() -> void = 0;
    /**
     * @brief Stop the timer.
     */
    virtual auto Stop() -> void = 0;
    /**
     * @brief Pause the timer.
     */
    virtual auto Pause() -> void = 0;
    /**
     * @brief Resume the timer.
     */
    virtual auto Resume() -> void = 0;
    /**
     * @brief Get the timer ticks.
     * 
     * @return std::uint32_t The timer ticks.
     */
    virtual auto GetTicks() -> std::uint32_t = 0;
    /**
     * @brief Check if the timer is started.
     * 
     * @return true The timer is started.
     * @return false The timer is not started.
     */
    virtual auto IsStarted() -> bool = 0;
    /**
     * @brief Check if timer is paused.
     * 
     * @return true The timer is paused.
     * @return false The timer is not paused. 
     */
    virtual auto IsPaused() -> bool = 0;
};

}  // namespace event
}  // namespace cgl

#endif//CGL_LIBRARY_INCLUDE_EVENT_ITIMER_HPP_
