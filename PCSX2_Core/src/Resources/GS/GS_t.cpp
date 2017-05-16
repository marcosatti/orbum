#include "Common/Types/Register/Register64_t.h"
#include "Common/Types/Memory/ConstantByteMemory_t.h"

#include "Resources/GS/GS_t.h"
#include "Resources/GS/CRTC/CRTC_t.h"

GS_t::GS_t() :
	CRTC(std::make_shared<CRTC_t>()),
	// Registers.
	PMODE(std::make_shared<Register64_t>("GS PMODE", false, false)),
	SMODE1(std::make_shared<Register64_t>("GS SMODE1", false, false)),
	SMODE2(std::make_shared<Register64_t>("GS SMODE2", false, false)),
	SRFSH(std::make_shared<Register64_t>("GS SRFSH", false, false)),
	SYNCH1(std::make_shared<Register64_t>("GS SYNCH1", false, false)),
	SYNCH2(std::make_shared<Register64_t>("GS SYNCH2", false, false)),
	SYNCV(std::make_shared<Register64_t>("GS SYNCV", false, false)),
	DISPFB1(std::make_shared<Register64_t>("GS DISPFB1", false, false)),
	DISPLAY1(std::make_shared<Register64_t>("GS DISPLAY1", false, false)),
	DISPFB2(std::make_shared<Register64_t>("GS DISPFB2", false, false)),
	DISPLAY2(std::make_shared<Register64_t>("GS DISPLAY2", false, false)),
	EXTBUF(std::make_shared<Register64_t>("GS EXTBUF", false, false)),
	EXTDATA(std::make_shared<Register64_t>("GS EXTDATA", false, false)),
	EXTWRITE(std::make_shared<Register64_t>("GS EXTWRITE", false, false)),
	BGCOLOR(std::make_shared<Register64_t>("GS BGCOLOR", false, false)),
	MEMORY_00F0(std::make_shared<ConstantByteMemory_t>("GS 00F0", false, false, 0x310)),
	CSR(std::make_shared<Register64_t>("GS CSR", false, false)),
	IMR(std::make_shared<Register64_t>("GS IMR", false, false)),
	MEMORY_1020(std::make_shared<ConstantByteMemory_t>("GS 1020", false, false, 0x20)),
	BUSDIR(std::make_shared<Register64_t>("GS BUSDIR", false, false)),
	MEMORY_1050(std::make_shared<ConstantByteMemory_t>("GS 1050", false, false, 0x30)),
	SIGLBLID(std::make_shared<Register64_t>("GS SIGLBLID", false, false)),
	MEMORY_1090(std::make_shared<ConstantByteMemory_t>("GS 1090", false, false, 0x60)),
	MEMORY_1100(std::make_shared<ConstantByteMemory_t>("GS 1100", false, false, 0x300)),
	MEMORY_2000(std::make_shared<ConstantByteMemory_t>("GS 2000", false, false, 0xE000))
{
}
