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

namespace Event = ::cgl::event;

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
     * @brief Construct a new AppRunner object
     * 
     * @param argc Command line argument count.
     * @param argv Command line arguments.
     */
    AppRunner(int argc, char** argv) :
        mApplication{argc, argv} {
    }
    /**
     * @brief Run the application.
     * 
     * @return int The application return code.
     */
    auto Run() -> int {
        LISTENER listener{mApplication};
        listener.PushEvent(Event::CoreEvent(Event::EventType::Init,
            Event::EventSource::None));
        return listener.Start();
    }
    /**
     * @brief Returns a raw pointer to the application instance.
     * 
     * @return const APP* The application raw pointer.
     */
    auto get() const -> const APP* {
        return mApplication.get();
    }
private:
    /**
     * @brief The Application instance.
     */
    APP mApplication;
};

}  // namespace application
}  // namespace cgl

#endif /* CGL_LIBRARY_INCLUDE_APPLICATION_APP_RUNNER_HPP_ */
