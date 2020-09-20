// Copyright 2020. Ulysses Don B. Rieken

#include <cstdio>

#include <sandbox_app.hpp>

namespace cgl {
namespace sandbox {
SandboxApp::SandboxApp() {
    std::printf("%s\n", __PRETTY_FUNCTION__);    
}

SandboxApp::~SandboxApp() {
    std::printf("%s\n", __PRETTY_FUNCTION__);    
}
}  // namespace sandbox
}  // namespace cgl
