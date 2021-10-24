/**
 * @file CGLError.test.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Unit test for CGLError
 * @version 0.1
 * @date 2021-10-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <error/CGLError.hpp>

#include <string>

#include <gtest/gtest.h>

namespace cgl {
namespace error {
namespace test {

constexpr auto NoError{"NoError"};
constexpr auto Unknown{"Unknown"};
constexpr auto CGLErrorCategory{"CGLErrorCategory"};

/**
 * @brief Construct a new TEST object
 * 
 * @test Verify NoError properties
 */
TEST(CGLErrorTest, testNoError) {
    auto errorCondition = makeErrorCondition(::cgl::error::ErrorCode::NoError);
    EXPECT_EQ(std::string{CGLErrorCategory}, errorCondition.category().name());
    EXPECT_EQ(std::string{NoError}, errorCondition.message());
}

/**
 * @brief Construct a new TEST object
 * 
 * @test Verify Unknown properties
 */
TEST(CGLErrorTest, testUnknown) {
    auto errorCondition = makeErrorCondition(::cgl::error::ErrorCode::Unknown);
    EXPECT_EQ(std::string{CGLErrorCategory}, errorCondition.category().name());
    EXPECT_EQ(std::string{Unknown}, errorCondition.message());
}

/**
 * @brief Construct a new TEST object
 * 
 * @test Verify equivalence
 */
TEST(CGLErrorTest, testEquivalence) {
    auto unknownCondition = makeErrorCondition(::cgl::error::ErrorCode::Unknown);
    auto noErrorCondition = makeErrorCondition(::cgl::error::ErrorCode::NoError);
}

}  // namespace test
}  // namespace error
}  // namespace cgl
