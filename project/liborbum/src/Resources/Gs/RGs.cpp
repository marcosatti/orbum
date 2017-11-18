#include "Resources/Gs/RGs.hpp"

RGs::RGs() :
	memory_00f0(0x310, 0, true),
	memory_1020(0x20, 0, true),
	memory_1050(0x30, 0, true),
	memory_1090(0x60, 0, true),
	memory_1100(0x300, 0, true),
	memory_2000(0xE000, 0, true)
{
}
