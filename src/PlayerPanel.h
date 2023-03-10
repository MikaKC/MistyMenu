#pragma once

#include "BasePanel.h"

class PlayerPanel : public BasePanel
{
protected:
	std::string m_pPlayerTitle;
public:

	static PlayerPanel* sharedObject();

	void LoadJSON() override;
	virtual bool init(const char* title);
	void LoadButtons() override;
	virtual void draw();
};