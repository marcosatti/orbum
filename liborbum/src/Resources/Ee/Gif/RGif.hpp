#pragma once

#include "Common/Types/Register/SizedWordRegister.hpp"
#include "Common/Types/Memory/ArrayByteMemory.hpp"

struct RGif
{
	RGif();

	/// GIF memory mapped registers. See page 21 of EE Users Manual.
	SizedWordRegister ctrl;
	SizedWordRegister mode;
	SizedWordRegister stat;
	ArrayByteMemory   memory_3030;
	SizedWordRegister tag0;
	SizedWordRegister tag1;
	SizedWordRegister tag2;
	SizedWordRegister tag3;
	SizedWordRegister cnt;
	SizedWordRegister p3cnt;
	SizedWordRegister p3tag;
	ArrayByteMemory   memory_30b0;
};

