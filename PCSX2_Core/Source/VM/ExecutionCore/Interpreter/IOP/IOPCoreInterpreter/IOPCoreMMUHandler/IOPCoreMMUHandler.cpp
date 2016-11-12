#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/ExecutionCore/Interpreter/IOP/IOPCoreInterpreter/IOPCoreMMUHandler/IOPCoreMMUHandler.h"
#include "VM/VMMain.h"
#include "Common/Types/PhysicalMMU/PhysicalMMU_t.h"
#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/IOP/IOP_t.h"
#include "PS2Resources/IOP/IOPCore/IOPCore_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreCOP0_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreCOP0Registers_t.h"
#include "Common/Types/MIPSCoprocessor/COP0Registers_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreException_t.h"
#include "Common/Util/MMUUtil/MMUUtil.h"

IOPCoreMMUHandler::IOPCoreMMUHandler(VMMain * vmMain) : 
	VMExecutionCoreComponent(vmMain),
	mClockSources{},
	mHasExceptionOccurred(false)
{
}

const std::vector<ClockSource_t>& IOPCoreMMUHandler::getClockSources()
{
	return mClockSources;
}

u8 IOPCoreMMUHandler::readByteU(u32 PS2MemoryAddress)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, READ);
	if (!mHasExceptionOccurred)
		return  getVM()->getResources()->IOP->PhysicalMMU->readByteU(PS2PhysicalAddress);
	else
		return 0;
}

void IOPCoreMMUHandler::writeByteU(u32 PS2MemoryAddress, u8 value) 
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, WRITE);
	if (!mHasExceptionOccurred && !mHasISCFailed)
		 getVM()->getResources()->IOP->PhysicalMMU->writeByteU(PS2PhysicalAddress, value);	
}

s8 IOPCoreMMUHandler::readByteS(u32 PS2MemoryAddress)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, READ);
	if (!mHasExceptionOccurred)
		return  getVM()->getResources()->IOP->PhysicalMMU->readByteS(PS2PhysicalAddress);
	else
		return 0;
}

void IOPCoreMMUHandler::writeByteS(u32 PS2MemoryAddress, s8 value)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, WRITE);
	if (!mHasExceptionOccurred && !mHasISCFailed)
		 getVM()->getResources()->IOP->PhysicalMMU->writeByteS(PS2PhysicalAddress, value);
}

u16 IOPCoreMMUHandler::readHwordU(u32 PS2MemoryAddress) 
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, READ);
	if (!mHasExceptionOccurred)
		return  getVM()->getResources()->IOP->PhysicalMMU->readHwordU(PS2PhysicalAddress);
	else
		return 0;
}

void IOPCoreMMUHandler::writeHwordU(u32 PS2MemoryAddress, u16 value)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, WRITE);
	if (!mHasExceptionOccurred && !mHasISCFailed)
		 getVM()->getResources()->IOP->PhysicalMMU->writeHwordU(PS2PhysicalAddress, value);
}

s16 IOPCoreMMUHandler::readHwordS(u32 PS2MemoryAddress)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, READ);
	if (!mHasExceptionOccurred)
		return  getVM()->getResources()->IOP->PhysicalMMU->readHwordS(PS2PhysicalAddress);
	else
		return 0;
}

void IOPCoreMMUHandler::writeHwordS(u32 PS2MemoryAddress, s16 value) 
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, WRITE);
	if (!mHasExceptionOccurred && !mHasISCFailed)
		 getVM()->getResources()->IOP->PhysicalMMU->writeHwordS(PS2PhysicalAddress, value);
}

u32 IOPCoreMMUHandler::readWordU(u32 PS2MemoryAddress)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, READ);
	if (!mHasExceptionOccurred)
		return  getVM()->getResources()->IOP->PhysicalMMU->readWordU(PS2PhysicalAddress);
	else
		return 0;
}

void IOPCoreMMUHandler::writeWordU(u32 PS2MemoryAddress, u32 value)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, WRITE);
	if (!mHasExceptionOccurred && !mHasISCFailed)
		 getVM()->getResources()->IOP->PhysicalMMU->writeWordU(PS2PhysicalAddress, value);
}

s32 IOPCoreMMUHandler::readWordS(u32 PS2MemoryAddress)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, READ);
	if (!mHasExceptionOccurred)
		return  getVM()->getResources()->IOP->PhysicalMMU->readWordS(PS2PhysicalAddress);
	else
		return 0;
}

void IOPCoreMMUHandler::writeWordS(u32 PS2MemoryAddress, s32 value)
{
	u32 PS2PhysicalAddress = getPS2PhysicalAddress(PS2MemoryAddress, WRITE);
	if (!mHasExceptionOccurred && !mHasISCFailed)
		 getVM()->getResources()->IOP->PhysicalMMU->writeWordS(PS2PhysicalAddress, value);
}

bool IOPCoreMMUHandler::hasExceptionOccurred() const
{
	return mHasExceptionOccurred;
}

const IOPCoreException_t & IOPCoreMMUHandler::getExceptionInfo()
{
	mHasExceptionOccurred = false;

	// Create TLB exception info.
	mExceptionInfo.mTLBExceptionInfo =
	{
		mPS2VirtualAddress,
		getVM()->getResources()->IOP->IOPCore->COP0->Context->getFieldValue(IOPCoreCOP0Register_Context_t::Fields::PTEBase),
		MMUUtil::getVirtualAddressHI19(mPS2VirtualAddress), 
		0, // mTLBEntryInfo->mASID, 
		0  // getVM()->getResources()->IOP->TLB->getNewTLBIndex()
	};

	// Return the exception.
	return mExceptionInfo;
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

	return mPS2PhysicalAddress;
}

void IOPCoreMMUHandler::getPS2PhysicalAddress_Stage1()
{
	auto& COP0 = getVM()->getResources()->IOP->IOPCore->COP0;

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
			mExceptionInfo.mExType = IOPCoreException_t::ExType::EX_ADDRESS_ERROR_INSTRUCTION_FETCH_LOAD;
			else if (mAccessType == WRITE)
			mExceptionInfo.mExType = IOPCoreException_t::ExType::EX_ADDRESS_ERROR_STORE;
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