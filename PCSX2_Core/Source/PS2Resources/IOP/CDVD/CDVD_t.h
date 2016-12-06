#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"

class Register8_t;
class ZeroRegister8_t;

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
	std::shared_ptr<Register8_t>     NCommand;  // Register "NCommand"  @ 0x1F402004.
	std::shared_ptr<Register8_t>     NReady;    // Register "NReady"    @ 0x1F402005.
	std::shared_ptr<Register8_t>     Error;     // Register "Error"     @ 0x1F402006.
	std::shared_ptr<ZeroRegister8_t> Break;     // Register "Break"     @ 0x1F402007.
	std::shared_ptr<Register8_t>     Status;    // Register "Status"    @ 0x1F402008 and 0x1F40200A (mirror).
	std::shared_ptr<Register8_t>     TrayState; // Register "TrayState" @ 0x1F40200B.
	std::shared_ptr<Register8_t>     CRTMinute; // Register "CRTMinute" @ 0x1F40200C.
	std::shared_ptr<Register8_t>     CRTSecond; // Register "CRTSecond" @ 0x1F40200D.
	std::shared_ptr<Register8_t>     CRTFrame;  // Register "CRTFrame"  @ 0x1F40200E.
	std::shared_ptr<Register8_t>     Type;      // Register "Type"      @ 0x1F40200F.
	std::shared_ptr<Register8_t>     Unknown13; // Register "Unknown13" @ 0x1F402013.
	std::shared_ptr<Register8_t>     RSV;       // Register "RSV"       @ 0x1F402015.
	std::shared_ptr<Register8_t>     SCommand;  // Register "SCommand"  @ 0x1F402016.
	std::shared_ptr<Register8_t>     SReady;    // Register "SReady"    @ 0x1F402017.
	std::shared_ptr<Register8_t>     SDataOut;  // Register "SDataOut"  @ 0x1F402018.
	std::shared_ptr<Register8_t>     Key20;     // Register "Key20"     @ 0x1F402020.
	std::shared_ptr<Register8_t>     Key21;     // Register "Key21"     @ 0x1F402021.
	std::shared_ptr<Register8_t>     Key22;     // Register "Key22"     @ 0x1F402022.
	std::shared_ptr<Register8_t>     Key23;     // Register "Key23"     @ 0x1F402023.
	std::shared_ptr<Register8_t>     Key24;     // Register "Key24"     @ 0x1F402024.
	std::shared_ptr<Register8_t>     Key28;     // Register "Key28"     @ 0x1F402028.
	std::shared_ptr<Register8_t>     Key29;     // Register "Key29"     @ 0x1F402029.
	std::shared_ptr<Register8_t>     Key2A;     // Register "Key2A"     @ 0x1F40202A.
	std::shared_ptr<Register8_t>     Key2B;     // Register "Key2B"     @ 0x1F40202B.
	std::shared_ptr<Register8_t>     Key2C;     // Register "Key2C"     @ 0x1F40202C.
	std::shared_ptr<Register8_t>     Key30;     // Register "Key30"     @ 0x1F402030.
	std::shared_ptr<Register8_t>     Key31;     // Register "Key31"     @ 0x1F402031.
	std::shared_ptr<Register8_t>     Key32;     // Register "Key32"     @ 0x1F402032.
	std::shared_ptr<Register8_t>     Key33;     // Register "Key33"     @ 0x1F402033.
	std::shared_ptr<Register8_t>     Key34;     // Register "Key34"     @ 0x1F402034.
	std::shared_ptr<Register8_t>     Key38;     // Register "Key38"     @ 0x1F402038.
	std::shared_ptr<Register8_t>     KeyXor;    // Register "KeyXor"    @ 0x1F402039.
	std::shared_ptr<Register8_t>     DecSet;    // Register "DecSet"    @ 0x1F40203A.
};