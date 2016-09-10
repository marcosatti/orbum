#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"

/*
GS_t defines the structure needed for the GS (graphics synthesiser unit).
*/

class PS2Resources_t;
class StorageObject_t;
class DeadStorageObject_t;
class BusErrorStorageObject_t;

class GS_t : public PS2ResourcesSubobject
{
public:
	explicit GS_t(const PS2Resources_t *const PS2Resources);

	/*
	GS Privileged registers, defined on page 26 onwards of the EE Users Manual. All are prefixed with GS_P_REGISTER, and start from PS2 physical address 0x12000000 to 0x14000000.
	If special functionality is needed, they are subclassed off StorageObject_t (or similar) and defined in Types/EERegisters_t.
	They are ordered by ascending, meaning the lowest physical address, to the highest.

	Also see the intitaliser list of EE_t(.cpp), where you can see the object parameter definitions.
	*/
	// 0x12000000.
	std::shared_ptr<StorageObject_t>         GS_P_REGISTER_PMODE;
	std::shared_ptr<StorageObject_t>         GS_P_REGISTER_SMODE1;
	std::shared_ptr<StorageObject_t>         GS_P_REGISTER_SMODE2;
	std::shared_ptr<StorageObject_t>         GS_P_REGISTER_SRFSH;
	std::shared_ptr<StorageObject_t>         GS_P_REGISTER_SYNCH1;
	std::shared_ptr<StorageObject_t>         GS_P_REGISTER_SYNCH2;
	std::shared_ptr<StorageObject_t>         GS_P_REGISTER_SYNCV;
	std::shared_ptr<StorageObject_t>         GS_P_REGISTER_DISPFB1;
	std::shared_ptr<StorageObject_t>         GS_P_REGISTER_DISPLAY1;
	std::shared_ptr<StorageObject_t>         GS_P_REGISTER_DISPFB2;
	std::shared_ptr<StorageObject_t>         GS_P_REGISTER_DISPLAY2;
	std::shared_ptr<StorageObject_t>         GS_P_REGISTER_EXTBUF;
	std::shared_ptr<StorageObject_t>         GS_P_REGISTER_EXTDATA;
	std::shared_ptr<StorageObject_t>         GS_P_REGISTER_EXTWRITE;
	std::shared_ptr<StorageObject_t>         GS_P_REGISTER_BGCOLOR;
	std::shared_ptr<DeadStorageObject_t>     GS_P_REGISTER_SPE_00f0;

	// 0x12001000.
	std::shared_ptr<StorageObject_t>         GS_P_REGISTER_CSR;
	std::shared_ptr<StorageObject_t>         GS_P_REGISTER_IMR;
	std::shared_ptr<DeadStorageObject_t>     GS_P_REGISTER_SPE_1020;
	std::shared_ptr<StorageObject_t>         GS_P_REGISTER_BUSDIR;
	std::shared_ptr<DeadStorageObject_t>     GS_P_REGISTER_SPE_1050;
	std::shared_ptr<StorageObject_t>         GS_P_REGISTER_SIGLBLID;
	std::shared_ptr<DeadStorageObject_t>     GS_P_REGISTER_SPE_1090;
	std::shared_ptr<DeadStorageObject_t>     GS_P_REGISTER_SPE_1100;

	// 0x12002000.
	std::shared_ptr<DeadStorageObject_t>     GS_P_REGISTER_SPE_2000;
	std::shared_ptr<BusErrorStorageObject_t> GS_P_REGISTER_SPEBusErr;

};

