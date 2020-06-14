// Copyright 2020. Ulysses Don Rieken

#include <gtest/gtest.h>

int main(int argc, char** argv) {
    int nReturn{0};
    ::testing::InitGoogleTest(&argc, argv);
    nReturn = RUN_ALL_TESTS();
    return nReturn;
}