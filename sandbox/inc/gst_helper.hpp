// Copyright 2020. Ulysses Don Rieken

#ifndef SANDBOX_INC_GST_HELPER_HPP_
#define SANDBOX_INC_GST_HELPER_HPP_

#include <gst/gst.h>

#include <string>

namespace sandbox {
namespace gst_helper {

auto initialize(int* argc, char*** argv) -> void;

}  // gst_helper
}  // namespace sandbox

#endif  // SANDBOX_INC_GST_HELPER_HPP_
