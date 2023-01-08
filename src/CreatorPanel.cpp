#include "CreatorPanel.h"
#include <fstream>

json jCreatorData;
std::vector<bool> m_bCreatorBools;

static CreatorPanel* gCreatorPanel = NULL;

CreatorPanel* CreatorPanel::sharedObject()
{
	if (gCreatorPanel == NULL)
	{
		gCreatorPanel = new (std::nothrow) CreatorPanel();
	}

	return gCreatorPanel;
}

void CreatorPanel::LoadJSON()
{
	std::ifstream stream("MistyMenu\\hacks\\creator.json");

	std::string dat;
	std::getline(stream, dat, '\0');

	stream.close();

	jCreatorData = json::parse(dat)["hacks"];

	for (int i = 0; i < static_cast<int>(jCreatorData.size()); i++)
	{
		m_bCreatorBools.push_back(false);
	}
}

void CreatorPanel::LoadButtons()
{
	for (int i = 0; i < static_cast<int>(jCreatorData.size()); i++)
	{
		json currentHack = jCreatorData.at(i);

		json opcodes = currentHack["opcodes"];

		bool current = m_bCreatorBools[i];

		if(ImGui::Checkbox(std::string(currentHack["name"]).c_str(), &current)){
			m_bCreatorBools[i] = current;
			for (int j = 0; j < opcodes.size(); j++)
			{
				json opcode = opcodes.at(j);
				uintptr_t addr;
				sscanf_s(std::string(opcode["addr"]).data(), "%x", &addr);

				std::string enabledBytes = std::string(opcode[(current ? "on" : "off")]);

				enabledBytes.push_back(' ');

				std::vector<uint8_t> bytes;

				std::string currentByte("");

				for (int h = 0; h < enabledBytes.size(); h++)
				{

					if (enabledBytes.at(h) == ' ')
					{
						int currentByteNum;
						sscanf_s(std::string("0x" + currentByte).data(), "%x", &currentByteNum);
						bytes.push_back(currentByteNum);
						currentByte.clear();
						continue;
					}

					currentByte.push_back(enabledBytes.at(h));
				}

				DWORD currentBase = gd::base;
				if (!opcode["lib"].is_null() && std::string(opcode["lib"]) == "libcocos2d.dll") {
					currentBase = (DWORD)GetModuleHandleA("libcocos2d.dll");
				}

				Utils::WriteProcMem(currentBase + addr, bytes);
			}
		}
		if (ImGui::IsItemHovered()) {
			ImGui::SetTooltip(std::string(currentHack["desc"]).c_str());
		}
	}
}

bool CreatorPanel::init(const char* title)
{
	m_pCreatorTitle = std::string(title);
	this->LoadJSON();

	return true;
}

void CreatorPanel::draw()
{
	BasePanel::draw(m_pCreatorTitle.c_str(), 375, 650);
	ImGui::SetWindowPos(ImVec2(395, 10), ImGuiCond_Once);

	PANEL_CREATE_CONTENT("cheats.creator");

	this->LoadButtons();

	PANEL_END_CONTENT();
}