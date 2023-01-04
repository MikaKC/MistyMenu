#pragma once
#include <imgui-hook.hpp>
#include <cocos2d.h>

using namespace cocos2d;

class MenuCheckbox
{
public:

	MenuCheckbox();
	virtual	~MenuCheckbox();

	bool init(const char* pCheckboxName, const char* pTooltip, bool* v, std::function<void()> pCallback);

	static MenuCheckbox* create(const char* pCheckboxName, const char* pTooltip, bool *v, std::function<void()> pCallback)
	{
		auto* menuCheckbox = new (std::nothrow) MenuCheckbox();

		if (menuCheckbox && menuCheckbox->init(pCheckboxName, pTooltip, v, pCallback))
		{
			return menuCheckbox;
		}

		CC_SAFE_DELETE(menuCheckbox);
		return nullptr;
	};
};

