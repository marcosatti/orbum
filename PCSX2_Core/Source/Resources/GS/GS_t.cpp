#include "stdafx.h"

#include "Common/Types/Registers/Register64_t.h"
#include "Common/Types/Memory/ConstantMemory_t.h"

#include "Resources/GS/GS_t.h"
#include "Resources/GS/CRTC/CRTC_t.h"

GS_t::GS_t() :
	CRTC(std::make_shared<CRTC_t>()),
	// Registers.
	PMODE(std::make_shared<Register64_t>("SPE: PMODE")),
	SMODE1(std::make_shared<Register64_t>("SPE: SMODE1")),
	SMODE2(std::make_shared<Register64_t>("SPE: SMODE2")),
	SRFSH(std::make_shared<Register64_t>("SPE: SRFSH")),
	SYNCH1(std::make_shared<Register64_t>("SPE: SYNCH1")),
	SYNCH2(std::make_shared<Register64_t>("SPE: SYNCH2")),
	SYNCV(std::make_shared<Register64_t>("SPE: SYNCV")),
	DISPFB1(std::make_shared<Register64_t>("SPE: DISPFB1")),
	DISPLAY1(std::make_shared<Register64_t>("SPE: DISPLAY1")),
	DISPFB2(std::make_shared<Register64_t>("SPE: DISPFB2")),
	DISPLAY2(std::make_shared<Register64_t>("SPE: DISPLAY2")),
	EXTBUF(std::make_shared<Register64_t>("SPE: EXTBUF")),
	EXTDATA(std::make_shared<Register64_t>("SPE: EXTDATA")),
	EXTWRITE(std::make_shared<Register64_t>("SPE: EXTWRITE")),
	BGCOLOR(std::make_shared<Register64_t>("SPE: BGCOLOR")),
	MEMORY_00F0(std::make_shared<ConstantMemory_t>(0x310, "SPE: SPE_00f0 (reserved)")),
	CSR(std::make_shared<Register64_t>("SPE: CSR")),
	IMR(std::make_shared<Register64_t>("SPE: IMR")),
	MEMORY_1020(std::make_shared<ConstantMemory_t>(0x20, "SPE: SPE_1020 (reserved)")),
	BUSDIR(std::make_shared<Register64_t>("SPE: BUSDIR")),
	MEMORY_1050(std::make_shared<ConstantMemory_t>(0x30, "SPE: SPE_1050 (reserved)")),
	SIGLBLID(std::make_shared<Register64_t>("SPE: SIGLBLID")),
	MEMORY_1090(std::make_shared<ConstantMemory_t>(0x60, "SPE: SPE_1090 (reserved)")),
	MEMORY_1100(std::make_shared<ConstantMemory_t>(0x300, "SPE: SPE_1100 (reserved)")),
	MEMORY_2000(std::make_shared<ConstantMemory_t>(0xE000, "SPE: SPE_2000 (reserved)"))
{
}
