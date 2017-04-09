#pragma once

#include <memory>

class HwordMemory_t;
class SPU2Core_t;

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
	std::shared_ptr<SPU2Core_t> CORES[Constants::IOP::SPU2::NUMBER_CORES];

	/*
	SPU2 Local Memory (2MB).
	Addressed within the SPU2 system logic as 16-bit units (half-words) (address range 0x00_0000 -> 0x0F_FFFF).
	The raw byte-addressed memory is still provided, with a wrapper applied for the half-word verison.
	*/
	std::shared_ptr<HwordMemory_t> MainMemory;
	std::shared_ptr<HwordMemory_t> DebugDummy; // Workaround to undo the optimisation of the hword memory dump function when using link time optimisation...
};