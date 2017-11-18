
#include "Common/Types/Bus/ByteBus.hpp"
#include "Common/Tables/EEDmacChannelTable.h"
#include "Common/Types/FifoQueue/SpscFifoQueue.h"

#include "VM/VM.h"
#include "VM/Systems/EE/DMAC/EEDmac_s.h"

#include "Resources/RResources.hpp"
#include "Resources/Ee/REe.hpp"
#include "Resources/Ee/Core/REeCore.hpp"
#include "Resources/Ee/Core/EeCoreCop0.hpp"
#include "Resources/Ee/Core/EeCoreCop0Registers.hpp"
#include "Resources/Ee/Dmac/REeDmac.hpp"
#include "Resources/Ee/Dmac/EeDmacChannelRegisters.hpp"
#include "Resources/EE/DMAC/Types/EEDmacChannels_t.h"
#include "Resources/Ee/Dmac/EeDmacRegisters.hpp"
#include "Resources/EE/DMAC/Types/EeDmaTag.h"

using LogicalMode_t = EEDmacChannelTable::LogicalMode_t;
using Direction = EEDmacChannelTable::Direction;
using PhysicalMode_t = EEDmacChannelTable::PhysicalMode_t;

EEDmac_s::EEDmac_s(VM * vm) :
	VMSystem_t(vm, Context_t::EEDmac),
	mChannel(nullptr),
	mDMAtag(0, 0)
{
	// Set resource pointer variables.
	mDMAC = getVM()->getResources()->EE->DMAC;
	mEEByteMMU = getVM()->getResources()->EE->MMU;
}

void EEDmac_s::initialise()
{
	// Reset channels.
	for (auto& channel : mDMAC->CHANNELS)
	{
		if (channel->CHCR != nullptr) channel->CHCR->initialise();
		if (channel->MADR != nullptr) channel->MADR->initialise();
		if (channel->QWC != nullptr) channel->QWC->initialise();
		if (channel->TADR != nullptr) channel->TADR->initialise();
		if (channel->ASR0 != nullptr) channel->ASR0->initialise();
		if (channel->ASR1 != nullptr) channel->ASR1->initialise();
		if (channel->SADR != nullptr) channel->SADR->initialise();
		if (channel->FifoQueue != nullptr) channel->FifoQueue->initialise();
	}

	// Reset DMAC.
	mDMAC->CTRL->initialise();
	mDMAC->STAT->initialise();
	mDMAC->PCR->initialise();
	mDMAC->SQWC->initialise();
	mDMAC->RBSR->initialise();
	mDMAC->RBOR->initialise();
	mDMAC->STADR->initialise();
	mDMAC->ENABLER->initialise();
	mDMAC->ENABLEW->initialise();
}

int EEDmac_s::step(const Event_t & event)
{
	// Used to skip ticks. If no channel is enabled for transfers, then all of the ticks will be consumed at the end.
	bool workDone = false;

	// Check if DMA transfers are enabled. If not, DMAC has nothing to do.
	if (mDMAC->CTRL->getFieldValue(, EeDmacRegister_Ctrl::DMAE) > 0)
	{
		// Check for any pending/started DMA transfers and perform transfer if enabled.
		for (auto& channel : mDMAC->CHANNELS)
		{
			// Set channel resource context.
			mChannel = channel.get();

			// Check if channel is enabled for transfer.
			if (mChannel->CHCR->getFieldValue(, EeDmacChannelRegister_Chcr::STR) > 0)
			{
				switch (mChannel->CHCR->logical_mode())
				{
				case LogicalMode_t::NORMAL:
				{
					workDone |= transferNormal();
					break;
				}
				case LogicalMode_t::CHAIN:
				{
					workDone |= transferChain();  
					break;
				}
				case LogicalMode_t::INTERLEAVED:
				{
					workDone |= transferInterleaved();
					break;
				}
				default:
				{
					throw std::runtime_error("Could not determine EE DMAC channel logical mode.");
				}
				}
			}
		}

		// Check for D_STAT interrupt bit status, send interrupt to EE Core (INT1 line) if not masked.
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

int EEDmac_s::transferData() const
{
	// Determine the runtime direction of data flow by checking the CHCR.DIR field.
	Direction direction = mChannel->CHCR->direction();

	// Get the main memory or SPR address we are reading or writing from. 
	// NOTE: The mask of 0x1FFFFFF0 comes from PCSX2, also in my own testing, the PS2 OS sets MADR to illegal addresses, such as 0x3xxxxxxx. This is to do with cache modes, but they are left un-implemented.
	const bool SPRFlag = (mChannel->MADR->getFieldValue(, EEDmacChannelRegister_MADR_t::SPR) != 0);
	const uword PhysicalAddressOffset = mChannel->MADR->getFieldValue(, EEDmacChannelRegister_MADR_t::ADDR) & 0x1FFFFFF0;

	// If we are using the from/toSPR channels (channel ID's 8 or 9), then we need to get the SPR address, and take a different code path. 
	// Within the these channels MADR.SPR is always 0 on these channels (have to use the SADR register as the SPR address).
	if (mChannel->channel_id() == 8 || mChannel->channel_id() == 9)
	{
		// We are doing a mem->SPR or SPR->mem, use both MADR and SADR registers.
		// NOTE: The mask of 0x3FF0 comes from PCSX2. I have not personally tested this, but assume it is required.
		//       This mask restricts the address to the 16 kB address range and makes the address qword aligned.
		const uword SPRPhysicalAddressOffset = mChannel->SADR->read_uword() & 0x3FF0;

		if (direction == Direction::FROM)
		{
			uqword packet = readQwordMemory(SPRPhysicalAddressOffset, true);
			writeQwordMemory(PhysicalAddressOffset, false, packet);

#if DEBUG_LOG_EE_DMAC_XFERS
			log(Debug, "EE DMAC Read uqword channel %s, SPRAddr = 0x%08llX, w0 = 0x%08X, w1 = 0x%08X, w2 = 0x%08X, w3 = 0x%08X -> MemAddr = 0x%08X", 
				mChannel->getInfo()->mMnemonic, SPRPhysicalAddressOffset, packet.UW[0], packet.UW[1], packet.UW[2], packet.UW[3], PhysicalAddressOffset);
#endif
		}
		else if (direction == Direction::TO)
		{
			uqword packet = readQwordMemory(PhysicalAddressOffset, false);
			writeQwordMemory(SPRPhysicalAddressOffset, true, packet);
			
#if DEBUG_LOG_EE_DMAC_XFERS
			log(Debug, "EE DMAC Write uqword channel %s, SPRAddr = 0x%08llX, w0 = 0x%08X, w1 = 0x%08X, w2 = 0x%08X, w3 = 0x%08X <- MemAddr = 0x%08X",
				mChannel->getInfo()->mMnemonic, SPRPhysicalAddressOffset, packet.UW[0], packet.UW[1], packet.UW[2], packet.UW[3], PhysicalAddressOffset);
#endif
		}
		else
		{
			throw std::runtime_error("EE DMAC could not determine transfer direction (SPR)! Please debug.");
		}

		// Increment the MADR & SADR register by a qword, and decrement the QWC register by a qword.
		mChannel->MADR->increment();
		mChannel->SADR->increment();
		mChannel->QWC->decrement();

		return 1;
	}
	else
	{
		// Else transfer data normally.
		if (direction == Direction::FROM)
		{
			// Transfer data, return early if we could not read from the FIFO queue.
			uqword packet;
			if (!mChannel->FifoQueue->read(, reinterpret_cast<ubyte*>(&packet), NUMBER_BYTES_IN_QWORD))
				return 0;
			writeQwordMemory(PhysicalAddressOffset, SPRFlag, packet);

#if DEBUG_LOG_EE_DMAC_XFERS
			log(Debug, "EE DMAC Read uqword channel %s, w0 = 0x%08X, w1 = 0x%08X, w2 = 0x%08X, w3 = 0x%08X -> MemAddr = 0x%08X", 
				mChannel->getInfo()->mMnemonic, packet.UW[0], packet.UW[1], packet.UW[2], packet.UW[3], PhysicalAddressOffset);
#endif
		}
		else if (direction == Direction::TO)
		{
			// Transfer data, return early if we could not write to the FIFO queue.
			uqword packet = readQwordMemory(PhysicalAddressOffset, SPRFlag);
			if (!mChannel->FifoQueue->write(, reinterpret_cast<const ubyte*>(&packet), NUMBER_BYTES_IN_QWORD))
				return 0;

#if DEBUG_LOG_EE_DMAC_XFERS
			log(Debug, "EE DMAC Write uqword channel %s, w0 = 0x%08X, w1 = 0x%08X, w2 = 0x%08X, w3 = 0x%08X <- MemAddr = 0x%08X",
				mChannel->getInfo()->mMnemonic, packet.UW[0], packet.UW[1], packet.UW[2], packet.UW[3], PhysicalAddressOffset);
#endif
		}
		else
		{
			throw std::runtime_error("EE DMAC could not determine transfer direction! Please debug.");
		}

		// Increment the MADR register by a qword, and decrement the QWC register by a qword.
		mChannel->MADR->increment();
		mChannel->QWC->decrement();

		return 1;
	}
}

void EEDmac_s::setStateSuspended() const
{
	// Emit the interrupt status bit.
	mDMAC->STAT->setFieldValue(, EeDmacRegister_Stat::CHANNEL_CIS_KEYS[mChannel->channel_id()], 1);

	// Change CHCR.STR to 0.
	mChannel->CHCR->setFieldValue(, EeDmacChannelRegister_Chcr::STR, 0);
}

void EEDmac_s::setStateFailedTransfer() const
{
	throw std::runtime_error("EE DMAC failed transfer not implemented.");
}

bool EEDmac_s::transferNormal()
{
	// Perform pre-start checks.
	if (!mChannel->CHCR->dma_started)
	{
		// Check the QWC register, make sure that size > 0 in order to start transfer.
		if (mChannel->QWC->read_uword() == 0)
		{
			setStateFailedTransfer();
			return false;
		}

		// Pre checks ok - start the DMA transfer.
		mChannel->CHCR->dma_started = true;
		return true;
	}
	else
	{
		// Check if QWC == 0 (transfer completed).
		if (mChannel->QWC->read_uword() == 0)
		{
			// If we are writing to a FIFO, check that the peripheral received the data before interrupting EE Core (except for toSPR).
			// Try again until condition is met.
			if ((mChannel->CHCR->direction() == Direction::TO) && (mChannel->channel_id() != 9))
			{
				if (mChannel->FifoQueue->read_available() > 0)
					return false;
			}

			// Send interrupt to EE Core.
			setStateSuspended();
			return true;
		}

		// Check for drain stall control conditions, and skip cycle if the data is not ready (when the next slice is not ready).
		if (isDrainStallControlOn() && isDrainStallControlWaiting())
		{
			setDMACStallControlSIS();
			return false;
		}

		// Transfer a data unit (128-bits). If no data was transfered, try again next cycle.
		int count = transferData();
		if (count == 0)
			return false;

		// Check for source stall control conditions, and update D_STADR if required.
		if (isSourceStallControlOn())
			setDMACStallControlSTADR();

		// Transfer successful, done for this cycle.
		return true;
	}
}

bool EEDmac_s::transferChain()
{
	// Perform pre-start checks.
	if (!mChannel->CHCR->dma_started)
	{
		// No prechecks needed - start DMA transfer.
		// If QWC transfer size is 0 initially, then it just means that we read a tag straight away.
		mChannel->CHCR->dma_started = true;
		return true;
	}
	else
	{
		// Check the QWC register, make sure that size > 0 for a transfer to occur (otherwise read a tag).
		if (mChannel->QWC->read_uword() > 0)
		{
			// Check for drain stall control conditions (including if we are in "refs" tag), and skip cycle if the data is not ready.
			if (isDrainStallControlOn() && isDrainStallControlWaiting() && mChannel->CHCR->tag_stall)
			{
				setDMACStallControlSIS();
				return false;
			}

			// Transfer a data unit (128-bits). If no data was transfered, try again next cycle.
			int count = transferData();
			if (count == 0)
				return false;

			// Check for source stall control conditions (including if we are in "cnts" tag id), and update D_STADR if required.
			if (isSourceStallControlOn() && mChannel->CHCR->tag_stall)
				setDMACStallControlSTADR();
			
			// Transfer successful, done for this cycle.
			return true;
		}
		else
		{
			// Check first if we need to exit the transfer (by tag instruction or IRQ).
			bool tagIRQ = (mChannel->CHCR->getFieldValue(, EeDmacChannelRegister_Chcr::TIE) > 0) && mChannel->CHCR->tag_irq;
			if (tagIRQ || mChannel->CHCR->tag_exit)
			{
				// If we are writing to a FIFO, check that the peripheral received the data before interrupting EE Core (except for toSPR).
				// Try again until condition is met.
				if ((mChannel->CHCR->direction() == Direction::TO) && (mChannel->channel_id() != 9))
				{
					if (mChannel->FifoQueue->read_available() > 0)
						return false;
				}

				// Send interrupt to EE Core.
				setStateSuspended();
				return true;
			}

			// We are instead reading in the next tag.
			// Check if we are in source or dest chain mode, read in a tag (to mDMAtag), and perform action based on tag id (which will set MADR, QWC, etc).
			// TODO: Do check based off the CHCR.DIR (direction) set or based on constant properties listed on pg 42 of EE Users Manual? Works both ways, but direction is less code.
			switch (mChannel->CHCR->direction()) 
			{
			case Direction::TO:
			{
				// Read in a tag, exit early if we need to wait for data.
				if (!readChainSourceTag())
					return false;

				// Execute the tag handler
				(this->*SRC_CHAIN_INSTRUCTION_TABLE[mDMAtag.getID()])();
				break;
			}
			case Direction::FROM:
			{
				// Read in a tag, exit early if we need to wait for data.
				if (!readChainDestTag())
					return false;

				// Execute the tag handler
				(this->*DST_CHAIN_INSTRUCTION_TABLE[mDMAtag.getID()])();
				break;
			}
			default:
			{
				throw std::runtime_error("EE DMAC could not determine chain mode context.");
			}
			}

			// Set the IRQ flag if the DMAtag.IRQ bit is set.
			mChannel->CHCR->tag_irq = (mDMAtag.getIRQ() > 0);

			// Set CHCR.TAG based upon the DMA tag read (bits 16-31).
			mChannel->CHCR->setFieldValue(, EeDmacChannelRegister_Chcr::TAG, mDMAtag.getTAG());

			// Transfer successful, done for this cycle.
			return true;
		}
	}
}

bool EEDmac_s::transferInterleaved()
{
	throw std::runtime_error("EE DMAC interleave mode not fully implemented (fix me up).");

	/*
	// Check the QWC register, make sure that size > 0 in order to start transfer.
	if (mChannel->QWC->read_uword() == 0)
	{
		setStateFailedTransfer();
		return;
	}

	// Data of size D_SQWC.TQWC is transferred first, then data of size D_SQWC.SQWC is skipped, until Dn_QWC is reached.
	if (!mChannel->isInterleaveInSkipMode())
	{
		// Transfer a data unit (128-bits). If no data was transfered, try again next cycle.
		uword dataCount = transferData();
		if (!dataCount)
		{
			return;
		}
	}
	else
	{
		// Skip data by incrementing the channel MADR.
		mChannel->MADR->increment();
	}
		
	// Increment the interleaved count.
	mChannel->incrementInterleaveCount();

	// Check the interleaved mode (transferring/skipping), and change mInterleavedSkipState if required, based on mInterleavedCountState.
	if (isInterleaveLimitReached())
	{
		mChannel->toggleInterleaveMode();
	}

	// Check if QWC == 0 (transfer completed), in which case stop transferring and update status.
	if (mChannel->QWC->read_uword() == 0)
	{
		setStateSuspended();
	}
	*/
}

void EEDmac_s::handleInterruptCheck() const
{
	auto& COP0 = getVM()->getResources()->EE->EECore->COP0;
	auto& D_STAT = mDMAC->STAT;

	// Set the interrupt line if there was a condition set, otherwise clear the interrupt line.
	if (D_STAT->isInterruptPending())
		COP0->Cause->set_irq_line(, 3);
	else
		COP0->Cause->clear_irq_line(, 3);
}

bool EEDmac_s::isSourceStallControlOn() const
{
	if (mChannel->CHCR->direction() == Direction::FROM)
	{
		const uword STS = mDMAC->CTRL->getFieldValue(, EeDmacRegister_Ctrl::STS);
		if (mChannel->channel_id() == EEDmacChannelTable::getSTSChannelIndex(STS))
		{
			return true;
		}
	}

	return false;
}

bool EEDmac_s::isDrainStallControlOn() const
{
	if (mChannel->CHCR->direction() == Direction::TO)
	{
		auto STD = mDMAC->CTRL->getFieldValue(, EeDmacRegister_Ctrl::STD);
		if (mChannel->channel_id() == EEDmacChannelTable::getSTDChannelIndex(STD))
		{
			return true;
		}
	}

	return false;
}

void EEDmac_s::setDMACStallControlSTADR() const
{
	uword MADR = mChannel->MADR->getFieldValue(, EEDmacChannelRegister_MADR_t::ADDR);
	mDMAC->STADR->setFieldValue(, EEDmacRegister_STADR_t::ADDR, MADR);
}

void EEDmac_s::setDMACStallControlSIS() const
{
	// Set the STAT.SIS bit.
	mDMAC->STAT->setFieldValue(, EeDmacRegister_Stat::SIS, 1);
}

bool EEDmac_s::isDrainStallControlWaiting() const
{
	if (mChannel->CHCR->direction() == Direction::TO)
	{
		const uword MADR = mChannel->MADR->getFieldValue(, EEDmacChannelRegister_MADR_t::ADDR);
		const uword STADR = mDMAC->STADR->getFieldValue(, EEDmacRegister_STADR_t::ADDR);

		if ((MADR + 8) > STADR)
		{
			return true;
		}
	}

	return false;
}

uqword EEDmac_s::readQwordMemory(const uptr address, const bool SPRAccess) const
{
	// Read mem[addr] or spr[addr] (128-bits). SPR is at offset 0x70000000.
	if (SPRAccess)
		return mEEByteMMU->read_uqword(0x70000000 + bytePhysicalAddress);
	else
		return mEEByteMMU->read_uqword(bytePhysicalAddress);
}

void EEDmac_s::writeQwordMemory(const uptr address, const bool SPRAccess, const uqword data) const
{
	// Write mem[addr] or spr[addr] (128-bits). SPR is at offset 0x70000000.
	if (SPRAccess)
		mEEByteMMU->write_uqword(0x70000000 + bytePhysicalAddress, data);
	else
		mEEByteMMU->write_uqword(bytePhysicalAddress, data);
}

bool EEDmac_s::readChainSourceTag()
{
	// Get tag memory address (TADR).
	const uword TADR = mChannel->TADR->getFieldValue(, EEDmacChannelRegister_TADR_t::ADDR);
	const bool SPRFlag = (mChannel->TADR->getFieldValue(, EEDmacChannelRegister_TADR_t::SPR) != 0);

	// Read EE tag (128-bits) from TADR.
	const uqword tag = readQwordMemory(TADR, SPRFlag);
	
	// Check if we need to transfer the tag.
	if (mChannel->CHCR->getFieldValue(, EeDmacChannelRegister_Chcr::TTE) > 0)
	{
		// Setup new tag with LSB 64-bits filled with data from MSB 64-bits of tag read from before, then send.
		// If there is no space in the FIFO queue, try again next cycle.
		uqword sendTag = uqword(tag.UW[2], tag.UW[3], 0, 0);
		if (!mChannel->FifoQueue->write(, reinterpret_cast<const ubyte*>(&sendTag), NUMBER_BYTES_IN_QWORD))
			return false;
	}
	
	// Set mDMAtag based upon the LSB 64-bits of tag.
	mDMAtag = EeDmaTag(tag.UW[0], tag.UW[1]);

#if DEBUG_LOG_EE_DMAC_TAGS
    log(Debug, "EE tag (source chain mode) read on channel %s, TADR = 0x%08X. Tag0 = 0x%08X, Tag1 = 0x%08X, TTE = %d.",
        mChannel->getInfo()->mMnemonic, mChannel->TADR->read_uword(), mDMAtag.getTag0(), mDMAtag.getTag1(), mChannel->CHCR->getFieldValue(EeDmacChannelRegister_Chcr::TTE));
    mDMAtag.logDebugAllFields();
#endif

	return true;
}

bool EEDmac_s::readChainDestTag()
{
	// Read tag from channel FIFO. If no data is available, try again next cycle.
	uqword tag;
	if (!mChannel->FifoQueue->read(, reinterpret_cast<ubyte*>(&tag), NUMBER_BYTES_IN_QWORD))
		return false;

	// Set mDMAtag based upon the first 2 words read from the channel.
	mDMAtag = EeDmaTag(tag.UW[0], tag.UW[1]);

#if DEBUG_LOG_EE_DMAC_TAGS
	log(Debug, "EE tag (dest chain mode) read on channel %s. Tag0 = 0x%08X, Tag1 = 0x%08X, TTE = %d.", 
		mChannel->getInfo()->mMnemonic, mDMAtag.getTag0(), mDMAtag.getTag1(), mChannel->CHCR->getFieldValue(, EeDmacChannelRegister_Chcr::TTE));
	mDMAtag.logDebugAllFields();
#endif
	
	// Check if we need to transfer the tag.
	if (mChannel->CHCR->getFieldValue(, EeDmacChannelRegister_Chcr::TTE) > 0)
	{
		throw std::runtime_error("EE DMAC dest chain mode TTE set but not implemented.");
	}
	
	return true;
}
