/**
 * @file main.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Entry point for unit tests
 * @version 0.1
 * @date 2021-09-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <gtest/gtest.h>

auto main(int argc, char** argv) -> int {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
