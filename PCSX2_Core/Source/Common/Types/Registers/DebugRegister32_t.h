#pragma once

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/Register32_t.h"

/*
Debug Register32_t - logs all reads and writes.
*/

class DebugRegister32_t : public Register32_t
{
public:
	explicit DebugRegister32_t(const char * mnemonic);

	u8 readByte(u32 arrayIndex) override;
	void writeByte(u32 arrayIndex, u8 value) override;
	u16 readHword(u32 arrayIndex) override;
	void writeHword(u32 arrayIndex, u16 value) override;
	u32 readWord() override;
	void writeWord(u32 value) override;
};

