#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"

/*
GS_t defines the structure needed for the GS (graphics synthesiser unit).
*/

class PS2Resources_t;
class Memory_t;
class ZeroMemory_t;
class BusErrMemory_t;

class GS_t : public PS2ResourcesSubobject
{
public:
	explicit GS_t(const PS2Resources_t *const PS2Resources);

	/*
	The H-BLNK and V-BLNK signals. These are needed by the EE Timers as gate conditions.
	Zero = low signal.
	Non-zero (1) = high signal.

	Use the set functions which will set the last state automatically (again needed by the EE Timers).
	*/
	u8 SIGNAL_HBLNK;
	u8 SIGNAL_HBLNK_LAST;
	u8 SIGNAL_VBLNK;
	u8 SIGNAL_VBLNK_LAST;
	void setSignalHBLNK(const u8 & hblnk);
	void setSignalVBLNK(const u8 & vblnk);

	/*
	GS Privileged registers, defined on page 26 onwards of the EE Users Manual. All are prefixed with GS_P_REGISTER, and start from PS2 physical address 0x12000000 to 0x14000000.
	If special functionality is needed, they are subclassed off MappedMemory_t (or similar) and defined in Types/EERegisters_t.
	They are ordered by ascending, meaning the lowest physical address, to the highest.

	Also see the intitaliser list of EE_t(.cpp), where you can see the object parameter definitions.
	*/
	// 0x12000000.
	std::shared_ptr<Memory_t>         GS_P_REGISTER_PMODE;
	std::shared_ptr<Memory_t>         GS_P_REGISTER_SMODE1;
	std::shared_ptr<Memory_t>         GS_P_REGISTER_SMODE2;
	std::shared_ptr<Memory_t>         GS_P_REGISTER_SRFSH;
	std::shared_ptr<Memory_t>         GS_P_REGISTER_SYNCH1;
	std::shared_ptr<Memory_t>         GS_P_REGISTER_SYNCH2;
	std::shared_ptr<Memory_t>         GS_P_REGISTER_SYNCV;
	std::shared_ptr<Memory_t>         GS_P_REGISTER_DISPFB1;
	std::shared_ptr<Memory_t>         GS_P_REGISTER_DISPLAY1;
	std::shared_ptr<Memory_t>         GS_P_REGISTER_DISPFB2;
	std::shared_ptr<Memory_t>         GS_P_REGISTER_DISPLAY2;
	std::shared_ptr<Memory_t>         GS_P_REGISTER_EXTBUF;
	std::shared_ptr<Memory_t>         GS_P_REGISTER_EXTDATA;
	std::shared_ptr<Memory_t>         GS_P_REGISTER_EXTWRITE;
	std::shared_ptr<Memory_t>         GS_P_REGISTER_BGCOLOR;
	std::shared_ptr<ZeroMemory_t>     GS_P_REGISTER_SPE_00f0;

	// 0x12001000.
	std::shared_ptr<Memory_t>         GS_P_REGISTER_CSR;
	std::shared_ptr<Memory_t>         GS_P_REGISTER_IMR;
	std::shared_ptr<ZeroMemory_t>     GS_P_REGISTER_SPE_1020;
	std::shared_ptr<Memory_t>         GS_P_REGISTER_BUSDIR;
	std::shared_ptr<ZeroMemory_t>     GS_P_REGISTER_SPE_1050;
	std::shared_ptr<Memory_t>         GS_P_REGISTER_SIGLBLID;
	std::shared_ptr<ZeroMemory_t>     GS_P_REGISTER_SPE_1090;
	std::shared_ptr<ZeroMemory_t>     GS_P_REGISTER_SPE_1100;

	// 0x12002000.
	std::shared_ptr<ZeroMemory_t>     GS_P_REGISTER_SPE_2000;
	std::shared_ptr<BusErrMemory_t> GS_P_REGISTER_SPEBusErr;

};

