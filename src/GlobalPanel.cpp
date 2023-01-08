#include "GlobalPanel.h"
#include <fstream>

json jGlobalData;
std::vector<bool> m_bGlobalBools;

static GlobalPanel* gCreatorPanel = NULL;

GlobalPanel* GlobalPanel::sharedObject()
{
	if (gCreatorPanel == NULL)
	{
		gCreatorPanel = new (std::nothrow) GlobalPanel();
	}

	return gCreatorPanel;
}

void GlobalPanel::LoadJSON()
{
	std::ifstream stream("MistyMenu\\hacks\\global.json");

	std::string dat;
	std::getline(stream, dat, '\0');

	stream.close();

	jGlobalData = json::parse(dat)["hacks"];

	for (int i = 0; i < static_cast<int>(jGlobalData.size()); i++)
	{
		m_bGlobalBools.push_back(false);
	}
}

void GlobalPanel::LoadButtons()
{
	for (int i = 0; i < static_cast<int>(jGlobalData.size()); i++)
	{
		json currentHack = jGlobalData.at(i);

		json opcodes = currentHack["opcodes"];

		bool current = m_bGlobalBools[i];

		if(ImGui::Checkbox(std::string(currentHack["name"]).c_str(), &current))
		{
			m_bGlobalBools[i] = current;
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

bool GlobalPanel::init(const char* title)
{
	m_pGlobalTitle = std::string(title);
	this->LoadJSON();

	return true;
}

void GlobalPanel::draw()
{
	BasePanel::draw(m_pGlobalTitle.c_str(), 375, 650);
	ImGui::SetWindowPos(ImVec2(1165, 10), ImGuiCond_Once);

	PANEL_CREATE_CONTENT("cheats.global");

	this->LoadButtons();

	PANEL_END_CONTENT();
}