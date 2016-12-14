#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"

class Register8_t;
class ConstantRegister8_t;

/*
Describes the CD-ROM / DVD resources that is attached through the IOP.
No official documentation - everything comes from PCSX2. Thanks to everyone involved!

The registers are assigned to the 0x1F402000 -> 0x1F402FFF space, mirrored across the region.
*/
class CDVD_t : public PS2ResourcesSubobject
{
public:
	explicit CDVD_t(const PS2Resources_t *const PS2Resources);

	/*
	CDVD Registers.
	DEBUG.
	*/
	std::shared_ptr<Register8_t>         N_COMMAND;     // Register "N_COMMAND"          @ 0x1F402004.
	std::shared_ptr<Register8_t>         N_READY;       // Register "N_READY"            @ 0x1F402005.
	std::shared_ptr<Register8_t>         ERROR;         // Register "ERROR"              @ 0x1F402006.
	std::shared_ptr<ConstantRegister8_t> BREAK;         // Register "BREAK"              @ 0x1F402007.
	std::shared_ptr<Register8_t>         STATUS;        // Register "STATUS"             @ 0x1F402008 and 0x1F40200A (mirror).
	std::shared_ptr<Register8_t>         TRAY_STATE;    // Register "TRAY_STATE"         @ 0x1F40200B.
	std::shared_ptr<Register8_t>         CRT_MINUTE;    // Register "CRT_MINUTE"         @ 0x1F40200C.
	std::shared_ptr<Register8_t>         CRT_SECOND;    // Register "CRT_SECOND"         @ 0x1F40200D.
	std::shared_ptr<Register8_t>         CRT_FRAME;     // Register "CRT_FRAME"          @ 0x1F40200E.
	std::shared_ptr<Register8_t>         TYPE;          // Register "TYPE"               @ 0x1F40200F.
	std::shared_ptr<Register8_t>         REGISTER_2013; // Register "Undocumented: 2013" @ 0x1F402013.
	std::shared_ptr<Register8_t>         RSV;           // Register "RSV"                @ 0x1F402015.
	std::shared_ptr<Register8_t>         S_COMMAND;     // Register "S_COMMAND"          @ 0x1F402016.
	std::shared_ptr<Register8_t>         S_READY;       // Register "S_READY"            @ 0x1F402017.
	std::shared_ptr<Register8_t>         S_DATA_OUT;    // Register "S_DATA_OUT"         @ 0x1F402018.
	std::shared_ptr<Register8_t>         KEY_20;        // Register "KEY_20"             @ 0x1F402020.
	std::shared_ptr<Register8_t>         KEY_21;        // Register "KEY_21"             @ 0x1F402021.
	std::shared_ptr<Register8_t>         KEY_22;        // Register "KEY_22"             @ 0x1F402022.
	std::shared_ptr<Register8_t>         KEY_23;        // Register "KEY_23"             @ 0x1F402023.
	std::shared_ptr<Register8_t>         KEY_24;        // Register "KEY_24"             @ 0x1F402024.
	std::shared_ptr<Register8_t>         KEY_28;        // Register "KEY_28"             @ 0x1F402028.
	std::shared_ptr<Register8_t>         KEY_29;        // Register "KEY_29"             @ 0x1F402029.
	std::shared_ptr<Register8_t>         KEY_2A;        // Register "KEY_2A"             @ 0x1F40202A.
	std::shared_ptr<Register8_t>         KEY_2B;        // Register "KEY_2B"             @ 0x1F40202B.
	std::shared_ptr<Register8_t>         KEY_2C;        // Register "KEY_2C"             @ 0x1F40202C.
	std::shared_ptr<Register8_t>         KEY_30;        // Register "KEY_30"             @ 0x1F402030.
	std::shared_ptr<Register8_t>         KEY_31;        // Register "KEY_31"             @ 0x1F402031.
	std::shared_ptr<Register8_t>         KEY_32;        // Register "KEY_32"             @ 0x1F402032.
	std::shared_ptr<Register8_t>         KEY_33;        // Register "KEY_33"             @ 0x1F402033.
	std::shared_ptr<Register8_t>         KEY_34;        // Register "KEY_34"             @ 0x1F402034.
	std::shared_ptr<Register8_t>         KEY_38;        // Register "KEY_38"             @ 0x1F402038.
	std::shared_ptr<Register8_t>         KEY_XOR;       // Register "KEY_XOR"            @ 0x1F402039.
	std::shared_ptr<Register8_t>         DEC_SET;       // Register "DEC_SET"            @ 0x1F40203A.
};