#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreInterpreter.h"
#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreCOP0_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreCOP0Registers_t.h"
#include "Common/Types/MIPSCoprocessor/COP0Registers_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreTLB_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreTLBEntryInfo_t.h"

void EECoreInterpreter::SYNC_STYPE()
{
	// TODO: not sure I need to implement anything, since there is no hardware to be synced.
#if defined(BUILD_DEBUG)
	// logDebug("SYNC_STYPE: Not implemented.");
	DEBUG_INSTRUCTION_SYNC++;
#else
	throw std::runtime_error("SYNC_STYPE: Not implemented.");
#endif
}

void EECoreInterpreter::PREF()
{
	// TODO: Probably dont need to implement, as its just a prefetch which is meaningless in an emulator.
#if defined(BUILD_DEBUG)
	// logDebug("(%s, %d) PREF: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("PREF: Not implemented.");
#endif
}

void EECoreInterpreter::DI()
{
	// Disable Interrupts. No Exceptions.
	auto& statusReg = getResources()->EE->EECore->COP0->Status;

	if ((statusReg->getFieldValue(EECoreCOP0Register_Status_t::Fields::EDI) == 1) ||
		(statusReg->getFieldValue(EECoreCOP0Register_Status_t::Fields::EXL) == 1) ||
		(statusReg->getFieldValue(EECoreCOP0Register_Status_t::Fields::ERL) == 1) || 
		(statusReg->getFieldValue(EECoreCOP0Register_Status_t::Fields::KSU) == 0))
	{
		statusReg->setFieldValue(EECoreCOP0Register_Status_t::Fields::EIE, 0);
	}
}

void EECoreInterpreter::EI()
{
	// Enable Interrupts. No Exceptions.
	auto& statusReg = getResources()->EE->EECore->COP0->Status;

	if ((statusReg->getFieldValue(EECoreCOP0Register_Status_t::Fields::EDI) == 1) ||
		(statusReg->getFieldValue(EECoreCOP0Register_Status_t::Fields::EXL) == 1) ||
		(statusReg->getFieldValue(EECoreCOP0Register_Status_t::Fields::ERL) == 1) ||
		(statusReg->getFieldValue(EECoreCOP0Register_Status_t::Fields::KSU) == 0))
	{
		statusReg->setFieldValue(EECoreCOP0Register_Status_t::Fields::EIE, 1);
	}
}

void EECoreInterpreter::CACHE()
{
#if defined(BUILD_DEBUG)
	// logDebug("(%s, %d) CACHE: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("CACHE: Not implemented.");
#endif
}

void EECoreInterpreter::TLBP()
{
	// PROBE_TLB(index). Coprocessor unusable exception.
	if (!checkCOP0Usable())
        return;

	u32 value = 0x80000000; // Only set index if an entry is found, otherwise return with the sign bit = 1, indicating not found..
	auto& Index = getResources()->EE->EECore->COP0->Index;
	auto& MMU = getResources()->EE->EECore->TLB;
	auto& EntryHi = getResources()->EE->EECore->COP0->EntryHi;

	// Find by VPN2 first.
	u32 searchVpn2 = EntryHi->getFieldValue(EECoreCOP0Register_EntryHi_t::Fields::VPN2) << 13;
	s32 tlbIndex = MMU->findTLBIndex(searchVpn2);

	if (tlbIndex == -1)
		Index->setFieldValue(EECoreCOP0Register_Index_t::Fields::Index, value);
	else
	{
		// A match was found, but need to check ASID or G bit.
		if (MMU->getTLBEntry(tlbIndex).mASID == EntryHi->getFieldValue(EECoreCOP0Register_EntryHi_t::Fields::ASID) 
			|| MMU->getTLBEntry(tlbIndex).mG > 0)
		{
			// Entry was found.
			value = static_cast<u32>(tlbIndex);
			Index->setFieldValue(EECoreCOP0Register_Index_t::Fields::Index, value);
		}
	}
}

void EECoreInterpreter::TLBR()
{
	// COP0{PageMask, EntryHi/Lo} = GET_TLB(index). Coprocessor unusable exception.
	if (!checkCOP0Usable())
        return;

	auto& Index = getResources()->EE->EECore->COP0->Index;
	auto& MMU = getResources()->EE->EECore->TLB;
	auto& PageMask = getResources()->EE->EECore->COP0->PageMask;
	auto& EntryHi = getResources()->EE->EECore->COP0->EntryHi;
	auto& EntryLo0 = getResources()->EE->EECore->COP0->EntryLo0;
	auto& EntryLo1 = getResources()->EE->EECore->COP0->EntryLo1;

	auto& tlbEntry = MMU->getTLBEntry(static_cast<s32>(Index->getFieldValue(EECoreCOP0Register_Index_t::Fields::Index)));

	// PageMask.
	PageMask->setFieldValue(EECoreCOP0Register_PageMask_t::Fields::MASK, tlbEntry.mMask);

	// EntryHi.
	EntryHi->setFieldValue(EECoreCOP0Register_EntryHi_t::Fields::ASID, tlbEntry.mASID);
	EntryHi->setFieldValue(EECoreCOP0Register_EntryHi_t::Fields::VPN2, tlbEntry.mVPN2);

	// EntryLo0 (even).
	EntryLo0->setFieldValue(EECoreCOP0Register_EntryLo0_t::Fields::S, tlbEntry.mS);
	EntryLo0->setFieldValue(EECoreCOP0Register_EntryLo0_t::Fields::PFN, tlbEntry.PhysicalInfo[0].mPFN);
	EntryLo0->setFieldValue(EECoreCOP0Register_EntryLo0_t::Fields::C, tlbEntry.PhysicalInfo[0].mC);
	EntryLo0->setFieldValue(EECoreCOP0Register_EntryLo0_t::Fields::D, tlbEntry.PhysicalInfo[0].mD);
	EntryLo0->setFieldValue(EECoreCOP0Register_EntryLo0_t::Fields::V, tlbEntry.PhysicalInfo[0].mV);
	EntryLo0->setFieldValue(EECoreCOP0Register_EntryLo0_t::Fields::G, tlbEntry.mG);

	// EntryLo1 (odd).
	EntryLo1->setFieldValue(EECoreCOP0Register_EntryLo1_t::Fields::PFN, tlbEntry.PhysicalInfo[1].mPFN);
	EntryLo1->setFieldValue(EECoreCOP0Register_EntryLo1_t::Fields::C, tlbEntry.PhysicalInfo[1].mC);
	EntryLo1->setFieldValue(EECoreCOP0Register_EntryLo1_t::Fields::D, tlbEntry.PhysicalInfo[1].mD);
	EntryLo1->setFieldValue(EECoreCOP0Register_EntryLo1_t::Fields::V, tlbEntry.PhysicalInfo[1].mV);
	EntryLo1->setFieldValue(EECoreCOP0Register_EntryLo1_t::Fields::G, tlbEntry.mG);
}

void EECoreInterpreter::TLBWI()
{
	// TLB[Index] = COP0{PageMask, EntryHi/Lo}. Coprocessor unusable exception.
	if (!checkCOP0Usable())
        return;

	auto& Index = getResources()->EE->EECore->COP0->Index;
	auto& MMU = getResources()->EE->EECore->TLB;
	auto& PageMask = getResources()->EE->EECore->COP0->PageMask;
	auto& EntryHi = getResources()->EE->EECore->COP0->EntryHi;
	auto& EntryLo0 = getResources()->EE->EECore->COP0->EntryLo0;
	auto& EntryLo1 = getResources()->EE->EECore->COP0->EntryLo1;

	EECoreTLBEntryInfo_t tlbEntry;

	// PageMask.
	tlbEntry.mMask = PageMask->getFieldValue(EECoreCOP0Register_PageMask_t::Fields::MASK);

	// EntryHi.
	tlbEntry.mASID = EntryHi->getFieldValue(EECoreCOP0Register_EntryHi_t::Fields::ASID);
	tlbEntry.mVPN2 = EntryHi->getFieldValue(EECoreCOP0Register_EntryHi_t::Fields::VPN2);

	// EntryLo0 (even).
	tlbEntry.mS = EntryLo0->getFieldValue(EECoreCOP0Register_EntryLo0_t::Fields::S);
	tlbEntry.PhysicalInfo[0].mPFN = EntryLo0->getFieldValue(EECoreCOP0Register_EntryLo0_t::Fields::PFN);
	tlbEntry.PhysicalInfo[0].mC = EntryLo0->getFieldValue(EECoreCOP0Register_EntryLo0_t::Fields::C);
	tlbEntry.PhysicalInfo[0].mD = EntryLo0->getFieldValue(EECoreCOP0Register_EntryLo0_t::Fields::D);
	tlbEntry.PhysicalInfo[0].mV = EntryLo0->getFieldValue(EECoreCOP0Register_EntryLo0_t::Fields::V);
	
	// EntryLo1 (odd).
	tlbEntry.PhysicalInfo[1].mPFN = EntryLo1->getFieldValue(EECoreCOP0Register_EntryLo1_t::Fields::PFN);
	tlbEntry.PhysicalInfo[1].mC = EntryLo1->getFieldValue(EECoreCOP0Register_EntryLo1_t::Fields::C);
	tlbEntry.PhysicalInfo[1].mD = EntryLo1->getFieldValue(EECoreCOP0Register_EntryLo1_t::Fields::D);
	tlbEntry.PhysicalInfo[1].mV = EntryLo1->getFieldValue(EECoreCOP0Register_EntryLo1_t::Fields::V);
	
	// G bit (and of Lo0 and Lo1)
	tlbEntry.mG = EntryLo0->getFieldValue(EECoreCOP0Register_EntryLo0_t::Fields::G) & EntryLo1->getFieldValue(EECoreCOP0Register_EntryLo1_t::Fields::G);

	// Write to TLB.
	MMU->setTLBEntry(tlbEntry, Index->getFieldValue(EECoreCOP0Register_Index_t::Fields::Index));
}

void EECoreInterpreter::TLBWR()
{
	// TLB[random] = COP0{PageMask, EntryHi/Lo}. Coprocessor unusable exception.
	if (!checkCOP0Usable())
        return;

	auto& Random = getResources()->EE->EECore->COP0->Random;
	auto& MMU = getResources()->EE->EECore->TLB;
	auto& PageMask = getResources()->EE->EECore->COP0->PageMask;
	auto& EntryHi = getResources()->EE->EECore->COP0->EntryHi;
	auto& EntryLo0 = getResources()->EE->EECore->COP0->EntryLo0;
	auto& EntryLo1 = getResources()->EE->EECore->COP0->EntryLo1;

	EECoreTLBEntryInfo_t tlbEntry;

	// PageMask.
	tlbEntry.mMask = PageMask->getFieldValue(EECoreCOP0Register_PageMask_t::Fields::MASK);

	// EntryHi.
	tlbEntry.mASID = EntryHi->getFieldValue(EECoreCOP0Register_EntryHi_t::Fields::ASID);
	tlbEntry.mVPN2 = EntryHi->getFieldValue(EECoreCOP0Register_EntryHi_t::Fields::VPN2);

	// EntryLo0 (even).
	tlbEntry.mS = EntryLo0->getFieldValue(EECoreCOP0Register_EntryLo0_t::Fields::S);
	tlbEntry.PhysicalInfo[0].mPFN = EntryLo0->getFieldValue(EECoreCOP0Register_EntryLo0_t::Fields::PFN);
	tlbEntry.PhysicalInfo[0].mC = EntryLo0->getFieldValue(EECoreCOP0Register_EntryLo0_t::Fields::C);
	tlbEntry.PhysicalInfo[0].mD = EntryLo0->getFieldValue(EECoreCOP0Register_EntryLo0_t::Fields::D);
	tlbEntry.PhysicalInfo[0].mV = EntryLo0->getFieldValue(EECoreCOP0Register_EntryLo0_t::Fields::V);

	// EntryLo1 (odd).
	tlbEntry.PhysicalInfo[1].mPFN = EntryLo1->getFieldValue(EECoreCOP0Register_EntryLo1_t::Fields::PFN);
	tlbEntry.PhysicalInfo[1].mC = EntryLo1->getFieldValue(EECoreCOP0Register_EntryLo1_t::Fields::C);
	tlbEntry.PhysicalInfo[1].mD = EntryLo1->getFieldValue(EECoreCOP0Register_EntryLo1_t::Fields::D);
	tlbEntry.PhysicalInfo[1].mV = EntryLo1->getFieldValue(EECoreCOP0Register_EntryLo1_t::Fields::V);

	// G bit (and of Lo0 and Lo1)
	tlbEntry.mG = EntryLo0->getFieldValue(EECoreCOP0Register_EntryLo0_t::Fields::G) & EntryLo1->getFieldValue(EECoreCOP0Register_EntryLo1_t::Fields::G);

	// Write to TLB.
	MMU->setTLBEntry(tlbEntry, Random->getFieldValue(EECoreCOP0Register_Random_t::Fields::Random));
}

