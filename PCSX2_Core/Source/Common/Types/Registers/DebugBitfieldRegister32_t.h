#pragma once

#include "Common/Types/Registers/DebugRegister32_t.h"
#include "Common/Types/BitfieldMap32/BitfieldMap32_t.h"

/*
Debug 32-bit bitfield register - see BitfieldRegister32_t for documentation.
Logs all reads and writes through read/write functions, except the get/setBitfieldValue() and any other BitfieldMap32_t functions.
*/
class DebugBitfieldRegister32_t : public DebugRegister32_t, public BitfieldMap32_t
{
public:
	explicit DebugBitfieldRegister32_t(const char * mnemonic);
	virtual ~DebugBitfieldRegister32_t();

	u32 getBitRange32(u8 startPosition, u8 bitLength) override;
	void setBitRange32(u8 startPosition, u8 bitLength, u32 value) override;

	void writeWordU(u32 value) override;
	void writeWordS(s32 value) override;
};

