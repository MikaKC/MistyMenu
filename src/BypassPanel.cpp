#include "BypassPanel.h"
#include <fstream>

json jBypassData;
std::vector<bool> m_bBypassBools;

static BypassPanel* gBypassPanel = NULL;

BypassPanel* BypassPanel::sharedObject()
{
	if (gBypassPanel == NULL)
	{
		gBypassPanel = new (std::nothrow) BypassPanel();
	}

	return gBypassPanel;
}

void BypassPanel::LoadJSON()
{
	std::ifstream stream("MistyMenu\\hacks\\bypass.json");

	std::string dat;
	std::getline(stream, dat, '\0');

	stream.close();

	jBypassData = json::parse(dat)["hacks"];

	for (int i = 0; i < static_cast<int>(jBypassData.size()); i++)
	{
		m_bBypassBools.push_back(false);
	}
}

void BypassPanel::LoadButtons()
{
	for (int i = 0; i < static_cast<int>(jBypassData.size()); i++)
	{
		json currentHack = jBypassData.at(i);

		json opcodes = currentHack["opcodes"];

		bool current = m_bBypassBools[i];

		if(ImGui::Checkbox(std::string(currentHack["name"]).c_str(), &current)) { 
			m_bBypassBools[i] = current;
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

bool BypassPanel::init(const char* title)
{
	m_pBypassTitle = std::string(title);
	this->LoadJSON();

	return true;
}

void BypassPanel::draw()
{
	BasePanel::draw(m_pBypassTitle.c_str(), 375, 675);
	ImGui::SetWindowPos(ImVec2(780, 10), ImGuiCond_Once);

	PANEL_CREATE_CONTENT("cheats.bypass");
	

	this->LoadButtons();

	PANEL_END_CONTENT();
}