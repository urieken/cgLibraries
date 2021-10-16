/**
 * @file Compilers.test.cpp
 * @author Ulysses Don Riekem (ulysses.rieken@gmail.com)
 * @brief Unit test for Compiler.
 * @version 0.1
 * @date 2021-09-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <system/ICompilers.hpp>
#include <system/Compilers.hpp>

#include <memory>
#include <sstream>

#include <gtest/gtest.h>

namespace cgl {
namespace system {
namespace test {

#if defined(__clang__)
constexpr auto compilerName{"CLANG"};
constexpr auto compilerMajor{__clang_major__};
constexpr auto compilerMinor{__clang_minor__};
constexpr auto compilerPatchLevel{__clang_patchlevel__};
#define FUNCTION_NAME __PRETTY_FUNCTION__
#elif defined(__GNUC___) || defined(__GNUG__)
constexpr auto compilerName{"GNU"};
constexpr auto compilerMajor{__GNUC__};
constexpr auto compilerMinor{__GNUC_MINOR__};
constexpr auto compilerPatchLevel{__GNUC_PATCHLEVEL__};
#elif defined(__MINGW32__)
constexpr auto compilerName{"MINGW32"};
constexpr auto compilerMajor{__MINGW32_MAJOR_VERSION};
constexpr auto compilerMinor{__MINGW32_MINOR_VERSION};
constexpr auto compilerPatchLevel{0};
#elif defined(__MINGW64__)
constexpr auto compilerName{"MINGW64"};
constexpr auto compilerMajor{__MINGW64_MAJOR_VERSION};
constexpr auto compilerMinor{__MINGW64_MINOR_VERSION};
constexpr auto compilerPatchLevel{0};
#elif defined(_MSC_VER)
constexpr auto compilerName{"MSC"};
constexpr auto compilerMajor{_MSC_VER};
constexpr auto compilerMinor{_MSC_VER};
constexpr auto compilerPatchLevel{_MSC_VER};
#endif

/**
 * @brief Test fixture for Compilers.
 */
class CompilersTest : public ::testing::Test {
protected:
    /**
     * @brief Pointer to the test object.
     */
    std::unique_ptr<system::ICompilers> mCompilers;
    /**
     * @brief Setup the test environment.
     */
    auto SetUp() -> void override {
        mCompilers = std::make_unique<system::Compilers>();
    }
};

/**
 * @brief Construct a new test object for Compilers
 * 
 * @test verify the compiler specific properties.
 */
TEST_F(CompilersTest, testCompilersProperties) {
    std::stringstream ss;
    ss << compilerMajor << "." << compilerMinor << "." << compilerPatchLevel;

    EXPECT_EQ(ss.str(), mCompilers->versionString());
    EXPECT_EQ(compilerName, mCompilers->name());
    EXPECT_EQ(compilerMajor, mCompilers->majorVersion());
    EXPECT_EQ(compilerMinor, mCompilers->minorVersion());
    EXPECT_EQ(compilerPatchLevel, mCompilers->patchLevel());
}

}  // namespace test
}  // namespace system
}  // namespace cgl
