#pragma once
#include <imgui-hook.hpp>
#include <cocos2d.h>

using namespace cocos2d;

class MenuCheckbox
{
protected:
	std::function<void()> m_pFunc;

public:

	MenuCheckbox();
	virtual	~MenuCheckbox();

	bool init(const char* pCheckboxName, const char* pTooltip, std::function<void()> pCallback);

	static MenuCheckbox* create(const char* pCheckboxName, const char* pTooltip, std::function<void()> pCallback)
	{
		auto* menuCheckbox = new (std::nothrow) MenuCheckbox();

		if (menuCheckbox && menuCheckbox->init(pCheckboxName, pTooltip, pCallback))
		{
			return menuCheckbox;
		}

		CC_SAFE_DELETE(menuCheckbox);
		return nullptr;
	};
};

