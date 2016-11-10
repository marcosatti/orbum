#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"

class DeadMemory_t;
class EEIntcRegister_STAT_t;
class EEIntcRegister_MASK_t;

class INTC_t : public PS2ResourcesSubobject
{
public:
	explicit INTC_t(const PS2Resources_t *const PS2Resources);

	/*
	INTC memory mapped registers. See page 24 of EE Users Manual.
	*/
	// 0x1000F000
	std::shared_ptr<EEIntcRegister_STAT_t> INTC_REGISTER_I_STAT;
	std::shared_ptr<EEIntcRegister_MASK_t> INTC_REGISTER_I_MASK;
	std::shared_ptr<DeadMemory_t>      INTC_MEMORY_f020;
};

