#include "MenuCheckbox.h"

MenuCheckbox::MenuCheckbox() {}

MenuCheckbox::~MenuCheckbox() {}

bool MenuCheckbox::init(const char* pCheckboxName, const char* pTooltip, bool *v, std::function<void()> pCallback)
{
    if (!ImGui::Checkbox(pCheckboxName, v)) return false;
    
    pCallback();

    if (ImGui::IsItemHovered())
        ImGui::SetTooltip(pTooltip);

    return true;
}