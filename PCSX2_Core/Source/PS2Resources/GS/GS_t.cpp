#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "PS2Resources/GS/GS_t.h"
#include "Common/Types/Memory/Memory_t.h"
#include "Common/Types/Memory/ConstantMemory_t.h"
#include "Common/Types/Memory/BusErrMemory_t.h"

GS_t::GS_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),

	// Registers.
	GS_P_REGISTER_PMODE(std::make_shared<Memory_t>(0x04, "SPE: PMODE")),
	GS_P_REGISTER_SMODE1(std::make_shared<Memory_t>(0x04, "SPE: SMODE1")),
	GS_P_REGISTER_SMODE2(std::make_shared<Memory_t>(0x04, "SPE: SMODE2")),
	GS_P_REGISTER_SRFSH(std::make_shared<Memory_t>(0x04, "SPE: SRFSH")),
	GS_P_REGISTER_SYNCH1(std::make_shared<Memory_t>(0x04, "SPE: SYNCH1")),
	GS_P_REGISTER_SYNCH2(std::make_shared<Memory_t>(0x04, "SPE: SYNCH2")),
	GS_P_REGISTER_SYNCV(std::make_shared<Memory_t>(0x04, "SPE: SYNCV")),
	GS_P_REGISTER_DISPFB1(std::make_shared<Memory_t>(0x04, "SPE: DISPFB1")),
	GS_P_REGISTER_DISPLAY1(std::make_shared<Memory_t>(0x04, "SPE: DISPLAY1")),
	GS_P_REGISTER_DISPFB2(std::make_shared<Memory_t>(0x04, "SPE: DISPFB2")),
	GS_P_REGISTER_DISPLAY2(std::make_shared<Memory_t>(0x04, "SPE: DISPLAY2")),
	GS_P_REGISTER_EXTBUF(std::make_shared<Memory_t>(0x04, "SPE: EXTBUF")),
	GS_P_REGISTER_EXTDATA(std::make_shared<Memory_t>(0x04, "SPE: EXTDATA")),
	GS_P_REGISTER_EXTWRITE(std::make_shared<Memory_t>(0x04, "SPE: EXTWRITE")),
	GS_P_REGISTER_BGCOLOR(std::make_shared<Memory_t>(0x04, "SPE: BGCOLOR")),
	GS_P_REGISTER_SPE_00f0(std::make_shared<ConstantMemory_t>(0x310, "SPE: SPE_00f0 (reserved)")),
	GS_P_REGISTER_CSR(std::make_shared<Memory_t>(0x04, "SPE: CSR")),
	GS_P_REGISTER_IMR(std::make_shared<Memory_t>(0x04, "SPE: IMR")),
	GS_P_REGISTER_SPE_1020(std::make_shared<ConstantMemory_t>(0x20, "SPE: SPE_1020 (reserved)")),
	GS_P_REGISTER_BUSDIR(std::make_shared<Memory_t>(0x04, "SPE: BUSDIR")),
	GS_P_REGISTER_SPE_1050(std::make_shared<ConstantMemory_t>(0x30, "SPE: SPE_1050 (reserved)")),
	GS_P_REGISTER_SIGLBLID(std::make_shared<Memory_t>(0x04, "SPE: SIGLBLID")),
	GS_P_REGISTER_SPE_1090(std::make_shared<ConstantMemory_t>(0x60, "SPE: SPE_1090 (reserved)")),
	GS_P_REGISTER_SPE_1100(std::make_shared<ConstantMemory_t>(0x300, "SPE: SPE_1100 (reserved)")),
	GS_P_REGISTER_SPE_2000(std::make_shared<ConstantMemory_t>(0xE000, "SPE: SPE_2000 (reserved)")),
	GS_P_REGISTER_SPEBusErr(std::make_shared<BusErrMemory_t>(0x1FF0000, "SPE: SPEBusErr"))
{
}

void GS_t::setSignalHBLNK(const u8& hblnk)
{
	SIGNAL_HBLNK_LAST = SIGNAL_HBLNK;
	SIGNAL_HBLNK = hblnk;
}

void GS_t::setSignalVBLNK(const u8& vblnk)
{
	SIGNAL_VBLNK_LAST = SIGNAL_VBLNK;
	SIGNAL_VBLNK = vblnk;
}
