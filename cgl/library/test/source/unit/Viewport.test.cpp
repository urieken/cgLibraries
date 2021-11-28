/**
 * @file Viewport.test.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Unit test for Viewport.
 * @version 0.1
 * @date 2021-11-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <display/Viewport.hpp> 

#include <display/Rect.hpp>

#include <cstdint>
#include <memory>

#include <gtest/gtest.h>

using Viewport = ::cgl::display::Viewport;
using Rect = ::cgl::display::Rect;

namespace cgl {
namespace display {
namespace test {
/**
 * @brief Test fixture for Viewport
 */
class ViewportTest : public ::testing::Test {
protected:
    /**
     * @brief Pointer to the test viewport.
     */
    std::unique_ptr<Viewport> mViewport;
    /**
     * @brief Test viewport id.
     */
    std::uint8_t mTestId;
    /**
     * @brief The test viewport coordinates.
     */
    Rect mRect;
    /**
     * @brief Setup the test environment.
     */
    auto SetUp() -> void override {
        mTestId = 101;
        mRect = {1, 2, 3, 4};
        mViewport = std::make_unique<Viewport>(mTestId, mRect);
    }
};
/**
 * @brief Construct a new test object
 * 
 * @test Verify properties after construction.
 */
TEST_F(ViewportTest, testConstruction) {
    auto rect = mViewport->getRect();
    EXPECT_EQ(mTestId, mViewport->getId());
    EXPECT_EQ(mRect.top, rect.top);
    EXPECT_EQ(mRect.left, rect.left);
    EXPECT_EQ(mRect.width, rect.width);
    EXPECT_EQ(mRect.height, rect.height);
}

}  // namespace test
}  // namespace display 
}  // namespace cgl
