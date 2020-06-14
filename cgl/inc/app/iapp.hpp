// Copyright 2020. Ulysses Don Rieken
/*! \file iapp.hpp
    \brief Header for application interface

    Base class for application classes.
 */
#ifndef CGL_INC_APP_IAPP_HPP_
#define CGL_INC_APP_IAPP_HPP_
//! Crazy Galen's Libraries
namespace cgl {
/*!
 * \addtogroup cgl
 * @{
 */
//! Crazy Galen's Application classes
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
    bool m_bDone;

 public:
    //! Default destructor
    virtual ~iapp() = default;

    //! Check whether application is running
    /*!
     * \return True if application is running
     */
    bool running() const {
       return !m_bDone;
    }
    //! Sets the application running flag
    /*!
     * \param True to set flag to running
     */
    void running(const bool& running) {
       m_bDone = !running;
    }
};
/*! @} End of Doxygen Groups*/
}  // End namespace app
/*! @} End of Doxygen Groups*/
}  // End namespace cgl

#endif  // CGL_INC_APP_IAPP_HPP_
