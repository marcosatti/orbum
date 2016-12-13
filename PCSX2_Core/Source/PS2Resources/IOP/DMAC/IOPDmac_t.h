#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "PS2Constants/PS2Constants.h"

class Register32_t;

/*
IOP DMAC resources.
*/
class IOPDmac_t : public PS2ResourcesSubobject
{
public:
	explicit IOPDmac_t(const PS2Resources_t *const PS2Resources);

	// DMAC Registers.
	std::shared_ptr<Register32_t> REGISTER_PCR;  // Register "PCR (Primary Control Register)"    @ 0x1F8010F0 -> 0x1F8010F3.
	std::shared_ptr<Register32_t> REGISTER_ICR;  // Register "ICR (Interrupt Control Register)"  @ 0x1F8010F4 -> 0x1F8010F7.
	std::shared_ptr<Register32_t> REGISTER_PCR2; // Register "PCR2 (Primary Control Register)"   @ 0x1F801570 -> 0x1F801573.
	std::shared_ptr<Register32_t> REGISTER_ICR2; // Register "ICR  (Interrupt Control Register)" @ 0x1F801574 -> 0x1F801577.
};

