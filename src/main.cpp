#include <matdash.hpp>
#include <imgui-hook.hpp>
#include "MenuCheckbox.h"
#include <direct.h>

// Panels
#include "PlayerPanel.h"

#define DEBUG_BUILD
// #undef DEBUG_BUILD

// defines add_hook to use minhook
#include <matdash/minhook.hpp>

// lets you use mod_main
#include <matdash/boilerplate.hpp>

#ifdef DEBUG_BUILD
#include <matdash/console.hpp>
#endif

#include <sys/stat.h>
#include <gd.h>

bool bShowWindow = false;
bool bFirstTimeRunning = true;

static ImFont* pFont = nullptr;

void init()
{
    srand(time(NULL));

    auto& style = ImGui::GetStyle();
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style.WindowBorderSize = 0.25f;
    style.ColorButtonPosition = ImGuiDir_Right;

    float rounding = 6.f;

    style.WindowRounding = 12.f;
    style.ChildRounding = rounding;
    style.FrameRounding = rounding;
    style.PopupRounding = rounding;
    style.ScrollbarRounding = rounding;
    style.TabRounding = rounding;

    pFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("MistyMenu\\assets\\Inter-SemiBold.ttf", 24.f);
    
    auto colors = style.Colors;

    // Colour ranges from 0 - 1, 1st param is R, 2nd is G, 3rd is B, 4th is A
    colors[ImGuiCol_WindowBg] = ImColor(30, 30, 30);
    colors[ImGuiCol_TitleBg] = colors[ImGuiCol_TitleBgActive] = ImColor(109, 94, 176);
    colors[ImGuiCol_CheckMark] = ImColor(142, 130, 191);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.71f, 0.71f, 0.71f, 0.35f);
    colors[ImGuiCol_ResizeGrip] = ImColor(109, 94, 176, 0);

    colors[ImGuiCol_FrameBg] = colors[ImGuiCol_FrameBgHovered] = ImColor(40, 40, 40);
    colors[ImGuiCol_FrameBgActive] = ImColor(45, 45, 45);

    colors[ImGuiCol_ResizeGripHovered] = ImColor(109, 94, 176, 0);
    colors[ImGuiCol_TitleBgCollapsed] = ImColor(109, 94, 176, 100);
    colors[ImGuiCol_ScrollbarBg] = ImColor(0, 0, 0, 0);

    colors[ImGuiCol_ResizeGripActive] = ImVec4(
        colors[ImGuiCol_ResizeGrip].x, 
        colors[ImGuiCol_ResizeGrip].y, 
        colors[ImGuiCol_ResizeGrip].z,
        0
    );

}

void draw()
{
    // Add font to the stack
    if (pFont) ImGui::PushFont(pFont);

    // If the window is not hidden, show content
    if (bShowWindow)
    {
        PlayerPanel::createPanel();
    }

    // Show splash at the beginning
    if (ImGui::GetTime() < 3.0) {
        ImGui::SetNextWindowPos({ 10, 10 });
        ImGui::Begin("mistymsg", nullptr,
            ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoSavedSettings);
        ImGui::Text("Misty Menu was loaded, press the TAB key to toggle");
        ImGui::End();
    }

    // Remove font from the stack
    if (pFont) ImGui::PopFont();
}

void mod_main(HMODULE) {
#ifdef DEBUG_BUILD
        matdash::create_console();
#endif

    ImGuiHook::setRenderFunction(draw);

    ImGuiHook::setToggleCallback([]() {
        bShowWindow = !bShowWindow;
    });

    ImGuiHook::setInitFunction(init);
    MH_Initialize();
    ImGuiHook::setupHooks([](void* target, void* hook, void** trampoline) {
        MH_CreateHook(target, hook, trampoline);
    });

    ImGuiHook::setKeybind(VK_TAB);
    MH_EnableHook(MH_ALL_HOOKS);
}