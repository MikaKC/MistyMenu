#pragma once

#include "BasePanel.h"

class CreatorPanel : public BasePanel
{
protected:
	std::string m_pCreatorTitle;
public:

	static CreatorPanel* sharedObject();

	void LoadJSON() override;
	virtual bool init(const char* title);
	void LoadButtons() override;
	virtual void draw();
};