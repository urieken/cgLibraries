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
#include <application/SDLSandboxApplication.hpp>

#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#include <imgui.h>
#include <backends/imgui_impl_sdl.h>
#include <backends/imgui_impl_sdlrenderer.h>


namespace cgl {
namespace sandbox {
namespace imgui {

constexpr auto NORMAL_FONT_FILE{"res/font/DroidSansMono.ttf"};
constexpr auto NORMAL_FONT_SIZE{16.0f};
constexpr auto BUTTON_FONT_FILE{"res/font/Alien_lines_1.9.ttf"};
constexpr auto BUTTON_FONT_SIZE{14.0f};

ImFont* NormalFont{nullptr};
ImFont* ButtonFont{nullptr};


IMGuiSDLRenderer::IMGuiSDLRenderer(const ::cgl::system::Arguments& arguments,
    SDL_Window* window, SDL_Renderer* renderer) :
    mWindow{window},
    mRenderer{renderer},
    mDrawColor{0, 0, 0, 255},
    mModulationColor{0, 0, 0, 255},
    mClearColors{64, 64, 64, 255},
    mDrawColors{0, 128, 0, 255},
    mFillColors{0, 0, 128, 255},
    mArguments{arguments} {


    IMGUI_CHECKVERSION();
    ::ImGui::CreateContext();
    ::ImGui::StyleColorsDark();
    ::ImGui_ImplSDL2_InitForSDLRenderer(mWindow);
    ::ImGui_ImplSDLRenderer_Init(mRenderer);
    auto io = ::ImGui::GetIO();
    NormalFont = io.Fonts->AddFontFromFileTTF(
        NORMAL_FONT_FILE, NORMAL_FONT_SIZE);
    // ButtonFont = io.Fonts->AddFontFromFileTTF(
    //     BUTTON_FONT_FILE, BUTTON_FONT_SIZE);
    io.Fonts->Build();
}

IMGuiSDLRenderer::~IMGuiSDLRenderer() {
    ::ImGui_ImplSDLRenderer_Shutdown();
    ::ImGui_ImplSDL2_Shutdown();
    ::ImGui::DestroyContext();
}

auto IMGuiSDLRenderer::OnEvent(const SDL_Event *event) -> bool {
    return ::ImGui_ImplSDL2_ProcessEvent(event);
}

auto IMGuiSDLRenderer::OnUpdate() -> void {
    ::ImGui_ImplSDLRenderer_NewFrame();
    ::ImGui_ImplSDL2_NewFrame(mWindow);
    ::ImGui::NewFrame();
    ::ImGui::PushFont(NormalFont);
    SystemInformation();
    ::ImGui::PopFont();
    // Arguments();
    // DrawColorInformation();
    // Events();
    Lesson01();
    Lesson08();
    ::ImGui::Render();

    
    ::ImGui_ImplSDLRenderer_RenderDrawData(::ImGui::GetDrawData());
}

auto IMGuiSDLRenderer::DrawColor() -> std::vector<int> {
    return mDrawColor;
}

auto IMGuiSDLRenderer::ModulationColor() -> std::vector<int> {
    return mModulationColor;
}

auto IMGuiSDLRenderer::AddCustomEvent(const std::string &key,
    const ::cgl::event::CustomSDLEevent &event) -> void {
    if (mUserEvents.end() == mUserEvents.find(key)) {
        mUserEvents[key] = event;
    }
}

auto IMGuiSDLRenderer::SystemInformation() -> void {
    ::ImGui::SetNextWindowSize(::ImVec2{350, 720}, ::ImGuiCond_Always);

    ::ImGui::Begin("System Information", nullptr, ::ImGuiWindowFlags_NoResize);

    ::ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "PLATFORM :");
    ::ImGui::SameLine();
    ::ImGui::Text("%s", ::SDL_GetPlatform());

    ::ImGui::Text("CORES    : %d", ::SDL_GetCPUCount());
    ::ImGui::Text("MEMORY   : %.2f GB", ::SDL_GetSystemRAM() / 1024.0f);   

    DisplayInformation();

    if (::ImGui::Button("Quit", ::ImVec2{350, 25})) {
        SDL_Event event{SDL_QUIT};
        ::SDL_PushEvent(&event);
    }


    ::ImGui::End();
}

auto IMGuiSDLRenderer::DisplayInformation() -> void {
    ::ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "DISPLAY COUNT :");
    ::ImGui::SameLine();

    auto displayCount = ::SDL_GetNumVideoDisplays();
    ::ImGui::Text("%d", displayCount);

    for(auto i = 0; i < displayCount; i++) {
        DisplayDetails(i);
    }
}

auto IMGuiSDLRenderer::DisplayDetails(const int& index) -> void {
    std::stringstream ss;
    ss << "DISPLAY:" << index;
    if(::ImGui::TreeNode(ss.str().c_str(), "%03d:%s",
        index, ::SDL_GetDisplayName(index))) {
        DisplayBounds(index);
        DisplayModes(index);
        ::ImGui::TreePop();
    }
}

auto IMGuiSDLRenderer::DisplayBounds(const int& index) -> void {
    SDL_Rect rect;
    if(0 == ::SDL_GetDisplayBounds(index, &rect)) {
        std::stringstream ss;
        ss << "BOUNDS:" << index;
        if(::ImGui::TreeNode(ss.str().c_str(), "BOUNDS")) {
            ::ImGui::Text("TOP    :%d", rect.x);
            ::ImGui::Text("LEFT   :%d", rect.y);
            ::ImGui::Text("WIDTH  :%d", rect.w);
            ::ImGui::Text("HEIGHT :%d", rect.h);
            ::ImGui::TreePop();
        }
    }
}

auto IMGuiSDLRenderer::DisplayModes(const int& index) -> void {
    auto modeCount = ::SDL_GetNumDisplayModes(index);
    std::stringstream ss;
    ss << "DISPLAY MODE COUNT:" << index;
    if(::ImGui::TreeNode(ss.str().c_str(), "DISPLAY MODES")) {
        for(auto mode = 0; mode < modeCount; mode++) {
            ss.str() = std::string{};
            ss << "DISPLAY MODE:" << mode;
            if (::ImGui::TreeNode(ss.str().c_str(), "%03d", mode)) {
                SDL_DisplayMode displayMode;
                if(0 == ::SDL_GetDisplayMode(index, mode, &displayMode)) {
                    ::ImGui::Text("WIDTH          :%d", displayMode.w);
                    ::ImGui::Text("HEIGHT         :%d", displayMode.h);
                    ::ImGui::Text("FORMAT         :0x%05xH",
                        displayMode.format);
                    ::ImGui::Text("NAME           :%s",
                        ::SDL_GetPixelFormatName(displayMode.format));
                    ::ImGui::Text("REFRESH RATE   :%dHz",
                        displayMode.refresh_rate);
                    ::ImGui::Text("BITS PER PIXEL :%i",
                        SDL_BITSPERPIXEL(displayMode.format));
                }
                ::ImGui::TreePop();
            }
        }
        ::ImGui::TreePop();
    }
}

auto IMGuiSDLRenderer::Arguments() -> void {
    ::ImGui::SetNextWindowSize(::ImVec2{300, 200},
        ::ImGuiCond_Always);
    ::ImGui::Begin("Arguments", nullptr, ::ImGuiWindowFlags_NoResize);
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
    ::ImGui::SetNextWindowSize(::ImVec2{250, 150}, ::ImGuiCond_Always);
    ::ImGui::Begin("Draw Color", nullptr, ::ImGuiWindowFlags_NoResize);
    ::ImGuiIO io = ::ImGui::GetIO();
    
    if (::ImGui::TreeNode("Modulation Color")) {
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
            ::ImGui::VSliderInt("##v", ::ImVec2{20, 150}, &mModulationColor[i],
                0, 255, "%d");
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

auto IMGuiSDLRenderer::Lesson01() -> void {
    ::ImGui::SetNextWindowSize(::ImVec2{250, 150}, ::ImGuiCond_Always);
    ::ImGui::Begin("LESSON 01", nullptr, ::ImGuiWindowFlags_NoResize);
    ::ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f),
        "Clear/Draw color");
    // ::ImGui::ColorEdit4("COLOR", &mColors[0]);
    if (::ImGui::TreeNode("Color components")) {
        bool update{false};
        update |= ::ImGui::SliderInt("Red", &mDrawColor[0], 0, 255);
        update |= ::ImGui::SliderInt("Green", &mDrawColor[1], 0, 255);
        update |= ::ImGui::SliderInt("Blue", &mDrawColor[2], 0, 255);
        if(update) {
            if(auto iter = mUserEvents.find("LESSON_01");
                mUserEvents.end() != iter) {
                SDL_Event event;

                ::SDL_memset(&event, 0, sizeof(event));

                event.type = iter->second.type;
                event.user.code = iter->second.code;
                event.user.data1 = mDrawColor.data();
                event.window.windowID = iter->second.id;

                ::SDL_PushEvent(&event);
            }
        }
        ::ImGui::TreePop();
    }
    ::ImGui::End();
}

auto IMGuiSDLRenderer::Lesson08() -> void {
    ::ImGui::SetNextWindowSize(::ImVec2{270, 150}, ::ImGuiCond_Always);
    ::ImGui::Begin("LESSON 08", nullptr, ::ImGuiWindowFlags_NoResize);
    ::ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f),
        "Geometry rendering");
    if(::ImGui::ColorEdit4("Clear", &mClearColors[0])) {
        if(auto iter = mUserEvents.find("LESSON_08");
            mUserEvents.end() != iter) {
                
            SDL_Event event;

            ::SDL_memset(&event, 0, sizeof(event));

            event.type = iter->second.type;
            event.user.code =
                static_cast<Sint32>(ImGuiEvent::ClearColorChange);
            event.user.data1 = mClearColors.data();
            event.window.windowID = iter->second.id;

            ::SDL_PushEvent(&event);
        }
    }
    if(::ImGui::ColorEdit4("Draw", &mDrawColors[0])) {
        if(auto iter = mUserEvents.find("LESSON_08");
            mUserEvents.end() != iter) {
                
            SDL_Event event;

            ::SDL_memset(&event, 0, sizeof(event));

            event.type = iter->second.type;
            event.user.code =
                static_cast<Sint32>(ImGuiEvent::DrawColorChange);
            event.user.data1 = mDrawColors.data();
            event.window.windowID = iter->second.id;

            ::SDL_PushEvent(&event);
        }
    }
    if(::ImGui::ColorEdit4("Fill", &mFillColors[0])) {
        if(auto iter = mUserEvents.find("LESSON_08");
            mUserEvents.end() != iter) {
                
            SDL_Event event;

            ::SDL_memset(&event, 0, sizeof(event));

            event.type = iter->second.type;
            event.user.code =
                static_cast<Sint32>(ImGuiEvent::FillColorChange);
            event.user.data1 = mFillColors.data();
            event.window.windowID = iter->second.id;

            ::SDL_PushEvent(&event);
        }
    }
    ::ImGui::End();
}

}  // namespace imgui
}  // namespace sandbox
}  // namespace cgl
