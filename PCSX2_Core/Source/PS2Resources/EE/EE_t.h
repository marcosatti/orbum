#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"

/*
TODO: finish writing documentation.
EE_t delares the EE structure of the PS2.
It encompasses everything seen on the diagram on page 22 of the EE Overview Manual, and the items within the EE Users Manual.
*/

class EECore_t;
class EEDmac_t;
class EEIntc_t;
class EETimers_t;
class IPU_t;
class GIF_t;
class VPU_t;
class BootROM_t;
class PhysicalMMU_t;

class Memory_t;
class Register32_t;
class DeadMemory_t;
class BusErrorMemory_t;
class EERegister_SIO_t;
class EERegister_MCH_t;

class EE_t : public PS2ResourcesSubobject
{
public:
	explicit EE_t(const PS2Resources_t *const PS2Resources);

	/*
	EE Core resources.
	*/
	std::shared_ptr<EECore_t> EECore;

	/*
	DMAC resources.
	*/
	std::shared_ptr<EEDmac_t> DMAC;

	/*
	INTC resources.
	*/
	std::shared_ptr<EEIntc_t> INTC;

	/*
	Timers resources.
	*/
	std::shared_ptr<EETimers_t> Timers;

	/*
	IPU resources.
	*/
	std::shared_ptr<IPU_t> IPU;

	/*
	GIF resources.
	*/
	std::shared_ptr<GIF_t> GIF;

	/*
	VPU 0/1 resources.
	*/
	std::shared_ptr<VPU_t> VPU;

	/*
	The EE physical memory space.
	*/
	std::shared_ptr<PhysicalMMU_t> PhysicalMMU;

	/*
	Main Memory (32MB). Allocated at 0x00000000.
	*/
	std::shared_ptr<Memory_t> MainMemory;

	/* 
	Boot ROM (4MB). Allocated at 0x1FC00000.
	Also mapped in the IOP physical memory space at 0x1FC00000.
	*/
	std::shared_ptr<BootROM_t> BootROM;

	/*
	Other memory.
	*/
	std::shared_ptr<DeadMemory_t>     UNKNOWN_1A000000;	// Undocumented memory/register @ 0x1A000000 -> 0x1A00FFFF. 

	/*
	EE registers, defined on page 21 onwards of the EE Users Manual. 
	The registers listed here are for any miscellaneous systems that are too small to have its own category.
	*/
	std::shared_ptr<Memory_t>         FIFO_VIF0;
	std::shared_ptr<Memory_t>         FIFO_VIF1;
	std::shared_ptr<Memory_t>         FIFO_GIF;
	std::shared_ptr<Memory_t>         FIFO_IPU_out;
	std::shared_ptr<Memory_t>         FIFO_IPU_in;
	std::shared_ptr<EERegister_SIO_t> MEMORY_SIO;         // Register "SIO"                @ 0x1000F100 -> 0x1000F200. Some information can be found in the Toshiba Tx79 architecture manual (similar to the EE).
	std::shared_ptr<Register32_t>     REGISTER_SB_SMFLG;
	std::shared_ptr<Register32_t>     REGISTER_F400;      // Register "Undocumented: F400" @ 0x1000F400 -> 0x1000F410.
	std::shared_ptr<DeadMemory_t>     MEMORY_F410;        // Register "Undocumented: F410" @ 0x1000F410 -> 0x1000F420. Needs to be a dead storage (by BIOS).
	std::shared_ptr<Register32_t>     REGISTER_F420;      // Register "Undocumented: F420" @ 0x1000F420 -> 0x1000F430.
	std::shared_ptr<EERegister_MCH_t> MEMORY_MCH;		  // Register "MCH"                @ 0x1000F430 -> 0x1000F450. No documentation (except for name)! From old PCSX2. Needed by the BIOS for RDRAM initalisation?
	std::shared_ptr<Memory_t>         MEMORY_F450;        // Register "Undocumented: F450" @ 0x1000F450 -> 0x1000F500.  
};