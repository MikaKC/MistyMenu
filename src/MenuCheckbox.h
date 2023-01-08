#pragma once
#include <imgui-hook.hpp>
#include <cocos2d.h>

using namespace cocos2d;

class MenuCheckbox : public cocos2d::CCObject
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
			menuCheckbox->autorelease();
			return menuCheckbox;
		}

		CC_SAFE_DELETE(menuCheckbox);
		return nullptr;
	};
};

