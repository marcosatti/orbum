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

	// The EE Core structure.
	std::shared_ptr<EECore_t> EECore;

	// EE registers, defined on page 21 onwards of the EE Users Manual. All are prefixed with EE_REGISTER.
	/*
	The SIO (serial I/O), which is largely undocumented. Some information can be found in the Toshiba Tx79 architecture manual (similar to the EE), but even then information is lacking.
	Some useful information can be found in the old PCSX2 under Hw.h (register names). In a real PS2, you can communicate with the EE over this serial port.
	*/
	std::shared_ptr<EERegisterSIO_t> EE_REGISTER_SIO;

	/*
	The MCH register. No documentation! From old PCSX2. Needed by the BIOS.
	*/
	std::shared_ptr<EERegisterMCH_t> EE_REGISTER_MCH;

	/*
	The DMAC extended registers. See EE Users Manual page 24.
	*/
	std::shared_ptr<PS2StorageObject_t> EE_REGISTER_DMAC_EXT;

	/*
	Absolutely unknown registers - really. No one knows what they do, except that the PS2 needs them. Usually these are dead storage objects - read 0 and discard writes.
	*/
	std::shared_ptr<PS2DeadStorageObject_t> EE_REGISTER_F410;
};