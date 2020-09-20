// Copyright 2020. ULysses Don Rieken

#include <gst_helper.hpp>

namespace sandbox {
namespace gst_helper {

auto initialize(int* argc, char*** argv) -> void {
    ::gst_init(argc, argv);
}

}  // gst_helper
}  // namespace sandbox
