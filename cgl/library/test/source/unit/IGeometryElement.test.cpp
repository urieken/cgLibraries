/**
 * @file IGeometryElement.test.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Unit test for IGeometryElement
 * @version 0.1
 * @date 2021-11-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <geometry/IGeometryElement.hpp>

#include <display/Color.hpp>

#include <cstdint>
#include <memory>
#include <vector>
#include <utility>

#include <gtest/gtest.h>

namespace Geometry = ::cgl::geometry;

using GeometryElement = Geometry::IGeometryElement;
using Color = ::cgl::display::Color;

namespace cgl {
namespace geometry {
namespace test {
/**
 * @brief Text fixture for IGeometryElement
 */
class IGeometryElementTest : public ::testing::Test {
protected:
    /**
     * @brief Pointer to the test element.
     */
    std::unique_ptr<GeometryElement> mElement;
};
/**
 * @brief Construct a new test object
 * 
 * @test Verify properties after construction.
 */
TEST_F(IGeometryElementTest, testConstruction) {
    const std::vector<int> coordinates {1, 2, 3, 4};
    const std::vector<int> newCoordinates {5, 10, 15, 20};
    mElement = std::make_unique<GeometryElement>(coordinates);
    auto coords = mElement->getCoordinates();
    auto colors = mElement->getColors();

    for(std::size_t idx = 0; idx < coordinates.size(); idx++) {
        EXPECT_EQ(coordinates[idx], coords[idx]);
    }
    EXPECT_EQ(0UL, colors.first.red);
    EXPECT_EQ(0UL, colors.first.green);
    EXPECT_EQ(0UL, colors.first.blue);
    EXPECT_EQ(0UL, colors.first.alpha);
    EXPECT_EQ(0UL, colors.second.red);
    EXPECT_EQ(0UL, colors.second.green);
    EXPECT_EQ(0UL, colors.second.blue);
    EXPECT_EQ(0UL, colors.second.alpha);

    mElement->setCoordinates(newCoordinates);
    auto newCoords = mElement->getCoordinates();

    for(std::size_t idx = 0; idx < newCoordinates.size(); idx++) {
        EXPECT_EQ(newCoordinates[idx], newCoords[idx]);
    }
}
/**
 * @brief Construct a new test object
 * 
 * @test Verify draw and fill colors.
 */
TEST_F(IGeometryElementTest, testSetColors) {
    const std::vector<int> coordinates {1, 2, 3, 4};
    std::pair<Color, Color> mColors{
        {128UL, 128UL, 128UL, 255UL},
        {200UL, 200UL, 200UL, 255UL}
    };
    mElement = std::make_unique<GeometryElement>(coordinates);
    auto colors = mElement->getColors();

    EXPECT_EQ(0UL, colors.first.red);
    EXPECT_EQ(0UL, colors.first.green);
    EXPECT_EQ(0UL, colors.first.blue);
    EXPECT_EQ(0UL, colors.first.alpha);
    EXPECT_EQ(0UL, colors.second.red);
    EXPECT_EQ(0UL, colors.second.green);
    EXPECT_EQ(0UL, colors.second.blue);
    EXPECT_EQ(0UL, colors.second.alpha);

    mElement->setDrawColor(mColors.first);
    mElement->setFillColor(mColors.second);
    auto newColors = mElement->getColors();

    EXPECT_EQ(mColors.first.red, newColors.first.red);
    EXPECT_EQ(mColors.first.green, newColors.first.green);
    EXPECT_EQ(mColors.first.blue, newColors.first.blue);
    EXPECT_EQ(mColors.first.alpha, newColors.first.alpha);
    EXPECT_EQ(mColors.second.red, newColors.second.red);
    EXPECT_EQ(mColors.second.green, newColors.second.green);
    EXPECT_EQ(mColors.second.blue, newColors.second.blue);
    EXPECT_EQ(mColors.second.alpha, newColors.second.alpha);

    auto draw = mElement->getDrawColor();
    auto fill = mElement->getFillColor();
    
    EXPECT_EQ(mColors.first.red, draw.red);
    EXPECT_EQ(mColors.first.green, draw.green);
    EXPECT_EQ(mColors.first.blue, draw.blue);
    EXPECT_EQ(mColors.first.alpha, draw.alpha);
    EXPECT_EQ(mColors.second.red, fill.red);
    EXPECT_EQ(mColors.second.green, fill.green);
    EXPECT_EQ(mColors.second.blue, fill.blue);
    EXPECT_EQ(mColors.second.alpha, fill.alpha);

}
/**
 * @brief Construct a new test object
 * 
 * @test Verify draw and fill colors.
 */
TEST_F(IGeometryElementTest, testColors) {
    const std::vector<int> coordinates {1, 2, 3, 4};
    std::pair<Color, Color> mColors{
        {128UL, 128UL, 128UL, 255UL},
        {200UL, 200UL, 200UL, 255UL}
    };
    mElement = std::make_unique<GeometryElement>(coordinates);
    mElement->setColors(mColors);
    auto colors = mElement->getColors();

    EXPECT_EQ(mColors.first.red, colors.first.red);
    EXPECT_EQ(mColors.first.green, colors.first.green);
    EXPECT_EQ(mColors.first.blue, colors.first.blue);
    EXPECT_EQ(mColors.first.alpha, colors.first.alpha);
    EXPECT_EQ(mColors.second.red, colors.second.red);
    EXPECT_EQ(mColors.second.green, colors.second.green);
    EXPECT_EQ(mColors.second.blue, colors.second.blue);
    EXPECT_EQ(mColors.second.alpha, colors.second.alpha);
}

}  // namespace test
}  // namespace geometry
}  // namespace cgl
