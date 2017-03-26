#pragma once

#include <memory>

class CRTC_t;
class Register64_t;
class ConstantByteMemory_t;

/*
GS_t defines the structure needed for the GS (graphics synthesiser unit).
*/
class GS_t
{
public:
	explicit GS_t();

	/*
	PCRTC resources.
	*/
	std::shared_ptr<CRTC_t> CRTC;

	/*
	GS privileged registers, defined on page 26 onwards of the EE Users Manual. All start from PS2 physical address 0x12000000 to 0x14000000.
	*/
	// 0x12000000.
	std::shared_ptr<Register64_t>     PMODE;
	std::shared_ptr<Register64_t>     SMODE1;
	std::shared_ptr<Register64_t>     SMODE2;
	std::shared_ptr<Register64_t>     SRFSH;
	std::shared_ptr<Register64_t>     SYNCH1;
	std::shared_ptr<Register64_t>     SYNCH2;
	std::shared_ptr<Register64_t>     SYNCV;
	std::shared_ptr<Register64_t>     DISPFB1;
	std::shared_ptr<Register64_t>     DISPLAY1;
	std::shared_ptr<Register64_t>     DISPFB2;
	std::shared_ptr<Register64_t>     DISPLAY2;
	std::shared_ptr<Register64_t>     EXTBUF;
	std::shared_ptr<Register64_t>     EXTDATA;
	std::shared_ptr<Register64_t>     EXTWRITE;
	std::shared_ptr<Register64_t>     BGCOLOR;
	std::shared_ptr<ConstantByteMemory_t> MEMORY_00F0;

	// 0x12001000.
	std::shared_ptr<Register64_t>     CSR;
	std::shared_ptr<Register64_t>     IMR;
	std::shared_ptr<ConstantByteMemory_t> MEMORY_1020;
	std::shared_ptr<Register64_t>     BUSDIR;
	std::shared_ptr<ConstantByteMemory_t> MEMORY_1050;
	std::shared_ptr<Register64_t>     SIGLBLID;
	std::shared_ptr<ConstantByteMemory_t> MEMORY_1090;
	std::shared_ptr<ConstantByteMemory_t> MEMORY_1100;

	// 0x12002000.
	std::shared_ptr<ConstantByteMemory_t> MEMORY_2000;

};

