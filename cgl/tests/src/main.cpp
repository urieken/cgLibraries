// Copyright 2020. Ulysses Don Rieken

#include <gtest/gtest.h>

auto main(int argc, char** argv) -> int {
    int nReturn{0};
    ::testing::InitGoogleTest(&argc, argv);
    nReturn = RUN_ALL_TESTS();
    return nReturn;
}
