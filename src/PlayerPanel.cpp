#include "PlayerPanel.h"
#include <fstream>

json jPlayerData;
std::vector<bool> m_bPlayerBools;

static PlayerPanel* gPlayerPanel = NULL;

PlayerPanel* PlayerPanel::sharedObject()
{
	if (gPlayerPanel == NULL)
	{
		gPlayerPanel = new (std::nothrow) PlayerPanel();
	}

	return gPlayerPanel;
}

void PlayerPanel::LoadJSON()
{
	std::ifstream stream("MistyMenu\\hacks\\player.json");

	std::string dat;
	std::getline(stream, dat, '\0');

	stream.close();

	jPlayerData = json::parse(dat)["hacks"];

	for (int i = 0; i < static_cast<int>(jPlayerData.size()); i++)
	{
		m_bPlayerBools.push_back(false);
	}
}

void PlayerPanel::LoadButtons()
{
	for (int i = 0; i < static_cast<int>(jPlayerData.size()); i++)
	{
		json currentHack = jPlayerData.at(i);

		json opcodes = currentHack["opcodes"];

		bool current = m_bPlayerBools[i];

		if(ImGui::Checkbox(std::string(currentHack["name"]).c_str(), &current))
		{
			m_bPlayerBools[i] = current;
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

bool PlayerPanel::init(const char* title) 
{
	m_pPlayerTitle = std::string(title);
	this->LoadJSON();

	return true;
}

void PlayerPanel::draw()
{
	BasePanel::draw(m_pPlayerTitle.c_str(), 375, 675);

	ImGui::SetWindowPos(ImVec2(10, 10), ImGuiCond_Once);

    PANEL_CREATE_CONTENT("cheats.player");

	this->LoadButtons();

	PANEL_END_CONTENT();
}