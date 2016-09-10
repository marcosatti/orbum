#include "stdafx.h"

#include <memory>
#include <fstream>

#include "VM/VMMain.h"
#include "VM/VMMMUHandler/VMMMUHandler.h"
#include "VM/ExecutionCore/Interpreter/Interpreter.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/EE/EECore/EECore_t.h"
#include "Common/PS2Resources/EE/Types/EERegisters_t.h"
#include "Common/PS2Resources/GS/GS_t.h"
#include "Common/PS2Constants/PS2Constants.h"
#include "Common/PS2Resources/Types/StorageObject/StorageObject_t.h"
#include "Common/PS2Resources/Types/DeadStorageObject/DeadStorageObject_t.h"
#include "Common/PS2Resources/Types/BusErrorStorageObject/BusErrorStorageObject_t.h"
#include "VM/VMMMUHandler/Types/ImageStorageObject_t.h"


VMMain::VMMain(ExecutionCoreType executionCoreType, const std::string & bootROMPath) : 
	mStatus(VMMain::VMStatus::CREATED),
	mExecutionCoreType(executionCoreType),
	mMMUComponent(std::make_shared<VMMMUHandler>(this)),
	mBootROMPath(bootROMPath)
{
	// Initialise everything.
	Reset();
}

void VMMain::LoadExecutable(std::string&& excutablePath) const
{
	// TODO: Implement.
}

void VMMain::Reset()
{
	// Initalise VM.
	initaliseResources();
	initaliseExecutionCore();
	initalisePS2PhysicalMemoryMap();

	// Initiaise BIOS (BootROM).
	initaliseBootROM();
	
	// Initalise the execution core.
	mExecutionCoreComponent->initalise();
}

void VMMain::Run()
{
	// Set to running.
	mStatus = VMStatus::RUNNING;

	// Run the VM.
	while (mStatus == VMStatus::RUNNING)
	{
		mExecutionCoreComponent->executionStep();
	}
}

void VMMain::Stop()
{
	// TODO: Implement.
}

VMMain::~VMMain()
{
}

const VMMain::VMStatus& VMMain::getStatus() const
{
	return mStatus;
}

const std::shared_ptr<PS2Resources_t>& VMMain::getResources() const
{
	return mPS2Resources;
}

const std::shared_ptr<VMMMUHandler>& VMMain::getMMU() const
{
	return mMMUComponent;
}

void VMMain::initaliseResources()
{
	mPS2Resources = std::make_shared<PS2Resources_t>();
}

void VMMain::initalisePS2PhysicalMemoryMap() const
{
	// Main memory 32MB
	getMMU()->mapMemory(getResources()->MainMemory);

	// Scratchpad memory 16KB
	getMMU()->mapMemory(getResources()->EE->EECore->ScratchpadMemory);

	// Boot ROM 4MB
	getMMU()->mapMemory(getResources()->BootROM);

	// EE Registers.
	{
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_T0_COUNT);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_T0_MODE);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_T0_COMP);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_T0_HOLD);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_TIMER_0040);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_T1_COUNT);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_T1_MODE);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_T1_COMP);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_T1_HOLD);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_TIMER_0840);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_T2_COUNT);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_T2_MODE);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_T2_COMP);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_TIMER_1030);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_T3_COUNT);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_T3_MODE);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_T3_COMP);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_TIMER_1830);

		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_IPU_CMD);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_IPU_CTRL);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_IPU_BP);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_IPU_TOP);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_IPU_2040);

		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_GIF_CTRL);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_GIF_MODE);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_GIF_STAT);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_GIF_3030);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_GIF_TAG0);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_GIF_TAG1);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_GIF_TAG2);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_GIF_TAG3);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_GIF_CNT);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_GIF_P3CNT);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_GIF_P3TAG);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_GIF_30b0);

		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF0_STAT);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF0_FBRST);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF0_ERR);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF0_MARK);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF0_CYCLE);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF0_MODE);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF0_NUM);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF0_MASK);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF0_CODE);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF0_ITOPS);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF0_38a0);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF0_38b0);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF0_38c0);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF0_ITOP);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF0_38e0);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF0_38f0);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF0_R0);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF0_R1);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF0_R2);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF0_R3);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF0_C0);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF0_C1);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF0_C2);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF0_C3);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF0_3980);

		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF1_STAT);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF1_FBRST);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF1_ERR);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF1_MARK);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF1_CYCLE);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF1_MODE);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF1_NUM);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF1_MASK);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF1_CODE);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF1_ITOPS);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF1_BASE);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF1_OFST);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF1_TOPS);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF1_ITOP);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF1_TOP);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF1_3cf0);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF1_R0);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF1_R1);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF1_R2);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF1_R3);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF1_C0);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF1_C1);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF1_C2);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF1_C3);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF1_3d80);

		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF0_FIFO);
		getMMU()->mapMemory(
			std::make_shared<ImageStorageObject_t>("Image: 0x10004000", 0x10004010, 0x10, 0xFF0, 0x10004000, getMMU()) // Image of 0x10004000.
		);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_VIF1_FIFO);
		getMMU()->mapMemory(
			std::make_shared<ImageStorageObject_t>("Image: 0x10005000", 0x10005010, 0x10, 0xFF0, 0x10005000, getMMU()) // Image of 0x10005000.
		);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_GIF_FIFO);
		getMMU()->mapMemory(
			std::make_shared<ImageStorageObject_t>("Image: 0x10006000", 0x10006010, 0x10, 0xFF0, 0x10006000, getMMU()) // Image of 0x10006000.
		);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_IPU_out_FIFO);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_IPU_in_FIFO);
		getMMU()->mapMemory(
			std::make_shared<ImageStorageObject_t>("Image: 0x10007000", 0x10007020, 0x20, 0xFE0, 0x10007000, getMMU()) // Image of 0x10007000.
		);

		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D0_CHCR);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D0_MADR);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D0_QWC);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D0_TADR);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D0_ASR0);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D0_ASR1);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_DMAC_8060);

		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D1_CHCR);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D1_MADR);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D1_QWC);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D1_TADR);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D1_ASR0);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D1_ASR1);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_DMAC_9060);

		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D2_CHCR);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D2_MADR);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D2_QWC);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D2_TADR);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D2_ASR0);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D2_ASR1);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_DMAC_a060);

		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D3_CHCR);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D3_MADR);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D3_QWC);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_DMAC_b030);

		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D4_CHCR);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D4_MADR);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D4_QWC);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D4_TADR);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_DMAC_b440);

		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D5_CHCR);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D5_MADR);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D5_QWC);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_DMAC_c030);

		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D6_CHCR);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D6_MADR);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D6_QWC);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D6_TADR);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_DMAC_c440);

		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D7_CHCR);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D7_MADR);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D7_QWC);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_DMAC_c830);

		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D8_CHCR);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D8_MADR);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D8_QWC);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_DMAC_d030);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D8_SADR);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_DMAC_d090);

		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D9_CHCR);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D9_MADR);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D9_QWC);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D9_TADR);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_DMAC_d440);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D9_SADR);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_DMAC_d490);

		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D_CTRL);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D_STAT);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D_PCR);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D_SQWC);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D_RBSR);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D_RBOR);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D_STADR);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_DMAC_e070);

		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_I_STAT);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_I_MASK);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_INTC_f020);

		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_SIO);

		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_SB_SMFLG);

		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_F400);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_F410);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_F420);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_MCH);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_F450);

		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_F500);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D_ENABLER);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_F530);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_D_ENABLEW);
		getMMU()->mapMemory(getResources()->EE->EE_REGISTER_F5A0);

		getMMU()->mapMemory(getResources()->EE->VU_MEM_VU0Micro0);
		getMMU()->mapMemory(
			std::make_shared<ImageStorageObject_t>("Image: 0x11000000", 0x11001000, 0x1000, 0x3000, 0x11000000, getMMU()) // Image of 0x11000000.
		);
		getMMU()->mapMemory(getResources()->EE->VU_MEM_VU0Mem0);
		getMMU()->mapMemory(
			std::make_shared<ImageStorageObject_t>("Image: 0x11004000", 0x11005000, 0x1000, 0x3000, 0x11004000, getMMU()) // Image of 0x11004000.
		);
		getMMU()->mapMemory(getResources()->EE->VU_MEM_VU1Micro1);
		getMMU()->mapMemory(getResources()->EE->VU_MEM_VU1Mem1);
		getMMU()->mapMemory(getResources()->EE->VU_MEM_VU1BusErr);
	}

	// GS Privileged Registers.
	{
		getMMU()->mapMemory(getResources()->GS->GS_P_REGISTER_PMODE);
		getMMU()->mapMemory(getResources()->GS->GS_P_REGISTER_SMODE1);
		getMMU()->mapMemory(getResources()->GS->GS_P_REGISTER_SMODE2);
		getMMU()->mapMemory(getResources()->GS->GS_P_REGISTER_SRFSH);
		getMMU()->mapMemory(getResources()->GS->GS_P_REGISTER_SYNCH1);
		getMMU()->mapMemory(getResources()->GS->GS_P_REGISTER_SYNCH2);
		getMMU()->mapMemory(getResources()->GS->GS_P_REGISTER_SYNCV);
		getMMU()->mapMemory(getResources()->GS->GS_P_REGISTER_DISPFB1);
		getMMU()->mapMemory(getResources()->GS->GS_P_REGISTER_DISPLAY1);
		getMMU()->mapMemory(getResources()->GS->GS_P_REGISTER_DISPFB2);
		getMMU()->mapMemory(getResources()->GS->GS_P_REGISTER_DISPLAY2);
		getMMU()->mapMemory(getResources()->GS->GS_P_REGISTER_EXTBUF);
		getMMU()->mapMemory(getResources()->GS->GS_P_REGISTER_EXTDATA);
		getMMU()->mapMemory(getResources()->GS->GS_P_REGISTER_EXTWRITE);
		getMMU()->mapMemory(getResources()->GS->GS_P_REGISTER_BGCOLOR);
		getMMU()->mapMemory(getResources()->GS->GS_P_REGISTER_SPE_00f0);
		getMMU()->mapMemory(
			std::make_shared<ImageStorageObject_t>("Image: 0x12000000", 0x12000400, 0x400, 0x400, 0x12000000, getMMU()) // Image of 0x12000000.
		);
		getMMU()->mapMemory(
			std::make_shared<ImageStorageObject_t>("Image: 0x12000000", 0x12000800, 0x800, 0x800, 0x12000000, getMMU()) // Image of 0x12000000.
		);

		getMMU()->mapMemory(getResources()->GS->GS_P_REGISTER_CSR);
		getMMU()->mapMemory(getResources()->GS->GS_P_REGISTER_IMR);
		getMMU()->mapMemory(getResources()->GS->GS_P_REGISTER_SPE_1020);
		getMMU()->mapMemory(getResources()->GS->GS_P_REGISTER_BUSDIR);
		getMMU()->mapMemory(getResources()->GS->GS_P_REGISTER_SPE_1050);
		getMMU()->mapMemory(getResources()->GS->GS_P_REGISTER_SIGLBLID);
		getMMU()->mapMemory(getResources()->GS->GS_P_REGISTER_SPE_1090);
		getMMU()->mapMemory(getResources()->GS->GS_P_REGISTER_SPE_1100);
		getMMU()->mapMemory(
			std::make_shared<ImageStorageObject_t>("Image: 0x12001000", 0x12001400, 0x400, 0x400, 0x12001000, getMMU()) // Image of 0x12001000.
		);
		getMMU()->mapMemory(
			std::make_shared<ImageStorageObject_t>("Image: 0x12001000", 0x12001800, 0x800, 0x800, 0x12001000, getMMU()) // Image of 0x12001000.
		);

		getMMU()->mapMemory(getResources()->GS->GS_P_REGISTER_SPE_2000);
		getMMU()->mapMemory(getResources()->GS->GS_P_REGISTER_SPEBusErr);
	}
}

void VMMain::initaliseExecutionCore()
{
	switch (mExecutionCoreType)
	{
	case ExecutionCoreType::INTERPRETER:
	{
		mExecutionCoreComponent = std::make_unique<Interpreter>(this);
		break;
	}
	case ExecutionCoreType::RECOMPILER:
	{
		// TODO: Implement.
		break;
	}
	}
}

void VMMain::initaliseBootROM() const
{
	char * memoryBase = reinterpret_cast<char*>(getResources()->BootROM->getClientMemoryAddress());
	std::ifstream file(mBootROMPath, std::ifstream::binary);
	if (file.fail()) 
		throw std::runtime_error("initaliseBootROM(): tried to open BIOS file, but it failed! Check file exists and has read permissions.");
	file.seekg(std::ifstream::beg);
	file.read(memoryBase, PS2Constants::BootROM::SIZE_BOOT_ROM);
}
