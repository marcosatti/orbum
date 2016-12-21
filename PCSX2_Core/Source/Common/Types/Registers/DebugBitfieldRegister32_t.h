#pragma once

#include "Common/Global/Globals.h"

#if defined(BUILD_DEBUG)

#include "Common/Types/Registers/BitfieldRegister32_t.h"

/*
Debug 32-bit bitfield register - see BitfieldRegister32_t for documentation.
Logs all reads and writes through the raw 32-bit read/write functions.
*/
class DebugBitfieldRegister32_t : public BitfieldRegister32_t
{
public:
	explicit DebugBitfieldRegister32_t(const char * mnemonic);
	virtual ~DebugBitfieldRegister32_t();

	u32 readWordU() override;
	void writeWordU(u32 value) override;
	s32 readWordS() override;
	void writeWordS(s32 value) override;
};

#endif