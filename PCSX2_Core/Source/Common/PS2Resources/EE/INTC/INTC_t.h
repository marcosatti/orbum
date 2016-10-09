#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"

class DeadMMemory_t;
class IntcRegisterStat_t;
class IntcRegisterMask_t;

class INTC_t : public PS2ResourcesSubobject
{
public:
	explicit INTC_t(const PS2Resources_t *const PS2Resources);

	/*
	INTC memory mapped registers. See page 24 of EE Users Manual.
	*/
	// 0x1000F000
	std::shared_ptr<IntcRegisterStat_t> INTC_REGISTER_I_STAT;
	std::shared_ptr<IntcRegisterMask_t> INTC_REGISTER_I_MASK;
	std::shared_ptr<DeadMMemory_t>      INTC_REGISTER_f020;
};

