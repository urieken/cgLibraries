/**
 * @file SDLTimer.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for SDL timer
 * @version 0.1
 * @date 2022-02-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_EVENT_SDL_TIMER_HPP_
#define CGL_LIBRARY_INCLUDE_EVENT_SDL_TIMER_HPP_

#include <event/ITimer.hpp>

#include <cstdint>

namespace cgl {
namespace event {
/**
 * @brief Wrapper for SDL timer.
 */
class SDLTimer : public ITimer {
public:
    virtual ~SDLTimer() = default;
    /**
     * @brief Construct a new SDLTimer object
     */
    SDLTimer();
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
     * @brief Time when the timer is started.
     */
    std::uint32_t mStartTicks;
    /**
     * @brief Tick count when the timer is paused.
     */
    std::uint32_t mPausedTicks;
    /**
     * @brief The timer is paued.
     */
    bool mPaused;
    /**
     * @brief The timer is started.
     */
    bool mStarted;
};
}  // namespace event
}  // namespace cgl

#endif//CGL_LIBRARY_INCLUDE_EVENT_SDL_TIMER_HPP_
