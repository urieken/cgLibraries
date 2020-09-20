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

auto app::OnInitialize(int* argc, char** argv) -> std::uint8_t {
    std::uint8_t ret{0};
    running(true);
    return ret;
}

auto app::OnCleanUp() -> void {
    running(false);
}

}  // namespace app
}  // namespace cgl
