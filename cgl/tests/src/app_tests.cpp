// Copyright 2020. Ulysses Don Rieken
#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <vector>

#include <app/app.hpp>

namespace cgl {
namespace app {
namespace tests {

class AppTestF : public ::testing::Test {
 protected:
    std::unique_ptr<app> application;
    std::vector<std::string> arguments;
    void SetUp() override {
        application = std::make_unique<app>();
    }
    void TearDown() override {
        application.reset(nullptr);
        arguments.clear();
    }
};

TEST_F(AppTestF, setApplicationRunningFlag) {
    arguments.push_back("ONE");
    arguments.push_back("TWO");
    arguments.push_back("THREE");
    int count{static_cast<int>(arguments.size())};
    std::vector<char*> c_strings;
    c_strings.reserve(arguments.size());
    for (auto& str : arguments) {
        c_strings.push_back(&str[0]);
    }
    application->OnInitialize(&count, &c_strings[0]);
    EXPECT_TRUE(application->running());
    application->OnCleanUp();
    EXPECT_FALSE(application->running());
}

}  // namespace tests
}  // namespace app
}  // namespace cgl
