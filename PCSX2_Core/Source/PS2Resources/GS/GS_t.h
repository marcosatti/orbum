#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"

class Register64_t;
class ConstantMemory_t;

/*
GS_t defines the structure needed for the GS (graphics synthesiser unit).
*/
class GS_t : public PS2ResourcesSubobject
{
public:
	explicit GS_t(const PS2Resources_t *const PS2Resources);

	/*
	The H-BLNK and V-BLNK signals. These are needed by the EE Timers as gate conditions.
	Zero = low signal.
	Non-zero (1) = high signal.

	Use the set functions which will set the last state automatically (again needed by the EE Timers).
	*/
	u8 SIGNAL_HBLNK;
	u8 SIGNAL_HBLNK_LAST;
	u8 SIGNAL_VBLNK;
	u8 SIGNAL_VBLNK_LAST;
	void setSignalHBLNK(const u8 & hblnk);
	void setSignalVBLNK(const u8 & vblnk);

	/*
	GS privileged registers, defined on page 26 onwards of the EE Users Manual. All start from PS2 physical address 0x12000000 to 0x14000000.
	*/
	// 0x12000000.
	std::shared_ptr<Register64_t>     PMODE;
	std::shared_ptr<Register64_t>     SMODE1;
	std::shared_ptr<Register64_t>     SMODE2;
	std::shared_ptr<Register64_t>     SRFSH;
	std::shared_ptr<Register64_t>     SYNCH1;
	std::shared_ptr<Register64_t>     SYNCH2;
	std::shared_ptr<Register64_t>     SYNCV;
	std::shared_ptr<Register64_t>     DISPFB1;
	std::shared_ptr<Register64_t>     DISPLAY1;
	std::shared_ptr<Register64_t>     DISPFB2;
	std::shared_ptr<Register64_t>     DISPLAY2;
	std::shared_ptr<Register64_t>     EXTBUF;
	std::shared_ptr<Register64_t>     EXTDATA;
	std::shared_ptr<Register64_t>     EXTWRITE;
	std::shared_ptr<Register64_t>     BGCOLOR;
	std::shared_ptr<ConstantMemory_t> MEMORY_00F0;

	// 0x12001000.
	std::shared_ptr<Register64_t>     CSR;
	std::shared_ptr<Register64_t>     IMR;
	std::shared_ptr<ConstantMemory_t> MEMORY_1020;
	std::shared_ptr<Register64_t>     BUSDIR;
	std::shared_ptr<ConstantMemory_t> MEMORY_1050;
	std::shared_ptr<Register64_t>     SIGLBLID;
	std::shared_ptr<ConstantMemory_t> MEMORY_1090;
	std::shared_ptr<ConstantMemory_t> MEMORY_1100;

	// 0x12002000.
	std::shared_ptr<ConstantMemory_t> MEMORY_2000;

};

