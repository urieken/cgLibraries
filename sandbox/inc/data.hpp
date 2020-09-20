// Copyright 2020. Ulysses Don Rieken

#ifndef SANDBOX_INC_DATA_HPP_
#define SANDBOX_INC_DATA_HPP_

#include <future>
#include <cstdint>

namespace sandbox {

auto foo(std::promise<std::uint8_t>&& count,
         std::uint8_t start, std::uint8_t stop) -> void;

auto cnt(std::uint8_t start, std::uint8_t stop) -> std::uint8_t;

}  // namespace sandbox

#endif  // SANDBOX_INC_DATA_HPP_
