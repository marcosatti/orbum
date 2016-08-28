#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/InterpreterEECore/InterpreterEECore.h"
#include "Common/Util/EECoreInstructionUtil/EECoreInstructionUtil.h"
#include "Common/PS2 Resources/EE/EECore/MMU/MMU_t.h"

void InterpreterEECore::SYNC_STYPE()
{
	// TODO: not sure I need to implement anything, since there is no hardware to be synced.
#if defined(BUILD_DEBUG)
	logDebug("SYNC_STYPE: Not implemented.");
#else
	throw std::runtime_error("SYNC_STYPE: Not implemented.");
#endif
}

void InterpreterEECore::PREF()
{
	// TODO: Probably dont need to implement, as its just a prefetch which is meaningless in an emulator.
#if defined(BUILD_DEBUG)
	logDebug("PREF: Not implemented.");
#else
	throw std::runtime_error("PREF: Not implemented.");
#endif
}

void InterpreterEECore::DI()
{
	// Disable Interrupts. No Exceptions.
	auto& statusReg = getVM()->getResources()->EE->EECore->COP0->Status;

	if ((statusReg->getFieldValue(RegisterStatus_t::Fields::EDI) == 1) ||
		(statusReg->getFieldValue(RegisterStatus_t::Fields::EXL) == 1) ||
		(statusReg->getFieldValue(RegisterStatus_t::Fields::ERL) == 1) || 
		(statusReg->getFieldValue(RegisterStatus_t::Fields::KSU) == 0))
	{
		statusReg->setFieldValue(RegisterStatus_t::Fields::EIE, 0);
	}
}

void InterpreterEECore::EI()
{
	// Enable Interrupts. No Exceptions.
	auto& statusReg = getVM()->getResources()->EE->EECore->COP0->Status;

	if ((statusReg->getFieldValue(RegisterStatus_t::Fields::EDI) == 1) ||
		(statusReg->getFieldValue(RegisterStatus_t::Fields::EXL) == 1) ||
		(statusReg->getFieldValue(RegisterStatus_t::Fields::ERL) == 1) ||
		(statusReg->getFieldValue(RegisterStatus_t::Fields::KSU) == 0))
	{
		statusReg->setFieldValue(RegisterStatus_t::Fields::EIE, 1);
	}
}

void InterpreterEECore::CACHE()
{
#if defined(BUILD_DEBUG)
	logDebug("CACHE: Not implemented.");
#else
	throw std::runtime_error("CACHE: Not implemented.");
#endif
}

void InterpreterEECore::TLBP()
{
	// PROBE_TLB(index). Coprocessor unusable exception.
	if (!getVM()->getResources()->EE->EECore->COP0->isCOP0Usable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 0 };
		Exceptions->ExceptionQueue->push(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	u32 value = 0x80000000; // Only set index if an entry is found, otherwise return with the sign bit = 1, indicating not found..
	auto& Index = getVM()->getResources()->EE->EECore->COP0->Index;
	auto& MMU = getVM()->getResources()->EE->EECore->MMU;
	auto& EntryHi = getVM()->getResources()->EE->EECore->COP0->EntryHi;

	// Find by VPN2 first.
	u32 searchVpn2 = EntryHi->getFieldValue(RegisterEntryHi_t::Fields::VPN2) << 13;
	s32 tlbIndex = MMU->findTLBIndex(searchVpn2);

	if (tlbIndex == -1)
		Index->setFieldValue(RegisterIndex_t::Fields::Index, value);
	else
	{
		// A match was found, but need to check ASID or G bit.
		if (MMU->getTLBEntry(tlbIndex).mASID == EntryHi->getFieldValue(RegisterEntryHi_t::Fields::ASID) 
			|| MMU->getTLBEntry(tlbIndex).mG > 0)
		{
			// Entry was found.
			value = static_cast<u32>(tlbIndex);
			Index->setFieldValue(RegisterIndex_t::Fields::Index, value);
		}
	}
}

void InterpreterEECore::TLBR()
{
	// COP0{PageMask, EntryHi/Lo} = GET_TLB(index). Coprocessor unusable exception.
	if (!getVM()->getResources()->EE->EECore->COP0->isCOP0Usable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 0 };
		Exceptions->ExceptionQueue->push(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& Index = getVM()->getResources()->EE->EECore->COP0->Index;
	auto& MMU = getVM()->getResources()->EE->EECore->MMU;
	auto& PageMask = getVM()->getResources()->EE->EECore->COP0->PageMask;
	auto& EntryHi = getVM()->getResources()->EE->EECore->COP0->EntryHi;
	auto& EntryLo0 = getVM()->getResources()->EE->EECore->COP0->EntryLo0;
	auto& EntryLo1 = getVM()->getResources()->EE->EECore->COP0->EntryLo1;

	auto& tlbEntry = MMU->getTLBEntry(static_cast<s32>(Index->getFieldValue(RegisterIndex_t::Fields::Index)));

	// PageMask.
	PageMask->setFieldValue(RegisterPageMask_t::Fields::MASK, tlbEntry.mMask);

	// EntryHi.
	EntryHi->setFieldValue(RegisterEntryHi_t::Fields::ASID, tlbEntry.mASID);
	EntryHi->setFieldValue(RegisterEntryHi_t::Fields::VPN2, tlbEntry.mVPN2);

	// EntryLo0 (even).
	EntryLo0->setFieldValue(RegisterEntryLo0_t::Fields::S, tlbEntry.mS);
	EntryLo0->setFieldValue(RegisterEntryLo0_t::Fields::PFN, tlbEntry.mPFNEven);
	EntryLo0->setFieldValue(RegisterEntryLo0_t::Fields::C, tlbEntry.mCEven);
	EntryLo0->setFieldValue(RegisterEntryLo0_t::Fields::D, tlbEntry.mDEven);
	EntryLo0->setFieldValue(RegisterEntryLo0_t::Fields::V, tlbEntry.mVEven);
	EntryLo0->setFieldValue(RegisterEntryLo0_t::Fields::G, tlbEntry.mG);

	// EntryLo1 (odd).
	EntryLo1->setFieldValue(RegisterEntryLo1_t::Fields::PFN, tlbEntry.mPFNOdd);
	EntryLo1->setFieldValue(RegisterEntryLo1_t::Fields::C, tlbEntry.mCOdd);
	EntryLo1->setFieldValue(RegisterEntryLo1_t::Fields::D, tlbEntry.mDOdd);
	EntryLo1->setFieldValue(RegisterEntryLo1_t::Fields::V, tlbEntry.mVOdd);
	EntryLo1->setFieldValue(RegisterEntryLo1_t::Fields::G, tlbEntry.mG);
}

void InterpreterEECore::TLBWI()
{
	// TLB[index] = COP0{PageMask, EntryHi/Lo}. Coprocessor unusable exception.
	if (!getVM()->getResources()->EE->EECore->COP0->isCOP0Usable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
 		COPExceptionInfo_t copExInfo = { 0 };
		Exceptions->ExceptionQueue->push(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& Index = getVM()->getResources()->EE->EECore->COP0->Index;
	auto& MMU = getVM()->getResources()->EE->EECore->MMU;
	auto& PageMask = getVM()->getResources()->EE->EECore->COP0->PageMask;
	auto& EntryHi = getVM()->getResources()->EE->EECore->COP0->EntryHi;
	auto& EntryLo0 = getVM()->getResources()->EE->EECore->COP0->EntryLo0;
	auto& EntryLo1 = getVM()->getResources()->EE->EECore->COP0->EntryLo1;

	TLBEntryInfo tlbEntry;

	// PageMask.
	tlbEntry.mMask = PageMask->getFieldValue(RegisterPageMask_t::Fields::MASK);

	// EntryHi.
	tlbEntry.mASID = EntryHi->getFieldValue(RegisterEntryHi_t::Fields::ASID);
	tlbEntry.mVPN2 = EntryHi->getFieldValue(RegisterEntryHi_t::Fields::VPN2);

	// EntryLo0 (even).
	tlbEntry.mS = EntryLo0->getFieldValue(RegisterEntryLo0_t::Fields::S);
	tlbEntry.mPFNEven = EntryLo0->getFieldValue(RegisterEntryLo0_t::Fields::PFN);
	tlbEntry.mCEven = EntryLo0->getFieldValue(RegisterEntryLo0_t::Fields::C);
	tlbEntry.mDEven = EntryLo0->getFieldValue(RegisterEntryLo0_t::Fields::D);
	tlbEntry.mVEven = EntryLo0->getFieldValue(RegisterEntryLo0_t::Fields::V);
	
	// EntryLo1 (odd).
	tlbEntry.mPFNOdd = EntryLo1->getFieldValue(RegisterEntryLo1_t::Fields::PFN);
	tlbEntry.mCOdd = EntryLo1->getFieldValue(RegisterEntryLo1_t::Fields::C);
	tlbEntry.mDOdd = EntryLo1->getFieldValue(RegisterEntryLo1_t::Fields::D);
	tlbEntry.mVOdd = EntryLo1->getFieldValue(RegisterEntryLo1_t::Fields::V);
	
	// G bit (and of Lo0 and Lo1)
	tlbEntry.mG = EntryLo0->getFieldValue(RegisterEntryLo0_t::Fields::G) & EntryLo1->getFieldValue(RegisterEntryLo1_t::Fields::G);

	// Write to TLB.
	MMU->setTLBEntry(tlbEntry, Index->getFieldValue(RegisterIndex_t::Fields::Index));
}

void InterpreterEECore::TLBWR()
{
	// TLB[random] = COP0{PageMask, EntryHi/Lo}. Coprocessor unusable exception.
	if (!getVM()->getResources()->EE->EECore->COP0->isCOP0Usable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 0 };
		Exceptions->ExceptionQueue->push(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& Random = getVM()->getResources()->EE->EECore->COP0->Random;
	auto& MMU = getVM()->getResources()->EE->EECore->MMU;
	auto& PageMask = getVM()->getResources()->EE->EECore->COP0->PageMask;
	auto& EntryHi = getVM()->getResources()->EE->EECore->COP0->EntryHi;
	auto& EntryLo0 = getVM()->getResources()->EE->EECore->COP0->EntryLo0;
	auto& EntryLo1 = getVM()->getResources()->EE->EECore->COP0->EntryLo1;

	TLBEntryInfo tlbEntry;

	// PageMask.
	tlbEntry.mMask = PageMask->getFieldValue(RegisterPageMask_t::Fields::MASK);

	// EntryHi.
	tlbEntry.mASID = EntryHi->getFieldValue(RegisterEntryHi_t::Fields::ASID);
	tlbEntry.mVPN2 = EntryHi->getFieldValue(RegisterEntryHi_t::Fields::VPN2);

	// EntryLo0 (even).
	tlbEntry.mS = EntryLo0->getFieldValue(RegisterEntryLo0_t::Fields::S);
	tlbEntry.mPFNEven = EntryLo0->getFieldValue(RegisterEntryLo0_t::Fields::PFN);
	tlbEntry.mCEven = EntryLo0->getFieldValue(RegisterEntryLo0_t::Fields::C);
	tlbEntry.mDEven = EntryLo0->getFieldValue(RegisterEntryLo0_t::Fields::D);
	tlbEntry.mVEven = EntryLo0->getFieldValue(RegisterEntryLo0_t::Fields::V);

	// EntryLo1 (odd).
	tlbEntry.mPFNOdd = EntryLo1->getFieldValue(RegisterEntryLo1_t::Fields::PFN);
	tlbEntry.mCOdd = EntryLo1->getFieldValue(RegisterEntryLo1_t::Fields::C);
	tlbEntry.mDOdd = EntryLo1->getFieldValue(RegisterEntryLo1_t::Fields::D);
	tlbEntry.mVOdd = EntryLo1->getFieldValue(RegisterEntryLo1_t::Fields::V);

	// G bit (and of Lo0 and Lo1)
	tlbEntry.mG = EntryLo0->getFieldValue(RegisterEntryLo0_t::Fields::G) & EntryLo1->getFieldValue(RegisterEntryLo1_t::Fields::G);

	// Write to TLB.
	MMU->setTLBEntry(tlbEntry, Random->getFieldValue(RegisterRandom_t::Fields::Random));
}
