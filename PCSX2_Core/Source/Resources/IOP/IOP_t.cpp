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
#include "Resources/IOP/CDVD/CDVD_t.h"
#include "Resources/IOP/SPU2/SPU2_t.h"
#include "Resources/IOP/Timers/IOPTimers_t.h"

IOP_t::IOP_t() :
	IOPCore(std::make_shared<IOPCore_t>()),
	DMAC(std::make_shared<IOPDmac_t>()),
	INTC(std::make_shared<IOPIntc_t>()),
	CDVD(std::make_shared<CDVD_t>()),
	SPU2(std::make_shared<SPU2_t>()),
	Timers(std::make_shared<IOPTimers_t>()),
	ByteMMU(std::make_shared<ByteMMU_t>(Constants::SIZE_4GB, Constants::SIZE_8KB, 1)),
	MainMemory(std::make_shared<ByteMemory_t>(Constants::IOP::IOPMemory::SIZE_IOP_MEMORY, "IOP Memory")),
	ParallelPort(std::make_shared<ByteMemory_t>(Constants::IOP::ParallelPort::SIZE_PARALLEL_PORT, "IOP Parallel Port")),

	// Registers.
	HW_SSBUS_SPD_ADDR(std::make_shared<Register32_t>()),
	HW_SSBUS_PIO_ADDR(std::make_shared<Register32_t>()),
	HW_SSBUS_SPD_DELAY(std::make_shared<Register32_t>()),
	HW_SSBUS_DEV1_DELAY(std::make_shared<Register32_t>()),
	HW_SSBUS_ROM_DELAY(std::make_shared<Register32_t>()),
	HW_SSBUS_SPU_DELAY(std::make_shared<Register32_t>()),
	HW_SSBUS_DEV5_DELAY(std::make_shared<Register32_t>()),
	HW_SSBUS_PIO_DELAY(std::make_shared<Register32_t>()),
	HW_SSBUS_COM_DELAY(std::make_shared<Register32_t>()),
	HW_RAM_SIZE(std::make_shared<Register32_t>()),
	HW_SSBUS_DEV1_ADDR(std::make_shared<Register32_t>()),
	HW_SSBUS_SPU_ADDR(std::make_shared<Register32_t>()),
	HW_SSBUS_DEV5_ADDR(std::make_shared<Register32_t>()),
	HW_SSBUS_SPU1_ADDR(std::make_shared<Register32_t>()),
	HW_SSBUS_DEV9_ADDR3(std::make_shared<Register32_t>()),
	HW_SSBUS_SPU1_DELAY(std::make_shared<Register32_t>()),
	HW_SSBUS_DEV9_DELAY2(std::make_shared<Register32_t>()),
	HW_SSBUS_DEV9_DELAY3(std::make_shared<Register32_t>()),
	HW_SSBUS_DEV9_DELAY1(std::make_shared<Register32_t>()),
	HW_ICFG(std::make_shared<Register32_t>()),
	REGISTER_1470(std::make_shared<Register32_t>()),
	REGISTER_1560(std::make_shared<Register32_t>()),
	REGISTER_1564(std::make_shared<Register32_t>()),
	REGISTER_1568(std::make_shared<Register32_t>()),
	REGISTER_15F0(std::make_shared<Register32_t>()),
	REGISTER_2070(std::make_shared<Register32_t>()),
	REGISTER_3800(std::make_shared<Register32_t>())
{
}