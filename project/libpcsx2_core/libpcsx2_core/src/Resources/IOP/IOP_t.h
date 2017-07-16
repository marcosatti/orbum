#pragma once

#include <memory>

class IOPCore_t;
class IOPDmac_t;
class IOPIntc_t;
class IOPTimers_t;
class SIO0_t;
class SIO2_t;
class ByteMemory_t;
class DebugMemory_t;
class ByteMMU_t;
class Register32_t;

/*
Describes the IOP, also known as the subsystem (interfaced through the SIF). Used for I/O operations as well as the PS1 mode.
There is no official documentation - some online resources exist for the PS1 which can help with certain parts, but otherwise
 it has been reversed engineered.
Big props to the PCSX2 team here - most of the implementation is based off their work.
*/
class IOP_t
{
public:
	IOP_t();

	/*
	The IOP core.
	*/
	std::shared_ptr<IOPCore_t> IOPCore;

	/*
	The IOP DMAC resources.
	*/
	std::shared_ptr<IOPDmac_t> DMAC;

	/*
	The IOP INTC resources.
	*/
	std::shared_ptr<IOPIntc_t> INTC;

	/*
	Timers resources.
	*/
	std::shared_ptr<IOPTimers_t> Timers;

	/*
	SIO2 Resources.
	*/
	std::shared_ptr<SIO0_t> SIO0;

	/*
	SIO2 Resources.
	*/
	std::shared_ptr<SIO2_t> SIO2;

	/*
	The IOP physical memory space.
	*/
	std::shared_ptr<ByteMMU_t> MMU;

	/*
	IOP Main Memory (2MB).
	*/
	std::shared_ptr<ByteMemory_t> MainMemory;

	/*
	IOP Parallel Port IO (64KB).
	*/
	std::shared_ptr<ByteMemory_t> ParallelPort;

	/*
	IOP memory/registers.
	The registers listed here are for any miscellaneous systems that are too small to have its own category.
	Any unknown or undocumented memory/registers have comments listed next to them.
	*/
	std::shared_ptr<Register32_t>  HW_SSBUS_SPD_ADDR;    
	std::shared_ptr<Register32_t>  HW_SSBUS_PIO_ADDR;    
	std::shared_ptr<Register32_t>  HW_SSBUS_SPD_DELAY;   
	std::shared_ptr<Register32_t>  HW_SSBUS_DEV1_DELAY;  
	std::shared_ptr<Register32_t>  HW_SSBUS_ROM_DELAY;   
	std::shared_ptr<Register32_t>  HW_SSBUS_SPU_DELAY;   
	std::shared_ptr<Register32_t>  HW_SSBUS_DEV5_DELAY;  
	std::shared_ptr<Register32_t>  HW_SSBUS_PIO_DELAY;   
	std::shared_ptr<Register32_t>  HW_SSBUS_COM_DELAY;   
	std::shared_ptr<Register32_t>  HW_RAM_SIZE;          
	std::shared_ptr<Register32_t>  HW_SSBUS_DEV1_ADDR;   
	std::shared_ptr<Register32_t>  HW_SSBUS_SPU_ADDR;    
	std::shared_ptr<Register32_t>  HW_SSBUS_DEV5_ADDR;   
	std::shared_ptr<Register32_t>  HW_SSBUS_SPU1_ADDR;   
	std::shared_ptr<Register32_t>  HW_SSBUS_DEV9_ADDR3;  
	std::shared_ptr<Register32_t>  HW_SSBUS_SPU1_DELAY;  
	std::shared_ptr<Register32_t>  HW_SSBUS_DEV9_DELAY2; 
	std::shared_ptr<Register32_t>  HW_SSBUS_DEV9_DELAY3; 
	std::shared_ptr<Register32_t>  HW_SSBUS_DEV9_DELAY1; 
	std::shared_ptr<Register32_t>  HW_ICFG;              
	std::shared_ptr<Register32_t>  REGISTER_1470;        
	std::shared_ptr<Register32_t>  REGISTER_1560;        
	std::shared_ptr<Register32_t>  REGISTER_1564;        
	std::shared_ptr<Register32_t>  REGISTER_1568;        
	std::shared_ptr<Register32_t>  REGISTER_15F0;        
	std::shared_ptr<Register32_t>  REGISTER_2070;        
	std::shared_ptr<Register32_t>  REGISTER_3800;        
};
