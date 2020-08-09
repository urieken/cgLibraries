// Copyright 2020. Ulysses Don Rieken

#ifndef SANDBOX_INC_GST_HELPER_HPP_
#define SANDBOX_INC_GST_HELPER_HPP_

#include <gst/gst.h>

#include <string>

namespace sandbox {
namespace gst_helper {

void initialize(int* argc, char*** argv);

}  // gst_helper
}  // namespace sandbox

#endif  // SANDBOX_INC_GST_HELPER_HPP_
