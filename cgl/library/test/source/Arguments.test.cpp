/**
 * @file Arguments.test.cpp
 * @author Ulysses Don Rieken(ulysses.rieken@gmail.com)
 * @brief Unit test for Argument
 * @version 0.1
 * @date 2021-10-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <system/Arguments.hpp>

#include <error/CGLError.hpp>

#include <memory>
#include <sstream>
#include <string>
#include <system_error>

#include <gtest/gtest.h>

namespace Error = ::cgl::error;
namespace System = ::cgl::system;

using Code = Error::ErrorCode;

namespace cgl {
namespace cpp_research {
/**
 * @brief Test fixture for Arguments.
 */
class ArgumentsTest : public ::testing::Test {
protected:
    /**
     * @brief Pointer to the test object.
     */
    std::unique_ptr<System::Arguments> mArguments;
    /**
     * @brief The test input stream.
     */
    std::stringstream mInputStream;
    /**
     * @brief Setup the test environment.
     */
    auto SetUp() -> void override {
        mArguments = std::make_unique<System::Arguments>();
        mInputStream.str(std::string{});
    }
    /**
     * @brief Prepare invalid input stream.
     */
    auto PrepareInputStreamWithMalformedPair() -> void {
        mInputStream << "key01:val01\n"
        << "key02:val02\n"
        // Underscore is not allowed in default pattern.
        << "key_03:val_03\n";
    }
    /**
     * @brief Prepare valid input stream.
     */
    auto PrepareValidInputStream() -> void {
        mInputStream << "key01:val01\n"
        << "key02:val02\n"
        << "key03:val03\n";
    }
};

/**
 * @brief Construct a new test object.
 * 
 * @test Verify error condition on malformed pair.
 */
TEST_F(ArgumentsTest, testInputStreamWithMalformedPair) {
    PrepareInputStreamWithMalformedPair();
    auto result = mArguments->ProcessInputStream(mInputStream);

    EXPECT_EQ(Code::MalformedKeyPair, static_cast<Code>(result.value()));
    EXPECT_EQ(std::nullopt, mArguments->GetProperty("key_03"));
}

/**
 * @brief Construct a new test object.
 * 
 * @test Verify error condition on valid input stream.
 */
TEST_F(ArgumentsTest, testValidInputStream) {
    PrepareValidInputStream();
    auto result = mArguments->ProcessInputStream(mInputStream);

    EXPECT_EQ(Code::NoError, static_cast<Code>(result.value()));
    EXPECT_EQ(std::string{"val01"}, mArguments->GetProperty("key01"));
    EXPECT_EQ(std::string{"val02"}, mArguments->GetProperty("key02"));
    EXPECT_EQ(std::string{"val03"}, mArguments->GetProperty("key03"));
}

}  // namespace cpp_research
}  // namespace cgl
