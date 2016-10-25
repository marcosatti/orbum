#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"

/*
TODO: finish writing documentation.
EE_t delares the EE structure of the PS2.
It encompasses everything seen on the diagram on page 22 of the EE Overview Manual, and the items within the EE Users Manual.
*/

class EECore_t;
class DMAC_t;
class INTC_t;
class Timers_t;
class IPU_t;
class GIF_t;
class VPU_t;
class BootROM_t;
class PhysicalMMU_t;

class MappedMemory_t;
class MappedMemory32_t;
class DeadMMemory_t;
class BusErrorMMemory_t;
class EERegisterSIO_t;
class EERegisterMCH_t;

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
	std::shared_ptr<DMAC_t> DMAC;

	/*
	INTC resources.
	*/
	std::shared_ptr<INTC_t> INTC;

	/*
	Timers resources.
	*/
	std::shared_ptr<Timers_t> Timers;

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
	Main Memory (32MB). Allocated at 0x00000000.
	*/
	std::shared_ptr<MappedMemory_t> MainMemory;

	/* 
	Boot ROM (4MB). Allocated at 0x1FC00000.
	Also mapped in the IOP physical memory space at 0x1FC00000.
	*/
	std::shared_ptr<BootROM_t> BootROM;

	/*
	The EE physical memory space.
	*/
	std::shared_ptr<PhysicalMMU_t> PhysicalMMU;

	/*
	EE registers, defined on page 21 onwards of the EE Users Manual. 
	The registers listed here are for any miscellaneous systems that are too small to have its own category.
	*/
	// 0x10004000
	std::shared_ptr<MappedMemory_t>   EE_REGISTER_VIF0_FIFO;
	std::shared_ptr<MappedMemory_t>   EE_REGISTER_VIF1_FIFO;
	std::shared_ptr<MappedMemory_t>   EE_REGISTER_GIF_FIFO;
	std::shared_ptr<MappedMemory_t>   EE_REGISTER_IPU_out_FIFO;
	std::shared_ptr<MappedMemory_t>   EE_REGISTER_IPU_in_FIFO;

	// 0x1000F100
	std::shared_ptr<EERegisterSIO_t>  EE_REGISTER_SIO;          // Register "SIO"                @ 0x1000F100 -> 0x1000F200. Some information can be found in the Toshiba Tx79 architecture manual (similar to the EE).
	
	// 0x1000F200
	std::shared_ptr<MappedMemory32_t> EE_REGISTER_SB_SMFLG;

	// 0x1000F400
	std::shared_ptr<MappedMemory32_t> EE_REGISTER_F400;         // Register "Undocumented: F400" @ 0x1000F400 -> 0x1000F410.
	std::shared_ptr<DeadMMemory_t>    EE_REGISTER_F410;         // Register "Undocumented: F410" @ 0x1000F410 -> 0x1000F420. Needs to be a dead storage (by BIOS).
	std::shared_ptr<MappedMemory32_t> EE_REGISTER_F420;         // Register "Undocumented: F420" @ 0x1000F420 -> 0x1000F430.
	std::shared_ptr<EERegisterMCH_t>  EE_REGISTER_MCH;		    // Register "MCH"                @ 0x1000F430 -> 0x1000F450. No documentation (except for name)! From old PCSX2. Needed by the BIOS for RDRAM initalisation?
	std::shared_ptr<MappedMemory_t>   EE_REGISTER_F450;         // Register "Undocumented: F450" @ 0x1000F450 -> 0x1000F500.  
};