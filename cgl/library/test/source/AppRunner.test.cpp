/**
 * @file AppRunner.test.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Unit test for AppRunner
 * @version 0.1
 * @date 2021-10-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <application/AppRunner.hpp>
#include <application/IApplication.hpp>

#include <MockApplication.hpp>

#include <memory>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace cgl {
namespace application {
namespace test {

/**
 * @brief Test fixture for AppRunner
 */
class AppRunnerTest : public ::testing::Test {
protected:
    /**
     * @brief Pointer to test object.
     */
    AppRunner<::testing::NiceMock<MockApplication>> mAppRunner;
    /**
     * @brief Construct a new AppRunnerTest object
     */
    AppRunnerTest() : mAppRunner{0, nullptr} {}
};

/**
 * @brief Construct a new test object
 * 
 * @test Verify the application return code.
 */
TEST_F(AppRunnerTest, testConstruction) {
    EXPECT_EQ(defaultTestReturnCode, mAppRunner.Run());
}

}  // namespace test
}  // namespace application
}  // namespace cgl
