#pragma once

#include <memory>

class ByteMemory_t;
class HwordMemory_t;

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
	std::shared_ptr<ByteMemory_t> SPU2_REGISTERS; // Register "" @ 0x1F900000. Mirrored at 0x1F900800.

	/*
	SPU2 Local Memory (2MB).
	Addressed within the SPU2 system logic as 16-bit units (half-words) (address range 0x00_0000 -> 0x0F_FFFF).
	The raw byte-addressed memory is still provided, with a wrapper applied for the half-word verison.
	*/
	std::shared_ptr<HwordMemory_t> MainMemory;
};