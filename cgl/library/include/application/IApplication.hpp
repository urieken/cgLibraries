/**
 * @file IApplication.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Header for application interface.
 * @version 0.1
 * @date 2021-10-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_APPLICATION_IAPPLICATION_HPP_
#define CGL_LIBRARY_INCLUDE_APPLICATION_IAPPLICATION_HPP_

#include <event/IEvent.hpp>

namespace cgl {
namespace application {

/**
 * @brief The application interface.
 */
class IApplication {
public:
    virtual ~IApplication() = default;
    /**
     * @brief Run the application.
     * 
     * @return int The application return code.
     */
    virtual auto Run() -> int = 0;
    /**
     * @brief Handle events.
     * 
     * @param event The event to be handled.
     * @return true The event was processed.
     * @return false An error has occurred or quit the application.
     */
    virtual auto OnEvent(const ::cgl::event::IEvent& event) -> bool = 0;
};

}  // namespace application
}  // namespace cgl

#endif /* CGL_LIBRARY_INCLUDE_APPLICATION_IAPPLICATION_HPP_ */
