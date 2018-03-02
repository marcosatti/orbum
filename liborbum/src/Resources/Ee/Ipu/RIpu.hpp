#pragma once

#include "Common/Types/Memory/ArrayByteMemory.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"

struct RIpu
{
	RIpu();

	/// IPU memory mapped registers. See page 21 of EE Users Manual.
	/// 0x10002000
	SizedWordRegister cmd;
	SizedWordRegister ctrl;
	SizedWordRegister bp;
	SizedWordRegister top;
	ArrayByteMemory   memory_2040;
};

