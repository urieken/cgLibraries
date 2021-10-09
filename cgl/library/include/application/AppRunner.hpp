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

#include <memory>

namespace cgl {
namespace application {
/**
 * @brief The application runner.
 * 
 * @tparam APP The application to be executed.
 */
template <typename APP>
class AppRunner {
public:
    /**
     * @brief Construct a new AppRunner object
     * 
     * @param argc Command line argument count.
     * @param argv Command line arguments.
     */
    AppRunner(int argc, char** argv) {
        mApplication = std::make_unique<APP>(argc, argv);
    }
    /**
     * @brief Run the application.
     * 
     * @return int The application return code.
     */
    auto Run() -> int {
        return mApplication->Run();
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
     * @brief Pointer to the Application instance.
     */
    std::unique_ptr<APP> mApplication;
};

}  // namespace application
}  // namespace cgl

#endif /* CGL_LIBRARY_INCLUDE_APPLICATION_APP_RUNNER_HPP_ */
