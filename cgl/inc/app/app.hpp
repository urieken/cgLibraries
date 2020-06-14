// Copyright 2020. Ulysses Don Rieken
/*! \file app.hpp
    \brief Header for default application application

    Default application class.
 */
#ifndef CGL_INC_APP_APP_HPP_
#define CGL_INC_APP_APP_HPP_

#include <app/iapp.hpp>
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
//! Default Application class
class app : public iapp {
 public:
    //! Constructor
    app();
    //! Destructor
    virtual ~app();
};
/*! @} End of Doxygen Groups*/
}  // End namespace app
/*! @} End of Doxygen Groups*/
}  // End namespace cgl

#endif  // CGL_INC_APP_APP_HPP_
