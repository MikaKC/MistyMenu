#pragma once

#include <imgui-hook.hpp>
#include <gd.h>
#include "MenuCheckbox.h"
#include "Json.hpp"

using json = nlohmann::json;

#define PANEL_CREATE_CONTENT(PANEL_TITLE) ImGui::BeginChild(PANEL_TITLE, ImVec2(ImGui::GetContentRegionAvail().x, 0), false, ImGuiWindowFlags_HorizontalScrollbar)
#define PANEL_END_CONTENT() ImGui::EndChild()

class BasePanel : public cocos2d::CCObject
{
public:
	virtual void LoadJSON() = 0;
	virtual void LoadButtons() = 0;
	virtual bool init(const char* title, int w = 300, int h = 500);
};