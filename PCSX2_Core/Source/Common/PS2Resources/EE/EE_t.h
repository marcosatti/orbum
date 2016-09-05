#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"

/*
TODO: finish writing documentation.
EE_t delares the EE structure of the PS2.
It encompasses everything seen on the diagram on page 22 of the EE Overview Manual, and the items within the EE Users Manual.
*/

class EECore_t;
class PS2StorageObject_t;
class PS2DeadStorageObject_t;
class EERegisterSIO_t;
class EERegisterMCH_t;

class EE_t : public PS2ResourcesSubobject
{
public:
	explicit EE_t(const PS2Resources_t*const PS2Resources);

	/*
	The EE Core structure.
	*/
	std::shared_ptr<EECore_t> EECore;

	/*
	EE registers, defined on page 21 onwards of the EE Users Manual. All are prefixed with EE_REGISTER. 
	If special functionality is needed, they are subclassed off PS2[Dead]StorageObject_t and defined in Types/EERegisters_t.
	They are ordered by ascending, meaning the lowest physical address, to the highest.

	Also see the intitaliser list of EE_t(.cpp), where you can see the object parameter definitions.
	*/
	std::shared_ptr<EERegisterSIO_t>        EE_REGISTER_SIO;       // Register "SIO" @ 0x1000F100 -> 0x1000F200. Some information can be found in the Toshiba Tx79 architecture manual (similar to the EE).

	std::shared_ptr<PS2StorageObject_t>     EE_REGISTER_F400;      // Register "Undocumented: F400"    @ 0x1000F400 -> 0x1000F410.
	std::shared_ptr<PS2DeadStorageObject_t> EE_REGISTER_F410;      // Register "Undocumented: F410"    @ 0x1000F410 -> 0x1000F420. Needs to be a dead storage (by BIOS).
	std::shared_ptr<PS2StorageObject_t>     EE_REGISTER_F420;      // Register "Undocumented: F420"    @ 0x1000F420 -> 0x1000F430.
	std::shared_ptr<EERegisterMCH_t>        EE_REGISTER_MCH;       // Register "MCH"                   @ 0x1000F430 -> 0x1000F450. No documentation (except for name)! From old PCSX2. Needed by the BIOS for RDRAM initalisation?
	std::shared_ptr<PS2StorageObject_t>     EE_REGISTER_F450;      // Register "Undocumented: F450"    @ 0x1000F450 -> 0x1000F500.

	std::shared_ptr<PS2StorageObject_t>     EE_REGISTER_F500;      // Register "Undocumented: F500"    @ 0x1000F500 -> 0x1000F520.
	std::shared_ptr<PS2StorageObject_t>     EE_REGISTER_D_ENABLER; // Register "DMAC: D_ENABLER"       @ 0x1000F520 -> 0x1000F530. 
	std::shared_ptr<PS2DeadStorageObject_t> EE_REGISTER_F530;      // Register "DMAC: F530 (reserved)" @ 0x1000F530 -> 0x1000F580.
	std::shared_ptr<PS2StorageObject_t>     EE_REGISTER_D_ENABLEW; // Register "DMAC: D_ENABLER"       @ 0x1000F590 -> 0x1000F5A0.
	std::shared_ptr<PS2DeadStorageObject_t> EE_REGISTER_F5A0;      // Register "DMAC: F5A0 (reserved)" @ 0x1000F5A0 -> 0x1000F5F0.
};