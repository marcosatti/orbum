#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"

class IOPCore_t;
class IOPDmac_t;
class CDVD_t;
class IOPTimers_t;
class Memory_t;
class DebugMemory_t;
class PhysicalMMU_t;
class Register32_t;

/*
Describes the IOP, also known as the subsystem (interfaced through the SIF). Used for I/O operations as well as the PS1 mode.
There is no official documentation - some online resources exist for the PS1 which can help with certain parts, but otherwise
 it has been reversed engineered.
Big props to the PCSX2 team here - most of the implementation is based off their work.
*/
class IOP_t : public PS2ResourcesSubobject
{
public:
	explicit IOP_t(const PS2Resources_t *const PS2Resources);

	/*
	The IOP core.
	*/
	std::shared_ptr<IOPCore_t> IOPCore;

	/*
	The IOP DMAC resources.
	*/
	std::shared_ptr<IOPDmac_t> DMAC;

	/*
	CD-ROM / DVD Drive resources (CDVD).
	*/
	std::shared_ptr<CDVD_t> CDVD;

	/*
	Timers resources.
	*/
	std::shared_ptr<IOPTimers_t> Timers;

	/*
	The IOP physical memory space.
	*/
	std::shared_ptr<PhysicalMMU_t> PhysicalMMU;

	/*
	IOP Main Memory (2MB). Allocated at 0x00000000.
	*/
	std::shared_ptr<Memory_t> MainMemory;

	/*
	IOP Parallel Port IO (64KB). Allocated at 0x1F000000.
	*/
	std::shared_ptr<Memory_t> ParallelPort;

	/*
	IOP memory/registers.
	The registers listed here are for any miscellaneous systems that are too small to have its own category.
	Any unknown or undocumented memory/registers have comments listed next to them.
	*/
	std::shared_ptr<Register32_t>  REGISTER_HW_SSBUS_SPD_ADDR;    // Register "HW_SSBUS_SPD_ADDR"    @ 0x1F801000 -> 0x1F801003.
	std::shared_ptr<Register32_t>  REGISTER_HW_SSBUS_PIO_ADDR;    // Register "HW_SSBUS_PIO_ADDR"    @ 0x1F801004 -> 0x1F801007.
	std::shared_ptr<Register32_t>  REGISTER_HW_SSBUS_SPD_DELAY;   // Register "HW_SSBUS_SPD_DELAY"   @ 0x1F801008 -> 0x1F80100B.
	std::shared_ptr<Register32_t>  REGISTER_HW_SSBUS_DEV1_DELAY;  // Register "HW_SSBUS_DEV1_DELAY"  @ 0x1F80100C -> 0x1F80100F.
	std::shared_ptr<Register32_t>  REGISTER_HW_SSBUS_ROM_DELAY;   // Register "HW_SSBUS_ROM_DELAY"   @ 0x1F801010 -> 0x1F801013.
	std::shared_ptr<Register32_t>  REGISTER_HW_SSBUS_SPU_DELAY;   // Register "HW_SSBUS_SPU_DELAY"   @ 0x1F801014 -> 0x1F801017.
	std::shared_ptr<Register32_t>  REGISTER_HW_SSBUS_DEV5_DELAY;  // Register "HW_SSBUS_DEV5_DELAY"  @ 0x1F801018 -> 0x1F80101B.
	std::shared_ptr<Register32_t>  REGISTER_HW_SSBUS_PIO_DELAY;   // Register "HW_SSBUS_PIO_DELAY"   @ 0x1F80101C -> 0x1F80101F.
	std::shared_ptr<Register32_t>  REGISTER_HW_SSBUS_COM_DELAY;   // Register "HW_SSBUS_COM_DELAY"   @ 0x1F801020 -> 0x1F801023.
	std::shared_ptr<Register32_t>  REGISTER_HW_SSBUS_DEV1_ADDR;   // Register "HW_SSBUS_DEV1_ADDR"   @ 0x1F801400 -> 0x1F801403.
	std::shared_ptr<Register32_t>  REGISTER_HW_SSBUS_SPU_ADDR;    // Register "HW_SSBUS_SPU_ADDR"    @ 0x1F801404 -> 0x1F801407.
	std::shared_ptr<Register32_t>  REGISTER_HW_SSBUS_DEV5_ADDR;   // Register "HW_SSBUS_DEV5_ADDR"   @ 0x1F801408 -> 0x1F80140B.
	std::shared_ptr<Register32_t>  REGISTER_HW_SSBUS_SPU1_ADDR;   // Register "HW_SSBUS_SPU1_ADDR"   @ 0x1F80140C -> 0x1F80140F.
	std::shared_ptr<Register32_t>  REGISTER_HW_SSBUS_DEV9_ADDR3;  // Register "HW_SSBUS_DEV9_ADDR3"  @ 0x1F801410 -> 0x1F801413.
	std::shared_ptr<Register32_t>  REGISTER_HW_SSBUS_SPU1_DELAY;  // Register "HW_SSBUS_SPU1_DELAY"  @ 0x1F801414 -> 0x1F801417.
	std::shared_ptr<Register32_t>  REGISTER_HW_SSBUS_DEV9_DELAY2; // Register "HW_SSBUS_DEV9_DELAY2" @ 0x1F801418 -> 0x1F80141B.
	std::shared_ptr<Register32_t>  REGISTER_HW_SSBUS_DEV9_DELAY3; // Register "HW_SSBUS_DEV9_DELAY3" @ 0x1F80141C -> 0x1F80141F.
	std::shared_ptr<Register32_t>  REGISTER_HW_SSBUS_DEV9_DELAY1; // Register "HW_SSBUS_DEV9_DELAY1" @ 0x1F801420 -> 0x1F801423.
	std::shared_ptr<Register32_t>  REGISTER_HW_ICFG;              // Register "HW_ICFG"              @ 0x1F801450 -> 0x1F801453.
	std::shared_ptr<Register32_t>  REGISTER_2070;                 // Register "Unknown: 1F802070"    @ 0x1F802070 -> 0x1F802073.
};
