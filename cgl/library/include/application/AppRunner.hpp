/**
 * @file AppRunner.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.co)
 * @brief Header for appication runner.
 * @version 0.1
 * @date 2021-10-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_INCLUDE_APPLICATION_APP_RUNNER_HPP_
#define CGL_LIBRARY_INCLUDE_APPLICATION_APP_RUNNER_HPP_

#include <event/CoreEvent.hpp>
#include <system/Arguments.hpp>

#include <memory>
#include <utility>

namespace Event = ::cgl::event;
namespace System = ::cgl::system;

namespace cgl {
namespace application {
/**
 * @brief The application runner.
 * 
 * @tparam APP The application to be executed.
 */
template <typename APP, typename LISTENER>
class AppRunner {
public:
    /**
     * @brief Construct a new App Runner object
     */
    AppRunner() :
        mApp{new APP{}} {
    }
    /**
     * @brief Construct a new AppRunner object
     * 
     * @param args Processed arguments to be sent to the application instance.
     */
    explicit AppRunner(System::Arguments& args) :
        mApp{new APP{args}} {
    }
    /**
     * @brief Run the application.
     * 
     * @return int The application return code.
     */
    auto Run() -> int {
        LISTENER listener{*mApp};
        listener.PushEvent(Event::CoreEvent(Event::EventType::Init,
            Event::EventSource::None));
        return listener.Start();
    }
private:
    /**
     * @brief The Application instance.
     */
    std::unique_ptr<APP> mApp;
};

}  // namespace application
}  // namespace cgl

#endif /* CGL_LIBRARY_INCLUDE_APPLICATION_APP_RUNNER_HPP_ */
