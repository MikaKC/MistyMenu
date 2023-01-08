#include <matdash.hpp>
#include <direct.h>

// Panels
#include "PlayerPanel.h"
#include "CreatorPanel.h"
#include "BypassPanel.h"
#include "GlobalPanel.h"

#define DEBUG_BUILD
#undef DEBUG_BUILD

// defines add_hook to use minhook
#include <matdash/minhook.hpp>

// lets you use mod_main
#include <matdash/boilerplate.hpp>

#ifdef DEBUG_BUILD
#include <matdash/console.hpp>
#endif

bool bShowWindow = false;
static ImFont* pFont = nullptr;

bool MoreOptionsLayer_initHook(gd::MoreOptionsLayer* self)
{
    bool ret = matdash::orig<&MoreOptionsLayer_initHook>(self);
    self->addToggle("Show FPS", "misty-menu-0001", "Shows the frames per second on the top of the screen.");
    return ret;
}


void init()
{
    srand(time(NULL));

    PlayerPanel::sharedObject()->init("Player Cheats");
    CreatorPanel::sharedObject()->init("Creator Cheats");
    GlobalPanel::sharedObject()->init("Global Cheats");
    BypassPanel::sharedObject()->init("Bypass Cheats");


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

    style.WindowBorderSize = 0.f;
    style.ScrollbarSize = 12.f;


    style.WindowPadding = ImVec2(8.00f, 8.00f);
    style.FramePadding = ImVec2(4.00f, 4.00f);
    style.CellPadding = ImVec2(4.00f, 2.00f);
    style.ItemSpacing = ImVec2(4.00f, 4.00f);
    style.ItemInnerSpacing = ImVec2(4.00f, 4.00f);
    style.TouchExtraPadding = ImVec2(0.00f, 0.00f);

    style.IndentSpacing = 21.00f;

    style.DisplaySafeAreaPadding = ImVec2(3.00f, 3.00f);

    pFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("MistyMenu\\assets\\Inter-SemiBold.ttf", 24.f);
    
    auto colors = style.Colors;

    // Colour ranges from 0 - 1, 1st param is R, 2nd is G, 3rd is B, 4th is A
    colors[ImGuiCol_WindowBg] = ImColor(30, 30, 30);
    colors[ImGuiCol_TitleBg] = colors[ImGuiCol_TitleBgActive] = ImColor(99, 100, 171);
    colors[ImGuiCol_CheckMark] = ImColor(99, 100, 171);
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
    if (pFont) ImGui::PushFont(pFont);

    if (gd::GameManager::sharedState()->getGameVariable("misty-menu-0001"))
    {
        ImGui::SetNextWindowPos({ 5, 5 });
        ImGui::SetNextWindowBgAlpha(0.25f);
        ImGui::Begin("fpscounter", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoSavedSettings);
        ImGui::Text("FPS: %.0f", ImGui::GetIO().Framerate);
        ImGui::End();
    }

    if (bShowWindow)
    {
        PlayerPanel::sharedObject()->draw();
        CreatorPanel::sharedObject()->draw();
        GlobalPanel::sharedObject()->draw();
        BypassPanel::sharedObject()->draw();
    }
#ifdef DEBUG_BUILD
    if (ImGui::GetTime() < 2.0) {
        ImGui::SetNextWindowPos({ 10, 10 });
        ImGui::Begin("mistymsg", nullptr,
            ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoSavedSettings);
        ImGui::Text("Misty Menu was loaded, press the TAB key to toggle");
        ImGui::End();
    }
#endif

    if (pFont) ImGui::PopFont();
}

void mod_main(HMODULE) {
#ifdef DEBUG_BUILD
    matdash::create_console();
#endif
    matdash::add_hook<&MoreOptionsLayer_initHook>(gd::base + 0x1DE8F0);
    
    ImGuiHook::setRenderFunction(draw);
    
    ImGuiHook::setToggleCallback([]() {
        bShowWindow = !bShowWindow;
    });
    
    ImGuiHook::setInitFunction(init);
    ImGuiHook::setupHooks([](void* target, void* hook, void** trampoline) {
        MH_CreateHook(target, hook, trampoline);
    });
    
    ImGuiHook::setKeybind(VK_TAB);
    MH_EnableHook(MH_ALL_HOOKS);
}