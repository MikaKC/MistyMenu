#include "BasePanel.h"

bool BasePanel::init(const char *title, int w, int h)
{
	if (!ImGui::Begin(title, nullptr, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoCollapse)) return false;
	
	ImGui::SetWindowSize(ImVec2(300, 500), ImGuiCond_Once);

	return true;
}