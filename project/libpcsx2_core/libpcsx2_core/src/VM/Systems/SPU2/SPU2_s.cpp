#include "Common/Global/Globals.h"
#include "Common/Types/FIFOQueue/FIFOQueue_t.h"
#include "Common/Types/Memory/HwordMemory_t.h"
#include "Common/Tables/SPU2CoreTable.h"
#include "Common/Types/Register/Register16_t.h"
#include "Common/Types/Register/PairRegister16_t.h"

#include "VM/VM.h"
#include "VM/Systems/SPU2/SPU2_s.h"

#include "Resources/Resources_t.h"
#include "Resources/Common/Common_t.h"
#include "Resources/IOP/INTC/IOPIntc_t.h"
#include "Resources/IOP/INTC/Types/IOPIntcRegisters_t.h"
#include "Resources/IOP/IOP_t.h"
#include "Resources/SPU2/SPU2_t.h"
#include "Resources/SPU2/Types/SPU2Registers_t.h"
#include "Resources/SPU2/Types/SPU2Cores_t.h"
#include "Resources/SPU2/Types/SPU2CoreRegisters_t.h"
#include "Resources/SPU2/Types/SPU2CoreVoices_t.h"
#include "Resources/SPU2/Types/SPU2CoreVoiceRegisters_t.h"

SPU2_s::SPU2_s(VM * vm) : 
	VMSystem_t(vm, Context_t::SPU2)
{
	mSPU2 = getVM()->getResources()->SPU2;
	mINTC = getVM()->getResources()->IOP->INTC;
}

void SPU2_s::initialise()
{

}

int SPU2_s::step(const Event_t & event)
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

	// Do an interrupt check, and send signal to the IOP INTC if needed.
	handleInterruptCheck();

	// SPU2 has completed 1 cycle.
#if ACCURACY_SKIP_TICKS_ON_NO_WORK
	if (!workDone)
		return event.mQuantity;
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

	int dmaCount = 0;
	switch (mCore->ATTR->getFieldValue(getContext(), SPU2CoreRegister_ATTR_t::Fields::DMAMode))
	{
	case 0:
		// Auto DMA write mode.
		if (mCore->isADMAEnabled(getContext())) 
			dmaCount = transferData_ADMA_Write(); 
		break;
	case 1:
		// Auto DMA read mode. 
		if (mCore->isADMAEnabled(getContext()))
			dmaCount = transferData_ADMA_Read();
		break;
	case 2:
		// Manual DMA write mode.
		dmaCount = transferData_MDMA_Write();
		break;
	case 3:
		// Manual DMA read mode.
		dmaCount = transferData_MDMA_Read();
		break;
	default:
		throw std::runtime_error("SPU2 could not determine DMA mode. Please fix.");
	}

	return (dmaCount > 0);
}

bool SPU2_s::handleSoundGeneration()
{
	// Check if core is enabled and do sound generation.
	if (mCore->ATTR->getFieldValue(getContext(), SPU2CoreRegister_ATTR_t::Fields::CoreEnable))
	{
		// Check if we are running out of data - that the end of data is less than 0x200 hwords away. Set STATX on this condition and send an interrupt (or clear it otherwise).
		// TODO: Check the logic and implement. Might need to set the IOP DMAC interrupt bit for the current core (a bit weird)? See SPU2-X/ReadInput.cpp (V_Core::ReadInput()).
		static int hackCount = 0;
		if ((++hackCount) % 2000 < 1000) 
		{
			mCore->STATX->setFieldValue(getContext(), SPU2CoreRegister_STATX_t::Fields::NeedData, 1);
			// mDMAC->ICR{0,1}->setFieldValue(getContext(), IOPDmacRegister_ICR{0,1}_t::Fields::TCI{...}, 1);
		}
		else
		{
			mCore->STATX->setFieldValue(getContext(), SPU2CoreRegister_STATX_t::Fields::NeedData, 0);
		}

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
	// TODO: Check this, its probably wrong. The write addresses are also meant to be used in conjunction with the current read address (double buffer).
	// TSA is not used here! The write addresses are fixed. See pages 13, 28 and 55 of the SPU2 Overview manual.

	// Check for incoming data and read it in, otherwise exit early as theres nothing to do.
	u16 data;
	if (!mCore->FIFOQueue->read(getContext(), reinterpret_cast<u8*>(&data), Constants::NUMBER_BYTES_IN_HWORD))
	{
		// TODO: check this especially!!!
		// Need to also clear the STATX.NeedData bit when out of data.
		mCore->STATX->setFieldValue(getContext(), SPU2CoreRegister_STATX_t::Fields::NeedData, 0);
		return 0;
	}

	// Depending on the current transfer count, we are in the left or right sound channel data block (from SPU2-X/Dma.cpp).
	// Data incoming is in a striped pattern with 0x100 hwords for the left channel, followed by 0x100 hwords for the right channel, repeated.
	int block = mCore->ATTR->mDMAOffset / 0x100;
	bool inLeftBlock = ((block % 2) == 0);
	u32 channelOffset;
	if (inLeftBlock)
		channelOffset = mCore->ATTR->mDMAOffset - (block / 2) * 0x100;
	else
		channelOffset = mCore->ATTR->mDMAOffset - (block / 2 + 1) * 0x100;

	// ADMA is limited to a hword space of 0x200 for each sound channel (left and right).
	channelOffset %= 0x200;

	// Calculate final address.
	u32 address;
	if (inLeftBlock)
		address = mCore->getInfo()->mBaseTSALeft + channelOffset;
	else
		address = mCore->getInfo()->mBaseTSARight + channelOffset;

	// Make sure address is not outside 2MB limit (remember, we are addressing by hwords).
	address %= 0x100000;

	// Write to SPU2 memory.
	writeHwordMemory(address, data);

	// Increment the transfer count.
	mCore->ATTR->mDMAOffset += 1;
	
	// ADMA has completed one transfer.
	return 1;
}

int SPU2_s::transferData_ADMA_Read() const
{
	throw std::runtime_error("SPU2 ADMA read not yet implemented. Look into the ATTR.DMAMode bits, as this might be incorrectly called.");
}

int SPU2_s::transferData_MDMA_Write() const
{
	// TODO: Check this!

	// Check for incoming data and read it in, otherwise exit early as theres nothing to do.
	u16 data;
	if (!mCore->FIFOQueue->read(getContext(), reinterpret_cast<u8*>(&data), Constants::NUMBER_BYTES_IN_HWORD))
	{
		// TODO: check this especially!!!
		// Need to also clear the STATX.NeedData bit when out of data.
		mCore->STATX->setFieldValue(getContext(), SPU2CoreRegister_STATX_t::Fields::NeedData, 0);
		return 0;
	}

	// Calculate write address. Make sure address is not outside 2MB limit (remember, we are addressing by hwords).
	u32 address = (mCore->TSAL->readPairWord(getContext()) + mCore->ATTR->mDMAOffset) % 0x100000;

	// Write to SPU2 memory.
	writeHwordMemory(address, data);

	// Increment the transfer count.
	mCore->ATTR->mDMAOffset += 1;
	
	// ADMA has completed one transfer.
	return 1;
}

int SPU2_s::transferData_MDMA_Read() const
{
	throw std::runtime_error("SPU2 MDMA read not yet implemented. Look into the ATTR.DMAMode bits, as this might be incorrectly called.");
}

u16 SPU2_s::readHwordMemory(const u32 hwordPhysicalAddress) const
{
	// Check for IRQ conditions by comparing the address given with the IRQA register pair. Set IRQ if they match.
	u32 irqAddr = mCore->IRQAL->readPairWord(getContext());
	if (irqAddr == hwordPhysicalAddress)
		mSPU2->SPDIF_IRQINFO->setFieldValue(getContext(), SPU2Register_SPDIF_IRQINFO_t::Fields::IRQ_KEYS[mCore->getCoreID()], 1);

	return mSPU2->MainMemory->readHword(getContext(), hwordPhysicalAddress);
}

void SPU2_s::writeHwordMemory(const u32 hwordPhysicalAddress, const u16 value) const
{
	// Check for IRQ conditions by comparing the address given with the IRQA register pair. Set IRQ if they match.
	u32 irqAddr = mCore->IRQAL->readPairWord(getContext());
	if (irqAddr == hwordPhysicalAddress)
		mSPU2->SPDIF_IRQINFO->setFieldValue(getContext(), SPU2Register_SPDIF_IRQINFO_t::Fields::IRQ_KEYS[mCore->getCoreID()], 1);

	mSPU2->MainMemory->writeHword(getContext(), hwordPhysicalAddress, value);
}

void SPU2_s::handleInterruptCheck() const
{
	if (mSPU2->SPDIF_IRQINFO->isInterrupted(getContext()))
	{
		// IRQ was set, notify the IOP INTC.
		mINTC->STAT->setFieldValue(getContext(), IOPIntcRegister_STAT_t::Fields::SPU, 1);
	}
}