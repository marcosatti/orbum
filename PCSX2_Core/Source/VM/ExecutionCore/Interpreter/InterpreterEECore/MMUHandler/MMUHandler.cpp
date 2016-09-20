#include "stdafx.h"

#include <cmath>

#include "Common/Global/Globals.h"

#include "VM/VMMain.h"
#include "VM/VMMMUHandler/VMMMUHandler.h"
#include "VM/ExecutionCore/Interpreter/InterpreterEECore/MMUHandler/MMUHandler.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/EE/EECore/EECore_t.h"
#include "Common/PS2Resources/EE/EECore/COP0/COP0_t.h"
#include "Common/PS2Resources/EE/EECore/COP0/Types/COP0_BitfieldRegisters_t.h"
#include "Common/PS2Resources/EE/EECore/Exceptions/Types/EECoreException_t.h"
#include "Common/PS2Resources/EE/EECore/MMU/MMU_t.h"
#include "Common/Util/EECoreMMUUtil/EECoreMMUUtil.h"

using TLBEntryInfo = MMU_t::TLBEntryInfo;

MMUHandler::MMUHandler(const VMMain *const vmMain) : 
	VMExecutionCoreComponent(vmMain),
	mHasExceptionOccurred(false), 
	mTLBEntryInfo(&MMU_t::EMPTY_TLB_ENTRY)
{
}

u8 MMUHandler::readByteU(u32 PS2MemoryAddress)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress);
	if (!mHasExceptionOccurred)
		return getVM()->getMMU()->readByteU(PS2PhysicalAddress);
	else
		return 0;
}

void MMUHandler::writeByteU(u32 PS2MemoryAddress, u8 value) 
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress);
	if (!mHasExceptionOccurred)
		getVM()->getMMU()->writeByteU(PS2PhysicalAddress, value);	
}

s8 MMUHandler::readByteS(u32 PS2MemoryAddress)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress);
	if (!mHasExceptionOccurred)
		return getVM()->getMMU()->readByteS(PS2PhysicalAddress);
	else
		return 0;
}

void MMUHandler::writeByteS(u32 PS2MemoryAddress, s8 value)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress);
	if (!mHasExceptionOccurred)
		getVM()->getMMU()->writeByteS(PS2PhysicalAddress, value);
}

u16 MMUHandler::readHwordU(u32 PS2MemoryAddress) 
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress);
	if (!mHasExceptionOccurred)
		return getVM()->getMMU()->readHwordU(PS2PhysicalAddress);
	else
		return 0;
}

void MMUHandler::writeHwordU(u32 PS2MemoryAddress, u16 value)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress);
	if (!mHasExceptionOccurred)
		getVM()->getMMU()->writeHwordU(PS2PhysicalAddress, value);
}

s16 MMUHandler::readHwordS(u32 PS2MemoryAddress)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress);
	if (!mHasExceptionOccurred)
		return getVM()->getMMU()->readHwordS(PS2PhysicalAddress);
	else
		return 0;
}

void MMUHandler::writeHwordS(u32 PS2MemoryAddress, s16 value) 
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress);
	if (!mHasExceptionOccurred)
		getVM()->getMMU()->writeHwordS(PS2PhysicalAddress, value);
}

u32 MMUHandler::readWordU(u32 PS2MemoryAddress)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress);
	if (!mHasExceptionOccurred)
		return getVM()->getMMU()->readWordU(PS2PhysicalAddress);
	else
		return 0;
}

void MMUHandler::writeWordU(u32 PS2MemoryAddress, u32 value)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress);
	if (!mHasExceptionOccurred)
		getVM()->getMMU()->writeWordU(PS2PhysicalAddress, value);
}

s32 MMUHandler::readWordS(u32 PS2MemoryAddress)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress);
	if (!mHasExceptionOccurred)
		return getVM()->getMMU()->readWordS(PS2PhysicalAddress);
	else
		return 0;
}

void MMUHandler::writeWordS(u32 PS2MemoryAddress, s32 value)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress);
	if (!mHasExceptionOccurred)
		getVM()->getMMU()->writeWordS(PS2PhysicalAddress, value);
}

u64 MMUHandler::readDwordU(u32 PS2MemoryAddress) 
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress);
	if (!mHasExceptionOccurred)
		return getVM()->getMMU()->readDwordU(PS2PhysicalAddress);
	else
		return 0;
}

void MMUHandler::writeDwordU(u32 PS2MemoryAddress, u64 value)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress);
	if (!mHasExceptionOccurred)
		getVM()->getMMU()->writeDwordU(PS2PhysicalAddress, value);
}

s64 MMUHandler::readDwordS(u32 PS2MemoryAddress)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress);
	if (!mHasExceptionOccurred)
		return getVM()->getMMU()->readDwordS(PS2PhysicalAddress);
	else
		return 0;
}

void MMUHandler::writeDwordS(u32 PS2MemoryAddress, s64 value) 
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress);
	if (!mHasExceptionOccurred)
		getVM()->getMMU()->writeDwordS(PS2PhysicalAddress, value);
}

bool MMUHandler::hasExceptionOccurred() const
{
	return mHasExceptionOccurred;
}

EECoreException_t MMUHandler::getExceptionInfo()
{
	mHasExceptionOccurred = false;

	// Create TLB exception info.
	TLBExceptionInfo_t tlbInfo =
	{
		mPS2VirtualAddress,
		getVM()->getResources()->EE->EECore->COP0->Context->getFieldValue(COP0RegisterContext_t::Fields::PTEBase),
		EECoreMMUUtil::getVirtualAddressHI19(mPS2VirtualAddress), 
		mTLBEntryInfo->mASID, 
		getVM()->getResources()->EE->EECore->MMU->getNewTLBIndex()
	};

	// Return the exception.
	return EECoreException_t(mExType, &tlbInfo, nullptr, nullptr);
}

u32 MMUHandler::getPS2PhysicalAddress(u32 PS2VirtualAddress)
{
	// Set the virtual address context.
	mPS2VirtualAddress = PS2VirtualAddress;

	// Perform the lookup.
	getPS2PhysicalAddress_Stage1();

	return mPS2PhysicalAddress;
}

void MMUHandler::getPS2PhysicalAddress_Stage1()
{
	// This process follows the information and diagram given on page 121 & 122 of the EE Core Users Manual. 
	// I am unsure if this is exactly what happens, as the information is a bit vague on how to obtain the page mask and ASID, 
	//  but I'm confident this is what it meant (I also dont see another way to do it).
	// Note: In the kernel context mode, for an VA in kseg0 and kseg1 a physical address is immediately returned, as they are both unmapped - no translation occurs.

	// BIG NOTE: where the lower bound of memory segments is 0x00000000, it has been omitted from the test statement (as it is implied through the use of u32).

	// Step 1 is to determine which CPU context we are in (user, supervisor or kernel).
	// User mode when KSU = 2, ERL = 0, EXL = 0 in the status register.
	if (getVM()->getResources()->EE->EECore->COP0->isOperatingUserMode())
	{
		// Operating in user mode.
		// First we check if the VA is within the context bounds.
		if (mPS2VirtualAddress > PS2Constants::EE::EECore::MMU::VADDRESS_USER_UPPER_BOUND)
		{
			// Throw address error if not within bounds.
			if (mAccessType == READ)
				mExType = EECoreException_t::ExType::EX_ADDRESS_ERROR_INSTRUCTION_FETCH_LOAD;
			else if (mAccessType == WRITE)
				mExType = EECoreException_t::ExType::EX_ADDRESS_ERROR_STORE;
			else 
				throw std::runtime_error("MMUHandler: could not throw internal EECoreException_t error (type = address error).");

			// Update state and return.
			mHasExceptionOccurred = true;
			return;
		}

		getPS2PhysicalAddress_Stage2();
	}
	else if (getVM()->getResources()->EE->EECore->COP0->isOperatingSupervisorMode())
	{
		// Operating in supervisor mode.
		// First we check if the VA is within the context bounds.
		if ((mPS2VirtualAddress > PS2Constants::EE::EECore::MMU::VADDRESS_SUPERVISOR_UPPER_BOUND_1 && mPS2VirtualAddress < PS2Constants::EE::EECore::MMU::VADDRESS_SUPERVISOR_LOWER_BOUND_2)
			|| (mPS2VirtualAddress > PS2Constants::EE::EECore::MMU::VADDRESS_SUPERVISOR_UPPER_BOUND_2))
		{
			// Throw address error if not within bounds.
			if (mAccessType == READ)
				mExType = EECoreException_t::ExType::EX_ADDRESS_ERROR_INSTRUCTION_FETCH_LOAD;
			else if (mAccessType == WRITE)
				mExType = EECoreException_t::ExType::EX_ADDRESS_ERROR_STORE;
			else 
				throw std::runtime_error("MMUHandler: could not throw internal EECoreException_t error (type = address error).");

			// Update state and return.
			mHasExceptionOccurred = true;
			return;
		}

		getPS2PhysicalAddress_Stage2();
	} 
	else if (getVM()->getResources()->EE->EECore->COP0->isOperatingKernelMode())
	{
		// Operating in kernel mode.
		// We do not need to check if the VA is valid - it is always valid over the full 4GB (U32) address space. However, kseg0 and kseg1 are not mapped, 
		//  and instead directly translate to physical addresses from 0x00000000 -> 0x1FFFFFFF (we need to emulate this). We also need to test for if
		//  Status.ERL == 1, in which case kuseg is unmapped. See EE Core Users Manual page 113 (especially notes).

		// Test for kseg0
		if (mPS2VirtualAddress >= PS2Constants::EE::EECore::MMU::VADDRESS_KERNEL_LOWER_BOUND_2 && mPS2VirtualAddress <= PS2Constants::EE::EECore::MMU::VADDRESS_KERNEL_UPPER_BOUND_2)
		{
			// We are in kseg0, so to get the physical address we just minus the kseg0 base address of 0x80000000.
			// We also do not test for the Config.K0 status, as we do not involve caches unless it is an explicit request.
			mPS2PhysicalAddress = (mPS2VirtualAddress - PS2Constants::EE::EECore::MMU::VADDRESS_KERNEL_LOWER_BOUND_2);
			return;
		}

		// Test for kseg1
		if (mPS2VirtualAddress >= PS2Constants::EE::EECore::MMU::VADDRESS_KERNEL_LOWER_BOUND_3 && mPS2VirtualAddress <= PS2Constants::EE::EECore::MMU::VADDRESS_KERNEL_UPPER_BOUND_3)
		{
			// We are in kseg1, so to get the physical address we just minus the kseg1 base address of 0xA0000000.
			mPS2PhysicalAddress = (mPS2VirtualAddress - PS2Constants::EE::EECore::MMU::VADDRESS_KERNEL_LOWER_BOUND_3);
			return;
		}
		
		// Test for Status.ERL = 1 (indicating kuseg is unmapped). Note that the VA still has to be within the segment bounds for this to work.
		if (getVM()->getResources()->EE->EECore->COP0->Status->getFieldValue(COP0RegisterStatus_t::Fields::ERL) == 1) {
			if (mPS2VirtualAddress <= PS2Constants::EE::EECore::MMU::VADDRESS_KERNEL_UPPER_BOUND_1)
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
		throw std::runtime_error("MMUHandler: could not determine context. Needs debugging!");
	}
}

void MMUHandler::getPS2PhysicalAddress_Stage2()
{
	// Stage 2 is to search through the TLB to see if there is a VPN match. 
	// Check if its in the TLB and get the information.
	s32 index = getVM()->getResources()->EE->EECore->MMU->findTLBIndex(mPS2VirtualAddress);
	if (index == -1)
	{
		// A match was not found, throw a TLB miss PS2 exception.
		if (mAccessType == READ)
			mExType = EECoreException_t::ExType::EX_TLB_REFILL_INSTRUCTION_FETCH_LOAD;
		else if (mAccessType == WRITE)
			mExType = EECoreException_t::ExType::EX_TLB_REFILL_STORE;
		else
			throw std::runtime_error("MMUHandler: could not throw internal EECoreException_t error (type = tlb refill).");
		
		// Update state and return.
		mHasExceptionOccurred = true;
		return;
	}
	mTLBEntryInfo = &getVM()->getResources()->EE->EECore->MMU->getTLBEntry(index);

	// Check the global bit, and check ASID if needed (against the ASID value in the EntryHi COP0 register).
	// TODO: Check if ASID checking is correct.
	if (mTLBEntryInfo->mG == 0)
	{
		// Not a global page map, need to make sure ASID's are the same.
		if (getVM()->getResources()->EE->EECore->COP0->EntryHi->getFieldValue(COP0RegisterEntryHi_t::Fields::ASID) != mTLBEntryInfo->mASID)
		{
			// Generate TLB refill exception.
			if (mAccessType == READ)
				mExType = EECoreException_t::ExType::EX_TLB_REFILL_INSTRUCTION_FETCH_LOAD;
			else if (mAccessType == WRITE)
				mExType = EECoreException_t::ExType::EX_TLB_REFILL_STORE;
			else
				throw std::runtime_error("MMUHandler: could not throw internal EECoreException_t error (type = tlb refill).");

			// Update state and return.
			mHasExceptionOccurred = true;
			return;
		}
	}

	// Move on to stage 3.
	getPS2PhysicalAddress_Stage3();
}

void MMUHandler::getPS2PhysicalAddress_Stage3()
{
	// Stage 3: Assess if the page is valid and it is marked dirty. Also check for the scratchpad ram access (deviates from the documentation a little).

	// Check if accessing scratchpad
	if (mTLBEntryInfo->mS)
	{
		// As mentioned in the TLB implementation (see the class MMU_t), the scratchpad ram is allocated in the TLB as a continuous block of 4 x 4KB pages (16KB).
		// This means that the VPN occupies the upper 18 bits, with the 2 next lower bits selecting which 4KB page we are in (0 -> 3).

		// In order to access the SPR within the emulator, we are utilising the 'reserved' region of the PS2's physical memory map. Since there is nothing allocated
		//  in this region for the PS2, we are free to use it for our own purposes. See Docs/Memory Mappings.xlsx for all of PCSX2's PS2 physical memory maps, 
		//  including non-standard maps.
		// The scratchpad ram (in PCSX2) corresponds to PS2 physical address 0x14000000.
		u32 offset16KB = mPS2VirtualAddress & Constants::MASK_16KB;
		mPS2PhysicalAddress = PS2Constants::EE::EECore::ScratchpadMemory::PADDRESS_SCRATCHPAD_MEMORY + offset16KB;
		return;
	}

	// Need to check now before continuing if the VPN is for a even or odd page. This is done by checking the LSB of the VPN from the original address accessed.
	// Neat trick: +1 to the TLB mask to get the mask for the LSB of the VPN.
	if (mPS2VirtualAddress & (mTLBEntryInfo->mMask + 1))
	{
		// Odd
		// Check if the entry is valid (V bit)
		if (!mTLBEntryInfo->mVOdd)
		{
			// Raise TLB invalid exception
			if (mAccessType == READ)
				mExType = EECoreException_t::ExType::EX_TLB_INVALID_INSTRUCTION_FETCH_LOAD;
			else if (mAccessType == WRITE)
				mExType = EECoreException_t::ExType::EX_TLB_INVALID_STORE;
			else
				throw std::runtime_error("MMUHandler: could not throw internal EECoreException_t error (type = tlb invalid).");

			// Update state and return.
			mHasExceptionOccurred = true;
			return;
		}	
		
		// Check if entry is allowed writes (dirty flag)
		if (!mTLBEntryInfo->mDOdd)
		{
			// Raise TLB modified exception if writing occurs.
			if (mAccessType == WRITE)
			{
				mExType = EECoreException_t::ExType::EX_TLB_MODIFIED;
				// Update state and return.
				mHasExceptionOccurred = true;
				return;
			}
		}

		// Move on to stage 4 (odd)
		return getPS2PhysicalAddress_Stage4Odd();
	}
	else
	{
		// Even
		// Check if the entry is valid (V bit)
		if (!mTLBEntryInfo->mVEven)
		{
			// Raise TLB invalid exception
			if (mAccessType == READ)
				mExType = EECoreException_t::ExType::EX_TLB_INVALID_INSTRUCTION_FETCH_LOAD;
			else if (mAccessType == WRITE)
				mExType = EECoreException_t::ExType::EX_TLB_INVALID_STORE;
			else
				throw std::runtime_error("MMUHandler: could not throw internal EECoreException_t error (type = tlb invalid).");

			// Update state and return.
			mHasExceptionOccurred = true;
			return;
		}

		// Check if entry is allowed writes (dirty flag)
		if (!mTLBEntryInfo->mDEven)
		{
			// Raise TLB modified exception if writing occurs.
			if (mAccessType == WRITE)
			{
				mExType = EECoreException_t::ExType::EX_TLB_MODIFIED;
				// Update state and return.
				mHasExceptionOccurred = true;
				return;
			}
		}

		// Move on to stage 4 (odd)
		return getPS2PhysicalAddress_Stage4Even();
	}
}

void MMUHandler::getPS2PhysicalAddress_Stage4Odd()
{
	// Cache access?
	// TODO: Maybe we actually dont need this in the emulator as the C flag only describes the cache method, not a location. The location is still refering to main memory.
	// See EE Core Users Manual page 126.
	/*
	if (tlbEntry.mCOdd > 0)
	{
	}
	*/

	// Else we are accessing main memory.
	// Combine PFN with offset using the TLB entry mask.
	u32 PFNBitPos = static_cast<u32>(log2(mTLBEntryInfo->mMask + 1));
	mPS2PhysicalAddress = ((mTLBEntryInfo->mPFNOdd << PFNBitPos) | (mPS2VirtualAddress & mTLBEntryInfo->mMask));
}

void MMUHandler::getPS2PhysicalAddress_Stage4Even()
{
	// Cache access?
	// TODO: Maybe we actually dont need this in the emulator as the C flag only describes the cache method, not a location. The location is still refering to main memory.
	// See EE Core Users Manual page 126.
	/*
	if (tlbEntry.mCEven > 0)
	{
	}
	*/

	// Else we are accessing main memory.
	// Combine PFN with offset using the TLB entry mask.
	u32 PFNBitPos = static_cast<u32>(log2(mTLBEntryInfo->mMask + 1));
	mPS2PhysicalAddress = ((mTLBEntryInfo->mPFNEven << PFNBitPos) | (mPS2VirtualAddress & mTLBEntryInfo->mMask));
}
