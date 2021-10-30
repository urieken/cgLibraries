/**
 * @file SDLRenderer.integration.test.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Integration test for SDLRenderer
 * @version 0.1
 * @date 2021-10-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <display/IRenderer.hpp>
#include <display/SDLRenderer.hpp>
#include <display/SDLWindow.hpp>

#include <memory>
#include <string>

#include <gtest/gtest.h>

#include <SDL2/SDL.h>

namespace Display = ::cgl::display;

namespace cgl {
namespace display {
namespace test {
/**
 * @brief Test fixture for SDLRenderer
 */
class SDLRendererTest : public ::testing::Test {
protected:
    /**
     * @brief Pointer to the test renderer.
     */
    std::unique_ptr<Display::IRenderer> mRenderer;
};

/**
 * @brief Construct a new test object
 * 
 * @test Run tests on invalid renderer.
 * @note It is expected that all SDL renderer calls will fail.
 */
TEST_F(SDLRendererTest, testRendererFaulure) {
    mRenderer = std::make_unique<Display::SDLRenderer>(0UL, 0, 0UL);
    mRenderer->SetDrawColor(0UL, 0UL, 0UL, 0UL);
    mRenderer->Clear();
    mRenderer->Present();
}
/**
 * @brief Construct a new test object
 * 
 * @test Run tests on a valid renderer.
 */
TEST_F(SDLRendererTest, testRenderer) {
    Display::SDLWindow testWindow{
        std::string{"Test window"},
        0, 0, 200, 200, SDL_WINDOW_SHOWN
    };
    mRenderer = std::make_unique<Display::SDLRenderer>(testWindow.GetId(),
        -1, SDL_RENDERER_ACCELERATED);
    mRenderer->SetDrawColor(0UL, 0UL, 0UL, 0UL);
    mRenderer->Clear();
    mRenderer->Present();
    ::SDL_Delay(100);
    mRenderer->SetDrawColor(255UL, 0UL, 0UL, 0UL);
    mRenderer->Clear();
    mRenderer->Present();
    ::SDL_Delay(100);
    mRenderer->SetDrawColor(0UL, 255UL, 0UL, 0UL);
    mRenderer->Clear();
    mRenderer->Present();
    ::SDL_Delay(100);
    mRenderer->SetDrawColor(0UL, 0UL, 255UL, 0UL);
    mRenderer->Clear();
    mRenderer->Present();
}
}  // namespace test
}  // namespace display
}  // namespace cgl
