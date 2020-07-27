// Copyright 2020. Ulysses Don Rieken

#include <cstdio>

#include <app/app.hpp>

namespace cgl {
namespace app {
app::app() {
    running(false);
}
app::~app() {
}
std::uint8_t app::OnInitialize(int* argc, char** argv) {
    std::uint8_t ret{0};
    running(true);
    return ret;
}
void app::OnCleanUp() {
    running(false);
}
}  // namespace app
}  // namespace cgl
