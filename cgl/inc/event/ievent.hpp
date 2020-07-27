// Copyright 2020. Ulysses Don Rieken
/*! \file ievent.hpp
    \brief Header for event interface.

    Base class for event classes.
 */
#include <cstdint>
#include <cstring>
#ifndef CGL_INC_EVENT_IEVENT_HPP_
#define CGL_INC_EVENT_IEVENT_HPP_
//! Crazy Galen's Libraries
namespace cgl {
/*!
 * \addtogroup cgl
 * @{
 */
//! Crazy Galen's Event classes.
namespace event {
/*!
 * \addtogroup event
 * @{
 */
//! Event interface
template <typename T_>
class ievent {
 private:
    //! Event ID.
    std::uint8_t mId;
    //! Event data.
    T_ mPayload;

 public:
    //! Default DTOR
    virtual ~ievent() = default;
    //!
    /*! Moves the payload to internal storage.
     * \param id The event id.
     * \param length Payload length.,
     * \param payload Data to be moved.
     */
    void setPayload(std::uint8_t id, std::size_t length, const T_* payload) {
        mId = id;
        std::memmove(&mPayload, payload, length);
    }
    /*! Returns the event id.
     * \return Current event id.
     */
    std::uint8_t getId() { return mId; }
    /*! Returns the event payload length.
     * \return Current payload length.
     */
    std::size_t getPayloadLength() {
        return sizeof mPayload;
    }
    /*! Returns a pointer to the payload.
     * \return Pointer to payload data.
     */
    T_* getPayload() {
        return &mPayload;
    }
};
}  // namespace event
}  // namespace cgl

#endif  // CGL_INC_EVENT_IEVENT_HPP_
