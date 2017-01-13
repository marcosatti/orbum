#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Context_t.h"
#include "Common/Util/MMUUtil/MMUUtil.h"
#include "Common/Types/PhysicalMMU/PhysicalMMU_t.h"

#include "VM/ExecutionCore/Interpreter/IOP/IOPCoreInterpreter/IOPCoreMMUHandler/IOPCoreMMUHandler.h"

#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/IOP/IOP_t.h"
#include "PS2Resources/IOP/IOPCore/IOPCore_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreCOP0_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreCOP0Registers_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreException_t.h"

IOPCoreMMUHandler::IOPCoreMMUHandler(VMMain * vmMain) : 
	VMExecutionCoreComponent(vmMain),
	mHasExceptionOccurred(false)
{
}

u8 IOPCoreMMUHandler::readByte(u32 PS2MemoryAddress)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, READ);
	if (!mHasExceptionOccurred)
		return  getResources()->IOP->PhysicalMMU->readByte(Context_t::IOP, PS2PhysicalAddress);
	else
		return 0;
}

void IOPCoreMMUHandler::writeByte(u32 PS2MemoryAddress, u8 value) 
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, WRITE);
	if (!mHasExceptionOccurred && !mHasISCFailed)
		 getResources()->IOP->PhysicalMMU->writeByte(Context_t::IOP, PS2PhysicalAddress, value);	
}

u16 IOPCoreMMUHandler::readHword(u32 PS2MemoryAddress) 
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, READ);
	if (!mHasExceptionOccurred)
		return  getResources()->IOP->PhysicalMMU->readHword(Context_t::IOP, PS2PhysicalAddress);
	else
		return 0;
}

void IOPCoreMMUHandler::writeHword(u32 PS2MemoryAddress, u16 value)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, WRITE);
	if (!mHasExceptionOccurred && !mHasISCFailed)
		 getResources()->IOP->PhysicalMMU->writeHword(Context_t::IOP, PS2PhysicalAddress, value);
}

u32 IOPCoreMMUHandler::readWord(u32 PS2MemoryAddress)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, READ);
	if (!mHasExceptionOccurred)
		return getResources()->IOP->PhysicalMMU->readWord(Context_t::IOP, PS2PhysicalAddress);
	else
		return 0;

}

void IOPCoreMMUHandler::writeWord(u32 PS2MemoryAddress, u32 value)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, WRITE);

	if (!mHasExceptionOccurred && !mHasISCFailed)
		getResources()->IOP->PhysicalMMU->writeWord(Context_t::IOP, PS2PhysicalAddress, value);
}

bool IOPCoreMMUHandler::hasExceptionOccurred() const
{
	return mHasExceptionOccurred;
}

const IOPCoreException_t & IOPCoreMMUHandler::getException()
{
	mHasExceptionOccurred = false;
	return mException;
}

u32 IOPCoreMMUHandler::getPS2PhysicalAddress(u32 PS2VirtualAddress, AccessType accessType)
{
	// Set the virtual address and access type context.
	mPS2VirtualAddress = PS2VirtualAddress;
	mAccessType = accessType;

	// Reset IsC failed flag.
	mHasISCFailed = false;

	// Perform the lookup.
	getPS2PhysicalAddress_Stage1();

	// If an exception occured, set COP0 context.
	if (mHasExceptionOccurred)
	{
		throw std::runtime_error("IOP MMU error handling not implemented.");
	}

	return mPS2PhysicalAddress;
}

void IOPCoreMMUHandler::getPS2PhysicalAddress_Stage1()
{
	auto& COP0 = getResources()->IOP->IOPCore->COP0;

	// Step 1 is to determine which CPU context we are in (user or kernel).
	// User mode when KUc = 1, kernel when KUc = 0.
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
				mException = IOPCoreException_t::EX_ADDRESS_ERROR_INSTRUCTION_FETCH_LOAD;
			else if (mAccessType == WRITE)
				mException = IOPCoreException_t::EX_ADDRESS_ERROR_STORE;
			else
				throw std::runtime_error("IOPCoreMMUHandler: could not throw internal IOPCoreException_t error (type = address error).");

			// Update state and return.
			mHasExceptionOccurred = true;
			return;
		}
	}
	else if (COP0->isOperatingKernelMode())
	{
		// Operating in kernel mode.
		// We do not need to check if the VA is valid - it is always valid over the full 4GB (U32) address space. However, kseg0 and kseg1 are not mapped, 
		//  and instead directly translate to physical addresses from 0x00000000 -> 0x1FFFFFFF (we need to emulate this).

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
		
		// Undocumented: the IOP seems to access the addresses 0xFFC00000 - 0xFFFFFFFF as if it was trying to access the BIOS (0x1FC00000).
		// The IOP's PhysicalMMU has an image mapping to handle this address. From PCSX2 code.
		if (mPS2VirtualAddress >= PS2Constants::IOP::IOPCore::MMU::VADDRESS_SPECIAL_2_LOWER_BOUND)
		{
			mPS2PhysicalAddress = mPS2VirtualAddress;
			return;
		}

		// Undocumented: the IOP accesses addresses 0x00000000 - 0x001FFFFF as if it was trying to access the main memory (2MB).
		// This is not TLB mapped. From PCSX2 code.
		if (mPS2VirtualAddress <= PS2Constants::IOP::IOPCore::MMU::VADDRESS_SPECIAL_1_UPPER_BOUND)
		{
			// Check if isolate cache is turned on, set failed write flag if it is.
			if (COP0->Status->getFieldValue(IOPCoreCOP0Register_Status_t::Fields::IsC))
				mHasISCFailed = true;

			mPS2PhysicalAddress = mPS2VirtualAddress;
			return;
		}

		// Else in a mapped region - do normal translation.
		getPS2PhysicalAddress_Stage2();
	}
	else
	{
		// Throw runtime error as this should never happen.
		throw std::runtime_error("IOPCoreMMUHandler: could not determine context. Needs debugging!");
	}
}

void IOPCoreMMUHandler::getPS2PhysicalAddress_Stage2()
{
	throw std::runtime_error("Stage 2 called but IOP VA translation not implemented. Address was not in kernel segments!");
}