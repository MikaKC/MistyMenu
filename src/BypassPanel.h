#pragma once

#include "BasePanel.h"

class BypassPanel : public BasePanel
{
protected:
	std::string m_pBypassTitle;
public:

	static BypassPanel* sharedObject();

	void LoadJSON() override;
	virtual bool init(const char* title);
	void LoadButtons() override;
	virtual void draw();
};