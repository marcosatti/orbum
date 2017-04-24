#pragma once

#include <memory>

class HwordMemory_t;
class SPU2Core_C0_t;
class SPU2Core_C1_t;
class SPU2Core_t;
class Register16_t;

/*
Describes the SPU2 (sound) resources that is attached through the IOP.
No official documentation - everything comes from PCSX2. Thanks to everyone involved!

The registers are assigned to the 0x1F900000 -> 0x1F900800 space.
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
	std::shared_ptr<Register16_t> SPDIF_OUT;
	std::shared_ptr<Register16_t> SPDIF_IRQINFO;
	std::shared_ptr<Register16_t> SPDIF_07C4;
	std::shared_ptr<Register16_t> SPDIF_MODE;
	std::shared_ptr<Register16_t> SPDIF_MEDIA;
	std::shared_ptr<Register16_t> SPDIF_07CA;
	std::shared_ptr<Register16_t> SPDIF_PROTECT;

	/*
	SPU2 Local Memory (2MB).
	Addressed within the SPU2 system logic as 16-bit units (half-words) (address range 0x00_0000 -> 0x0F_FFFF).
	The raw byte-addressed memory is still provided, with a wrapper applied for the half-word verison.
	*/
	std::shared_ptr<HwordMemory_t> MainMemory;
	std::shared_ptr<HwordMemory_t> DebugDummy; // Workaround to undo the optimisation of the hword memory dump function when using link time optimisation...
};