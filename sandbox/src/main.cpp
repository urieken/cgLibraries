// Copyright 2020. Ulysses Don Rieken

#include <cstdio>

#include <compilers/compilers.hpp>

int main(int argc, char** argv) {
    int code{0};
    std::printf("BUILT WITH %s : %s\n",
        cgl::Compilers::name().c_str(),
        cgl::Compilers::versionString().c_str());
    std::printf("[ARGC : %d][APP : %s]\n", argc, argv[0]);
    return code;
}
