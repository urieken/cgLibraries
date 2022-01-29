/**
 * @file SDLEvent.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for SDLEvent
 * @version 0.1
 * @date 2021-10-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_EVENT_SDL_EVENT_HPP_
#define CGL_LIBRARY_INCLUDE_EVENT_SDL_EVENT_HPP_

#include <event/IEvent.hpp>

#include <cstdint>

#include <SDL2/SDL.h>

namespace cgl {
namespace event {
/**
 * @brief Custom SDL event.
 */
struct CustomSDLEevent {
    /**
     * @brief The event type.
     */
    std::uint32_t type;
    /**
     * @brief Can be as id for window, scene, etc.
     */
    std::uint32_t id;
    /**
     * @brief The event code.
     */
    std::uint32_t code;
};

/**
 * @brief Wrapper for SDL events.
 */
class SDLEvent final : public IEvent {
public:
    /**
     * @brief Construct a new SDLEvent object
     */
    SDLEvent();
    /**
     * @brief Construct a new SDLEvent object
     * 
     * @param type The CoreEvent.
     * @param source The EventSource.
     * @param data The event data.
     */
    SDLEvent(const EventType& type, const EventSource& source,
        SDL_Event* data = nullptr);
    ~SDLEvent() = default;
    /**
     * @brief Returns a pointer to event data.
     * 
     * @return const void* The pointer event data.
     */
    auto Data() const -> const void* override;
private:
    /**
     * @brief SDL event data.
     */
    SDL_Event* mData;
};

}  // namespace event
}  // namespace cgl

#endif /* CGL_LIBRARY_INCLUDE_EVENT_SDL_EVENT_HPP_ */
