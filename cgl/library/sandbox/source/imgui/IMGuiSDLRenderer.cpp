/**
 * @file IMGuiSDLRenderer.cpp
 * @author Ulysses Don Rieken (ulysses.rieken@gmail.com)
 * @brief Source for IMGuiSDLRenderer
 * @version 0.1
 * @date 2021-12-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <imgui/IMGuiSDLRenderer.hpp>

#include <iomanip>
#include <sstream>
#include <vector>

#include <imgui.h>
#include <backends/imgui_impl_sdl.h>
#include <backends/imgui_impl_sdlrenderer.h>


namespace cgl {
namespace sandbox {
namespace imgui {

IMGuiSDLRenderer::IMGuiSDLRenderer(const ::cgl::system::Arguments& arguments,
    SDL_Window* window, SDL_Renderer* renderer) :
    mDrawColor{0, 0, 0, 255},
    mArguments{arguments} {
    IMGUI_CHECKVERSION();
    ::ImGui::CreateContext();
    ::ImGui::StyleColorsDark();
    ::ImGui_ImplSDL2_InitForSDLRenderer(window);
    ::ImGui_ImplSDLRenderer_Init(renderer);
}

IMGuiSDLRenderer::~IMGuiSDLRenderer() {
    ::ImGui_ImplSDLRenderer_Shutdown();
    ::ImGui_ImplSDL2_Shutdown();
    ::ImGui::DestroyContext();
}

auto IMGuiSDLRenderer::OnEvent(const SDL_Event *event) -> bool {
    return ::ImGui_ImplSDL2_ProcessEvent(event);
}

auto IMGuiSDLRenderer::OnUpdate(SDL_Window* window) -> void {
    ::ImGui_ImplSDLRenderer_NewFrame();
    ::ImGui_ImplSDL2_NewFrame(window);
    ::ImGui::NewFrame();
    SystemInformation();
    Arguments();
    DrawColorInformation();
    Events();
    ::ImGui::Render();
    ::ImGui_ImplSDLRenderer_RenderDrawData(::ImGui::GetDrawData());
}

auto IMGuiSDLRenderer::DrawColor() -> std::vector<int> {
    return mDrawColor;
}

auto IMGuiSDLRenderer::SystemInformation() -> void {
    ::ImGui::SetNextWindowSize(::ImVec2{180, 110},
        ::ImGuiCond_Always);
    ::ImGui::Begin("System Information", nullptr,
        ::ImGuiWindowFlags_NoResize);
    ::ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Platform :");
    ::ImGui::SameLine();
    ::ImGui::Text("%s", SDL_GetPlatform());
    ::ImGui::Text("CPU cores: %d", SDL_GetCPUCount());
    ::ImGui::Text("RAM: %.2f GB", SDL_GetSystemRAM() / 1024.0f);   
    if (::ImGui::Button("Quit", ::ImVec2{160, 20})) {
        SDL_Event event{SDL_QUIT};
        ::SDL_PushEvent(&event);
    }
    ::ImGui::End();
}

auto IMGuiSDLRenderer::Arguments() -> void {
    ::ImGui::SetNextWindowSize(::ImVec2{300, 200},
        ::ImGuiCond_Always);
    ::ImGui::Begin("Arguments", nullptr,
        ::ImGuiWindowFlags_NoResize);
    if (::ImGui::TreeNode("Properties")) {
        ::ImGui::SetNextTreeNodeOpen(true, ::ImGuiCond_Once);
        if (::ImGui::TreeNode("Application")) {
            ::ImGui::Text("Name   : %s",
                mArguments.GetProperty("name")->c_str());
            ::ImGui::TreePop();
        }
        if (::ImGui::TreeNode("Window")) {
            std::stringstream ss;
            ss << "0x" << std::hex << std::setfill('0')
               << std::setw(5) 
               << mArguments.GetProperty("sdl_window_flags")
                    .value_or("0") << "H"; 
            ::ImGui::Text("Top    : %s",
                mArguments.GetProperty("top")->c_str());
            ::ImGui::Text("Left   : %s",
                mArguments.GetProperty("left")->c_str());
            ::ImGui::Text("Width  : %s",
                mArguments.GetProperty("width")->c_str());
            ::ImGui::Text("Height : %s",
                mArguments.GetProperty("height")->c_str());
            ::ImGui::Text("Flags  : %s", ss.str().c_str());
            ::ImGui::TreePop();
        }
        ::ImGui::TreePop();
    }
    ::ImGui::End();
}

auto GenerateColor(int index, float saturation) -> ::ImColor {
    switch(index) {
        case 0 : {
            return ::ImColor{saturation, 0.0f, 0.0f};
        }break;
        case 1 : {
            return ::ImColor{0.0f, saturation, 0.0f};
        }break;
        case 2 : {
            return ::ImColor{0.0f, 0.0f, saturation};
        }break;
        default:
            return ::ImColor{0.0f, 0.0f, 0.0f};
        break;
    }
    return ::ImColor{0.0f, 0.0f, 0.0f};
}

auto IMGuiSDLRenderer::DrawColorInformation() -> void {
    ::ImGui::SetNextWindowSize(::ImVec2{120, 210},
        ::ImGuiCond_Always);
    ::ImGui::Begin("Draw Color", nullptr,
        ::ImGuiWindowFlags_NoResize);
    ::ImGuiIO io = ::ImGui::GetIO();
    if (::ImGui::TreeNode("Clear Color")) {
        const float spacing{4.0f};
        ::ImGui::PushStyleVar(::ImGuiStyleVar_ItemSpacing,
            ::ImVec2{spacing, spacing});
        for (auto i = 0; i < 3; i++) {
            if (0 < i) {
                ::ImGui::SameLine();
            }
            ::ImVec4 backColor = GenerateColor(i, 0.5f);
            ::ImVec4 hoverColor = GenerateColor(i, 0.75f);
            ::ImVec4 activeColor = GenerateColor(i, 0.85f);
            ::ImVec4 grabColor = GenerateColor(i, 1.0f);
            ::ImGui::PushID(i);
            ::ImGui::PushStyleColor(::ImGuiCol_FrameBg, backColor);
            ::ImGui::PushStyleColor(::ImGuiCol_FrameBgHovered, hoverColor);
            ::ImGui::PushStyleColor(::ImGuiCol_FrameBgActive, activeColor);
            ::ImGui::PushStyleColor(::ImGuiCol_SliderGrab, grabColor);
            ::ImGui::VSliderInt("##v",
                ::ImVec2{20, 150}, &mDrawColor[i], 0, 255, "%d");
            ::ImGui::PopStyleColor(4);
            ::ImGui::PopID();            
        }
        ::ImGui::PopStyleVar();
        ::ImGui::TreePop();
    }
    ::ImGui::End();
}

auto IMGuiSDLRenderer::Events() -> void {
    ::ImGui::SetNextWindowSize(::ImVec2{300, 150},
        ::ImGuiCond_Always);
    ::ImGui::Begin("Events", nullptr,
        ::ImGuiWindowFlags_NoResize);
    ::ImGuiIO io = ::ImGui::GetIO();
    if (::ImGui::IsMousePosValid()) {
        ::ImGui::Text("Mouse position : (%g, %g)",
            io.MousePos.x, io.MousePos.y);
    }
    for (auto i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++) {
        if (::ImGui::IsKeyDown(i)) {
            ::ImGui::Text("Key %d(0x%X) is down for (%.02f seconds)",
                i, i, io.KeysDownDuration[i]);
        }
        if (::ImGui::IsKeyPressed(i)) {
            ::ImGui::Text("Pressed %d (0x%X)", i, i);
        }
        if (::ImGui::IsKeyReleased(i)) {
            ::ImGui::Text("Released %d (0x%X)", i, i);
        }
    }
    ::ImGui::End();
}

}  // namespace imgui
}  // namespace sandbox
}  // namespace cgl
