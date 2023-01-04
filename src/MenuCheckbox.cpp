#include "MenuCheckbox.h"

MenuCheckbox::MenuCheckbox() {}

MenuCheckbox::~MenuCheckbox() {}

bool MenuCheckbox::init(const char* pCheckboxName, const char* pTooltip, std::function<void()> pCallback)
{
    m_pFunc = pCallback;
    static bool* m_bCheck = new bool;

    ImGui::Checkbox(pCheckboxName, m_bCheck);

    if (ImGui::IsItemClicked()) 
    {
        m_pFunc();
    }

    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::SetTooltip(pTooltip);
        ImGui::EndTooltip();
    }

    return true;
}