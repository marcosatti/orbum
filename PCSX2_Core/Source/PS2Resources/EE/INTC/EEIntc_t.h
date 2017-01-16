#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubcategory.h"

class ConstantMemory_t;
class EEIntcRegister_STAT_t;
class EEIntcRegister_MASK_t;

class EEIntc_t : public PS2ResourcesSubcategory
{
public:
	explicit EEIntc_t(const PS2Resources_t * PS2Resources);

	/*
	EE INTC memory mapped registers. See page 24 of EE Users Manual.
	STAT is dependant on MASK.
	*/
	std::shared_ptr<EEIntcRegister_MASK_t> MASK;
	std::shared_ptr<EEIntcRegister_STAT_t> STAT;
	std::shared_ptr<ConstantMemory_t>      MEMORY_F020;
};

