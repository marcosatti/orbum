#pragma once

#include <memory>

class IOPCore_t;
class IOPDmac_t;
class IOPIntc_t;
class CDVD_t;
class SPU2_t;
class IOPTimers_t;
class ByteMemory_t;
class DebugMemory_t;
class ByteMMU_t;
class Register32_t;

/*
Describes the IOP, also known as the subsystem (interfaced through the SIF). Used for I/O operations as well as the PS1 mode.
There is no official documentation - some online resources exist for the PS1 which can help with certain parts, but otherwise
 it has been reversed engineered.
Big props to the PCSX2 team here - most of the implementation is based off their work.
*/
class IOP_t
{
public:
	explicit IOP_t();

	/*
	The IOP core.
	*/
	std::shared_ptr<IOPCore_t> IOPCore;

	/*
	The IOP DMAC resources.
	*/
	std::shared_ptr<IOPDmac_t> DMAC;

	/*
	The IOP INTC resources.
	*/
	std::shared_ptr<IOPIntc_t> INTC;

	/*
	CD-ROM / DVD Drive resources (CDVD).
	*/
	std::shared_ptr<CDVD_t> CDVD;

	/*
	SPU2 Resources.
	*/
	std::shared_ptr<SPU2_t> SPU2;

	/*
	Timers resources.
	*/
	std::shared_ptr<IOPTimers_t> Timers;

	/*
	The IOP physical memory space.
	*/
	std::shared_ptr<ByteMMU_t> MMU;

	/*
	IOP Main Memory (2MB). Allocated at 0x00000000.
	*/
	std::shared_ptr<ByteMemory_t> MainMemory;

	/*
	IOP Parallel Port IO (64KB). Allocated at 0x1F000000.
	*/
	std::shared_ptr<ByteMemory_t> ParallelPort;

	/*
	IOP memory/registers.
	The registers listed here are for any miscellaneous systems that are too small to have its own category.
	Any unknown or undocumented memory/registers have comments listed next to them.
	*/
	std::shared_ptr<Register32_t>  HW_SSBUS_SPD_ADDR;    // Register "HW_SSBUS_SPD_ADDR"    @ 0x1F801000 -> 0x1F801003.
	std::shared_ptr<Register32_t>  HW_SSBUS_PIO_ADDR;    // Register "HW_SSBUS_PIO_ADDR"    @ 0x1F801004 -> 0x1F801007.
	std::shared_ptr<Register32_t>  HW_SSBUS_SPD_DELAY;   // Register "HW_SSBUS_SPD_DELAY"   @ 0x1F801008 -> 0x1F80100B.
	std::shared_ptr<Register32_t>  HW_SSBUS_DEV1_DELAY;  // Register "HW_SSBUS_DEV1_DELAY"  @ 0x1F80100C -> 0x1F80100F.
	std::shared_ptr<Register32_t>  HW_SSBUS_ROM_DELAY;   // Register "HW_SSBUS_ROM_DELAY"   @ 0x1F801010 -> 0x1F801013.
	std::shared_ptr<Register32_t>  HW_SSBUS_SPU_DELAY;   // Register "HW_SSBUS_SPU_DELAY"   @ 0x1F801014 -> 0x1F801017.
	std::shared_ptr<Register32_t>  HW_SSBUS_DEV5_DELAY;  // Register "HW_SSBUS_DEV5_DELAY"  @ 0x1F801018 -> 0x1F80101B.
	std::shared_ptr<Register32_t>  HW_SSBUS_PIO_DELAY;   // Register "HW_SSBUS_PIO_DELAY"   @ 0x1F80101C -> 0x1F80101F.
	std::shared_ptr<Register32_t>  HW_SSBUS_COM_DELAY;   // Register "HW_SSBUS_COM_DELAY"   @ 0x1F801020 -> 0x1F801023.
	std::shared_ptr<Register32_t>  HW_RAM_SIZE;          // Register "HW_RAM_SIZE"          @ 0x1F801060 -> 0x1F801063.   
	std::shared_ptr<Register32_t>  HW_SSBUS_DEV1_ADDR;   // Register "HW_SSBUS_DEV1_ADDR"   @ 0x1F801400 -> 0x1F801403.
	std::shared_ptr<Register32_t>  HW_SSBUS_SPU_ADDR;    // Register "HW_SSBUS_SPU_ADDR"    @ 0x1F801404 -> 0x1F801407.
	std::shared_ptr<Register32_t>  HW_SSBUS_DEV5_ADDR;   // Register "HW_SSBUS_DEV5_ADDR"   @ 0x1F801408 -> 0x1F80140B.
	std::shared_ptr<Register32_t>  HW_SSBUS_SPU1_ADDR;   // Register "HW_SSBUS_SPU1_ADDR"   @ 0x1F80140C -> 0x1F80140F.
	std::shared_ptr<Register32_t>  HW_SSBUS_DEV9_ADDR3;  // Register "HW_SSBUS_DEV9_ADDR3"  @ 0x1F801410 -> 0x1F801413.
	std::shared_ptr<Register32_t>  HW_SSBUS_SPU1_DELAY;  // Register "HW_SSBUS_SPU1_DELAY"  @ 0x1F801414 -> 0x1F801417.
	std::shared_ptr<Register32_t>  HW_SSBUS_DEV9_DELAY2; // Register "HW_SSBUS_DEV9_DELAY2" @ 0x1F801418 -> 0x1F80141B.
	std::shared_ptr<Register32_t>  HW_SSBUS_DEV9_DELAY3; // Register "HW_SSBUS_DEV9_DELAY3" @ 0x1F80141C -> 0x1F80141F (mirrored in EE space).
	std::shared_ptr<Register32_t>  HW_SSBUS_DEV9_DELAY1; // Register "HW_SSBUS_DEV9_DELAY1" @ 0x1F801420 -> 0x1F801423.
	std::shared_ptr<Register32_t>  HW_ICFG;              // Register "HW_ICFG"              @ 0x1F801450 -> 0x1F801453.
	std::shared_ptr<Register32_t>  REGISTER_1470;        // Register "Undocumented: 1470"   @ 0x1F801470 -> 0x1F801473 (in EE space only).
	std::shared_ptr<Register32_t>  REGISTER_1560;        // Register "Undocumented: 1560"   @ 0x1F801560 -> 0x1F801563.
	std::shared_ptr<Register32_t>  REGISTER_1564;        // Register "Undocumented: 1564"   @ 0x1F801564 -> 0x1F801567.
	std::shared_ptr<Register32_t>  REGISTER_1568;        // Register "Undocumented: 1568"   @ 0x1F801568 -> 0x1F80156B.
	std::shared_ptr<Register32_t>  REGISTER_15F0;        // Register "Undocumented: 15F0"   @ 0x1F8015F0 -> 0x1F8015F3.
	std::shared_ptr<Register32_t>  REGISTER_2070;        // Register "Undocumented: 2070"   @ 0x1F802070 -> 0x1F802073.
	std::shared_ptr<Register32_t>  REGISTER_3800;        // Register "Undocumented: 3800"   @ 0x1F803800 -> 0x1F803800.

private:
	/*
	Initalise the IOP physical memory space.
	*/
	void initIOPPhysicalMemoryMap() const;
};
