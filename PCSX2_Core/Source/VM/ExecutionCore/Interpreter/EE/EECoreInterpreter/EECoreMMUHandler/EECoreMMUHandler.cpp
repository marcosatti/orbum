#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VMMain.h"
#include "Common/Types/PhysicalMMU/PhysicalMMU_t.h"
#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreMMUHandler/EECoreMMUHandler.h"
#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreCOP0_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreCOP0Registers_t.h"
#include "Common/Types/MIPSCoprocessor/COP0Registers_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreException_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreTLB_t.h"
#include "Common/Util/MMUUtil/MMUUtil.h"
#include "PS2Resources/EE/EECore/Types/EECoreTLBEntryInfo_t.h"

EECoreMMUHandler::EECoreMMUHandler(VMMain * vmMain) : 
	VMExecutionCoreComponent(vmMain),
	mHasExceptionOccurred(false), 
	mAccessType(READ),
	mTLBEntryInfo(&EECoreTLB_t::EMPTY_TLB_ENTRY), 
	mPS2VirtualAddress(0), 
	mPS2PhysicalAddress(0),
	mIndexEvenOdd(0)
{
}

u8 EECoreMMUHandler::readByteU(u32 PS2MemoryAddress)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, READ);
	if (!mHasExceptionOccurred)
		return getResources()->EE->PhysicalMMU->readByteU(PS2PhysicalAddress);
	else
		return 0;
}

void EECoreMMUHandler::writeByteU(u32 PS2MemoryAddress, u8 value) 
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, WRITE);
	if (!mHasExceptionOccurred)
		getResources()->EE->PhysicalMMU->writeByteU(PS2PhysicalAddress, value);	
}

s8 EECoreMMUHandler::readByteS(u32 PS2MemoryAddress)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, READ);
	if (!mHasExceptionOccurred)
		return getResources()->EE->PhysicalMMU->readByteS(PS2PhysicalAddress);
	else
		return 0;
}

void EECoreMMUHandler::writeByteS(u32 PS2MemoryAddress, s8 value)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, WRITE);
	if (!mHasExceptionOccurred)
		getResources()->EE->PhysicalMMU->writeByteS(PS2PhysicalAddress, value);
}

u16 EECoreMMUHandler::readHwordU(u32 PS2MemoryAddress) 
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, READ);
	if (!mHasExceptionOccurred)
		return getResources()->EE->PhysicalMMU->readHwordU(PS2PhysicalAddress);
	else
		return 0;
}

void EECoreMMUHandler::writeHwordU(u32 PS2MemoryAddress, u16 value)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, WRITE);
	if (!mHasExceptionOccurred)
		getResources()->EE->PhysicalMMU->writeHwordU(PS2PhysicalAddress, value);
}

s16 EECoreMMUHandler::readHwordS(u32 PS2MemoryAddress)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, READ);
	if (!mHasExceptionOccurred)
		return getResources()->EE->PhysicalMMU->readHwordS(PS2PhysicalAddress);
	else
		return 0;
}

void EECoreMMUHandler::writeHwordS(u32 PS2MemoryAddress, s16 value) 
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, WRITE);
	if (!mHasExceptionOccurred)
		getResources()->EE->PhysicalMMU->writeHwordS(PS2PhysicalAddress, value);
}

u32 EECoreMMUHandler::readWordU(u32 PS2MemoryAddress)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, READ);
	if (!mHasExceptionOccurred)
		return getResources()->EE->PhysicalMMU->readWordU(PS2PhysicalAddress);
	else
		return 0;
}

void EECoreMMUHandler::writeWordU(u32 PS2MemoryAddress, u32 value)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, WRITE);
	if (!mHasExceptionOccurred)
		getResources()->EE->PhysicalMMU->writeWordU(PS2PhysicalAddress, value);
}

s32 EECoreMMUHandler::readWordS(u32 PS2MemoryAddress)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, READ);
	if (!mHasExceptionOccurred)
		return getResources()->EE->PhysicalMMU->readWordS(PS2PhysicalAddress);
	else
		return 0;
}

void EECoreMMUHandler::writeWordS(u32 PS2MemoryAddress, s32 value)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, WRITE);
	if (!mHasExceptionOccurred)
		getResources()->EE->PhysicalMMU->writeWordS(PS2PhysicalAddress, value);
}

u64 EECoreMMUHandler::readDwordU(u32 PS2MemoryAddress) 
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, READ);
	if (!mHasExceptionOccurred)
		return getResources()->EE->PhysicalMMU->readDwordU(PS2PhysicalAddress);
	else
		return 0;
}

void EECoreMMUHandler::writeDwordU(u32 PS2MemoryAddress, u64 value)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, WRITE);
	if (!mHasExceptionOccurred)
		getResources()->EE->PhysicalMMU->writeDwordU(PS2PhysicalAddress, value);
}

s64 EECoreMMUHandler::readDwordS(u32 PS2MemoryAddress)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, READ);
	if (!mHasExceptionOccurred)
		return getResources()->EE->PhysicalMMU->readDwordS(PS2PhysicalAddress);
	else
		return 0;
}

void EECoreMMUHandler::writeDwordS(u32 PS2MemoryAddress, s64 value) 
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, WRITE);
	if (!mHasExceptionOccurred)
		getResources()->EE->PhysicalMMU->writeDwordS(PS2PhysicalAddress, value);
}

u128 EECoreMMUHandler::readQwordU(u32 PS2VirtualAddress)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2VirtualAddress, READ);
	if (!mHasExceptionOccurred)
		return getResources()->EE->PhysicalMMU->readQwordU(PS2PhysicalAddress);
	else
		return u128(0, 0);
}

void EECoreMMUHandler::writeQwordU(u32 PS2VirtualAddress, u128 value)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2VirtualAddress, WRITE);
	if (!mHasExceptionOccurred)
		getResources()->EE->PhysicalMMU->writeQwordU(PS2PhysicalAddress, value);
}

bool EECoreMMUHandler::hasExceptionOccurred() const
{
	return mHasExceptionOccurred;
}

const EECoreException_t & EECoreMMUHandler::getExceptionInfo()
{
	mHasExceptionOccurred = false;

	// Create TLB exception info.
	mExceptionInfo.mTLBExceptionInfo =
	{
		mPS2VirtualAddress,
		getResources()->EE->EECore->COP0->Context->getFieldValue(EECoreCOP0Register_Context_t::Fields::PTEBase),
		MMUUtil::getVirtualAddressHI19(mPS2VirtualAddress), 
		mTLBEntryInfo->mASID, 
		getResources()->EE->EECore->TLB->getNewTLBIndex()
	};

	// Return the exception.
	return mExceptionInfo;
}

u32 EECoreMMUHandler::getPS2PhysicalAddress(u32 PS2VirtualAddress, AccessType accessType)
{
	// Set the virtual address and access type context.
	mPS2VirtualAddress = PS2VirtualAddress;
	mAccessType = accessType;

	// Perform the lookup.
	getPS2PhysicalAddress_Stage1();

	return mPS2PhysicalAddress;
}

void EECoreMMUHandler::getPS2PhysicalAddress_Stage1()
{
	// This process follows the information and diagram given on page 121 & 122 of the EE Core Users Manual. 
	// I am unsure if this is exactly what happens, as the information is a bit vague on how to obtain the page mask and ASID, 
	//  but I'm confident this is what it meant (I also dont see another way to do it).
	// Note: In the kernel context mode, for an VA in kseg0 and kseg1 a physical address is immediately returned, as they are both unmapped - no translation occurs.

	auto& COP0 = getResources()->EE->EECore->COP0;

	// Stage 1 is to determine which CPU context we are in (user, supervisor or kernel).
	// User mode when KSU = 2, ERL = 0, EXL = 0 in the status register.
	if (COP0->isOperatingUserMode())
	{
		// Operating in user mode.
		// First we check if the VA is within the context bounds.
		if (mPS2VirtualAddress <= PS2Constants::MIPS::MMU::VADDRESS_USER_UPPER_BOUND)
		{
			getPS2PhysicalAddress_Stage2();
		}
		else
		{
			// Throw address error if not within bounds.
			if (mAccessType == READ)
			mExceptionInfo.mExType = EECoreException_t::ExType::EX_ADDRESS_ERROR_INSTRUCTION_FETCH_LOAD;
			else if (mAccessType == WRITE)
			mExceptionInfo.mExType = EECoreException_t::ExType::EX_ADDRESS_ERROR_STORE;
			else
			throw std::runtime_error("EECoreMMUHandler: could not throw internal EECoreException_t error (type = address error).");

			// Update state and return.
			mHasExceptionOccurred = true;
			return;
		}
	}
	else if (COP0->isOperatingSupervisorMode())
	{
		// Operating in supervisor mode.
		// First we check if the VA is within the context bounds.
		if ((mPS2VirtualAddress >= PS2Constants::MIPS::MMU::VADDRESS_SUPERVISOR_LOWER_BOUND_2 && mPS2VirtualAddress <= PS2Constants::MIPS::MMU::VADDRESS_SUPERVISOR_UPPER_BOUND_1)
			|| (mPS2VirtualAddress <= PS2Constants::MIPS::MMU::VADDRESS_SUPERVISOR_UPPER_BOUND_2))
		{
			getPS2PhysicalAddress_Stage2();
		}
		else
		{
			// Throw address error if not within bounds.
			if (mAccessType == READ)
			mExceptionInfo.mExType = EECoreException_t::ExType::EX_ADDRESS_ERROR_INSTRUCTION_FETCH_LOAD;
			else if (mAccessType == WRITE)
			mExceptionInfo.mExType = EECoreException_t::ExType::EX_ADDRESS_ERROR_STORE;
			else
			throw std::runtime_error("EECoreMMUHandler: could not throw internal EECoreException_t error (type = address error).");

			// Update state and return.
			mHasExceptionOccurred = true;
			return;
		}
	}
	else if (COP0->isOperatingKernelMode())
	{
		// Operating in kernel mode.
		// We do not need to check if the VA is valid - it is always valid over the full 4GB (U32) address space. However, kseg0 and kseg1 are not mapped, 
		//  and instead directly translate to physical addresses from 0x00000000 -> 0x1FFFFFFF (we need to emulate this). We also need to test for if
		//  Status.ERL == 1, in which case kuseg is unmapped. See EE Core Users Manual page 113 (especially notes).

		// Test for kseg0
		if (mPS2VirtualAddress >= PS2Constants::MIPS::MMU::MMU::VADDRESS_KERNEL_LOWER_BOUND_2 && mPS2VirtualAddress <= PS2Constants::MIPS::MMU::MMU::VADDRESS_KERNEL_UPPER_BOUND_2)
		{
			// We are in kseg0, so to get the physical address we just minus the kseg0 base address of 0x80000000.
			// We also do not test for the Config.K0 status, as we do not involve caches unless it is an explicit request.
			mPS2PhysicalAddress = (mPS2VirtualAddress - PS2Constants::MIPS::MMU::MMU::VADDRESS_KERNEL_LOWER_BOUND_2);
			return;
		}

		// Test for kseg1
		if (mPS2VirtualAddress >= PS2Constants::MIPS::MMU::MMU::VADDRESS_KERNEL_LOWER_BOUND_3 && mPS2VirtualAddress <= PS2Constants::MIPS::MMU::MMU::VADDRESS_KERNEL_UPPER_BOUND_3)
		{
			// We are in kseg1, so to get the physical address we just minus the kseg1 base address of 0xA0000000.
			mPS2PhysicalAddress = (mPS2VirtualAddress - PS2Constants::MIPS::MMU::MMU::VADDRESS_KERNEL_LOWER_BOUND_3);
			return;
		}
		
		// Test for Status.ERL = 1 (indicating kuseg is unmapped). Note that the VA still has to be within the segment bounds for this to work.
		if (COP0->Status->getFieldValue(EECoreCOP0Register_Status_t::Fields::ERL) == 1) {
			if (mPS2VirtualAddress <= PS2Constants::MIPS::MMU::MMU::VADDRESS_KERNEL_UPPER_BOUND_1)
			{
				// We are in kuseg unmapped region, so just return the VA.
				mPS2PhysicalAddress = mPS2VirtualAddress;
				return;
			}
		}

		// Else in a mapped region - do normal translation.
		getPS2PhysicalAddress_Stage2();
	}
	else
	{
		// Throw runtime error as this should never happen.
		throw std::runtime_error("EECoreMMUHandler: could not determine context. Needs debugging!");
	}
}

void EECoreMMUHandler::getPS2PhysicalAddress_Stage2()
{
	auto& EECore = getResources()->EE->EECore;
	auto& COP0 = EECore->COP0;
	auto& TLB = EECore->TLB;

	// Stage 2 is to search through the TLB to see if there is a VPN match. 
	// Check if its in the TLB and get the information.
	s32 index = TLB->findTLBIndex(mPS2VirtualAddress);
	if (index == -1)
	{
		// A match was not found, throw a TLB miss PS2 exception.
		if (mAccessType == READ)
			mExceptionInfo.mExType = EECoreException_t::ExType::EX_TLB_REFILL_INSTRUCTION_FETCH_LOAD;
		else if (mAccessType == WRITE)
			mExceptionInfo.mExType = EECoreException_t::ExType::EX_TLB_REFILL_STORE;
		else
			throw std::runtime_error("EECoreMMUHandler: could not throw internal EECoreException_t error (type = tlb refill).");
		
		// Update state and return.
		mHasExceptionOccurred = true;
		return;
	}
	mTLBEntryInfo = &TLB->getTLBEntry(index);

	// Check the global bit, and check ASID if needed (against the ASID value in the EntryHi COP0 register).
	// TODO: Check if ASID checking is correct.
	if (mTLBEntryInfo->mG == 0)
	{
		// Not a global page map, need to make sure ASID's are the same.
		if (COP0->EntryHi->getFieldValue(EECoreCOP0Register_EntryHi_t::Fields::ASID) != mTLBEntryInfo->mASID)
		{
			// Generate TLB refill exception.
			if (mAccessType == READ)
				mExceptionInfo.mExType = EECoreException_t::ExType::EX_TLB_REFILL_INSTRUCTION_FETCH_LOAD;
			else if (mAccessType == WRITE)
				mExceptionInfo.mExType = EECoreException_t::ExType::EX_TLB_REFILL_STORE;
			else
				throw std::runtime_error("EECoreMMUHandler: could not throw internal EECoreException_t error (type = tlb refill).");

			// Update state and return.
			mHasExceptionOccurred = true;
			return;
		}
	}

	// Move on to stage 3.
	getPS2PhysicalAddress_Stage3();
}

void EECoreMMUHandler::getPS2PhysicalAddress_Stage3()
{
	// Stage 3: Assess if the page is valid and it is marked dirty. Also check for the scratchpad ram access (deviates from the documentation a little).

	// Check if accessing scratchpad
	if (mTLBEntryInfo->mS)
	{
		// As mentioned in the TLB implementation (see the class EECoreTLB_t), the scratchpad ram is allocated in the TLB as a continuous block of 4 x 4KB pages (16KB).
		// This means that the VPN occupies the upper 18 bits, with the 2 next lower bits selecting which 4KB page we are in (0 -> 3).
		u32 offset16KB = mPS2VirtualAddress & Constants::MASK_16KB;
		mPS2PhysicalAddress = PS2Constants::EE::EECore::ScratchpadMemory::PADDRESS_SCRATCHPAD_MEMORY + offset16KB;
		return;
	}

	// Need to check now before continuing if the VPN is for a even or odd page (0 = Even, 1 = Odd). 
	// This is done by checking the LSB of the VPN from the original address accessed.
	// Neat trick: +1 to the TLB mask to get the mask for the LSB of the VPN. Note that this mask is always equal to or greater than 4KB.
	u32 indexEvenOddMask = ((mTLBEntryInfo->mMask << 12) | 0xFFF) + 1;
	mIndexEvenOdd = (mPS2VirtualAddress & indexEvenOddMask) ? 1 : 0;

	// Check if the entry is valid (V bit)
	if (!mTLBEntryInfo->PhysicalInfo[mIndexEvenOdd].mV)
	{
		// Raise TLB invalid exception
		if (mAccessType == READ)
			mExceptionInfo.mExType = EECoreException_t::ExType::EX_TLB_INVALID_INSTRUCTION_FETCH_LOAD;
		else if (mAccessType == WRITE)
			mExceptionInfo.mExType = EECoreException_t::ExType::EX_TLB_INVALID_STORE;
		else
			throw std::runtime_error("EECoreMMUHandler: could not throw internal EECoreException_t error (type = tlb invalid).");

		// Update state and return.
		mHasExceptionOccurred = true;
		return;
	}

	// Check if entry is allowed writes (dirty flag) and raise TLB modified exception if writing occurs.
	if (!mTLBEntryInfo->PhysicalInfo[mIndexEvenOdd].mD && mAccessType == WRITE)
	{
		mExceptionInfo.mExType = EECoreException_t::ExType::EX_TLB_MODIFIED;
		// Update state and return.
		mHasExceptionOccurred = true;
		return;
	}

	// Move on to stage 4.
	getPS2PhysicalAddress_Stage4();
}

void EECoreMMUHandler::getPS2PhysicalAddress_Stage4()
{
	// Cache access?
	// TODO: Maybe we actually dont need this in the emulator as the C flag only describes the cache method, not a location. The location is still refering to main memory.
	// See EE Core Users Manual page 126.
	/*
	if (tlbEntry.PhysicalInfo[mIndexEvenOdd].mC > 0)
	{
	}
	*/

	// Else we are accessing main memory.
	// Combine PFN with offset using the TLB entry mask, to get the physical address (PhyAddr = PFN (shifted) | Offset).
	u32 mask = (mTLBEntryInfo->mMask << 12) | 0xFFF;
	mPS2PhysicalAddress = ((mTLBEntryInfo->PhysicalInfo[mIndexEvenOdd].mPFN << 12) | (mPS2VirtualAddress & mask));
}