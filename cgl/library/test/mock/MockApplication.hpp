/**
 * @file MockApplication.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Mock for the Application class
 * @version 0.1
 * @date 2021-10-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_TEST_MOCK_MOCK_APPLICATION_HPP_
#define CGL_LIBRARY_TEST_MOCK_MOCK_APPLICATION_HPP_

#include <application/IApplication.hpp>

#include <event/IEvent.hpp>

#include <system/Unused.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace Event = ::cgl::event;
namespace System = ::cgl::system;

namespace cgl {
namespace application {
namespace test {

constexpr auto defaultTestReturnCode{12345};

class MockApplication : public IApplication {
public:
    /**
     * @brief Construct a new Mock Application object
     * 
     * @param argc Command line argument count.
     * @param argv Command line arguments.
     */
    MockApplication(int argc, char** argv) {
        System::unused(argc, argv);
        ON_CALL(*this, Run())
            .WillByDefault(::testing::Return(defaultTestReturnCode));
    }
    MOCK_METHOD0(Run, int());
    MOCK_METHOD1(OnEvent, bool(const Event::IEvent&));

};

}  // namespace test
}  // namespace application
}  // namespace cgl

#endif /* CGL_LIBRARY_TEST_MOCK_MOCK_APPLICATION_HPP_ */
