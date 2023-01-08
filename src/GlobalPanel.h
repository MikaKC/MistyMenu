#pragma once

#include "BasePanel.h"

class GlobalPanel : public BasePanel
{
protected:
	std::string m_pGlobalTitle;
public:

	static GlobalPanel* sharedObject();

	void LoadJSON() override;
	virtual bool init(const char* title);
	void LoadButtons() override;
	virtual void draw();
};