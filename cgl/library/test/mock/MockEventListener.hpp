/**
 * @file MockEventListener.hpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Mock for EventListener
 * @version 0.1
 * @date 2021-10-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CGL_LIBRARY_TEST_MOCK_MOCK_EVENT_LISTENER_HPP_
#define CGL_LIBRARY_TEST_MOCK_MOCK_EVENT_LISTENER_HPP_

#include <event/IEventListener.hpp>

#include <application/IApplication.hpp>
#include <event/IEvent.hpp>
#include <system/Unused.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace Application = ::cgl::application;

namespace cgl {
namespace event {
namespace test {

constexpr auto defaultTestReturnCode{12345};

/**
 * @brief Mock for EventListener
 */
class MockEventListener : public IEventListener {
public:
    explicit MockEventListener(Application::IApplication& app) {
        ::cgl::system::unused(app);
        ON_CALL(*this, Start())
            .WillByDefault(::testing::Return(defaultTestReturnCode));
    }
    MOCK_METHOD0(Start, int());
    MOCK_METHOD0(Stop, void());
    MOCK_METHOD1(PushEvent, void(const IEvent&));
};

}  // namespace test
}  // namespace event
}  // namespace cgl

#endif /* CGL_LIBRARY_TEST_MOCK_MOCK_EVENT_LISTENER_HPP_ */
