// Copyright 2020. Ulysses Don Rieken

#ifndef CGL_INC_APP_APP_RUNNER_HPP_
#define CGL_INC_APP_APP_RUNNER_HPP_

#include <memory>

namespace cgl {
namespace app {

template <typename T>
class AppRunner {
 private:
    std::unique_ptr<T> mApplication;
 public:
    AppRunner() = default;
    virtual ~AppRunner() = default;

    auto Run(int* argc, char** argv) -> int {
        int ret{-1};
        mApplication = std::make_unique<T>();
        // Create a constant or enumeration and replace '0'.
        if (0 == mApplication->OnSetup(argc, argv)) {
            ret = mApplication->Run();
        }
        mApplication->OnCleanUp();
        return ret;
    }
};

}  // namespace app
}  // namespace cgl

#endif  // CGL_INC_APP_APP_RUNNER_HPP_
