// Copyright 2020. ULysses Don Rieken

#include <gst_helper.hpp>

namespace sandbox {
namespace gst_helper {

void initialize(int* argc, char*** argv) {
    ::gst_init(argc, argv);
}

}  // gst_helper
}  // namespace sandbox
