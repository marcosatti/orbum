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

	u8 readByteU(u32 arrayIndex) override;
	void writeByteU(u32 arrayIndex, u8 value) override;
	s8 readByteS(u32 arrayIndex) override;
	void writeByteS(u32 arrayIndex, s8 value) override;
	u16 readHwordU(u32 arrayIndex) override;
	void writeHwordU(u32 arrayIndex, u16 value) override;
	s16 readHwordS(u32 arrayIndex) override;
	void writeHwordS(u32 arrayIndex, s16 value) override;
	u32 readWordU() override;
	void writeWordU(u32 value) override;
	s32 readWordS() override;
	void writeWordS(s32 value) override;
};

