// Copyright 2020. Ulysses Don Rieken
/*! \file iapp.hpp
    \brief Header for application interface.

    Base class for application classes.
 */
#include <cstdint>

#ifndef CGL_INC_APP_IAPP_HPP_
#define CGL_INC_APP_IAPP_HPP_
//! Crazy Galen's Libraries
namespace cgl {
/*!
 * \addtogroup cgl
 * @{
 */
//! Crazy Galen's Application classes.
namespace app {
/*!
 * \addtogroup app
 * @{
 */
//! Application interface
class iapp {
 private:
    //! Application running flag
    /*!
     * Application exits when set to true
     */
    bool mDone;

 public:
    //! Default destructor
    virtual ~iapp() = default;

    //! Check whether application is running.
    /*!
     * \return True if application is running.
     */
    auto running() -> const bool {
       return !mDone;
    }
    //! Sets the application running flag.
    /*!
     * \param running True to set flag to running.
     */
    auto running(const bool& running) -> void {
       mDone = !running;
    }
    //! Handler for application initialize event.
    /*!
     * \param argc Pointer to command line argument counter.
     * \param argv Command line arguments.
     * \return Return code.
     */
    virtual auto OnInitialize(int* argc, char** argv) -> std::uint8_t = 0;
    //! Handler for application cleanup event.
    virtual auto OnCleanUp() -> void = 0;
};
/*! @} End of Doxygen Groups*/
}  // End namespace app
/*! @} End of Doxygen Groups*/
}  // End namespace cgl

#endif  // CGL_INC_APP_IAPP_HPP_
