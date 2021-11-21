/**
 * @file Rectangle.test.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Unit test for Rectangle
 * @version 0.1
 * @date 2021-11-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <geometry/IGeometryElement.hpp>

#include <display/Color.hpp>
#include <geometry/Rectangle.hpp>

#include <memory>

#include <gtest/gtest.h>


namespace Geometry = ::cgl::geometry;

using Color = ::cgl::display::Color;

namespace cgl {
namespace geometry {
namespace test {

/**
 * @brief Test fixture for Rectangle.
 */
class RectangleTest : public ::testing::Test {
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
TEST_F(RectangleTest, testDefaultsAfterConstruction) {
    mElement = std::make_unique<Geometry::Rectangle>();

    EXPECT_EQ(0, mElement->getCoordinates().size());
}
/**
 * @brief Construct a new test object.
 * 
 * @test Verify properties after construction.
 */
TEST_F(RectangleTest, testValuesfterConstruction) {
    const std::pair<int, int> topLeft = std::pair<int, int>(1, 2);
    const std::pair<int, int> bottomRight = std::pair<int, int>(3, 4);
    mElement = std::make_unique<Geometry::Rectangle>(topLeft, bottomRight);

    EXPECT_EQ(topLeft.first, mElement->getCoordinates().at(0));
    EXPECT_EQ(topLeft.second, mElement->getCoordinates().at(1));
    EXPECT_EQ(bottomRight.first, mElement->getCoordinates().at(2));
    EXPECT_EQ(bottomRight.second, mElement->getCoordinates().at(3));
}
/**
 * @brief Construct a new test object.
 * 
 * @test Verify default colors.
 */
TEST_F(RectangleTest, testColors) {
    const std::pair<int, int> topLeft = std::pair<int, int>(1, 2);
    const std::pair<int, int> bottomRight = std::pair<int, int>(3, 4);
    const std::pair<Color, Color> colors{{16, 32, 64, 128}, {10, 20, 30, 40}};
    mElement = std::make_unique<Geometry::Rectangle>(topLeft, bottomRight,
        colors);

    EXPECT_EQ(colors.first.red, mElement->getDrawColor().red);
    EXPECT_EQ(colors.first.green, mElement->getDrawColor().green);
    EXPECT_EQ(colors.first.blue, mElement->getDrawColor().blue);
    EXPECT_EQ(colors.first.alpha, mElement->getDrawColor().alpha);
    EXPECT_EQ(colors.second.red, mElement->getFillColor().red);
    EXPECT_EQ(colors.second.green, mElement->getFillColor().green);
    EXPECT_EQ(colors.second.blue, mElement->getFillColor().blue);
    EXPECT_EQ(colors.second.alpha, mElement->getFillColor().alpha);
}

}  // namespace test
}  // namespace geometry
}  // namespace cgl
