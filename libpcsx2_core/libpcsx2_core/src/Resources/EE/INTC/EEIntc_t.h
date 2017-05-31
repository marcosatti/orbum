#pragma once

#include <memory>

class ConstantByteMemory_t;
class EEIntcRegister_STAT_t;
class EEIntcRegister_MASK_t;

class EEIntc_t
{
public:
	EEIntc_t();

	/*
	EE INTC memory mapped registers. See page 24 of EE Users Manual.
	*/
	std::shared_ptr<EEIntcRegister_MASK_t> MASK;
	std::shared_ptr<EEIntcRegister_STAT_t> STAT;
	std::shared_ptr<ConstantByteMemory_t>  MEMORY_F020;
};

