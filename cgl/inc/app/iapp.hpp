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
    bool running() const {
       return !mDone;
    }
    //! Sets the application running flag.
    /*!
     * \param running True to set flag to running.
     */
    void running(const bool& running) {
       mDone = !running;
    }
    //! Handler for application initialize event.
    /*!
     * \param argc Pointer to command line argument counter.
     * \param argv Command line arguments.
     * \return Return code.
     */
    virtual uint_fast8_t OnInitialize(int* argc, char** argv) = 0;
    //! Handler for application cleanup event.
    virtual void OnCleanUp() = 0;
};
/*! @} End of Doxygen Groups*/
}  // End namespace app
/*! @} End of Doxygen Groups*/
}  // End namespace cgl

#endif  // CGL_INC_APP_IAPP_HPP_
