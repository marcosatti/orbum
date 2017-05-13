#pragma once

#include <memory>

class Register8_t;
class CDVDRegister_NS_COMMAND_t;
class CDVDRegister_NS_RDY_DIN_t;
class FIFOQueue_t;
class CDVDNvram_t;
class CDVDFIFOQueue_NS_DATA_OUT_t;

/*
Describes the CD-ROM / DVD resources that is attached through the IOP.
No official documentation - everything comes from PCSX2. Thanks to everyone involved!
The registers are assigned to the 0x1F402000 -> 0x1F402FFF space.

Notes:
- Follows the psx-style cd-rom setup, such as from the no$psx docs (command register, with parameter and response fifo's).
- 2 types of command and fifo sets - the S_ and N_ sets.
- N_ set controls the raw cd-rom data?
- S_ set controls the mechacon?
- STATUS controls what the emulator is currently doing: ie: nothing, seeking, reading, etc. 
  This is set upon writing to the N_COMMAND register, where it also resets the INTR_STAT.CmdComplete bit. Use this in order to step the state within the emulator.
  INTR_STAT.CmdComplete is set upon completion, and the IOP.INTC.CDROM bit is set.
- N_2005 needs to be set to 0x4E upon boot (ready), seems to use 0x40 after that, or 0x0 if not ready...
*/
class CDVD_t
{
public:
	CDVD_t();

	/*
	CDVD Registers.
	*/
	std::shared_ptr<CDVDRegister_NS_COMMAND_t> N_COMMAND;
	std::shared_ptr<CDVDRegister_NS_RDY_DIN_t> N_RDY_DIN;
	std::shared_ptr<CDVDFIFOQueue_NS_DATA_OUT_t> N_DATA_OUT;
	std::shared_ptr<Register8_t>               BREAK;  
	std::shared_ptr<Register8_t>               INTR_STAT;
	std::shared_ptr<Register8_t>               STATUS;
	std::shared_ptr<Register8_t>               TRAY_STATE;
	std::shared_ptr<Register8_t>               CRT_MINUTE;    
	std::shared_ptr<Register8_t>               CRT_SECOND;    
	std::shared_ptr<Register8_t>               CRT_FRAME;     
	std::shared_ptr<Register8_t>               TYPE;   
	std::shared_ptr<Register8_t>               REGISTER_2013; 
	std::shared_ptr<Register8_t>               RSV;
	std::shared_ptr<CDVDRegister_NS_COMMAND_t> S_COMMAND;
	std::shared_ptr<CDVDRegister_NS_RDY_DIN_t> S_RDY_DIN;
	std::shared_ptr<CDVDFIFOQueue_NS_DATA_OUT_t> S_DATA_OUT; 
	std::shared_ptr<Register8_t>               KEY_20; 
	std::shared_ptr<Register8_t>               KEY_21; 
	std::shared_ptr<Register8_t>               KEY_22; 
	std::shared_ptr<Register8_t>               KEY_23; 
	std::shared_ptr<Register8_t>               KEY_24; 
	std::shared_ptr<Register8_t>               KEY_28; 
	std::shared_ptr<Register8_t>               KEY_29; 
	std::shared_ptr<Register8_t>               KEY_2A; 
	std::shared_ptr<Register8_t>               KEY_2B; 
	std::shared_ptr<Register8_t>               KEY_2C; 
	std::shared_ptr<Register8_t>               KEY_30; 
	std::shared_ptr<Register8_t>               KEY_31; 
	std::shared_ptr<Register8_t>               KEY_32; 
	std::shared_ptr<Register8_t>               KEY_33; 
	std::shared_ptr<Register8_t>               KEY_34; 
	std::shared_ptr<Register8_t>               KEY_38; 
	std::shared_ptr<Register8_t>               KEY_XOR;
	std::shared_ptr<Register8_t>               DEC_SET;      

	/*
	CDVD NVRAM state.
	*/
	std::shared_ptr<CDVDNvram_t> NVRAM;
};