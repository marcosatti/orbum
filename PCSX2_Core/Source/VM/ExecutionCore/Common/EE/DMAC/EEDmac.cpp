#include "stdafx.h"

#include "VM/ExecutionCore/Common/EE/DMAC/EEDmac.h"
#include "PS2Constants/PS2Constants.h"
#include "VM/VMMain.h"
#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreExceptions_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreException_t.h"
#include "PS2Resources/EE/DMAC/EEDmac_t.h"
#include "PS2Resources/EE/DMAC/Types/EEDmacChannelRegisters_t.h"
#include "PS2Resources/EE/DMAC/Types/EEDmacChannels_t.h"
#include "PS2Resources/EE/DMAC/Types/EEDmacRegisters_t.h"
#include "PS2Resources/EE/DMAC/Types/DMAtag_t.h"
#include "Common/Types/PhysicalMMU/PhysicalMMU_t.h"
#include "Common/Types/FIFOQueue/FIFOQueue_t.h"
#include "Common/Tables/EEDmacChannelTable/EEDmacChannelTable.h"

using ExType = EECoreException_t::ExType;
using ChannelProperties_t = EEDmacChannelTable::ChannelProperties_t;
using ChannelID_t = EEDmacChannelTable::ChannelID_t;
using Direction_t = EEDmacChannelTable::Direction_t;
using PhysicalMode_t = EEDmacChannelTable::PhysicalMode_t;
using ChainMode_t = EEDmacChannelTable::ChainMode_t;

EEDmac::EEDmac(VMMain* vmMain) :
	VMExecutionCoreComponent(vmMain),
	mChannelIndex(0),
	mChannelProperties(nullptr),
	mDMAtag()
{
	// Set resource pointer variables.
	mDMAC = getResources()->EE->DMAC;
	mEEMMU = getResources()->EE->PhysicalMMU;
}

EEDmac::~EEDmac()
{
}

s64 EEDmac::executionStep(const ClockSource_t& clockSource)
{
	// Check if DMA transfers are enabled. If not, DMAC has nothing to do.
	if (isDMACEnabled())
	{
		// Check for any pending/started DMA transfers and perform transfer if enabled.
		for (mChannelIndex = 0; mChannelIndex < PS2Constants::EE::DMAC::NUMBER_DMAC_CHANNELS; mChannelIndex++)
		{
			// Set context variables.
			mChannel = mDMAC->CHANNELS[mChannelIndex];
			mChannelProperties = mChannel->getChannelProperties();

			// Check if channel is enabled for transfer.
			if (isChannelEnabled())
			{
				switch (getChannelRuntimeLogicalMode())
				{
				case 0x0:
				{
					executionStep_Normal();
					break;
				}
				case 0x1:
				{
					executionStep_Chain();       
					break;
				}
				case 0x2:
				{
					executionStep_Interleaved(); 
					break;
				}
				default:
				{
					throw std::runtime_error("Could not determine DMA transfer logical mode context. Please fix!");
				}
				}
			}
		}

		// Check for D_STAT interrupt bit status, send interrupt to EE Core (INT1 line) if not masked.
		if (isInterruptPending())
			raiseInterrupt();
	}

	// DMAC has completed 1 cycle.
	return 1;
}

Direction_t EEDmac::getChannelRuntimeDirection()
{
	Direction_t direction = mChannelProperties->Direction;
	if (direction == Direction_t::BOTH)
		direction = static_cast<Direction_t>(mChannel->CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::DIR));

	return direction;
}

u32 EEDmac::transferData()
{
	// Determine the direction of data flow. If set to BOTH (true for VIF1 and SIF2 channels), get the runtime direction by checking the CHCR.DIR field.
	Direction_t direction = getChannelRuntimeDirection();

	// Get the main memory or SPR address we are reading or writing from. 
	// NOTE: The mask of 0x1FFFFFF0 comes from PCSX2, also in my own testing, the PS2 OS acceses illegal addresses, such as 0x3xxxxxxx.
	//       I can only assume that the DMAC hardware corrects this value. The resulting address will also be qword aligned and restricted to the 'system' memory region.
	const bool SPRFlag = (mChannel->MADR->getFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR) != 0);
	const u32 PhysicalAddressOffset = mChannel->MADR->getFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR) & 0x1FFFFFF0;

	// If we are using the from/toSPR channels, then we need to get the SPR address, and take a different code path. 
	// Within the these channels MADR.SPR is always 0 on these channels (have to use the SADR register as the SPR address).
	if (mChannelProperties->ChannelID == ChannelID_t::toSPR || mChannelProperties->ChannelID == ChannelID_t::fromSPR)
	{
		// We are doing a mem->SPR or SPR->mem, use both MADR and SADR registers.
		// NOTE: The mask of 0x3FF0 comes from PCSX2. I have not personally tested this, but assume it is required.
		//       This mask restricts the address to the 16 kB address range and makes the address qword aligned.
		const u32 SPRPhysicalAddressOffset = mChannel->SADR->getFieldValue(EEDmacChannelRegister_SADR_t::Fields::ADDR) & 0x3FF0;

		if (direction == Direction_t::FROM)
		{
			u128 packet = readDataMemory(SPRPhysicalAddressOffset, true);
			writeDataMemory(PhysicalAddressOffset, false, packet);
		}
		else if (direction == Direction_t::TO)
		{
			u128 packet = readDataMemory(PhysicalAddressOffset, false);
			writeDataMemory(SPRPhysicalAddressOffset, true, packet);
		}

		// Update slice count by 1, the MADR & SADR register by 0x10 (increment), and decrement the QWC register by 1.
		mChannel->mSliceCountState += 1;
		mChannel->MADR->increment();
		mChannel->SADR->increment();
		mChannel->QWC->decrement();

		return 1;
	}
	else
	{
		// Else transfer data normally.
		if (direction == Direction_t::FROM)
		{
			// Check if channel does not have data ready - need to try again next cycle.
			if (isChannelQueueEmpty())
				return 0;

			u128 packet = readDataChannel();
			writeDataMemory(PhysicalAddressOffset, SPRFlag, packet);
		}
		else if (direction == Direction_t::TO)
		{
			// Check if channel is full - need to try again next cycle.
			if (isChannelQueueFull())
				return 0;

			u128 packet = readDataMemory(PhysicalAddressOffset, SPRFlag);
			writeDataChannel(packet);
		}

		// Update slice count by 1, the MADR register by 0x10 (increment), and decrement the QWC register by 1.
		mChannel->mSliceCountState += 1;
		mChannel->MADR->increment();
		mChannel->QWC->decrement();

		return 1;
	}
}

bool EEDmac::isChannelEnabled()
{
	if (mChannel->CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::STR) > 0)
		return true;
	else
		return false;
}

u32 EEDmac::getChannelRuntimeLogicalMode()
{
	return mChannel->CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::MOD);
}

u32 EEDmac::getChannelQWC()
{
	return mChannel->QWC->getFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC);
}

bool EEDmac::isChannelQueueEmpty()
{
	return mChannel->mFIFOQueue->getCurrentSize() == 0;
}

bool EEDmac::isChannelQueueFull()
{
	return !(mChannel->mFIFOQueue->getCurrentSize() < mChannel->mFIFOQueue->getMaxSize());
}

bool EEDmac::isChannelSliceQuotaReached()
{
	if (mChannelProperties->PhysicalMode == PhysicalMode_t::SLICE)
	{
		if (mChannel->mSliceCountState % 8 == 0)
		{
			return true;
		}
	}

	return false;
}

void EEDmac::setChannelSliceQuotaReset()
{
	mChannel->mSliceCountState = 0;
}

void EEDmac::setChannelStateSuspended()
{
	// Emit the interrupt status bit.
	mDMAC->STAT->setFieldValue(EEDmacRegister_STAT_t::Fields::CIS_KEYS[mChannelIndex], 1);

	// Change CHCR.STR to 0.
	mChannel->CHCR->setFieldValue(EEDmacChannelRegister_CHCR_t::Fields::STR, 0);
}

void EEDmac::setChannelStateFailedTransfer()
{
	throw std::runtime_error("failed transfer not implemented.");
}


void EEDmac::executionStep_Normal()
{
	// Check the QWC register, make sure that size > 0 in order to start transfer.
	if (getChannelQWC() == 0)
	{
		setChannelStateFailedTransfer();
		return;
	}

	// Check for drain stall control conditions, and skip cycle if the data is not ready (when the next slice is not ready).
	if (isDrainStallControlOn() && isDrainStallControlWaiting())
	{
		setDMACStallControlSIS();
		return;
	}

	// Transfer a data unit (128-bits). If no data was transfered, try again next cycle.
	u32 dataCount = transferData();
	if (!dataCount)
	{
		return;
	}

	// Check for source stall control conditions, and update D_STADR if required.
	if (isSourceStallControlOn())
	{
		setDMACStallControlSTADR();
	}

	// Check if QWC == 0 (transfer completed), in which case stop transferring and update status.
	if (getChannelQWC() == 0)
	{
		setChannelStateSuspended();
	}

	// If the physical mode is set to slice, suspend transfer after 8 units are completed.
	if (isChannelSliceQuotaReached())
	{
		setChannelSliceQuotaReset();
		setChannelStateSuspended();
	}
}

void EEDmac::executionStep_Chain()
{
	// Check the QWC register, make sure that size > 0 for a transfer to occur (otherwise read a tag).
	if (getChannelQWC() > 0)
	{
		// Check for drain stall control conditions (including if we are in "refs" tag), and skip cycle if the data is not ready.
		if (isChainInDrainStallControlTag() && isDrainStallControlOn() && isDrainStallControlWaiting())
		{
			setDMACStallControlSIS();
			return;
		}

		// Transfer a data unit (128-bits). If no data was transfered, try again next cycle.
		u32 dataCount = transferData();
		if (!dataCount)
		{
			return;
		}

		// Check for source stall control conditions (including if we are in "cnts" tag id), and update D_STADR if required.
		if (isChainInSourceStallControlTag() && isSourceStallControlOn())
		{
			setDMACStallControlSTADR();
		}

		// If QWC is now 0, check for suspend conditions.
		if (getChannelQWC() == 0)
		{
			// Check if we need to emit an interrupt due to tag (done after packet transfer has completed).
			if (isChainInInterruptTag())
			{
				setChannelStateSuspended();
			}

			// Check if we need to exit based on tag instruction ("end", "ret", etc).
			if (isChainInExitTag())
			{
				setChainExitContextReset();
				setChannelStateSuspended();
			}
		}
	}
	else
	{
		// Check if we are in source or dest chain mode, read in a tag, and perform action based on tag id (which will set MADR, QWC, etc).
		switch (mChannelProperties->ChainMode)
		{
		case ChainMode_t::SOURCE:
		{
			// Some additional processing needed on src chain first run before starting a transfer (set TADR register).
			if (isChainSourceInFirstCycle())
				setChainSourceFirstCycle();

			// Read in a tag, exit early if we need to wait for data.
			if (!readChainSourceTag())
				return;

			// Execute the tag handler
			(this->*SRC_CHAIN_INSTRUCTION_TABLE[mDMAtag.getID()])();
			break;
		}
		case ChainMode_t::DEST:
		{
			// Read in a tag, exit early if we need to wait for data.
			if (!readChainDestTag())
				return;

			// Execute the tag handler
			(this->*DST_CHAIN_INSTRUCTION_TABLE[mDMAtag.getID()])();
			break;
		}
		default:
		{
			throw std::runtime_error("Could not determine chain mode context.");
		}
		}
	}

	// If the physical mode is set to slice, suspend transfer after 8 units are completed.
	// Common to both tag reads and transfers.
	if (isChannelSliceQuotaReached())
	{
		setChannelSliceQuotaReset();
		setChannelStateSuspended();
	}
}

void EEDmac::executionStep_Interleaved()
{
	// Check the QWC register, make sure that size > 0 in order to start transfer.
	if (getChannelQWC() == 0)
	{
		setChannelStateFailedTransfer();
		return;
	}

	// Data of size D_SQWC.TQWC is transferred first, then data of size D_SQWC.SQWC is skipped, until Dn_QWC is reached.
	if (!isInterleaveInSkipMode())
	{
		// Transfer a data unit (128-bits). If no data was transfered, try again next cycle.
		u32 dataCount = transferData();
		if (!dataCount)
		{
			return;
		}
	}
	else
	{
		// Skip data by incrementing the channel MADR.
		setInterleaveSkipDataCycle();
	}
		
	// Increment the mInterleavedCountState.
	setInterleaveModeCountIncrement();

	// Check the interleaved mode (transferring/skipping), and change mInterleavedSkipState if required, based on mInterleavedCountState.
	if (isInterleaveLimitReached())
	{
		setInterleaveModeToggle();
	}

	// Check if QWC == 0 (transfer completed), in which case stop transferring and update status.
	if (getChannelQWC() == 0)
	{
		setChannelStateSuspended();
	}

	// If the physical mode is set to slice, suspend transfer after 8 units are completed.
	if (isChannelSliceQuotaReached())
	{
		setChannelSliceQuotaReset();
		setChannelStateSuspended();
	}
}

bool EEDmac::isDMACEnabled()
{
	if (mDMAC->CTRL->getFieldValue(EEDmacRegister_CTRL_t::Fields::DMAE) > 0)
		return true;
	else
		return false;
}

bool EEDmac::isInterruptPending()
{
	auto& D_STAT = mDMAC->STAT;

	// Check channel interrupt status.
	for (auto i = 0; i < PS2Constants::EE::DMAC::NUMBER_DMAC_CHANNELS; i++)
	{
		auto& cisKey = EEDmacRegister_STAT_t::Fields::CIS_KEYS[i];
		auto& cimKey = EEDmacRegister_STAT_t::Fields::CIM_KEYS[i];

		auto& cisValue = D_STAT->getFieldValue(cisKey);
		auto& cimValue = D_STAT->getFieldValue(cimKey);

		// Set EE Core interrupt if (CIS & CIM) is true.
		if (cisValue & cimValue)
		{
			return true;
		}
	}

	// Check stall control interrupt status.
	if (D_STAT->getFieldValue(EEDmacRegister_STAT_t::Fields::SIS) & D_STAT->getFieldValue(EEDmacRegister_STAT_t::Fields::SIS))
	{
		return true;
	}

	// Check MFIFO interrupt status.
	if (D_STAT->getFieldValue(EEDmacRegister_STAT_t::Fields::MEIS) & D_STAT->getFieldValue(EEDmacRegister_STAT_t::Fields::MEIM))
	{
		return true;
	}

	// Check for BUSERR interrupt status.
	if (D_STAT->getFieldValue(EEDmacRegister_STAT_t::Fields::BEIS))
	{
		return true;
	}

	return false;
}

void EEDmac::raiseInterrupt()
{
	auto& Exceptions = getResources()->EE->EECore->Exceptions;
	IntExceptionInfo_t intex = {1, 0, 0};
	Exceptions->setException(EECoreException_t(ExType::EX_INTERRUPT, nullptr, &intex, nullptr));
}

bool EEDmac::isSourceStallControlOn()
{
	if (getChannelRuntimeDirection() == Direction_t::FROM)
	{
		const u32 STS = mDMAC->CTRL->getFieldValue(EEDmacRegister_CTRL_t::Fields::STS);
		if (mChannelIndex == EEDmacChannelTable::getSTSChannelIndex(STS))
		{
			return true;
		}
	}

	return false;
}

bool EEDmac::isDrainStallControlOn()
{
	if (getChannelRuntimeDirection() == Direction_t::TO)
	{
		auto STD = mDMAC->CTRL->getFieldValue(EEDmacRegister_CTRL_t::Fields::STD);
		if (mChannelIndex == EEDmacChannelTable::getSTDChannelIndex(STD))
		{
			return true;
		}
	}

	return false;
}

void EEDmac::setDMACStallControlSTADR()
{
	u32 MADR = mChannel->MADR->getFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR);
	mDMAC->STADR->setFieldValue(EEDmacRegister_STADR_t::Fields::ADDR, MADR);
}

void EEDmac::setDMACStallControlSIS()
{
	mDMAC->STAT->setFieldValue(EEDmacRegister_STAT_t::Fields::SIS, 1);
}

bool EEDmac::isDrainStallControlWaiting()
{
	if (getChannelRuntimeDirection() == Direction_t::TO)
	{
		const u32 MADR = mChannel->MADR->getFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR);
		const u32 STADR = mDMAC->STADR->getFieldValue(EEDmacRegister_STADR_t::Fields::ADDR);

		if ((MADR + 8) > STADR)
		{
			return true;
		}
	}

	return false;
}

u128 EEDmac::readDataChannel()
{
	return mChannel->mFIFOQueue->read();
}

void EEDmac::writeDataChannel(u128 data)
{
	mChannel->mFIFOQueue->write(data);
}

u128 EEDmac::readDataMemory(u32 physicalAddress, bool SPRAccess)
{
	// Read mem[addr] or spr[addr] (128-bits).
	if (SPRAccess)
		return mEEMMU->readQwordU(PS2Constants::EE::EECore::ScratchpadMemory::PADDRESS_SCRATCHPAD_MEMORY + physicalAddress);
	else
		return mEEMMU->readQwordU(physicalAddress);
}

void EEDmac::writeDataMemory(u32 physicalAddress, bool SPRAccess, u128 data)
{
	// Write mem[addr] or spr[addr] (128-bits).
	if (SPRAccess)
		mEEMMU->writeQwordU(PS2Constants::EE::EECore::ScratchpadMemory::PADDRESS_SCRATCHPAD_MEMORY + physicalAddress, data);
	else
		mEEMMU->writeQwordU(physicalAddress, data);
}

bool EEDmac::isChainInDrainStallControlTag()
{
	return ((mChannel->CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::TAG) >> 12) & 0x7) == 0x4;
}

bool EEDmac::isChainInSourceStallControlTag()
{
	return ((mChannel->CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::TAG) >> 12) & 0x7) == 0x0;
}

bool EEDmac::isChainInInterruptTag()
{
	if (mChannel->CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::TIE) != 0
		&& (mChannel->CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::TAG) & 0x8000) != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool EEDmac::isChainInExitTag()
{
	if (mChannel->mChainExitState)
		return true;
	else
		return false;
}

bool EEDmac::isChainSourceInFirstCycle()
{
	if (mChannel->mChainSrcFirstRun)
		return true;
	else
		return false;
}

void EEDmac::setChainSourceFirstCycle()
{
	// Set TADR to (MADR + (QWC * 0x10)) as the next tag address on first run.
	auto ADDR = mChannel->MADR->getFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR);
	auto SPRFlag = mChannel->MADR->getFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR);
	auto QWC = mChannel->QWC->getFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC);
	mChannel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, ADDR + (QWC * 0x10));
	mChannel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR, SPRFlag);

	mChannel->mChainSrcFirstRun = false;
}

void EEDmac::setChainExitContextReset()
{
	mChannel->mChainSrcFirstRun = true;
	mChannel->mChainExitState = false;
	mChannel->mChainStackLevelState = 0;
}

bool EEDmac::readChainSourceTag()
{
	// Check first if we need to transfer the tag - return false if the channel queue is full.
	if (mChannel->CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::TTE))
	{
		if (isChannelQueueFull())
			return false;
	}

	// Read tag from TADR.
	// Get the main memory or SPR address we are reading or writing from.
	u128 data;
	const u32 TADR = mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR);
	const bool SPRFlag = (mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR) != 0);
	data = readDataMemory(TADR, SPRFlag);

	// Set mDMAtag based upon the u128 read from memory.
	mDMAtag.setValue(data.lo);

	// Set CHCR.TAG based upon the DMA tag read (bits 16-31).
	mChannel->CHCR->setFieldValue(EEDmacChannelRegister_CHCR_t::Fields::TAG, (data.lo >> 16) & 0xFFFF);

	// Check if we need to transfer the tag.
	if (mChannel->CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::TTE))
	{
		// Write the tag to the channel.
		writeDataChannel(data);

		// Update DataCountState by 1 (counts towards slice channel quota).
		mChannel->mSliceCountState += 1;
	}

	return true;
}

bool EEDmac::readChainDestTag()
{
	// Check first if there is data available.
	if (isChannelQueueEmpty())
		return false;

	// Read tag from channel FIFO (always next to transfer data).
	u128 data = readDataChannel();

	// Set mDMAtag based upon the u128 read from the channel.
	mDMAtag.setValue(data.lo);

	// Set CHCR.TAG based upon the DMA tag read (bits 16-31).
	mChannel->CHCR->setFieldValue(EEDmacChannelRegister_CHCR_t::Fields::TAG, (data.lo >> 16) & 0xFFFF);

	// Check if we need to transfer the tag.
	if (mChannel->CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::TTE))
	{
		// Write the tag to memory (MADR) and increment.
		const u32 MADR = mChannel->MADR->getFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR);
		const bool SPRFlag = (mChannel->MADR->getFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR) != 0);
		writeDataMemory(MADR, SPRFlag, data);
		mChannel->MADR->increment();

		// Update DataCountState by 1 (counts towards slice channel quota).
		mChannel->mSliceCountState += 1;
	}
	
	return true;
}

void EEDmac::INSTRUCTION_UNSUPPORTED()
{
	throw std::runtime_error("DMAC chain mode called invalid tag ID");
}

void EEDmac::SRC_CNT()
{
	// Transfers QWC qwords after the tag, and reads the next qword as the next tag.
	mChannel->QWC->setFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC, mDMAtag.getQWC());

	// Copy TADR + 0x10 into MADR.
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10);
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR));

	// Calculate where the next tag will be.
	u32 nextTagAddr = mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + (mDMAtag.getQWC() + 1) * 0x10;
	mChannel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, nextTagAddr); // SPR flag unchanged within TADR register.
}

void EEDmac::SRC_NEXT()
{
	// Transfers QWC qwords after the tag, and reads the ADDR field as the next tag.
	mChannel->QWC->setFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC, mDMAtag.getQWC());

	// Copy TADR + 0x10 into MADR.
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10);
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR));

	// Set next tag.
	mChannel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, mDMAtag.getADDR());
	mChannel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, mDMAtag.getSPR());
}

void EEDmac::SRC_REF()
{
	// Transfers QWC qwords from ADDR field, and reads the next qword as the tag.
	mChannel->QWC->setFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC, mDMAtag.getQWC());

	// Set MADR = tag.ADDR.
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mDMAtag.getADDR());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mDMAtag.getSPR());

	// Set next qword as tag.
	mChannel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10); // SPR flag unchanged within TADR register.
}

void EEDmac::SRC_REFS()
{
	// TODO: add in stall control.

	// Transfers QWC qwords from ADDR field, and reads the next qword as the tag.
	mChannel->QWC->setFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC, mDMAtag.getQWC());

	// Set MADR = tag.ADDR.
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mDMAtag.getADDR());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mDMAtag.getSPR());

	// Set next qword as tag.
	mChannel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10); // SPR flag unchanged within TADR register.
}

void EEDmac::SRC_REFE()
{
	// Transfers QWC qwords from ADDR, and suspends after packet transfer.
	mChannel->QWC->setFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC, mDMAtag.getQWC());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mDMAtag.getADDR());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mDMAtag.getSPR());
	mChannel->mChainExitState = true;
}

void EEDmac::SRC_CALL()
{
	// Transfers QWC qwords after tag, and pushes the next qword after the tag onto the stack. Sets the next tag to ADDR field.
	mChannel->QWC->setFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC, mDMAtag.getQWC());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10);
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR));
	mChannel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, mDMAtag.getADDR());
	mChannel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR, mDMAtag.getSPR());

	// Set stack to after tag.
	u32& stackIdx = mChannel->mChainStackLevelState;

	if (stackIdx >= 2)
	{
		// Check for stack overflow.
		mChannel->mChainExitState = true;
	}
	else
	{
		// Push onto the stack.
		mChannel->ASR[stackIdx]->setFieldValue(EEDmacChannelRegister_ASR_t::Fields::ADDR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10);
		mChannel->ASR[stackIdx]->setFieldValue(EEDmacChannelRegister_ASR_t::Fields::SPR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR));
		stackIdx += 1;
	}
}

void EEDmac::SRC_RET()
{
	// Transfers QWC qwords after tag, pops next tag from stack. If stack level = 0, transfers QWC qwords after tag and suspends transfer.
	u32& stackIdx = mChannel->mChainStackLevelState;
	if (stackIdx > 0)
	{
		// Pop the stack.
		mChannel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, mChannel->ASR[stackIdx]->getFieldValue(EEDmacChannelRegister_ASR_t::Fields::ADDR));
		mChannel->TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, mChannel->ASR[stackIdx]->getFieldValue(EEDmacChannelRegister_ASR_t::Fields::SPR));
		stackIdx -= 1;
	}
	else
	{
		// Check for stack underflow.
		mChannel->mChainExitState = true;
	}

	// In both cases, QWC following the tag is always performed.
	mChannel->QWC->setFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC, mDMAtag.getQWC());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10);
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR));
}

void EEDmac::SRC_END()
{
	// Transfers QWC qwords after tag, and suspends after packet transfer.
	mChannel->QWC->setFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC, mDMAtag.getQWC());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10);
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mChannel->TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR));
	mChannel->mChainExitState = true;
}

void EEDmac::DST_CNT()
{
	// Transfers QWC qwords after the tag to tag.ADDR, and reads the next qword as the next tag.
	mChannel->QWC->setFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC, mDMAtag.getQWC());

	// Set MADR to tag values.
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mDMAtag.getADDR());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mDMAtag.getSPR());
}

void EEDmac::DST_CNTS()
{
	// TODO: need to copy MADR to STADR during the transfer.
	// Transfers QWC qwords after the tag to tag.ADDR, and reads the next qword as the next tag.
	mChannel->QWC->setFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC, mDMAtag.getQWC());

	// Set MADR to tag values.
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mDMAtag.getADDR());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mDMAtag.getSPR());
}

void EEDmac::DST_END()
{
	// Transfers QWC qwords after the tag to tag.ADDR, and suspends transfer after completing.
	mChannel->QWC->setFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC, mDMAtag.getQWC());

	// Set MADR to tag values.
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR, mDMAtag.getADDR());
	mChannel->MADR->setFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR, mDMAtag.getSPR());
	mChannel->mChainExitState = true;
}

bool EEDmac::isInterleaveInSkipMode()
{
	if (mChannel->mInterleavedInSkipBlock)
		return true;
	else
		return false;
}

bool EEDmac::isInterleaveLimitReached()
{
	// In transfer block?
	if (!mChannel->mInterleavedInSkipBlock)
	{
		// Have we reached the TWQC limit?
		if (mChannel->mInterleavedBlockCount >= mDMAC->SQWC->getFieldValue(EEDmacRegister_SWQC_t::Fields::TQWC))
		{
			return true;
		}
	}

	// In skip block?
	if (mChannel->mInterleavedInSkipBlock)
	{
		// Have we reached the TWQC limit?
		if (mChannel->mInterleavedBlockCount >= mDMAC->SQWC->getFieldValue(EEDmacRegister_SWQC_t::Fields::SQWC))
		{
			return true;
		}
	}

	return false;
}

void EEDmac::setInterleaveModeToggle()
{
	// Toggle mode and reset the count.
	mChannel->mInterleavedInSkipBlock = !mChannel->mInterleavedInSkipBlock;
	mChannel->mInterleavedBlockCount = 0;
}

void EEDmac::setInterleaveModeCountIncrement()
{
	mChannel->mInterleavedBlockCount += 1;
}

void EEDmac::setInterleaveSkipDataCycle()
{
	mChannel->MADR->increment();
}
