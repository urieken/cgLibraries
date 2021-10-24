/**
 * @file MockApplication.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Mock for application
 * @version 0.1
 * @date 2021-10-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_TEST_SOURCE_MOCK_MOCK_APPLICATION_HPP_
#define CGL_LIBRARY_TEST_SOURCE_MOCK_MOCK_APPLICATION_HPP_

#include <application/IApplication.hpp>

#include <event/IEvent.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace App = ::cgl::application;
namespace Event = ::cgl::event;

namespace cgl {
namespace application {
namespace test {
/**
 * @brief Mock for the application class.
 */
class MockApplication : public App::IApplication {
public:
    MOCK_METHOD1(OnEvent, bool(const Event::IEvent));
};

}  // namespace test
}  // namespace application
}  // namespace cgl

#endif /* CGL_LIBRARY_TEST_SOURCE_MOCK_MOCK_APPLICATION_HPP_ */
