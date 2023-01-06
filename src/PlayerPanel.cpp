#include "PlayerPanel.h"
#include "Utils.h"
#include <fstream>

json jData;

void PlayerPanel::LoadJSON()
{
	std::ifstream stream("MistyMenu\\hacks\\player.json");
	
	std::string dat;
	std::getline(stream, dat, '\0');

	stream.close();

	jData = json::parse(dat)["hacks"];

	for (int i = 0; i < static_cast<int>(jData.size()); i++)
	{
		m_bBools.push_back(false);
	}
}

void PlayerPanel::LoadButtons()
{
	for (int i = 0; i < static_cast<int>(jData.size()); i++)
	{
		json currentHack = jData.at(i);

		static bool m_bCurrent = m_bBools[i];

		json opcodes = currentHack["opcodes"];

		if (ImGui::Checkbox(std::string(currentHack["name"]).c_str(), &m_bCurrent)) {
			for (int j = 0; j < opcodes.size(); j++)
			{
				json opcode = opcodes.at(j);
				uintptr_t addr;
				sscanf_s(std::string(opcode["addr"]).data(), "%x", &addr);

				std::string enabledBytes = std::string(opcode[(m_bCurrent ? "on" : "off")]);

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
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::SetTooltip(std::string(currentHack["desc"]).c_str());
			ImGui::EndTooltip();
		}
	}

}

bool PlayerPanel::init(const char* title)
{
	if (!BasePanel::init(title, 450, 800)) return false;

    PANEL_CREATE_CONTENT("cheats.player");

	this->LoadJSON();
	this->LoadButtons();

    PANEL_END_CONTENT();

	return true;
}