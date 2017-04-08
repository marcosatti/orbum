#pragma once

#include <memory>

class IOPIntcRegister_STAT_t;
class IOPIntcRegister_MASK_t;
class IOPIntcRegister_CTRL_t;

/*
IOP INTC resources.
*/
class IOPIntc_t
{
public:
	IOPIntc_t();

	std::shared_ptr<IOPIntcRegister_CTRL_t> CTRL; // Register "CTRL" @ 0x1F801078 -> 0x1F80107B.
	std::shared_ptr<IOPIntcRegister_MASK_t> MASK; // Register "MASK" @ 0x1F801074 -> 0x1F801077.
	std::shared_ptr<IOPIntcRegister_STAT_t> STAT; // Register "STAT" @ 0x1F801070 -> 0x1F801073. 
};

