#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/GS/GS_t.h"
#include "Common/PS2Resources/Types/StorageObject/StorageObject_t.h"
#include "Common/PS2Resources/Types/DeadStorageObject/DeadStorageObject_t.h"
#include "Common/PS2Resources/Types/BusErrorStorageObject/BusErrorStorageObject_t.h"

GS_t::GS_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),

	// Registers.
	GS_P_REGISTER_PMODE(std::make_shared<StorageObject_t>(0x04, "SPE: PMODE", 0x12000000)),
	GS_P_REGISTER_SMODE1(std::make_shared<StorageObject_t>(0x04, "SPE: SMODE1", 0x12000010)),
	GS_P_REGISTER_SMODE2(std::make_shared<StorageObject_t>(0x04, "SPE: SMODE2", 0x12000020)),
	GS_P_REGISTER_SRFSH(std::make_shared<StorageObject_t>(0x04, "SPE: SRFSH", 0x12000030)),
	GS_P_REGISTER_SYNCH1(std::make_shared<StorageObject_t>(0x04, "SPE: SYNCH1", 0x12000040)),
	GS_P_REGISTER_SYNCH2(std::make_shared<StorageObject_t>(0x04, "SPE: SYNCH2", 0x12000050)),
	GS_P_REGISTER_SYNCV(std::make_shared<StorageObject_t>(0x04, "SPE: SYNCV", 0x12000060)),
	GS_P_REGISTER_DISPFB1(std::make_shared<StorageObject_t>(0x04, "SPE: DISPFB1", 0x12000070)),
	GS_P_REGISTER_DISPLAY1(std::make_shared<StorageObject_t>(0x04, "SPE: DISPLAY1", 0x12000080)),
	GS_P_REGISTER_DISPFB2(std::make_shared<StorageObject_t>(0x04, "SPE: DISPFB2", 0x12000090)),
	GS_P_REGISTER_DISPLAY2(std::make_shared<StorageObject_t>(0x04, "SPE: DISPLAY2", 0x120000a0)),
	GS_P_REGISTER_EXTBUF(std::make_shared<StorageObject_t>(0x04, "SPE: EXTBUF", 0x120000b0)),
	GS_P_REGISTER_EXTDATA(std::make_shared<StorageObject_t>(0x04, "SPE: EXTDATA", 0x120000c0)),
	GS_P_REGISTER_EXTWRITE(std::make_shared<StorageObject_t>(0x04, "SPE: EXTWRITE", 0x120000d0)),
	GS_P_REGISTER_BGCOLOR(std::make_shared<StorageObject_t>(0x04, "SPE: BGCOLOR", 0x120000e0)),
	GS_P_REGISTER_SPE_00f0(std::make_shared<DeadStorageObject_t>(0x310, "SPE: SPE_00f0 (reserved)", 0x120000f0)),
	GS_P_REGISTER_CSR(std::make_shared<StorageObject_t>(0x04, "SPE: CSR", 0x12001000)),
	GS_P_REGISTER_IMR(std::make_shared<StorageObject_t>(0x04, "SPE: IMR", 0x12001010)),
	GS_P_REGISTER_SPE_1020(std::make_shared<DeadStorageObject_t>(0x20, "SPE: SPE_1020 (reserved)", 0x12001020)),
	GS_P_REGISTER_BUSDIR(std::make_shared<StorageObject_t>(0x04, "SPE: BUSDIR", 0x12001040)),
	GS_P_REGISTER_SPE_1050(std::make_shared<DeadStorageObject_t>(0x30, "SPE: SPE_1050 (reserved)", 0x12001050)),
	GS_P_REGISTER_SIGLBLID(std::make_shared<StorageObject_t>(0x04, "SPE: SIGLBLID", 0x12001080)),
	GS_P_REGISTER_SPE_1090(std::make_shared<DeadStorageObject_t>(0x60, "SPE: SPE_1090 (reserved)", 0x12001090)),
	GS_P_REGISTER_SPE_1100(std::make_shared<DeadStorageObject_t>(0x300, "SPE: SPE_1100 (reserved)", 0x12001100)),
	GS_P_REGISTER_SPE_2000(std::make_shared<DeadStorageObject_t>(0xE000, "SPE: SPE_2000 (reserved)", 0x12002000)),
	GS_P_REGISTER_SPEBusErr(std::make_shared<BusErrorStorageObject_t>(0x1FF0000, "SPE: SPEBusErr", 0x12010000))
{
}
