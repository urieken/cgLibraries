/**
 * @file CodeEvent.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for Core Event.
 * @version 0.1
 * @date 2021-10-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_EVENT_CORE_EVENT_HPP_
#define CGL_LIBRARY_INCLUDE_EVENT_CORE_EVENT_HPP_

#include <event/IEvent.hpp>

#include <cstddef>
#include <string>

namespace cgl {
namespace event {
/**
 * @brief Wrapper for core events.
 */
class CoreEvent final : public IEvent {
public:
    /**
     * @brief Construct a new CoreEvent object
     */
    CoreEvent();
    /**
     * @brief Construct a new CoreEvent object
     * 
     * @param type The CoreEvent.
     * @param source The EventSource.
     */
    CoreEvent(const EventType& type, const EventSource& source);
    /**
     * @brief Construct a new CoreEvent object
     * 
     * @param type The CoreEvent.
     * @param source The EventSource.
     * @param data Additional event data.
     */
    CoreEvent(const EventType& type, const EventSource& source,
        const std::string& data);
    ~CoreEvent() = default;
    /**
     * @brief Returns a pointer to event data.
     * 
     * @return const void* The pointer event data.
     */
    auto Data() const -> const void* override;
public:
    /**
     * @brief Event data.
     */
    std::string mData;
};

}  // namespace event
}  // namespace cgl

#endif /* CGL_LIBRARY_INCLUDE_EVENT_CORE_EVENT_HPP_ */
