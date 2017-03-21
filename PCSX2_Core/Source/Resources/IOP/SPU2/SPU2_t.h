#pragma once

#include <memory>

class Memory_t;

/*
Describes the SPU2 (sound) resources that is attached through the IOP.
No official documentation - everything comes from PCSX2. Thanks to everyone involved!

The registers are assigned to the 0x1F900000 -> 0x1F900800 space.
*/
class SPU2_t
{
public:
	explicit SPU2_t();

	/*
	SPU2 Registers.
	DEBUG.
	*/
	std::shared_ptr<Memory_t> SPU2_REGISTERS; // Register "" @ 0x1F900000. Mirrored at 0x1F900800.
};