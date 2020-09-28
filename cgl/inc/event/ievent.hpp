// Copyright 2020. Ulysses Don Rieken
/*! \file ievent.hpp
    \brief Header for event interface.

    Base class for event classes.
 */

#include <memory>
#include <cstdint>
#include <cstring>
#include <system_error>

#include <error/error_types.hpp>

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
class iEvent {
 private:
    //! Event ID.
    std::uint8_t mId;
    //! Length of payload
    std::size_t mPayloadLength;
    //! Event data.
    void* mPayload;
    //! The error object instance
    std::shared_ptr<std::error_code> mError;

 public:
    //! Default DTOR
    virtual ~iEvent() = default;
    //!
    /*! Moves the payload to internal storage.
     * \param id The event id.
     * \param length Payload length.,
     * \param payload Data to be moved.
     */
    virtual auto setPayload(std::uint8_t id,
        std::size_t length, const void* payload) -> void {
        mId = id;
        mPayloadLength = length;
        std::memmove(&mPayload, payload, mPayloadLength);
    }
    /*! Returns the event id.
     * \return Current event id.
     */
    virtual auto getId() -> std::uint8_t { return mId; }
    /*! Returns the event payload length.
     * \return Current payload length.
     */
    virtual auto getPayloadLength() -> std::size_t {
        return mPayloadLength;
    }
    /*! Returns a pointer to the payload.
     * \return Pointer to payload data.
     */
    virtual auto getPayload() -> void* {
        return &mPayload;
    }
    /*! Sets the error code 
     * \param error The error code to be set
     */
    virtual auto setError(std::shared_ptr<std::error_code> error) -> void {
        mError = error;
    }
    /*! Returns a pointer to the error object
     * \return Pointer to the error object
     */
    virtual auto getError() -> std::shared_ptr<std::error_code> {
        return mError;
    }
};
}  // namespace event
}  // namespace cgl

#endif  // CGL_INC_EVENT_IEVENT_HPP_
