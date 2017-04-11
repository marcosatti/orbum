#include "stdafx.h"

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/Memory/ByteMemory_t.h"
#include "Common/Types/ByteMMU/ByteMMU_t.h"
#include "Common/Types/Register/Register32_t.h"

#include "Resources/IOP/IOP_t.h"
#include "Resources/IOP/IOPCore/IOPCore_t.h"
#include "Resources/IOP/DMAC/IOPDmac_t.h"
#include "Resources/IOP/INTC/IOPIntc_t.h"
#include "Resources/IOP/Timers/IOPTimers_t.h"

IOP_t::IOP_t() :
	IOPCore(std::make_shared<IOPCore_t>()),
	DMAC(std::make_shared<IOPDmac_t>()),
	INTC(std::make_shared<IOPIntc_t>()),
	Timers(std::make_shared<IOPTimers_t>()),
	MMU(std::make_shared<ByteMMU_t>(32, 16, 0)), // Number of page index bits optimised for minimum memory usage (Marco Satti).
	MainMemory(std::make_shared<ByteMemory_t>("IOP MainMem", false, false, Constants::IOP::IOPMemory::SIZE_IOP_MEMORY)),
	ParallelPort(std::make_shared<ByteMemory_t>("IOP ParallelPort IO Mem", false, false, Constants::IOP::ParallelPort::SIZE_PARALLEL_PORT)),

	// Registers.
	HW_SSBUS_SPD_ADDR(std::make_shared<Register32_t>("IOP HW_SSBUS_SPD_ADDR", false, false)),
	HW_SSBUS_PIO_ADDR(std::make_shared<Register32_t>("IOP HW_SSBUS_PIO_ADDR", false, false)),
	HW_SSBUS_SPD_DELAY(std::make_shared<Register32_t>("IOP HW_SSBUS_SPD_DELAY", false, false)),
	HW_SSBUS_DEV1_DELAY(std::make_shared<Register32_t>("IOP HW_SSBUS_DEV1_DELAY", false, false)),
	HW_SSBUS_ROM_DELAY(std::make_shared<Register32_t>("IOP HW_SSBUS_ROM_DELAY", false, false)),
	HW_SSBUS_SPU_DELAY(std::make_shared<Register32_t>("IOP HW_SSBUS_SPU_DELAY", false, false)),
	HW_SSBUS_DEV5_DELAY(std::make_shared<Register32_t>("IOP HW_SSBUS_DEV5_DELAY", false, false)),
	HW_SSBUS_PIO_DELAY(std::make_shared<Register32_t>("IOP HW_SSBUS_PIO_DELAY", false, false)),
	HW_SSBUS_COM_DELAY(std::make_shared<Register32_t>("IOP HW_SSBUS_COM_DELAY", false, false)),
	HW_RAM_SIZE(std::make_shared<Register32_t>("IOP HW_RAM_SIZE", false, false)),
	HW_SSBUS_DEV1_ADDR(std::make_shared<Register32_t>("IOP HW_SSBUS_DEV1_ADDR", false, false)),
	HW_SSBUS_SPU_ADDR(std::make_shared<Register32_t>("IOP HW_SSBUS_SPU_ADDR", false, false)),
	HW_SSBUS_DEV5_ADDR(std::make_shared<Register32_t>("IOP HW_SSBUS_DEV5_ADDR", false, false)),
	HW_SSBUS_SPU1_ADDR(std::make_shared<Register32_t>("IOP HW_SSBUS_SPU1_ADDR", false, false)),
	HW_SSBUS_DEV9_ADDR3(std::make_shared<Register32_t>("IOP HW_SSBUS_DEV9_ADDR3", false, false)),
	HW_SSBUS_SPU1_DELAY(std::make_shared<Register32_t>("IOP HW_SSBUS_SPU1_DELAY", false, false)),
	HW_SSBUS_DEV9_DELAY2(std::make_shared<Register32_t>("IOP HW_SSBUS_DEV9_DELAY2", false, false)),
	HW_SSBUS_DEV9_DELAY3(std::make_shared<Register32_t>("IOP HW_SSBUS_DEV9_DELAY3", false, false)),
	HW_SSBUS_DEV9_DELAY1(std::make_shared<Register32_t>("IOP HW_SSBUS_DEV9_DELAY1", false, false)),
	HW_ICFG(std::make_shared<Register32_t>("IOP HW_ICFG", false, false)),
	REGISTER_1470(std::make_shared<Register32_t>("IOP REGISTER_1470", false, false)),
	REGISTER_1560(std::make_shared<Register32_t>("IOP REGISTER_1560", false, false)),
	REGISTER_1564(std::make_shared<Register32_t>("IOP REGISTER_1564", false, false)),
	REGISTER_1568(std::make_shared<Register32_t>("IOP REGISTER_1568", false, false)),
	REGISTER_15F0(std::make_shared<Register32_t>("IOP REGISTER_15F0", false, false)),
	REGISTER_2070(std::make_shared<Register32_t>("IOP REGISTER_2070", false, false)),
	REGISTER_3800(std::make_shared<Register32_t>("IOP REGISTER_3800", false, false))
{
}