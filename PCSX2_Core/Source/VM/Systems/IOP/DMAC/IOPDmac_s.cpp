#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/PhysicalMMU/PhysicalMMU_t.h"
#include "Common/Tables/IOPDmacChannelTable/IOPDmacChannelTable.h"
#include "Common/Types/FIFOQueue/FIFOQueue_t.h"

#include "VM/VM.h"
#include "VM/Systems/IOP/DMAC/IOPDmac_s.h"

#include "Resources/Resources_t.h"
#include "Resources/IOP/IOP_t.h"
#include "Resources/IOP/INTC/IOPIntc_t.h"
#include "Resources/IOP/INTC/Types/IOPIntcRegisters_t.h"
#include "Resources/IOP/DMAC/IOPDmac_t.h"
#include "Resources/IOP/DMAC/Types/IOPDmacChannelRegisters_t.h"
#include "Resources/IOP/DMAC/Types/IOPDmacChannels_t.h"
#include "Resources/IOP/DMAC/Types/IOPDmacRegisters_t.h"

using ChannelProperties_t = IOPDmacChannelTable::ChannelProperties_t;
using LogicalMode_t = IOPDmacChannelTable::LogicalMode_t;
using Direction_t = IOPDmacChannelTable::Direction_t;

IOPDmac_s::IOPDmac_s(VM * vm) :
	VMSystem_s(vm, System_t::IOPDmac),
	mChannel(nullptr)
{
	// Set resource pointer variables.
	mDMAC = getVM()->getResources()->IOP->DMAC;
	mINTC = getVM()->getResources()->IOP->INTC;
	mIOPPhysicalMMU = getVM()->getResources()->IOP->PhysicalMMU;
}

IOPDmac_s::~IOPDmac_s()
{
}

int IOPDmac_s::step(const ClockSource_t clockSource, const int ticksAvailable)
{
	// Check if DMA transfers are enabled. If not, DMAC has nothing to do.
	if (mDMAC->GCTRL->readWord(RAW) > 0)
	{
		// Run through each channel enabled. Note there is no master DMAC enable bit to check - only the individual channels.
		for (auto& channel : mDMAC->CHANNELS)
		{
			// Set channel resource context.
			mChannel = channel.get();

			// Check if channel is enabled for transfer (both from PCR and the CHCR).
			if (isChannelEnabled())
			{
				switch (mChannel->CHCR->getLogicalMode())
				{
				case LogicalMode_t::NORMAL:
				{
					// Normal mode.
					transferNormal();
					break;
				}
				case LogicalMode_t::BLOCK:
				{
					// Block mode ("sync blocks to DMA requests"). 
					// Due to the emulator implementation, logic is not different to normal mode. TODO: verify?
					transferNormal();
					break;
				}
				case LogicalMode_t::LINKEDLIST:
				{
					// Linked list mode.
					throw std::runtime_error("IOP DMAC linked list mode not implemented.");
				}
				case LogicalMode_t::CHAIN:
				{
					// Reserved (not defined).
					throw std::runtime_error("IOP DMAC channel had chain operating mode.");
				}
				default:
				{
					throw std::runtime_error("Could not determine IOP DMAC channel logical mode.");
				}
				}
			}
		}

		// Check for ICR0 or ICR1 interrupt bit status, send interrupt to IOP INTC (IRQ 3) if not masked.
		handleInterruptCheck();
	}
	
	return 1;
}

void IOPDmac_s::transferNormal() const
{
	// Transfer a data unit (32-bits). If no data was transfered, try again next cycle.
	if (!transferData())
		return;

	// Check if there is no more data to process, in which case stop transferring and update status.
	if (mChannel->BCR->isFinished(false))
		setStateSuspended();
}

void IOPDmac_s::handleInterruptCheck() const
{
	// Check ICR0 and ICR1 for interrupt status, else clear the master interrupt and INTC bits.
	if (mDMAC->ICR0->isInterruptPending() || mDMAC->ICR1->isInterruptPending())
		mINTC->STAT->setFieldValue(IOPIntcRegister_STAT_t::Fields::DMA, 1);
	else
	{
		mDMAC->ICR0->setFieldValue(IOPDmacRegister_ICR0_t::Fields::MasterInterrupt, 0);
		mINTC->STAT->setFieldValue(IOPIntcRegister_STAT_t::Fields::DMA, 0);
	}
}

int IOPDmac_s::transferData() const
{
	// Determine the direction of data flow. 
	Direction_t direction = mChannel->CHCR->getDirection();

	// Get the main memory address.
	const u32 physicalAddress = mChannel->MADR->readWord(RAW);

	// Transfer data to or from the FIFO queue.
	if (direction == Direction_t::FROM)
	{
		// Check if channel does not have data ready - need to try again next cycle.
		if (mChannel->mFIFOQueue->isEmpty())
			return 0;

		u32 packet = mChannel->mFIFOQueue->readWord(RAW);
		writeDataMemory(physicalAddress, packet);

		log(Debug, "IOP DMAC Read u32 channel %s, value = 0x%08X -> MemAddr = 0x%08X", mChannel->getChannelProperties()->mMnemonic, packet, physicalAddress);
	}
	else if (direction == Direction_t::TO)
	{
		// Check if channel is full - need to try again next cycle.
		if (mChannel->mFIFOQueue->isFull())
			return 0;

		u32 packet = readDataMemory(physicalAddress);
		mChannel->mFIFOQueue->writeWord(RAW, packet);

		log(Debug, "IOP DMAC Write u32 channel %s, value = 0x%08X <- MemAddr = 0x%08X", mChannel->getChannelProperties()->mMnemonic, packet, physicalAddress);
	}
	else
	{
		throw std::runtime_error("IOP DMAC could not determine direction! Please debug.");
	}

	// Increment or decrement (depending on CHCR.MAS) the MADR register by a word.
	if (mChannel->CHCR->getFieldValue(IOPDmacChannelRegister_CHCR_t::Fields::MAS) == 0)
		mChannel->MADR->increment();
	else
		mChannel->MADR->decrement();

	// Update number of word units left (BCR).
	mChannel->BCR->decrement();

	return 1;
}

void IOPDmac_s::setStateSuspended() const
{
	// Stop channel.
	mChannel->CHCR->setFieldValue(IOPDmacChannelRegister_CHCR_t::Fields::Start, 0);

	// Emit interrupt stat bit (use ICR0 or ICR1 based on channel index).
	if (mChannel->getChannelID() < 7)
		mDMAC->ICR0->setFieldValue(IOPDmacRegister_ICR0_t::Fields::CHANNEL_TCI_KEYS[mChannel->getChannelID()], 1);
	else
		mDMAC->ICR1->setFieldValue(IOPDmacRegister_ICR1_t::Fields::CHANNEL_TCI_KEYS[mChannel->getChannelID() % 7], 1);
}

bool IOPDmac_s::isChannelEnabled() const
{
	if (mChannel->CHCR->getFieldValue(IOPDmacChannelRegister_CHCR_t::Fields::Start) > 0)
	{
		if (mChannel->getChannelID() < 7)
			return (mDMAC->PCR0->getFieldValue(IOPDmacRegister_PCR0_t::Fields::CHANNEL_ENABLE_KEYS[mChannel->getChannelID()]) > 0);
		else
			return (mDMAC->PCR1->getFieldValue(IOPDmacRegister_PCR1_t::Fields::CHANNEL_ENABLE_KEYS[mChannel->getChannelID() % 7]) > 0);
	}
	else
	{
		return false;
	}
}

u32 IOPDmac_s::readDataMemory(u32 PhysicalAddressOffset) const
{
	return mIOPPhysicalMMU->readWord(RAW, PhysicalAddressOffset);
}

void IOPDmac_s::writeDataMemory(u32 PhysicalAddressOffset, u32 data) const
{
	mIOPPhysicalMMU->writeWord(RAW, PhysicalAddressOffset, data);
}
