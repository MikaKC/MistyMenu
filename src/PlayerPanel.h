#pragma once

#include "BasePanel.h"

class PlayerPanel : public BasePanel
{
protected:
	std::vector<bool> m_bBools;

public:

	void LoadJSON() override;
	virtual bool init(const char* title);
	void LoadButtons() override;

	static PlayerPanel* createPanel()
	{
		auto pRet = new (std::nothrow) PlayerPanel();
		if (pRet && pRet->init("Player Hacks"))
		{
			pRet->autorelease();
			return pRet;
		}

		CC_SAFE_DELETE(pRet);
		return nullptr;
	};
};