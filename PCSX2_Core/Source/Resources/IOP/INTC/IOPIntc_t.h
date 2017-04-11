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

	std::shared_ptr<IOPIntcRegister_CTRL_t> CTRL; 
	std::shared_ptr<IOPIntcRegister_MASK_t> MASK; 
	std::shared_ptr<IOPIntcRegister_STAT_t> STAT; 
};

