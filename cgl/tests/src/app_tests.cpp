// Copyright 2020. Ulysses Don Rieken
#include <gtest/gtest.h>

#include <memory>

#include <app/app.hpp>

namespace cgl {
namespace app {
namespace tests {

class AppTestF : public ::testing::Test {
 protected:
    std::unique_ptr<app> application;
    void SetUp() override {
        application = std::make_unique<app>();
    }
    void TearDown() override {
        application.reset(nullptr);
    }
};

TEST_F(AppTestF, setApplicationRunningFlag) {
    bool flag{true};
    application->running(flag);
    EXPECT_TRUE(application->running());
    flag = !flag;
    application->running(flag);
    EXPECT_FALSE(application->running());
}

}  // namespace tests
}  // namespace app
}  // namespace cgl
