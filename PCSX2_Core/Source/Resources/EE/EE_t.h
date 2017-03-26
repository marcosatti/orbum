#pragma once

#include <memory>

class EECore_t;
class EEDmac_t;
class EEIntc_t;
class EETimers_t;
class IPU_t;
class GIF_t;
class VPU_t;
class PhysicalMMU_t;
class ByteMemory_t;
class ROByteMemory_t;
class Register32_t;
class ConstantByteMemory_t;
class BusErrorMemory_t;
class EERegister_SIO_t;
class EERegister_MCH_t;

/*
TODO: finish writing documentation.
EE_t delares the EE structure of the PS2.
It encompasses everything seen on the diagram on page 22 of the EE Overview Manual, and the items within the EE Users Manual.
*/
class EE_t
{
public:
	explicit EE_t();

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
	std::shared_ptr<ByteMemory_t> MainMemory;

	/* 
	Various ROM banks. See PCSX2's source code ("MemoryTypes.h", "Memory.cpp", "IopMem.cpp") and the EE Users Manual page 20. 
	BootROM (BIOS, 4MB). Allocated in EE & IOP physical memory space @ 0x1FC00000.
	ROM1 (DVD Player, 256kB). Allocaled in EE & IOP physical memory space @ 0x1E000000.
	EROM (DVD Player extensions, 1,792kB). Allocated in EE physical memory space @ 0x1E040000.
	ROM2 (Chinese ROM extensions, 512kB). Allocated in EE physical memory space @ 0x1E400000.
	*/
	std::shared_ptr<ROByteMemory_t> BootROM;
	std::shared_ptr<ROByteMemory_t> ROM1;
	std::shared_ptr<ROByteMemory_t> EROM;
	std::shared_ptr<ROByteMemory_t> ROM2;

	/*
	Other memory.
	*/
	std::shared_ptr<ConstantByteMemory_t>     UNKNOWN_1A000000;	// Undocumented memory/register @ 0x1A000000 -> 0x1A00FFFF. 

	/*
	EE memory/registers, defined on page 21 onwards of the EE Users Manual. 
	The registers listed here are for any miscellaneous systems that are too small to have its own category.
	Any unknown or undocumented memory/registers have comments listed next to them.
	*/
	std::shared_ptr<EERegister_SIO_t> MEMORY_SIO;         // Register "SIO"                @ 0x1000F100 -> 0x1000F1FF. Some information can be found in the Toshiba Tx79 architecture manual (similar to the EE).
	std::shared_ptr<Register32_t>     REGISTER_F400;      // Register "Undocumented: F400" @ 0x1000F400 -> 0x1000F403.
	std::shared_ptr<ConstantByteMemory_t> MEMORY_F410;        // Register "Undocumented: F410" @ 0x1000F410 -> 0x1000F41F. Needs to be a dead storage (by BIOS).
	std::shared_ptr<Register32_t>     REGISTER_F420;      // Register "Undocumented: F420" @ 0x1000F420 -> 0x1000F423.
	std::shared_ptr<EERegister_MCH_t> MEMORY_MCH;		  // Register "MCH"                @ 0x1000F430 -> 0x1000F44F. No documentation (except for name)! From old PCSX2. Needed by the BIOS for RDRAM initalisation?
	std::shared_ptr<ByteMemory_t>         MEMORY_F450;        // Register "Undocumented: F450" @ 0x1000F450 -> 0x1000F4FF.  
};