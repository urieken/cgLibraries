/**
 * @file Line.test.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Unit test for Line
 * @version 0.1
 * @date 2021-11-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <geometry/IGeometryElement.hpp>

#include <display/Color.hpp>
#include <geometry/Line.hpp>

#include <memory>

#include <gtest/gtest.h>

namespace Geometry = ::cgl::geometry;

using Color = ::cgl::display::Color;
using GeometryElement = Geometry::IGeometryElement;

namespace cgl {
namespace geometry {
namespace test {

/**
 * @brief Test fixture for Line
 */
class LineTest : public ::testing::Test {
protected:
    /**
     * @brief Pointer to the test element.
     */
    std::unique_ptr<GeometryElement> mElement;
};
/**
 * @brief Construct a new test object.
 * 
 * @test Verify default properties after construction.
 */
TEST_F(LineTest, testDefaultsAfterConstruction) {
    mElement = std::make_unique<Geometry::Line>();

    EXPECT_EQ(0, mElement->getCoordinates().size());    
}
/**
 * @brief Construct a new test object.
 * 
 * @test Verify properties after construction.
 */
TEST_F(LineTest, testValuesfterConstruction) {
    const std::pair<int, int> begin = std::pair<int, int>(1, 2);
    const std::pair<int, int> end = std::pair<int, int>(3, 4);
    mElement = std::make_unique<Geometry::Line>(begin, end);

    EXPECT_EQ(begin.first, mElement->getCoordinates().at(0));
    EXPECT_EQ(begin.second, mElement->getCoordinates().at(1));
    EXPECT_EQ(end.first, mElement->getCoordinates().at(2));
    EXPECT_EQ(end.second, mElement->getCoordinates().at(3));
}
/**
 * @brief Construct a new test object.
 * 
 * @test Verify default colors.
 */
TEST_F(LineTest, testColors) {
    const std::pair<int, int> begin = std::pair<int, int>(1, 2);
    const std::pair<int, int> end = std::pair<int, int>(3, 4);
    Color color{16, 32, 64, 128};
    mElement = std::make_unique<Geometry::Line>(begin, end, color);

    EXPECT_EQ(color.red, mElement->getDrawColor().red);
    EXPECT_EQ(color.green, mElement->getDrawColor().green);
    EXPECT_EQ(color.blue, mElement->getDrawColor().blue);
    EXPECT_EQ(color.alpha, mElement->getDrawColor().alpha);
}


}  // namespace test
}  // namesapce geometry
}  // namesapce cgl
