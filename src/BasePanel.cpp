#include "BasePanel.h"

void BasePanel::draw(const char *title, int w, int h)
{
	if (!ImGui::Begin(title, nullptr, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoCollapse)) return;
	
	ImGui::SetWindowSize(ImVec2(w, h), ImGuiCond_Once);
}