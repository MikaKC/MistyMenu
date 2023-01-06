#include "MenuCheckbox.h"

MenuCheckbox::MenuCheckbox() {}

MenuCheckbox::~MenuCheckbox() {}

bool MenuCheckbox::init(const char* pCheckboxName, const char* pTooltip, bool *v, std::function<void()> pCallback)
{
    if (ImGui::Checkbox(pCheckboxName, v))
    {
        pCallback();

        if (ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::SetTooltip(pTooltip);
            ImGui::EndTooltip();
        }

        return true;
    }

    return false;
}