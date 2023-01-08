#pragma once

#include <iostream>
#include <Windows.h>
#include <vector>

namespace Utils
{
	void WriteProcMem(std::uintptr_t addr, std::vector<uint8_t> bytes);
}