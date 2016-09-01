#pragma once

#include <memory>

#include "Common/PS2 Resources/EE/EECore/EECore_t.h"
#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "Common/PS2 Resources/Types/PS2DeadStorageObject/PS2DeadStorageObject_t.h"
#include "Types/EERegisters_t.h"

/*
TODO: finish writing documentation.
EE_t delares the EE structure of the PS2.
It encompasses everything seen on the diagram on page 22 of the EE Overview Manual, and the items within the EE Users Manual.
*/
class EE_t : public PS2ResourcesSubobject
{
public:
	explicit EE_t(const PS2Resources_t *const PS2Resources) :
		PS2ResourcesSubobject(PS2Resources)
	{
	}

	// The EE Core structure.
	std::shared_ptr<EECore_t> EECore = std::make_shared<EECore_t>(getRootResources());

	// EE registers, defined on page 21 onwards of the EE Users Manual. All are prefixed with EE_REGISTER.
	/*
	The SIO (serial I/O), which is largely undocumented. Some information can be found in the Toshiba Tx79 architecture manual (similar to the EE), but even then information is lacking.
	Some useful information can be found in the old PCSX2 under Hw.h (register names). In a real PS2, you can communicate with the EE over this serial port.
	*/
	std::shared_ptr<EERegisterSIO_t> EE_REGISTER_SIO = std::make_shared<EERegisterSIO_t>();

	/*
	The MCH register. No documentation! From old PCSX2, as well as needed by the BIOS.
	*/
	std::shared_ptr<EERegisterMCH_t> EE_REGISTER_MCH = std::make_shared<EERegisterMCH_t>();

	/*
	The DMAC extended registers. See EE Users Manual page 24.
	*/
	std::shared_ptr<PS2StorageObject_t> EE_REGISTER_DMAC_EXT = std::make_shared<PS2StorageObject_t>(PS2Constants::EE::EE_REGISTER_DMAC_EXT::SIZE_EE_REGISTER_DMAC_EXT, "DMAC EXT (F500)", PS2Constants::EE::EE_REGISTER_DMAC_EXT::PADDRESS_EE_REGISTER_DMAC_EXT);

	/*
	Absolutely unknown registers - really. No one knows what they do, except that the PS2 needs them. Usually these are dead storage objects - read 0 and discard writes.
	*/
	std::shared_ptr<PS2DeadStorageObject_t> EE_REGISTER_F410 = std::make_shared<PS2DeadStorageObject_t>(0x10, "F410", 0x1000F410); // Unknown register named "F410". Used by the BIOS.
};