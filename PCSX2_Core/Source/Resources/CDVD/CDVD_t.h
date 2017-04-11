#pragma once

#include <memory>

class Register8_t;
class ConstantRegister8_t;

/*
Describes the CD-ROM / DVD resources that is attached through the IOP.
No official documentation - everything comes from PCSX2. Thanks to everyone involved!

The registers are assigned to the 0x1F402000 -> 0x1F402FFF space, mirrored across the region.
*/
class CDVD_t
{
public:
	CDVD_t();

	/*
	CDVD Registers.
	*/
	std::shared_ptr<Register8_t>         N_COMMAND;     
	std::shared_ptr<Register8_t>         N_READY;       
	std::shared_ptr<Register8_t>         ERROR;         
	std::shared_ptr<ConstantRegister8_t> BREAK;         
	std::shared_ptr<Register8_t>         STATUS;        
	std::shared_ptr<Register8_t>         TRAY_STATE;    
	std::shared_ptr<Register8_t>         CRT_MINUTE;    
	std::shared_ptr<Register8_t>         CRT_SECOND;    
	std::shared_ptr<Register8_t>         CRT_FRAME;     
	std::shared_ptr<Register8_t>         TYPE;          
	std::shared_ptr<Register8_t>         REGISTER_2013; 
	std::shared_ptr<Register8_t>         RSV;           
	std::shared_ptr<Register8_t>         S_COMMAND;     
	std::shared_ptr<Register8_t>         S_READY;       
	std::shared_ptr<Register8_t>         S_DATA_OUT;    
	std::shared_ptr<Register8_t>         KEY_20;        
	std::shared_ptr<Register8_t>         KEY_21;        
	std::shared_ptr<Register8_t>         KEY_22;        
	std::shared_ptr<Register8_t>         KEY_23;        
	std::shared_ptr<Register8_t>         KEY_24;        
	std::shared_ptr<Register8_t>         KEY_28;        
	std::shared_ptr<Register8_t>         KEY_29;        
	std::shared_ptr<Register8_t>         KEY_2A;        
	std::shared_ptr<Register8_t>         KEY_2B;        
	std::shared_ptr<Register8_t>         KEY_2C;        
	std::shared_ptr<Register8_t>         KEY_30;        
	std::shared_ptr<Register8_t>         KEY_31;        
	std::shared_ptr<Register8_t>         KEY_32;        
	std::shared_ptr<Register8_t>         KEY_33;        
	std::shared_ptr<Register8_t>         KEY_34;        
	std::shared_ptr<Register8_t>         KEY_38;        
	std::shared_ptr<Register8_t>         KEY_XOR;       
	std::shared_ptr<Register8_t>         DEC_SET;       
};