#include "stdafx.h"

#include "Common/Types/Context_t.h"
#include "Common/Types/PhysicalMMU/PhysicalMMU_t.h"
#include "Common/Tables/IOPDmacChannelTable/IOPDmacChannelTable.h"
#include "Common/Types/FIFOQueue/FIFOQueue_t.h"

#include "VM/ExecutionCore/Common/IOP/DMAC/IOPDmac.h"

#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/IOP/IOP_t.h"
#include "PS2Resources/IOP/INTC/IOPIntc_t.h"
#include "PS2Resources/IOP/INTC/Types/IOPIntcRegisters_t.h"
#include "PS2Resources/IOP/DMAC/IOPDmac_t.h"
#include "PS2Resources/IOP/DMAC/Types/IOPDmacChannelRegisters_t.h"
#include "PS2Resources/IOP/DMAC/Types/IOPDmacChannels_t.h"
#include "PS2Resources/IOP/DMAC/Types/IOPDmacRegisters_t.h"

using LogicalMode_t = IOPDmacChannelTable::LogicalMode_t;
using Direction_t = IOPDmacChannelTable::Direction_t;

IOPDmac::IOPDmac(VMMain* vmMain) :
	VMExecutionCoreComponent(vmMain),
	mChannelIndex(0),
	mChannel(nullptr)
{
	// Set resource pointer variables.
	mDMAC = getResources()->IOP->DMAC;
	mINTC = getResources()->IOP->INTC;
	mIOPPhysicalMMU = getResources()->IOP->PhysicalMMU;
}

IOPDmac::~IOPDmac()
{
}

s64 IOPDmac::executionStep(const ClockSource_t& clockSource)
{
	// Run through each channel enabled. Note there is no master DMAC enable bit to check - only the individual channels.
	for (mChannelIndex = 0; mChannelIndex < PS2Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS; mChannelIndex++)
	{
		// Set context variables.
		mChannel = &(*mDMAC->CHANNELS[mChannelIndex]); // I give up, for now I need the speed for debugging. Change back later & sort out why this is so slow.

		// Check if channel is enabled for transfer (both from PCR and the CHCR).
		if (isDMACChannelEnabled() && (mChannel->CHCR->getFieldValue(IOPDmacChannelRegister_CHCR_t::Fields::START_B) > 0))
		{
			switch (mChannel->getRuntimeLogicalMode())
			{
			case LogicalMode_t::NORMAL:
			{
				// Normal mode.
				executionStep_Normal();
				break;
			}
			case LogicalMode_t::BLOCK: 
			{
				// Block mode ("sync blocks to DMA requests"). 
				// Due to the emulator implementation, logic is not different to normal mode.
				executionStep_Normal();
				break;
			}
			case LogicalMode_t::LINKEDLIST:
			{
				// Linked list mode.
				throw std::runtime_error("IOP DMAC linked list mode not implemented.");
			}
			case LogicalMode_t::RESERVED:
			{
				// Reserved (not defined).
				throw std::runtime_error("IOP DMAC channel had reserved operating mode.");
			}
			default:
			{
				throw std::runtime_error("Could not determine IOP DMAC channel operating mode.");
			}
			}
		}
	}

	// Check for D_ICR interrupt bit status, send interrupt to IOP INTC (IRQ 3) if not masked.
	handleInterruptCheck();
	
	return 1;
}

void IOPDmac::executionStep_Normal()
{
	// Transfer a data unit (32-bits). If no data was transfered, try again next cycle.
	u32 dataCount = transferData();
	if (!dataCount)
	{
		return;
	}

	// Check if BCR.BS == 0 (transfer completed), in which case stop transferring and update status.
	if (mChannel->BCR->getFieldValue(IOPDmacChannelRegister_BCR_t::Fields::BS) == 0)
	{
		setStateSuspended();
	}
}

bool IOPDmac::isDMACChannelEnabled() const
{
	u32 pcrGroup = mChannelIndex / 7;
	u32 pcrIndex = mChannelIndex % 7;

	return (mDMAC->PCRS[pcrGroup]->getFieldValue(IOPDmacRegister_PCR_t::Fields::ENA_KEYS[pcrIndex]) > 0);
}

void IOPDmac::handleInterruptCheck() const
{
	bool interrupt = false;
	for (auto& ICR : mDMAC->ICRS)
		interrupt |= ICR->isInterrupted();

	if (interrupt)
	{
		// DMAC connected to INTC IRQ line 3.
		// TODO: Assuming edge triggered interrupt. Need to deassert line on no condition?
		mINTC->STAT->raiseIRQLine(3);
	}
}

u32 IOPDmac::transferData() const
{
	// Determine the direction of data flow. 
	Direction_t direction = static_cast<Direction_t>(mChannel->CHCR->getFieldValue(IOPDmacChannelRegister_CHCR_t::Fields::TD));

	// Get the main memory address.
	const u32 PhysicalAddressOffset = mChannel->MADR->readWord(Context_t::RAW);

	// Transfer data to or from the FIFO queue.
	if (direction == Direction_t::FROM)
	{
		// Check if channel does not have data ready - need to try again next cycle.
		if (mChannel->mFIFOQueue->isEmpty())
			return 0;

		u32 packet = mChannel->mFIFOQueue->readWord(Context_t::RAW);
		writeDataMemory(PhysicalAddressOffset, packet);
	}
	else if (direction == Direction_t::TO)
	{
		// Check if channel is full - need to try again next cycle.
		if (mChannel->mFIFOQueue->isFull())
			return 0;

		u32 packet = readDataMemory(PhysicalAddressOffset);
		mChannel->mFIFOQueue->writeWord(Context_t::RAW, packet);
	}

	// Increment or decrement (depending on CHCR.MAS) the MADR register by a word.
	if (mChannel->CHCR->getFieldValue(IOPDmacChannelRegister_CHCR_t::Fields::MAS) == 0)
		mChannel->MADR->increment();
	else
		mChannel->MADR->decrement();

	// Update number of units/blocks left (BCR).
	mChannel->BCR->decrement();

	return 1;
}

void IOPDmac::setStateSuspended() const
{
	// Stop channel.
	mChannel->CHCR->setFieldValue(IOPDmacChannelRegister_CHCR_t::Fields::START_B, 0);

	// Emit interrupt stat bit.
	u32 icrIndex = mChannelIndex % 7;
	if (mChannelIndex < 8)
		mDMAC->ICR->raiseIRQLine(icrIndex);
	else
		mDMAC->ICR2->raiseIRQLine(icrIndex);
}

void IOPDmac::setStateFailedTransfer() const
{
	throw std::runtime_error("IOP DMAC failed transfer not implemented.");
}

u32 IOPDmac::readDataMemory(u32 PhysicalAddressOffset) const
{
	return mIOPPhysicalMMU->readWord(Context_t::RAW, PhysicalAddressOffset);
}

void IOPDmac::writeDataMemory(u32 PhysicalAddressOffset, u32 data) const
{
	mIOPPhysicalMMU->writeWord(Context_t::RAW, PhysicalAddressOffset, data);
}
