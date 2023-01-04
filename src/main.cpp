#include <matdash.hpp>
#include <imgui-hook.hpp>
#include "MenuCheckbox.h"

#define DEBUG_BUILD

// defines add_hook to use minhook
#include <matdash/minhook.hpp>

// lets you use mod_main
#include <matdash/boilerplate.hpp>

#ifdef DEBUG_BUILD
#include <matdash/console.hpp>
#endif

#include <gd.h>

bool bShowWindow = false;

static ImFont* pFont = nullptr;

void init()
{
    auto& style = ImGui::GetStyle();
    style.WindowTitleAlign = ImVec2(0.f, 0.5f);
    style.WindowBorderSize = 0.25f;
    style.ColorButtonPosition = ImGuiDir_Right;
    
    pFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\CascadiaCode.ttf", 24.f);
    
    auto colors = style.Colors;

    // Colour ranges from 0 - 1, 1st param is R, 2nd is G, 3rd is B, 4th is A
    colors[ImGuiCol_FrameBg] = ImVec4(0.31f, 0.31f, 0.31f, 0.54f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.59f, 0.59f, 0.59f, 0.40f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.61f, 0.61f, 0.61f, 0.67f);
    colors[ImGuiCol_TitleBg] = colors[ImGuiCol_TitleBgActive] = ImColor(109, 94, 176);
    colors[ImGuiCol_CheckMark] = ImColor(142, 130, 191);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.71f, 0.71f, 0.71f, 0.35f);
    colors[ImGuiCol_ResizeGrip] = ImColor(109, 94, 176, 120);

    colors[ImGuiCol_ResizeGripHovered] = ImColor(109, 94, 176, 175);

    colors[ImGuiCol_ResizeGripActive] = ImVec4(
        colors[ImGuiCol_ResizeGrip].x, 
        colors[ImGuiCol_ResizeGrip].y, 
        colors[ImGuiCol_ResizeGrip].z,
        colors[ImGuiCol_ResizeGrip].w + 0.4f
    );

}

void draw()
{
    // Add font to the stack
    if (pFont) ImGui::PushFont(pFont);

    // If the window is not hidden, show content
    if (bShowWindow)
    {
        ImGui::SetNextWindowContentSize(ImVec2(0.75f, 0.75f));
        
        if (ImGui::Begin("Player Cheats", nullptr, ImGuiWindowFlags_HorizontalScrollbar))
        {
            ImGui::SetWindowSize(ImVec2(300, 500));

            const auto avail = ImGui::GetContentRegionAvail();

            ImGui::BeginChild("cheats.player", ImVec2(avail.x, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

            MenuCheckbox::create("NoClip", "Makes the player invincible", [=](){
                // Callback
            });

            MenuCheckbox::create("NoTouch", "Makes the player no-touch.", [=]() {
                
            });

            ImGui::EndChild();
        }
    }

    // Show splash at the beginning
    if (ImGui::GetTime() < 5.0) {
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