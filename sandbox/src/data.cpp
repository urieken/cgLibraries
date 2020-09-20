// Copyright 2020. Ulysses Don Rieken

#include <thread>
#include <chrono>
#include <cstdio>

#include <data.hpp>

namespace sandbox {

auto foo(std::promise<std::uint8_t>&& count,
         std::uint8_t start, std::uint8_t stop) -> void {
    std::printf("%s:%d:%d\n", __func__, __FILE__, __LINE__);
    auto counter = 0;
    for (auto i = start; i < stop; i++) {
        std::printf("COUNT : %d\n", i);
        counter++;
        std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }
    count.set_value(counter);
}

auto cnt(std::uint8_t start, std::uint8_t stop) -> std::uint8_t {
    auto counter = 0;
    for (auto i = start; i < stop; i++) {
        std::printf("COUNTER : %d\n", i);
        counter++;
        std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }
    return counter;
}

}  // namespace sandbox
