#include "stdafx.h"

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/Memory/Memory_t.h"
#include "Common/Types/PhysicalMMU/PhysicalMMU_t.h"
#include "Common/Types/Memory/DebugMemory_t.h"
#include "Common/Types/Registers/Register32_t.h"
#include "Common/Types/Registers/BitfieldRegister32_t.h"
#include "Common/Types/Registers/Constant/ConstantRegister8_t.h"
#include "Common/Types/Registers/Constant/ConstantRegister32_t.h"

#include "PS2Constants/PS2Constants.h"

#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/Common/Common_t.h"
#include "PS2Resources/Common/Types/SBUSRegisters_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/Types/BootROM_t.h"
#include "PS2Resources/IOP/DMAC/Types/IOPDmacChannels_t.h"
#include "PS2Resources/IOP/DMAC/Types/IOPDmacChannelRegisters_t.h"
#include "PS2Resources/IOP/DMAC/Types/IOPDmacRegisters_t.h"
#include "PS2Resources/IOP/Timers/Types/IOPTimersTimers_t.h"
#include "PS2Resources/IOP/Timers/Types/IOPTimersTimerRegisters_t.h"
#include "PS2Resources/IOP/INTC/Types/IOPIntcRegisters_t.h"
#include "PS2Resources/IOP/IOP_t.h"
#include "PS2Resources/IOP/IOPCore/IOPCore_t.h"
#include "PS2Resources/IOP/DMAC/IOPDmac_t.h"
#include "PS2Resources/IOP/INTC/IOPIntc_t.h"
#include "PS2Resources/IOP/CDVD/CDVD_t.h"
#include "PS2Resources/IOP/Timers/IOPTimers_t.h"

IOP_t::IOP_t(const PS2Resources_t* PS2Resources) :
	PS2ResourcesSubcategory(PS2Resources),
	IOPCore(std::make_shared<IOPCore_t>(getRoot())),
	DMAC(std::make_shared<IOPDmac_t>(getRoot())),
	INTC(std::make_shared<IOPIntc_t>(getRoot())),
	CDVD(std::make_shared<CDVD_t>(getRoot())),
	Timers(std::make_shared<IOPTimers_t>(getRoot())),
	PhysicalMMU(std::make_shared<PhysicalMMU_t>(Constants::SIZE_4GB, Constants::SIZE_8KB, 1)),
	MainMemory(std::make_shared<Memory_t>(PS2Constants::IOP::IOPMemory::SIZE_IOP_MEMORY, "IOP Memory")),
	ParallelPort(std::make_shared<DebugMemory_t>(PS2Constants::IOP::ParallelPort::SIZE_PARALLEL_PORT, "IOP Parallel Port")),

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
	REGISTER_1578(std::make_shared<Register32_t>()),
	REGISTER_15F0(std::make_shared<Register32_t>()),
	REGISTER_2070(std::make_shared<Register32_t>()),
	REGISTER_3800(std::make_shared<Register32_t>())
{
}

void IOP_t::postResourcesInit()
{
	CDVD->postResourcesInit();
	DMAC->postResourcesInit();
	INTC->postResourcesInit();
	IOPCore->postResourcesInit();
	Timers->postResourcesInit();

	initIOPPhysicalMemoryMap();
}

void IOP_t::initIOPPhysicalMemoryMap() const
{
	// IOP Memory.
	{
		// Main Memory.
		PhysicalMMU->mapObject(PS2Constants::IOP::IOPMemory::PADDRESS_IOP_MEMORY, MainMemory);

		// Various ROMs.
		PhysicalMMU->mapObject(PS2Constants::EE::ROM::PADDRESS_BOOT_ROM, getRoot()->EE->BootROM);
		PhysicalMMU->mapObject(PS2Constants::EE::ROM::PADDRESS_ROM1, getRoot()->EE->ROM1);

		// Mirror of the Boot ROM at 0xFFC00000. Needed by IOP bios initalisation.
		PhysicalMMU->mapObject(0xFFC00000, getRoot()->EE->BootROM);

		// Scratchpad Memory.
		PhysicalMMU->mapObject(PS2Constants::IOP::IOPCore::ScratchpadMemory::PADDRESS_SCRATCHPAD_MEMORY, IOPCore->ScratchpadMemory);
	}

	// IOP Registers.
	{
		// Misc IOP Registers.
		PhysicalMMU->mapObject(0x1F801000, HW_SSBUS_SPD_ADDR);
		PhysicalMMU->mapObject(0x1F801004, HW_SSBUS_PIO_ADDR);
		PhysicalMMU->mapObject(0x1F801008, HW_SSBUS_SPD_DELAY);
		PhysicalMMU->mapObject(0x1F80100C, HW_SSBUS_DEV1_DELAY);
		PhysicalMMU->mapObject(0x1F801010, HW_SSBUS_ROM_DELAY);
		PhysicalMMU->mapObject(0x1F801014, HW_SSBUS_SPU_DELAY);
		PhysicalMMU->mapObject(0x1F801018, HW_SSBUS_DEV5_DELAY);
		PhysicalMMU->mapObject(0x1F80101C, HW_SSBUS_PIO_DELAY);
		PhysicalMMU->mapObject(0x1F801020, HW_SSBUS_COM_DELAY);
		PhysicalMMU->mapObject(0x1F801060, HW_RAM_SIZE);
		PhysicalMMU->mapObject(0x1F801400, HW_SSBUS_DEV1_ADDR);
		PhysicalMMU->mapObject(0x1F801404, HW_SSBUS_SPU_ADDR);
		PhysicalMMU->mapObject(0x1F801408, HW_SSBUS_DEV5_ADDR);
		PhysicalMMU->mapObject(0x1F80140C, HW_SSBUS_SPU1_ADDR);
		PhysicalMMU->mapObject(0x1F801410, HW_SSBUS_DEV9_ADDR3);
		PhysicalMMU->mapObject(0x1F801414, HW_SSBUS_SPU1_DELAY);
		PhysicalMMU->mapObject(0x1F801418, HW_SSBUS_DEV9_DELAY2);
		PhysicalMMU->mapObject(0x1F80141C, HW_SSBUS_DEV9_DELAY3);
		PhysicalMMU->mapObject(0x1F801420, HW_SSBUS_DEV9_DELAY1);
		PhysicalMMU->mapObject(0x1F801450, HW_ICFG);
		PhysicalMMU->mapObject(0x1F801560, REGISTER_1560);
		PhysicalMMU->mapObject(0x1F801564, REGISTER_1564);
		PhysicalMMU->mapObject(0x1F801568, REGISTER_1568);
		PhysicalMMU->mapObject(0x1F801578, REGISTER_1578);
		PhysicalMMU->mapObject(0x1F8015F0, REGISTER_15F0);
		PhysicalMMU->mapObject(0x1F802070, REGISTER_2070);

		// DMAC Registers.
		PhysicalMMU->mapObject(0x1F801080, DMAC->CHANNEL_fromMDEC->MADR);
		PhysicalMMU->mapObject(0x1F801084, DMAC->CHANNEL_fromMDEC->BCR);
		PhysicalMMU->mapObject(0x1F801088, DMAC->CHANNEL_fromMDEC->CHCR);
		PhysicalMMU->mapObject(0x1F801090, DMAC->CHANNEL_toMDEC->MADR);
		PhysicalMMU->mapObject(0x1F801094, DMAC->CHANNEL_toMDEC->BCR);
		PhysicalMMU->mapObject(0x1F801098, DMAC->CHANNEL_toMDEC->CHCR);
		PhysicalMMU->mapObject(0x1F8010A0, DMAC->CHANNEL_GPU->MADR);
		PhysicalMMU->mapObject(0x1F8010A4, DMAC->CHANNEL_GPU->BCR);
		PhysicalMMU->mapObject(0x1F8010A8, DMAC->CHANNEL_GPU->CHCR);
		PhysicalMMU->mapObject(0x1F8010B0, DMAC->CHANNEL_CDROM->MADR);
		PhysicalMMU->mapObject(0x1F8010B4, DMAC->CHANNEL_CDROM->BCR);
		PhysicalMMU->mapObject(0x1F8010B8, DMAC->CHANNEL_CDROM->CHCR);
		PhysicalMMU->mapObject(0x1F8010C0, DMAC->CHANNEL_SPU2c1->MADR);
		PhysicalMMU->mapObject(0x1F8010C4, DMAC->CHANNEL_SPU2c1->BCR);
		PhysicalMMU->mapObject(0x1F8010C8, DMAC->CHANNEL_SPU2c1->CHCR);
		PhysicalMMU->mapObject(0x1F8010CC, DMAC->CHANNEL_SPU2c1->TADR);
		PhysicalMMU->mapObject(0x1F8010D0, DMAC->CHANNEL_PIO->MADR);
		PhysicalMMU->mapObject(0x1F8010D4, DMAC->CHANNEL_PIO->BCR);
		PhysicalMMU->mapObject(0x1F8010D8, DMAC->CHANNEL_PIO->CHCR);
		PhysicalMMU->mapObject(0x1F8010E0, DMAC->CHANNEL_OTClear->MADR);
		PhysicalMMU->mapObject(0x1F8010E4, DMAC->CHANNEL_OTClear->BCR);
		PhysicalMMU->mapObject(0x1F8010E8, DMAC->CHANNEL_OTClear->CHCR);
		PhysicalMMU->mapObject(0x1F801500, DMAC->CHANNEL_SPU2c2->MADR);
		PhysicalMMU->mapObject(0x1F801504, DMAC->CHANNEL_SPU2c2->BCR);
		PhysicalMMU->mapObject(0x1F801508, DMAC->CHANNEL_SPU2c2->CHCR);
		PhysicalMMU->mapObject(0x1F801510, DMAC->CHANNEL_DEV9->MADR);
		PhysicalMMU->mapObject(0x1F801514, DMAC->CHANNEL_DEV9->BCR);
		PhysicalMMU->mapObject(0x1F801518, DMAC->CHANNEL_DEV9->CHCR);
		PhysicalMMU->mapObject(0x1F801520, DMAC->CHANNEL_SIF0->MADR);
		PhysicalMMU->mapObject(0x1F801524, DMAC->CHANNEL_SIF0->BCR);
		PhysicalMMU->mapObject(0x1F801528, DMAC->CHANNEL_SIF0->CHCR);
		PhysicalMMU->mapObject(0x1F80152C, DMAC->CHANNEL_SIF0->TADR);
		PhysicalMMU->mapObject(0x1F801530, DMAC->CHANNEL_SIF1->MADR);
		PhysicalMMU->mapObject(0x1F801534, DMAC->CHANNEL_SIF1->BCR);
		PhysicalMMU->mapObject(0x1F801538, DMAC->CHANNEL_SIF1->CHCR);
		PhysicalMMU->mapObject(0x1F801540, DMAC->CHANNEL_fromSIO2->MADR);
		PhysicalMMU->mapObject(0x1F801544, DMAC->CHANNEL_fromSIO2->BCR);
		PhysicalMMU->mapObject(0x1F801548, DMAC->CHANNEL_fromSIO2->CHCR);
		PhysicalMMU->mapObject(0x1F801550, DMAC->CHANNEL_toSIO2->MADR);
		PhysicalMMU->mapObject(0x1F801554, DMAC->CHANNEL_toSIO2->BCR);
		PhysicalMMU->mapObject(0x1F801558, DMAC->CHANNEL_toSIO2->CHCR);
		PhysicalMMU->mapObject(0x1F8010F0, DMAC->PCR);
		PhysicalMMU->mapObject(0x1F8010F4, DMAC->ICR);
		PhysicalMMU->mapObject(0x1F801570, DMAC->PCR2);
		PhysicalMMU->mapObject(0x1F801574, DMAC->ICR2);

		// INTC Registers.
		PhysicalMMU->mapObject(0x1F801070, INTC->STAT);
		PhysicalMMU->mapObject(0x1F801074, INTC->MASK);
		PhysicalMMU->mapObject(0x1F801078, INTC->CTRL);
			
		// CDVD Registers.
		PhysicalMMU->mapObject(0x1F402004, CDVD->N_COMMAND);
		PhysicalMMU->mapObject(0x1F402005, CDVD->N_READY);
		PhysicalMMU->mapObject(0x1F402006, CDVD->ERROR);
		PhysicalMMU->mapObject(0x1F402007, CDVD->BREAK);
		PhysicalMMU->mapObject(0x1F402008, CDVD->STATUS);
		PhysicalMMU->mapObject(0x1F40200A, CDVD->STATUS); // Mirrored?
		PhysicalMMU->mapObject(0x1F40200B, CDVD->TRAY_STATE);
		PhysicalMMU->mapObject(0x1F40200C, CDVD->CRT_MINUTE);
		PhysicalMMU->mapObject(0x1F40200D, CDVD->CRT_SECOND);
		PhysicalMMU->mapObject(0x1F40200E, CDVD->CRT_FRAME);
		PhysicalMMU->mapObject(0x1F40200F, CDVD->TYPE);
		PhysicalMMU->mapObject(0x1F402013, CDVD->REGISTER_2013);
		PhysicalMMU->mapObject(0x1F402015, CDVD->RSV);
		PhysicalMMU->mapObject(0x1F402016, CDVD->S_COMMAND);
		PhysicalMMU->mapObject(0x1F402017, CDVD->S_READY);
		PhysicalMMU->mapObject(0x1F402018, CDVD->S_DATA_OUT);
		PhysicalMMU->mapObject(0x1F402020, CDVD->KEY_20);
		PhysicalMMU->mapObject(0x1F402021, CDVD->KEY_21);
		PhysicalMMU->mapObject(0x1F402022, CDVD->KEY_22);
		PhysicalMMU->mapObject(0x1F402023, CDVD->KEY_23);
		PhysicalMMU->mapObject(0x1F402024, CDVD->KEY_24);
		PhysicalMMU->mapObject(0x1F402028, CDVD->KEY_28);
		PhysicalMMU->mapObject(0x1F402029, CDVD->KEY_29);
		PhysicalMMU->mapObject(0x1F40202A, CDVD->KEY_2A);
		PhysicalMMU->mapObject(0x1F40202B, CDVD->KEY_2B);
		PhysicalMMU->mapObject(0x1F40202C, CDVD->KEY_2C);
		PhysicalMMU->mapObject(0x1F402030, CDVD->KEY_30);
		PhysicalMMU->mapObject(0x1F402031, CDVD->KEY_31);
		PhysicalMMU->mapObject(0x1F402032, CDVD->KEY_32);
		PhysicalMMU->mapObject(0x1F402033, CDVD->KEY_33);
		PhysicalMMU->mapObject(0x1F402034, CDVD->KEY_34);
		PhysicalMMU->mapObject(0x1F402038, CDVD->KEY_38);
		PhysicalMMU->mapObject(0x1F402039, CDVD->KEY_XOR);
		PhysicalMMU->mapObject(0x1F40203A, CDVD->DEC_SET);

		// Timers Registers.
		PhysicalMMU->mapObject(0x1F801100, Timers->TIMER_0->COUNT);
		PhysicalMMU->mapObject(0x1F801104, Timers->TIMER_0->MODE);
		PhysicalMMU->mapObject(0x1F801108, Timers->TIMER_0->COMP);
		PhysicalMMU->mapObject(0x1F801110, Timers->TIMER_1->COUNT);
		PhysicalMMU->mapObject(0x1F801114, Timers->TIMER_1->MODE);
		PhysicalMMU->mapObject(0x1F801118, Timers->TIMER_1->COMP);
		PhysicalMMU->mapObject(0x1F801120, Timers->TIMER_2->COUNT);
		PhysicalMMU->mapObject(0x1F801124, Timers->TIMER_2->MODE);
		PhysicalMMU->mapObject(0x1F801128, Timers->TIMER_2->COMP);
		PhysicalMMU->mapObject(0x1F801480, Timers->TIMER_3->COUNT);
		PhysicalMMU->mapObject(0x1F801484, Timers->TIMER_3->MODE);
		PhysicalMMU->mapObject(0x1F801488, Timers->TIMER_3->COMP);
		PhysicalMMU->mapObject(0x1F801490, Timers->TIMER_4->COUNT);
		PhysicalMMU->mapObject(0x1F801494, Timers->TIMER_4->MODE);
		PhysicalMMU->mapObject(0x1F801498, Timers->TIMER_4->COMP);
		PhysicalMMU->mapObject(0x1F8014A0, Timers->TIMER_5->COUNT);
		PhysicalMMU->mapObject(0x1F8014A4, Timers->TIMER_5->MODE);
		PhysicalMMU->mapObject(0x1F8014A8, Timers->TIMER_5->COMP);

		// Parallel Port.
		PhysicalMMU->mapObject(PS2Constants::IOP::ParallelPort::PADDRESS_PARALLEL_PORT, ParallelPort);

	}

	// SIF Registers
	{
		PhysicalMMU->mapObject(0x1D000000, getRoot()->Common->SBUS_MSCOM);
		PhysicalMMU->mapObject(0x1D000010, getRoot()->Common->SBUS_SMCOM);
		PhysicalMMU->mapObject(0x1D000020, getRoot()->Common->SBUS_MSFLG);
		PhysicalMMU->mapObject(0x1D000030, getRoot()->Common->SBUS_SMFLG);
		PhysicalMMU->mapObject(0x1D000040, getRoot()->Common->SBUS_F240);
		PhysicalMMU->mapObject(0x1D000060, getRoot()->Common->SBUS_F260);
	}
}
