/**
 * @file KeyPairString.test.cpp
 * @author Ulysses Don Rieken(ulysses.rieken@gmail.com)
 * @brief Unit test for KeyPairString
 * @version 0.1
 * @date 2021-10-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <system/KeyPairString.hpp>

#include <memory>

#include <gtest/gtest.h>

namespace System = ::cgl::system;

namespace cgl {
namespace cpp_research {
/**
 * @brief Test fixture for KeyPairString
 */
class KeyPairStringTest : public ::testing::Test {
protected:
    /**
     * @brief The allowed characters for key and value strings.
     */
    std::string mAllowedCharacters;
    /**
     * @brief The delimeter for key and value strings.
     */
    std::string mDelimeter;
    /**
     * @brief Pointer to the test object.
     */
    std::unique_ptr<System::KeyPairString> mKeyPairString;
    /**
     * @brief Setup the test environment.
     */
    auto SetUp() -> void override {
        mAllowedCharacters = "([a-zA-Z0-9]+)";
        mDelimeter = ":";
        mKeyPairString =
            std::make_unique<System::KeyPairString>(mAllowedCharacters, mDelimeter);
    }
};
/**
 * @brief Construct a new test object
 * 
 * @test Verify valid input string.
 */
TEST_F(KeyPairStringTest, testValidInputString) {
    const std::string validKey{"key"};
    const std::string validValue{"value"};
    const std::string invalidKey{"key_"};
    const std::string invalidValue{"value_"};


    EXPECT_TRUE(mKeyPairString->IsValid(std::string(validKey)
        .append(mDelimeter).append(validValue)));
    EXPECT_FALSE(mKeyPairString->IsValid(std::string(invalidKey)
        .append(mDelimeter).append(invalidValue)));
}
/**
 * @brief Construct a new test object
 * 
 * @test Verify KeyValuePair.
 */
TEST_F(KeyPairStringTest, testKeyValuePair) {
    const std::string validKey{"key"};
    const std::string validValue{"value"};
    const std::string invalidKey{"key_"};
    const std::string invalidValue{"value_"};
    
    auto ValidkeyPair = mKeyPairString->Parse(std::string(validKey)
        .append(mDelimeter).append(validValue));
    auto InvalidkeyPair = mKeyPairString->Parse(std::string(invalidKey)
        .append(mDelimeter).append(invalidValue));

    EXPECT_EQ(validKey, ValidkeyPair.key);
    EXPECT_EQ(validValue, ValidkeyPair.value);
    EXPECT_EQ(0, InvalidkeyPair.key.length());
    EXPECT_EQ(0, InvalidkeyPair.value.length());
}

}  // namespace cpp_research
}  // namespace cgl
