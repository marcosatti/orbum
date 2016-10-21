#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/ExecutionCore/Interpreter/IOP/IOPInterpreter/IOPMMUHandler/IOPMMUHandler.h"
#include "VM/VMMain.h"
#include "Common/PS2Resources/Types/PhysicalMMU/PhysicalMMU_t.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/IOP/IOP_t.h"
#include "Common/PS2Resources/IOP/IOPCOP0/IOPCOP0_t.h"
#include "Common/PS2Resources/Types/MIPSCoprocessor/COP0_BitfieldRegisters_t.h"
#include "Common/PS2Resources/IOP/IOPExceptions/Types/IOPException_t.h"
#include "Common/Util/MMUUtil/MMUUtil.h"

IOPMMUHandler::IOPMMUHandler(VMMain * vmMain) : 
	VMExecutionCoreComponent(vmMain),
	mClockSources{},
	mHasExceptionOccurred(false)
	//mTLBEntryInfo(&EECoreTLB_t::EMPTY_TLB_ENTRY)
{
}

const std::vector<ClockSource_t>& IOPMMUHandler::getClockSources()
{
	return mClockSources;
}

u8 IOPMMUHandler::readByteU(u32 PS2MemoryAddress)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress);
	if (!mHasExceptionOccurred)
		return  getVM()->getResources()->IOP->PhysicalMMU->readByteU(PS2PhysicalAddress);
	else
		return 0;
}

void IOPMMUHandler::writeByteU(u32 PS2MemoryAddress, u8 value) 
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress);
	if (!mHasExceptionOccurred)
		 getVM()->getResources()->IOP->PhysicalMMU->writeByteU(PS2PhysicalAddress, value);	
}

s8 IOPMMUHandler::readByteS(u32 PS2MemoryAddress)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress);
	if (!mHasExceptionOccurred)
		return  getVM()->getResources()->IOP->PhysicalMMU->readByteS(PS2PhysicalAddress);
	else
		return 0;
}

void IOPMMUHandler::writeByteS(u32 PS2MemoryAddress, s8 value)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress);
	if (!mHasExceptionOccurred)
		 getVM()->getResources()->IOP->PhysicalMMU->writeByteS(PS2PhysicalAddress, value);
}

u16 IOPMMUHandler::readHwordU(u32 PS2MemoryAddress) 
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress);
	if (!mHasExceptionOccurred)
		return  getVM()->getResources()->IOP->PhysicalMMU->readHwordU(PS2PhysicalAddress);
	else
		return 0;
}

void IOPMMUHandler::writeHwordU(u32 PS2MemoryAddress, u16 value)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress);
	if (!mHasExceptionOccurred)
		 getVM()->getResources()->IOP->PhysicalMMU->writeHwordU(PS2PhysicalAddress, value);
}

s16 IOPMMUHandler::readHwordS(u32 PS2MemoryAddress)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress);
	if (!mHasExceptionOccurred)
		return  getVM()->getResources()->IOP->PhysicalMMU->readHwordS(PS2PhysicalAddress);
	else
		return 0;
}

void IOPMMUHandler::writeHwordS(u32 PS2MemoryAddress, s16 value) 
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress);
	if (!mHasExceptionOccurred)
		 getVM()->getResources()->IOP->PhysicalMMU->writeHwordS(PS2PhysicalAddress, value);
}

u32 IOPMMUHandler::readWordU(u32 PS2MemoryAddress)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress);
	if (!mHasExceptionOccurred)
		return  getVM()->getResources()->IOP->PhysicalMMU->readWordU(PS2PhysicalAddress);
	else
		return 0;
}

void IOPMMUHandler::writeWordU(u32 PS2MemoryAddress, u32 value)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress);
	if (!mHasExceptionOccurred)
		 getVM()->getResources()->IOP->PhysicalMMU->writeWordU(PS2PhysicalAddress, value);
}

s32 IOPMMUHandler::readWordS(u32 PS2MemoryAddress)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress);
	if (!mHasExceptionOccurred)
		return  getVM()->getResources()->IOP->PhysicalMMU->readWordS(PS2PhysicalAddress);
	else
		return 0;
}

void IOPMMUHandler::writeWordS(u32 PS2MemoryAddress, s32 value)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress);
	if (!mHasExceptionOccurred)
		 getVM()->getResources()->IOP->PhysicalMMU->writeWordS(PS2PhysicalAddress, value);
}

bool IOPMMUHandler::hasExceptionOccurred() const
{
	return mHasExceptionOccurred;
}

const IOPException_t & IOPMMUHandler::getExceptionInfo()
{
	mHasExceptionOccurred = false;

	// Create TLB exception info.
	mExceptionInfo.mTLBExceptionInfo =
	{
		mPS2VirtualAddress,
		getVM()->getResources()->IOP->COP0->Context->getFieldValue(COP0RegisterContext_t::Fields::PTEBase),
		MMUUtil::getVirtualAddressHI19(mPS2VirtualAddress), 
		0, // mTLBEntryInfo->mASID, 
		0  // getVM()->getResources()->IOP->TLB->getNewTLBIndex()
	};

	// Return the exception.
	return mExceptionInfo;
}

u32 IOPMMUHandler::getPS2PhysicalAddress(u32 PS2VirtualAddress)
{
	logDebug("(%s, %d) IOP MMU Called. VA = 0x%08X.", __FILENAME__, __LINE__, PS2VirtualAddress);

	// Set the virtual address context.
	mPS2VirtualAddress = PS2VirtualAddress;

	// Perform the lookup.
	getPS2PhysicalAddress_Stage1();

	return mPS2PhysicalAddress;
}

void IOPMMUHandler::getPS2PhysicalAddress_Stage1()
{
	// This process follows the information and diagram given on page 121 & 122 of the EE Core Users Manual. 
	// I am unsure if this is exactly what happens, as the information is a bit vague on how to obtain the page mask and ASID, 
	//  but I'm confident this is what it meant (I also dont see another way to do it).
	// Note: In the kernel context mode, for an VA in kseg0 and kseg1 a physical address is immediately returned, as they are both unmapped - no translation occurs.

	// BIG NOTE: where the lower bound of memory segments is 0x00000000, it has been omitted from the test statement (as it is implied through the use of u32).

	// Step 1 is to determine which CPU context we are in (user, supervisor or kernel).
	// User mode when KSU = 2, ERL = 0, EXL = 0 in the status register.
	if (getVM()->getResources()->IOP->COP0->isOperatingUserMode())
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
			mExceptionInfo.mExType = IOPException_t::ExType::EX_ADDRESS_ERROR_INSTRUCTION_FETCH_LOAD;
			else if (mAccessType == WRITE)
			mExceptionInfo.mExType = IOPException_t::ExType::EX_ADDRESS_ERROR_STORE;
			else
			throw std::runtime_error("IOPMMUHandler: could not throw internal IOPException_t error (type = address error).");

			// Update state and return.
			mHasExceptionOccurred = true;
			return;
		}
	}
	else if (getVM()->getResources()->IOP->COP0->isOperatingSupervisorMode())
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
			mExceptionInfo.mExType = IOPException_t::ExType::EX_ADDRESS_ERROR_INSTRUCTION_FETCH_LOAD;
			else if (mAccessType == WRITE)
			mExceptionInfo.mExType = IOPException_t::ExType::EX_ADDRESS_ERROR_STORE;
			else
			throw std::runtime_error("IOPMMUHandler: could not throw internal IOPException_t error (type = address error).");

			// Update state and return.
			mHasExceptionOccurred = true;
			return;
		}
	} 
	else if (getVM()->getResources()->IOP->COP0->isOperatingKernelMode())
	{
		// Operating in kernel mode.
		// We do not need to check if the VA is valid - it is always valid over the full 4GB (U32) address space. However, kseg0 and kseg1 are not mapped, 
		//  and instead directly translate to physical addresses from 0x00000000 -> 0x1FFFFFFF (we need to emulate this). We also need to test for if
		//  Status.ERL == 1, in which case kuseg is unmapped. See EE Core Users Manual page 113 (especially notes).

		// Test for kseg0
		if (mPS2VirtualAddress >= PS2Constants::MIPS::MMU::VADDRESS_KERNEL_LOWER_BOUND_2 && mPS2VirtualAddress <= PS2Constants::MIPS::MMU::VADDRESS_KERNEL_UPPER_BOUND_2)
		{
			// We are in kseg0, so to get the physical address we just minus the kseg0 base address of 0x80000000.
			// We also do not test for the Config.K0 status, as we do not involve caches unless it is an explicit request.
			mPS2PhysicalAddress = (mPS2VirtualAddress - PS2Constants::MIPS::MMU::VADDRESS_KERNEL_LOWER_BOUND_2);
			return;
		}

		// Test for kseg1
		if (mPS2VirtualAddress >= PS2Constants::MIPS::MMU::VADDRESS_KERNEL_LOWER_BOUND_3 && mPS2VirtualAddress <= PS2Constants::MIPS::MMU::VADDRESS_KERNEL_UPPER_BOUND_3)
		{
			// We are in kseg1, so to get the physical address we just minus the kseg1 base address of 0xA0000000.
			mPS2PhysicalAddress = (mPS2VirtualAddress - PS2Constants::MIPS::MMU::VADDRESS_KERNEL_LOWER_BOUND_3);
			return;
		}
		
		// Test for Status.ERL = 1 (indicating kuseg is unmapped). Note that the VA still has to be within the segment bounds for this to work.
		if (getVM()->getResources()->IOP->COP0->Status->getFieldValue(COP0RegisterStatus_t::Fields::ERL) == 1) {
			if (mPS2VirtualAddress <= PS2Constants::MIPS::MMU::VADDRESS_KERNEL_UPPER_BOUND_1)
			{
				// We are in kuseg unmapped region, so just return the VA.
				mPS2PhysicalAddress = mPS2VirtualAddress;
				return;
			}
		}
		
		// Undocumented: the IOP seems to access the addresses 0xFFC00000 - 0xFFFFFFFF as if it was trying to access the BIOS (0x1FC00000).
		// The IOP's PhysicalMMU has an image mapping to handle this address.
		if (mPS2VirtualAddress >= 0xFFC00000)
		{
			mPS2PhysicalAddress = mPS2VirtualAddress;
			return;
		}

		// Undocumented: the IOP accesses addresses 0x00000000 - 0x001FFFFF as if it was trying to access the main memory (2MB).
		// This is not TLB mapped.
		if (mPS2VirtualAddress <= 0x001FFFFF)
		{
			mPS2PhysicalAddress = mPS2VirtualAddress;
			return;
		}

		// Else in a mapped region - do normal translation.
		getPS2PhysicalAddress_Stage2();
	}
	else
	{
		// Throw runtime error as this should never happen.
		throw std::runtime_error("IOPMMUHandler: could not determine context. Needs debugging!");
	}
}

void IOPMMUHandler::getPS2PhysicalAddress_Stage2()
{
	throw std::runtime_error("Stage 2 called but IOP VA translation not implemented. Address was not in kernel segments!");
}

/*
void IOPMMUHandler::getPS2PhysicalAddress_Stage2()
{
	// Stage 2 is to search through the TLB to see if there is a VPN match. 
	// Check if its in the TLB and get the information.
	s32 index = getVM()->getResources()->IOP->TLB->findTLBIndex(mPS2VirtualAddress);
	if (index == -1)
	{
		// A match was not found, throw a TLB miss PS2 exception.
		if (mAccessType == READ)
			mExceptionInfo.mExType = IOPException_t::ExType::EX_TLB_REFILL_INSTRUCTION_FETCH_LOAD;
		else if (mAccessType == WRITE)
			mExceptionInfo.mExType = IOPException_t::ExType::EX_TLB_REFILL_STORE;
		else
			throw std::runtime_error("IOPMMUHandler: could not throw internal IOPException_t error (type = tlb refill).");
		
		// Update state and return.
		mHasExceptionOccurred = true;
		return;
	}
	mTLBEntryInfo = &getVM()->getResources()->IOP->TLB->getTLBEntry(index);

	// Check the global bit, and check ASID if needed (against the ASID value in the EntryHi COP0 register).
	// TODO: Check if ASID checking is correct.
	if (mTLBEntryInfo->mG == 0)
	{
		// Not a global page map, need to make sure ASID's are the same.
		if (getVM()->getResources()->IOP->COP0->EntryHi->getFieldValue(COP0RegisterEntryHi_t::Fields::ASID) != mTLBEntryInfo->mASID)
		{
			// Generate TLB refill exception.
			if (mAccessType == READ)
				mExceptionInfo.mExType = IOPException_t::ExType::EX_TLB_REFILL_INSTRUCTION_FETCH_LOAD;
			else if (mAccessType == WRITE)
				mExceptionInfo.mExType = IOPException_t::ExType::EX_TLB_REFILL_STORE;
			else
				throw std::runtime_error("IOPMMUHandler: could not throw internal IOPException_t error (type = tlb refill).");

			// Update state and return.
			mHasExceptionOccurred = true;
			return;
		}
	}

	// Move on to stage 3.
	getPS2PhysicalAddress_Stage3();
}

void IOPMMUHandler::getPS2PhysicalAddress_Stage3()
{
	// Stage 3: Assess if the page is valid and it is marked dirty. Also check for the scratchpad ram access (deviates from the documentation a little).

	// Check if accessing scratchpad
	if (mTLBEntryInfo->mS)
	{
		// As mentioned in the TLB implementation (see the class EECoreTLB_t), the scratchpad ram is allocated in the TLB as a continuous block of 4 x 4KB pages (16KB).
		// This means that the VPN occupies the upper 18 bits, with the 2 next lower bits selecting which 4KB page we are in (0 -> 3).

		// In order to access the SPR within the emulator, we are utilising the 'reserved' region of the PS2's physical memory map. Since there is nothing allocated
		//  in this region for the PS2, we are free to use it for our own purposes. See Docs/Memory Mappings.xlsx for all of PCSX2's PS2 physical memory maps, 
		//  including non-standard maps.
		// The scratchpad ram (in PCSX2) corresponds to PS2 physical address 0x14000000.
		u32 offset16KB = mPS2VirtualAddress & Constants::MASK_16KB;
		mPS2PhysicalAddress = PS2Constants::EE::EECore::ScratchpadMemory::PADDRESS_SCRATCHPAD_MEMORY + offset16KB;
		return;
	}

	// Need to check now before continuing if the VPN is for a even or odd page (0 = Even, 1 = Odd). 
	// This is done by checking the LSB of the VPN from the original address accessed.
	// Neat trick: +1 to the TLB mask to get the mask for the LSB of the VPN.
	mIndexEvenOdd = mPS2VirtualAddress & (mTLBEntryInfo->mMask + 1);

	// Check if the entry is valid (V bit)
	if (!mTLBEntryInfo->PhysicalInfo[mIndexEvenOdd].mV)
	{
		// Raise TLB invalid exception
		if (mAccessType == READ)
			mExceptionInfo.mExType = IOPException_t::ExType::EX_TLB_INVALID_INSTRUCTION_FETCH_LOAD;
		else if (mAccessType == WRITE)
			mExceptionInfo.mExType = IOPException_t::ExType::EX_TLB_INVALID_STORE;
		else
			throw std::runtime_error("IOPMMUHandler: could not throw internal IOPException_t error (type = tlb invalid).");

		// Update state and return.
		mHasExceptionOccurred = true;
		return;
	}

	// Check if entry is allowed writes (dirty flag)
	if (!mTLBEntryInfo->PhysicalInfo[mIndexEvenOdd].mD)
	{
		// Raise TLB modified exception if writing occurs.
		if (mAccessType == WRITE)
		{
			mExceptionInfo.mExType = IOPException_t::ExType::EX_TLB_MODIFIED;
			// Update state and return.
			mHasExceptionOccurred = true;
			return;
		}
	}

	// Move on to stage 4.
	getPS2PhysicalAddress_Stage4();
}

void IOPMMUHandler::getPS2PhysicalAddress_Stage4()
{
	// Cache access?
	// TODO: Maybe we actually dont need this in the emulator as the C flag only describes the cache method, not a location. The location is still refering to main memory.
	// See EE Core Users Manual page 126.
	/*
	if (tlbEntry.PhysicalInfo[mIndexEvenOdd].mC > 0)
	{
	}
	

	// Else we are accessing main memory.
	// Combine PFN with offset using the TLB entry mask, to get the physical address (PhyAddr = PFN (shifted) | Offset).
	u32 mask = (mTLBEntryInfo->mMask << 12) | 0xFFF;
	mPS2PhysicalAddress = ((mTLBEntryInfo->PhysicalInfo[mIndexEvenOdd].mPFN << 12) | (mPS2VirtualAddress & mask));
}
*/