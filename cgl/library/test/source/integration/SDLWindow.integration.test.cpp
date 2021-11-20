/**
 * @file SDLWindow.integration.test.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Integration test for SDLWindow
 * @version 0.1
 * @date 2021-10-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <display/IWindow.hpp>
#include <display/SDLWindow.hpp>

#include <memory>

#include <gtest/gtest.h>

#include <SDL2/SDL.h>

namespace Display = ::cgl::display;

namespace cgl {
namespace display {
namespace test {
/**
 * @brief Test fixture for SDLWindow
 */
class SDLWindowTest : public ::testing::Test {
protected:
    /**
     * @brief Pointer to the test object.
     */
    std::unique_ptr<Display::IWindow> mWindow;
};
/**
 * @brief Construct a new test object
 * 
 * @test Test construction with SDL not initialized.
 */
TEST_F(SDLWindowTest, testConstructionWithSDLUnitialized) {
    mWindow = std::make_unique<Display::SDLWindow>("SDLWindowTest",
        100, 100, 200, 200, SDL_WINDOW_SHOWN);
    EXPECT_NE(0, ::SDL_WasInit(SDL_INIT_EVERYTHING));
    EXPECT_NE(0, mWindow->GetId());
    ::SDL_Delay(100);
}

}  // namespace test
}  // namespace display
}  // namespace cgl
