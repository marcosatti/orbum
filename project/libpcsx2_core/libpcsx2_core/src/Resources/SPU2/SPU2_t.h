#pragma once

#include <memory>

class HwordMemory_t;
class ByteMemory_t;
class SPU2Core_C0_t;
class SPU2Core_C1_t;
class SPU2Core_t;
class Register16_t;
class SPU2Register_SPDIF_IRQINFO_t;

/*
Describes the SPU2 (sound) resources that is attached through the IOP.
No official documentation, except for the SPU2 Overview manual which does help.
Most of the implementation comes from PCSX2. Thanks to everyone involved!

The registers are assigned to the 0x1F900000 -> 0x1F900800 space in the IOP.
*/
class SPU2_t
{
public:
	SPU2_t();

	/*
	SPU2 Cores.
	*/
	std::shared_ptr<SPU2Core_C0_t> CORE_0;
	std::shared_ptr<SPU2Core_C1_t> CORE_1;
	std::shared_ptr<SPU2Core_t>    CORES[Constants::SPU2::NUMBER_CORES];

	/*
	SPDIF Registers.
	*/
	std::shared_ptr<Register16_t>                 SPDIF_OUT;
	std::shared_ptr<SPU2Register_SPDIF_IRQINFO_t> SPDIF_IRQINFO;
	std::shared_ptr<Register16_t>                 SPDIF_07C4;
	std::shared_ptr<Register16_t>                 SPDIF_MODE;
	std::shared_ptr<Register16_t>                 SPDIF_MEDIA;
	std::shared_ptr<Register16_t>                 SPDIF_07CA;
	std::shared_ptr<Register16_t>                 SPDIF_PROTECT;

	/*
	SPU2 Local Memory (2MB).
	Addressed within the SPU2 system logic as 16-bit units (half-words) (address range 0x00_0000 -> 0x0F_FFFF).
	The raw byte-addressed memory is still provided, with a wrapper applied for the half-word verison.
	*/
	std::shared_ptr<HwordMemory_t> MainMemory;

	/*
	Unknown memory / registers.
	There is a block of registers (with IOP MMU prefix address 0x1F900xxx) after both the core 0 and 1 known registers that are accessed.
	For core 0 this is in the range [0x346, 0x400).
	For core 1 this is in the range [0x746, 0x760), [0x7B0, 0x7C0) and [0x7CE, 0x800).
	*/
	std::shared_ptr<ByteMemory_t> MEMORY_0346;
	std::shared_ptr<ByteMemory_t> MEMORY_0746;
	std::shared_ptr<ByteMemory_t> MEMORY_07B0;
	std::shared_ptr<ByteMemory_t> MEMORY_07CE;
};