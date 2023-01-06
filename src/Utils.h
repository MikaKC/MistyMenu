#pragma once

#include <iostream>
#include <Windows.h>

namespace Utils
{
	void WriteProcMem(std::uintptr_t addr, std::vector<uint8_t> bytes)
	{
		WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(addr), (LPCVOID)bytes.data(), bytes.size(), NULL);
	}
}