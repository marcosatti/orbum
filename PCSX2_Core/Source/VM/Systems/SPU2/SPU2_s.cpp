#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/FIFOQueue/FIFOQueue32_t.h"
#include "Common/Types/Memory/HwordMemory_t.h"
#include "Common/Tables/SPU2CoreTable.h"

#include "VM/VM.h"
#include "VM/Systems/SPU2/SPU2_s.h"

#include "Resources/Resources_t.h"
#include "Resources/Common/Common_t.h"
#include "Resources/IOP/INTC/IOPIntc_t.h"
#include "Resources/IOP/INTC/Types/IOPIntcRegisters_t.h"
#include "Resources/IOP/IOP_t.h"
#include "Resources/SPU2/SPU2_t.h"
#include "Resources/SPU2/Types/SPU2Cores_t.h"
#include "Resources/SPU2/Types/SPU2CoreRegisters_t.h"
#include "Resources/SPU2/Types/SPU2CoreVoices_t.h"
#include "Resources/SPU2/Types/SPU2CoreVoiceRegisters_t.h"

SPU2_s::SPU2_s(VM * vm) : 
	VMSystem_s(vm, System_t::SPU2)
{
	mSPU2 = getVM()->getResources()->SPU2;
	mINTC = getVM()->getResources()->IOP->INTC;
}

void SPU2_s::initalise()
{

}

int SPU2_s::step(const ClockSource_t clockSource, const int ticksAvailable)
{
#if ACCURACY_SKIP_TICKS_ON_NO_WORK
	// Used to skip ticks. If no DMA transfer happened, or sound generation was not performed
	//  then all of the ticks will be consumed.
	bool workDone = false;
#endif

	// For each core (core 0 and core 1), run through DMA transfers and sound generation.
	for (auto& core : mSPU2->CORES)
	{
		// Set context.
		mCore = core.get();

#if ACCURACY_SKIP_TICKS_ON_NO_WORK
		workDone |= handleDMATransfer();
		workDone |= handleSoundGeneration();
#else
		handleDMATransfer();
		handleSoundGeneration();
#endif
	}

	// SPU2 has completed 1 cycle.
#if ACCURACY_SKIP_TICKS_ON_NO_WORK
	if (!workDone)
		return ticksAvailable;
	else
		return 1;
#else
	return 1;
#endif
}

bool SPU2_s::handleDMATransfer()
{
	// Check which DMA mode we are in, based on the ATTR.DMAMode bits. Either manual DMA read/writes or auto DMA read/writes are possible.
	// If we are using auto DMA, the ADMAS register still needs to be set properly.
	// TODO: Not sure this is actually correct - I am lead to believe it is like this because of Nocash's psx docs (SPUCNT.SoundTxferMode), and it works.
	// TODO: Currently, reading from the SPU2 memory is unsupported. Although it is implemented in PCSX2/SPU2-X, I haven't been able to trigger it.
	//       In terms of the ATTR register, manual/auto DMA read mode probably sets it to 0b01xxxx or 0b11xxxx respectively, so these are set to throw an error for now.
	// TODO: I do not know what the "DMABits" field is for, but probably doesn't matter after looking at SPU2-X code (not needed?). Probably not even related to DMA...
	//       Nocash PSX docs says related to other things, such as CD audio (SPUCNT)... 
	if (mCore->ATTR->getFieldValue(getContext(), SPU2CoreRegister_ATTR_t::Fields::DMABits > 0))
		throw std::runtime_error("SPU2 ATTR DMABits field set to non-zero. What is this for?");

	bool dmaPerformed = false;
	switch (mCore->ATTR->getFieldValue(getContext(), SPU2CoreRegister_ATTR_t::Fields::DMAMode > 0))
	{
	case 0:
		// Auto DMA write mode.
		if (mCore->isADMAEnabled(getContext())) 
			dmaPerformed = transferData_ADMA_Write(); 
		break;
	case 1:
		// Auto DMA read mode. 
		if (mCore->isADMAEnabled(getContext()))
			dmaPerformed = transferData_ADMA_Read();
		break;
	case 2:
		// Manual DMA write mode.
		dmaPerformed = transferData_MDMA_Write(); 
		break;
	case 3:
		// Manual DMA read mode.
		dmaPerformed = transferData_MDMA_Read(); 
		break;
	default:
		throw std::runtime_error("SPU2 could not determine DMA mode. Please fix.");
	}

	return dmaPerformed;
}

bool SPU2_s::handleSoundGeneration()
{
	// Check if core is enabled and do sound generation.
	if (mCore->ATTR->getFieldValue(getContext(), SPU2CoreRegister_ATTR_t::Fields::CoreEnable))
	{
		return false; 
	}
	else
	{
		// No sound generation was performed.
		return false;
	}
}

int SPU2_s::transferData_ADMA_Write() const
{
	// Only transfer if data is available.
	if (mCore->FIFOQueue->getCurrentSize() > 0)
	{
		// Get the source or destination transfer start address (TSAL/H). The address is always relative to the base addresses in the SPU2 memory.
		// See page 28 of the SPU2 Overview manual for these base addresses.
		u32 TSA = ((mCore->TSAH->readHword(getContext()) << 16) | mCore->TSAL->readHword(getContext()));

		// ADMA write data is split up into the left and right sound channels, and stored at different locations.
		u32 leftAddr = mCore->getInfo()->mBaseTSALeft + TSA;
		u32 rightAddr = mCore->getInfo()->mBaseTSARight + TSA;

		// Perform write from FIFO to memory for left then right channels.
		u32 data = mCore->FIFOQueue->readWord(getContext());
		mSPU2->MainMemory->writeWord(getContext(), leftAddr, data);

		// Reduce the transfer count.
		mCore->ADMAS->mCount -= 1;

		return 1;
	}
	else
	{
		return 0;
	}
}

int SPU2_s::transferData_ADMA_Read() const
{
	throw std::runtime_error("SPU2 ADMA read not yet implemented. Look into the ATTR.DMAMode bits, as this might be incorrectly called.");
}

int SPU2_s::transferData_MDMA_Write() const
{
	throw std::runtime_error("SPU2 MDMA write not yet implemented. Look into the ATTR.DMAMode bits, as this might be incorrectly called.");
}

int SPU2_s::transferData_MDMA_Read() const
{
	throw std::runtime_error("SPU2 MDMA read not yet implemented. Look into the ATTR.DMAMode bits, as this might be incorrectly called.");
}