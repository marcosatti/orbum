
#include "Common/Types/Bus/ByteBus.hpp"
#include "Common/Tables/IOPDmacChannelTable.h"
#include "Common/Types/FifoQueue/SpscFifoQueue.h"

#include "VM/VM.h"
#include "VM/Systems/IOP/DMAC/IOPDmac_s.h"

#include "Resources/RResources.hpp"
#include "Resources/IOP/IOP_t.h"
#include "Resources/Iop/Intc/RIopIntc.hpp"
#include "Resources/IOP/INTC/Types/IOPIntcRegisters_t.h"
#include "Resources/IOP/DMAC/IOPDmac_t.h"
#include "Resources/Iop/Dmac/IopDmacChannelRegisters.hpp"
#include "Resources/Iop/Dmac/IopDmacChannels.hpp"
#include "Resources/Iop/Dmac/IopDmacRegisters.hpp"

using LogicalMode_t = IOPDmacChannelTable::LogicalMode_t;
using Direction = IOPDmacChannelTable::Direction;

IOPDmac_s::IOPDmac_s(VM * vm) :
	VMSystem_t(vm, Context_t::IOPDmac),
	mChannel(nullptr),
	mDMAtag(0, 0)
{
	// Set resource pointer variables.
	mDMAC = getVM()->getResources()->IOP->DMAC;
	mINTC = getVM()->getResources()->IOP->INTC;
	mIOPByteMMU = getVM()->getResources()->IOP->MMU;
}

void IOPDmac_s::initialise()
{
	// Reset channels.
	for (auto& channel : mDMAC->CHANNELS)
	{
		if (channel->CHCR != nullptr) channel->CHCR->initialise();
		if (channel->MADR != nullptr) channel->MADR->initialise();
		if (channel->BCR != nullptr) channel->BCR->initialise();
		if (channel->TADR != nullptr) channel->TADR->initialise();
		if (channel->FifoQueue != nullptr) channel->FifoQueue->initialise();
	}

	// Reset DMAC.
	mDMAC->PCR0->initialise();
	mDMAC->ICR0->initialise();
	mDMAC->PCR1->initialise();
	mDMAC->ICR1->initialise();
	mDMAC->GCTRL->initialise();
}

int IOPDmac_s::step(const Event_t & event)
{
	// Used to skip ticks. If no channel is enabled for transfers, then all of the ticks will be consumed at the end.
	bool workDone = false;

	// Check if DMA transfers are enabled. If not, DMAC has nothing to do.
	if (mDMAC->GCTRL->read_uword() > 0)
	{
		// Run through each channel enabled. Note there is no master DMAC enable bit to check - only the individual channels.
		for (auto& channel : mDMAC->CHANNELS)
		{
			// Set channel resource context.
			mChannel = channel.get();

			// Check if channel is enabled for transfer (both from PCR and the CHCR).
			if ((mDMAC->PCRW->is_channel_enabled(, mChannel)) 
				&& (mChannel->CHCR->getFieldValue(, IopDmacChannelRegister_Chcr::Start) > 0))
			{
				switch (mChannel->CHCR->logical_mode())
				{
				case LogicalMode_t::NORMAL_BURST:
				{
					// Normal/burst mode.
					workDone |= transferNormalBurst();
					break;
				}
				case LogicalMode_t::NORMAL_SLICE:
				{
					// Normal/slice mode.
					workDone |= transferNormalSlice();
					break;
				}
				case LogicalMode_t::LINKEDLIST:
				{
					// Linked list mode.
					throw std::runtime_error("IOP DMAC linked list mode not implemented.");
				}
				case LogicalMode_t::CHAIN:
				{
					// Chain mode (listed as undefined in nocash PSX docs), based of wisi's docs.
					workDone |= transferChain();
					break;
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
	
	// DMAC has completed 1 cycle.
#if ACCURACY_SKIP_TICKS_ON_NO_WORK
	if (!workDone)
		return event.mQuantity;
	else
		return 1;
#else
	return 1;
#endif
}

bool IOPDmac_s::transferNormalBurst()
{
	// Perform pre-start checks.
	if (!mChannel->CHCR->dma_started)
	{
		// Calculate transfer size.
		mChannel->BCR->calculate(, false);

		// Pre checks ok - start the DMA transfer.
		mChannel->CHCR->dma_started = true;
		return true;
	}
	else
	{
		// Check if BCR == 0 (transfer completed).
		if (mChannel->BCR->mTransferLength == 0)
		{
			// If we are writing to a FIFO, check that the peripheral received the data before interrupting IOP INTC.
			// Try again until condition is met.
			if (mChannel->CHCR->direction() == Direction::TO)
			{
				if (mChannel->FifoQueue->read_available() > 0)
					return false;
			}

			// Send interrupt to IOP INTC.
			setStateSuspended();
			return true;
		}

		// Transfer a data unit (32-bits). If no data was transfered, try again next cycle.
		int count = transferData();
		if (count == 0)
			return false;

		// Transfer successful, done for this cycle.
		return true;
	}
}

bool IOPDmac_s::transferNormalSlice()
{
	// Perform pre-start checks.
	if (!mChannel->CHCR->dma_started)
	{
		// Calculate transfer size.
		mChannel->BCR->calculate(, true);

		// Pre checks ok - start the DMA transfer.
		mChannel->CHCR->dma_started = true;
		return true;
	}
	else
	{
		// Check if BCR == 0 (transfer completed).
		if (mChannel->BCR->mTransferLength == 0)
		{
			// If we are writing to a FIFO, check that the peripheral received the data before interrupting IOP INTC.
			// Try again until condition is met.
			if (mChannel->CHCR->direction() == Direction::TO)
			{
				if (mChannel->FifoQueue->read_available() > 0)
					return false;
			}

			// Send interrupt to IOP INTC.
			setStateSuspended();
			return true;
		}

		// Transfer a data unit (32-bits). If no data was transfered, try again next cycle.
		int count = transferData();
		if (count == 0)
			return false;

		// Transfer successful, done for this cycle.
		return true;
	}
}

bool IOPDmac_s::transferChain()
{
	// Perform pre-start checks.
	if (!mChannel->CHCR->dma_started)
	{
		// Tag length is always 0 to begin with.
		// TODO: wisi's DMA docs mention the TBCR register, which is not implemented, but used instead over BCR for chain modes (tag transfer length).
		//       But for the IOP, TBCR is always 0 so far. If emulator crashes with MMU error, this will probably need to be put in.
		mChannel->BCR->mTransferLength = 0;

		// Pre checks ok - start the DMA transfer.
		mChannel->CHCR->dma_started = true;
		return true;
	}
	else
	{
		// Check the transfer size, make sure that size > 0 for a transfer to occur (otherwise read a tag). 
		if (mChannel->BCR->mTransferLength > 0)
		{
			// Transfer a data unit (32-bits). If no data was transfered, try again next cycle. 
			int count = transferData();
			if (count == 0)
				return false;

			// Transfer successful, done for this cycle.
			return true;
		}
		else
		{
			// Check first if we need to exit the transfer (by tag instruction or IRQ).
			bool tagIRQ = isChannelIRQEnabled() && mChannel->CHCR->tag_irq;
			if (tagIRQ || mChannel->CHCR->tag_exit)
			{
				// If we are writing to a FIFO, check that the peripheral received the data before interrupting IOP INTC.
				// Try again until condition is met.
				if (mChannel->CHCR->direction() == Direction::TO)
				{
					if (mChannel->FifoQueue->read_available() > 0)
						return false;
				}

				// Send interrupt to IOP INTC.
				setStateSuspended();
				return true;
			}

			// Check if we are in source or dest chain mode, read in a tag (to mDMAtag), and perform action based on tag id (which will set MADR, BCR, etc).
			// TODO: Do check based off the CHCR.DIR (direction) set or based on constant properties? Works both ways, but direction is less code.
			switch (mChannel->CHCR->direction())
			{
			case Direction::TO:
			{
				// Read in a tag, exit early if we need to wait for data.
				if (!readChainSourceTag())
					return false;
				
				break;
			}
			case Direction::FROM:
			{
				// Read in a tag, exit early if we need to wait for data.
				if (!readChainDestTag())
					return false;
				
				break;
			}
			default:
			{
				throw std::runtime_error("IOP DMAC could not determine chain mode context.");
			}
			}

			// Set the tag flag properties.
			mChannel->CHCR->tag_exit = (mDMAtag.getERT() > 0);
			mChannel->CHCR->tag_irq = (mDMAtag.getIRQ() > 0);

			// Set the tag data transfer address.
			mChannel->MADR->write_uword(mDMAtag.getADDR());

			// Chain mode setup was successful, done for this cycle.
			return true;
		}
	}
}

void IOPDmac_s::handleInterruptCheck() const
{
	// Check ICR0 and ICR1 for interrupt status, else clear the master interrupt and INTC bits.
	if (mDMAC->ICRW->isInterruptPending())
	{
		mINTC->STAT->setFieldValue(, IOPIntcRegister_STAT_t::DMAC, 1);
	}
	else
	{
		mDMAC->ICR0->setFieldValue(, IopDmacRegister_Icr0::MasterInterrupt, 0);
		mINTC->STAT->setFieldValue(, IOPIntcRegister_STAT_t::DMAC, 0);
	}
}

int IOPDmac_s::transferData() const
{
	// Determine the direction of data flow. 
	Direction direction = mChannel->CHCR->direction();

	// Get the main memory address.
	const uptr address = mChannel->MADR->read_uword();

	// Transfer data to or from the FIFO queue.
	if (direction == Direction::FROM)
	{
		// Transfer data, return early if we could not read from the FIFO queue.
		uword packet;
		if (!mChannel->FifoQueue->read(, reinterpret_cast<ubyte*>(&packet), NUMBER_BYTES_IN_WORD))
			return 0;
		writeWordMemory(physicalAddress, packet);

#if DEBUG_LOG_IOP_DMAC_XFERS
		log(Debug, "IOP DMAC Read uword channel %s, value = 0x%08X -> MemAddr = 0x%08X", mChannel->getInfo()->mMnemonic, packet, physicalAddress);
#endif
	}
	else if (direction == Direction::TO)
	{
		// Transfer data, return early if we could not write to the FIFO queue.
		uword packet = readWordMemory(physicalAddress);
		if (!mChannel->FifoQueue->write(, reinterpret_cast<const ubyte*>(&packet), NUMBER_BYTES_IN_WORD))
			return 0;

#if DEBUG_LOG_IOP_DMAC_XFERS
		log(Debug, "IOP DMAC Write uword channel %s, value = 0x%08X <- MemAddr = 0x%08X", mChannel->getInfo()->mMnemonic, packet, physicalAddress);
#endif
	}
	else
	{
		throw std::runtime_error("IOP DMAC could not determine direction! Please debug.");
	}

	// Increment or decrement (depending on CHCR.MAS) the MADR register by a word.
	if (mChannel->CHCR->getFieldValue(, IopDmacChannelRegister_Chcr::MAS) == 0)
		mChannel->MADR->increment();
	else
		mChannel->MADR->decrement();

	// Update number of word units left (BCR).
	mChannel->BCR->mTransferLength -= 1;

	return 1;
}

void IOPDmac_s::setStateSuspended() const
{
	// Stop channel.
	mChannel->CHCR->setFieldValue(, IopDmacChannelRegister_Chcr::Start, 0);

	// Set channel transfer complete interrupt bit.
	mDMAC->ICRW->setChannelTCI(, mChannel, 1);
}

bool IOPDmac_s::isChannelIRQEnabled() const
{
	return (mDMAC->ICRW->getChannelIQE(, mChannel) > 0);
}

uword IOPDmac_s::readWordMemory(const uptr address) const
{
	return mIOPByteMMU->read_uword(bytePhysicalAddress);
}

void IOPDmac_s::writeWordMemory(const uptr address, const uword data) const
{
	mIOPByteMMU->write_uword(bytePhysicalAddress, data);
}

uqword IOPDmac_s::readQwordMemory(const uptr address) const
{
	return mIOPByteMMU->read_uqword(bytePhysicalAddress);
}

bool IOPDmac_s::readChainSourceTag()
{
	// Get tag memory address (TADR).
	const uword TADR = mChannel->TADR->read_uword();

	// Read EE tag (128-bits) from TADR.
	const uqword tag = readQwordMemory(TADR);

	// Check if we need to transfer the tag (CHCR bit 8 aka "chopping enable" set).
	if (mChannel->CHCR->getFieldValue(, IopDmacChannelRegister_Chcr::CE) > 0)
	{
		// Setup new tag with LSB 64-bits filled with data from MSB 64-bits of tag read from before, then send.
		// If there is no space in the FIFO queue, try again next cycle.
		uqword sendTag = uqword(tag.UW[2], tag.UW[3], 0, 0);
		if (!mChannel->FifoQueue->write(, reinterpret_cast<const ubyte*>(&sendTag), NUMBER_BYTES_IN_QWORD))
			return false;
	}

	// Set mDMAtag based upon the LSB 64-bits of tag.
	mDMAtag = IopDmaTag(tag.UW[0], tag.UW[1]);

#if DEBUG_LOG_IOP_DMAC_TAGS
    log(Debug, "IOP tag (source chain mode) read on channel %s, TADR = 0x%08X. Tag0 = 0x%08X, Tag1 = 0x%08X, TTE = %d.",
        mChannel->getInfo()->mMnemonic, TADR, mDMAtag.getTag0(), mDMAtag.getTag1(), mChannel->CHCR->getFieldValue(, IopDmacChannelRegister_Chcr::CE));
    mDMAtag.logDebugAllFields();
#endif

	// Set tag transfer length.
	// The maximum supported length is 1MB - 16 bytes, rounded up to the nearest qword alignment (from PCSX2).
	// TODO: qword alignment is forced for source chain mode, but not dest - does it matter? Probably doesn't need it, when source chain is enforced anyway (ie: will never receive data that isn't qword aligned).
	// TODO: there is also a 'cache mode' part, but not sure where (also from PCSX2). It shouldn't need to be implemented anyway (explains the 0xFFFFC mask).
	mChannel->BCR->mTransferLength = (mDMAtag.getLength() + 3) & 0xFFFFC;

	// Increment TADR.
	mChannel->TADR->increment(, 0x10);

	// TODO: look into the tag transfer enable (TTE) option not set (CHCR bit 8 aka "chopping enable" set).
	//       PCSX2 does not implement anything at all, but wisi might know something. SIF0 has this bit set always. For now, left unimplemented.
	if (mChannel->CHCR->getFieldValue(, IopDmacChannelRegister_Chcr::CE) == 0)
		throw std::runtime_error("IOP DMAC source chain mode had TTE set to 0 - what is meant to happen?");

	return true;
}

bool IOPDmac_s::readChainDestTag()
{
	// Read tag from channel FIFO. If no data is available, try again next cycle.
	uqword tag;
	if (!mChannel->FifoQueue->read(, reinterpret_cast<ubyte*>(&tag), NUMBER_BYTES_IN_QWORD))
		return false;

	// Set mDMAtag based upon the first 2 words read from the channel.
	mDMAtag = IopDmaTag(tag.UW[0], tag.UW[1]);
	
#if DEBUG_LOG_IOP_DMAC_TAGS
	log(Debug, "IOP tag (dest chain mode) read on channel %s. Tag0 = 0x%08X, Tag1 = 0x%08X, TTE = %d.", 
		mChannel->getInfo()->mMnemonic, mDMAtag.getTag0(), mDMAtag.getTag1(), mChannel->CHCR->getFieldValue(, IopDmacChannelRegister_Chcr::CE));
	mDMAtag.logDebugAllFields();
#endif

	// Set tag transfer length.
	// The maximum supported length is 1MB - 16 bytes.
	// TODO: qword alignment is forced for source chain mode, but not dest - does it matter? Probably doesn't need it, when source chain is enforced anyway (ie: will never receive data that isn't qword aligned).
	// TODO: there is also a 'cache mode' part, but not sure where (also from PCSX2). It shouldn't need to be implemented anyway.
	// TODO: check if "& 0xFFFFC" is needed, or if its just PCSX2 specific.
	mChannel->BCR->mTransferLength = mDMAtag.getLength();

	// TODO: look into the tag transfer enable (TTE) option not set (CHCR bit 8 aka "chopping enable").
	//       PCSX2 does not implement anything at all, but wisi might know something. SIF1 has this bit set always. For now, left unimplemented.
	if (mChannel->CHCR->getFieldValue(, IopDmacChannelRegister_Chcr::CE) == 0)
		throw std::runtime_error("IOP DMAC dest chain mode had TTE set to 0 - what is meant to happen?");

	return true;
}
