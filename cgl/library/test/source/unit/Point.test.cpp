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
#include <geometry/Point.hpp>

#include <memory>

#include <gtest/gtest.h>

namespace Geometry = ::cgl::geometry;

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

    EXPECT_EQ(0, point->getX());
    EXPECT_EQ(0, point->getY());
    EXPECT_EQ(0, point->getCoordinates().first);
    EXPECT_EQ(0, point->getCoordinates().second);
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

    EXPECT_EQ(X, point->getX());
    EXPECT_EQ(Y, point->getY());
    EXPECT_EQ(X, point->getCoordinates().first);
    EXPECT_EQ(Y, point->getCoordinates().second);
}
/**
 * @brief Construct a new test object.
 * 
 * @test Verify default properties after setting new values.
 */
TEST_F(PointTest, testValues) {
    constexpr auto X{1};
    constexpr auto Y{2};
    mElement = std::make_unique<Geometry::Point>();
    const auto point = static_cast<Geometry::Point*>(mElement.get());

    EXPECT_EQ(0, point->getX());
    EXPECT_EQ(0, point->getY());
    EXPECT_EQ(0, point->getCoordinates().first);
    EXPECT_EQ(0, point->getCoordinates().second);
    point->setX(X);
    point->setY(Y);
    EXPECT_EQ(X, point->getX());
    EXPECT_EQ(Y, point->getY());
    EXPECT_EQ(X, point->getCoordinates().first);
    EXPECT_EQ(Y, point->getCoordinates().second);
    point->setCoordinates(0, 0);
    EXPECT_EQ(0, point->getX());
    EXPECT_EQ(0, point->getY());
    EXPECT_EQ(0, point->getCoordinates().first);
    EXPECT_EQ(0, point->getCoordinates().second);
}

}  // namespace test
}  // namespace geometry
}  // namespace cgl
