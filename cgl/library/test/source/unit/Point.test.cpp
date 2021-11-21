/**
 * @file Point.test.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Unit test for Point
 * @version 0.1
 * @date 2021-11-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <geometry/IGeometryElement.hpp>

#include <display/Color.hpp>
#include <geometry/Point.hpp>

#include <memory>

#include <gtest/gtest.h>

namespace Geometry = ::cgl::geometry;

using Color = ::cgl::display::Color;

namespace cgl {
namespace geometry {
namespace test {

/**
 * @brief Test fixture for Point.
 */
class PointTest : public ::testing::Test {
protected:
    /**
     * @brief Pointer to the test element.
     */
    std::unique_ptr<Geometry::IGeometryElement> mElement;
};
/**
 * @brief Construct a new test object.
 * 
 * @test Verify default properties after construction.
 */
TEST_F(PointTest, testDefaultsAfterConstruction) {
    mElement = std::make_unique<Geometry::Point>();
    const auto point = static_cast<Geometry::Point*>(mElement.get());

    EXPECT_EQ(0, point->getCoordinates().size());
}
/**
 * @brief Construct a new test object.
 * 
 * @test Verify properties after construction.
 */
TEST_F(PointTest, testValuesfterConstruction) {
    constexpr auto X{1};
    constexpr auto Y{2};
    mElement = std::make_unique<Geometry::Point>(X, Y);
    const auto point = static_cast<Geometry::Point*>(mElement.get());

    EXPECT_EQ(X, point->getCoordinates().at(0));
    EXPECT_EQ(Y, point->getCoordinates().at(1));
}
/**
 * @brief Construct a new test object.
 * 
 * @test Verify default colors.
 */
TEST_F(PointTest, testColors) {
    constexpr auto X{1};
    constexpr auto Y{2};
    Color color{16, 32, 64, 128};
    mElement = std::make_unique<Geometry::Point>(X, Y, color);
    const auto point = static_cast<Geometry::Point*>(mElement.get());

    EXPECT_EQ(color.red, mElement->getDrawColor().red);
    EXPECT_EQ(color.green, mElement->getDrawColor().green);
    EXPECT_EQ(color.blue, mElement->getDrawColor().blue);
    EXPECT_EQ(color.alpha, mElement->getDrawColor().alpha);
}

}  // namespace test
}  // namespace geometry
}  // namespace cgl
