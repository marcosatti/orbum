

#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter_s.h"

#include "Resources/Ee/Core/REeCore.hpp"
#include "Resources/Ee/Core/EeCoreCop0.hpp"
#include "Resources/Ee/Core/EeCoreCop0Registers.hpp"
#include "Resources/Ee/Core/EeCoreTlb.hpp"
#include "Resources/Ee/Core/EeCoreTlbEntry.hpp"

void EECoreInterpreter_s::SYNC_STYPE()
{
	// TODO: not sure I need to implement anything, since there is no hardware to be synced.
}

void EECoreInterpreter_s::PREF()
{
	// TODO: Probably dont need to implement, as its just a prefetch which is meaningless in an emulator.
}

void EECoreInterpreter_s::DI()
{
	// Disable Interrupts. No Exceptions.
	auto& statusReg = mEECore->COP0->Status;

	if ((statusReg->getFieldValue(, EeCoreCop0Register_Status::EDI) == 1) ||
		(statusReg->getFieldValue(, EeCoreCop0Register_Status::EXL) == 1) ||
		(statusReg->getFieldValue(, EeCoreCop0Register_Status::ERL) == 1) || 
		(statusReg->getFieldValue(, EeCoreCop0Register_Status::KSU) == 0))
	{
		statusReg->setFieldValue(, EeCoreCop0Register_Status::EIE, 0);
	}
}

void EECoreInterpreter_s::EI()
{
	// Enable Interrupts. No Exceptions.
	auto& statusReg = mEECore->COP0->Status;

	if ((statusReg->getFieldValue(, EeCoreCop0Register_Status::EDI) == 1) ||
		(statusReg->getFieldValue(, EeCoreCop0Register_Status::EXL) == 1) ||
		(statusReg->getFieldValue(, EeCoreCop0Register_Status::ERL) == 1) ||
		(statusReg->getFieldValue(, EeCoreCop0Register_Status::KSU) == 0))
	{
		statusReg->setFieldValue(, EeCoreCop0Register_Status::EIE, 1);
	}
}

void EECoreInterpreter_s::CACHE()
{
	// TODO: Probably dont need to implement, as cache is not implemented in an emulator.
}

void EECoreInterpreter_s::TLBP()
{
	// PROBE_TLB(index). Coprocessor unusable exception.
	if (handleCOP0Usable())
        return;

	uword value = 0x80000000; // Only set index if an entry is found, otherwise return with the sign bit = 1, indicating not found..
	auto& Index = mEECore->COP0->Index;
	auto& MMU = mEECore->TLB;
	auto& EntryHi = mEECore->COP0->EntryHi;

	// Find by VPN2 first.
	uword searchVpn2 = EntryHi->getFieldValue(, EeCoreCop0Register_EntryHi::VPN2) << 13;
	int tlb_index = MMU->find_tlb_entry_index(searchVpn2);

	if (tlbIndex == -1)
		Index->setFieldValue(, EeCoreCop0Register_Index::Index, value);
	else
	{
		// A match was found, but need to check ASID or G bit.
		if (MMU->tlb_entry_at(tlbIndex).mASID == EntryHi->getFieldValue(, EeCoreCop0Register_EntryHi::ASID) 
			|| MMU->tlb_entry_at(tlbIndex).mG > 0)
		{
			// Entry was found.
			value = static_cast<uword>(tlbIndex);
			Index->setFieldValue(, EeCoreCop0Register_Index::Index, value);
		}
	}
}

void EECoreInterpreter_s::TLBR()
{
	// COP0{PageMask, EntryHi/Lo} = GET_TLB(index). Coprocessor unusable exception.
	if (handleCOP0Usable())
        return;

	auto& Index = mEECore->COP0->Index;
	auto& MMU = mEECore->TLB;
	auto& PageMask = mEECore->COP0->PageMask;
	auto& EntryHi = mEECore->COP0->EntryHi;
	auto& EntryLo0 = mEECore->COP0->EntryLo0;
	auto& EntryLo1 = mEECore->COP0->EntryLo1;

	auto& tlbEntry = MMU->tlb_entry_at(static_cast<s32>(Index->getFieldValue(, EeCoreCop0Register_Index::Index)));

	// PageMask.
	PageMask->setFieldValue(, EeCoreCop0Register_PageMask::MASK, tlbEntry.mMask);

	// EntryHi.
	EntryHi->setFieldValue(, EeCoreCop0Register_EntryHi::ASID, tlbEntry.mASID);
	EntryHi->setFieldValue(, EeCoreCop0Register_EntryHi::VPN2, tlbEntry.mVPN2);

	// EntryLo0 (even).
	EntryLo0->setFieldValue(, EeCoreCop0Register_EntryLo0::S, tlbEntry.mS);
	EntryLo0->setFieldValue(, EeCoreCop0Register_EntryLo0::PFN, tlbEntry.PhysicalInfo[0].mPFN);
	EntryLo0->setFieldValue(, EeCoreCop0Register_EntryLo0::C, tlbEntry.PhysicalInfo[0].mC);
	EntryLo0->setFieldValue(, EeCoreCop0Register_EntryLo0::D, tlbEntry.PhysicalInfo[0].mD);
	EntryLo0->setFieldValue(, EeCoreCop0Register_EntryLo0::V, tlbEntry.PhysicalInfo[0].mV);
	EntryLo0->setFieldValue(, EeCoreCop0Register_EntryLo0::G, tlbEntry.mG);

	// EntryLo1 (odd).
	EntryLo1->setFieldValue(, EeCoreCop0Register_EntryLo1::PFN, tlbEntry.PhysicalInfo[1].mPFN);
	EntryLo1->setFieldValue(, EeCoreCop0Register_EntryLo1::C, tlbEntry.PhysicalInfo[1].mC);
	EntryLo1->setFieldValue(, EeCoreCop0Register_EntryLo1::D, tlbEntry.PhysicalInfo[1].mD);
	EntryLo1->setFieldValue(, EeCoreCop0Register_EntryLo1::V, tlbEntry.PhysicalInfo[1].mV);
	EntryLo1->setFieldValue(, EeCoreCop0Register_EntryLo1::G, tlbEntry.mG);
}

void EECoreInterpreter_s::TLBWI()
{
	// TLB[Index] = COP0{PageMask, EntryHi/Lo}. Coprocessor unusable exception.
	if (handleCOP0Usable())
        return;

	auto& Index = mEECore->COP0->Index;
	auto& MMU = mEECore->TLB;
	auto& PageMask = mEECore->COP0->PageMask;
	auto& EntryHi = mEECore->COP0->EntryHi;
	auto& EntryLo0 = mEECore->COP0->EntryLo0;
	auto& EntryLo1 = mEECore->COP0->EntryLo1;

	EeCoreTlbEntry tlbEntry;

	// PageMask.
	tlbEntry.mMask = PageMask->getFieldValue(, EeCoreCop0Register_PageMask::MASK);

	// EntryHi.
	tlbEntry.mASID = EntryHi->getFieldValue(, EeCoreCop0Register_EntryHi::ASID);
	tlbEntry.mVPN2 = EntryHi->getFieldValue(, EeCoreCop0Register_EntryHi::VPN2);

	// EntryLo0 (even).
	tlbEntry.mS = EntryLo0->getFieldValue(, EeCoreCop0Register_EntryLo0::S);
	tlbEntry.PhysicalInfo[0].mPFN = EntryLo0->getFieldValue(, EeCoreCop0Register_EntryLo0::PFN);
	tlbEntry.PhysicalInfo[0].mC = EntryLo0->getFieldValue(, EeCoreCop0Register_EntryLo0::C);
	tlbEntry.PhysicalInfo[0].mD = EntryLo0->getFieldValue(, EeCoreCop0Register_EntryLo0::D);
	tlbEntry.PhysicalInfo[0].mV = EntryLo0->getFieldValue(, EeCoreCop0Register_EntryLo0::V);
	
	// EntryLo1 (odd).
	tlbEntry.PhysicalInfo[1].mPFN = EntryLo1->getFieldValue(, EeCoreCop0Register_EntryLo1::PFN);
	tlbEntry.PhysicalInfo[1].mC = EntryLo1->getFieldValue(, EeCoreCop0Register_EntryLo1::C);
	tlbEntry.PhysicalInfo[1].mD = EntryLo1->getFieldValue(, EeCoreCop0Register_EntryLo1::D);
	tlbEntry.PhysicalInfo[1].mV = EntryLo1->getFieldValue(, EeCoreCop0Register_EntryLo1::V);
	
	// G bit (and of Lo0 and Lo1)
	tlbEntry.mG = EntryLo0->getFieldValue(, EeCoreCop0Register_EntryLo0::G) & EntryLo1->getFieldValue(, EeCoreCop0Register_EntryLo1::G);

	// Write to TLB.
	MMU->set_tlb_entry_at(tlbEntry, Index->getFieldValue(, EeCoreCop0Register_Index::Index));
}

void EECoreInterpreter_s::TLBWR()
{
	// TLB[random] = COP0{PageMask, EntryHi/Lo}. Coprocessor unusable exception.
	if (handleCOP0Usable())
        return;

	auto& Random = mEECore->COP0->Random;
	auto& MMU = mEECore->TLB;
	auto& PageMask = mEECore->COP0->PageMask;
	auto& EntryHi = mEECore->COP0->EntryHi;
	auto& EntryLo0 = mEECore->COP0->EntryLo0;
	auto& EntryLo1 = mEECore->COP0->EntryLo1;

	EeCoreTlbEntry tlbEntry;

	// PageMask.
	tlbEntry.mMask = PageMask->getFieldValue(, EeCoreCop0Register_PageMask::MASK);

	// EntryHi.
	tlbEntry.mASID = EntryHi->getFieldValue(, EeCoreCop0Register_EntryHi::ASID);
	tlbEntry.mVPN2 = EntryHi->getFieldValue(, EeCoreCop0Register_EntryHi::VPN2);

	// EntryLo0 (even).
	tlbEntry.mS = EntryLo0->getFieldValue(, EeCoreCop0Register_EntryLo0::S);
	tlbEntry.PhysicalInfo[0].mPFN = EntryLo0->getFieldValue(, EeCoreCop0Register_EntryLo0::PFN);
	tlbEntry.PhysicalInfo[0].mC = EntryLo0->getFieldValue(, EeCoreCop0Register_EntryLo0::C);
	tlbEntry.PhysicalInfo[0].mD = EntryLo0->getFieldValue(, EeCoreCop0Register_EntryLo0::D);
	tlbEntry.PhysicalInfo[0].mV = EntryLo0->getFieldValue(, EeCoreCop0Register_EntryLo0::V);

	// EntryLo1 (odd).
	tlbEntry.PhysicalInfo[1].mPFN = EntryLo1->getFieldValue(, EeCoreCop0Register_EntryLo1::PFN);
	tlbEntry.PhysicalInfo[1].mC = EntryLo1->getFieldValue(, EeCoreCop0Register_EntryLo1::C);
	tlbEntry.PhysicalInfo[1].mD = EntryLo1->getFieldValue(, EeCoreCop0Register_EntryLo1::D);
	tlbEntry.PhysicalInfo[1].mV = EntryLo1->getFieldValue(, EeCoreCop0Register_EntryLo1::V);

	// G bit (and of Lo0 and Lo1)
	tlbEntry.mG = EntryLo0->getFieldValue(, EeCoreCop0Register_EntryLo0::G) & EntryLo1->getFieldValue(, EeCoreCop0Register_EntryLo1::G);

	// Write to TLB.
	MMU->set_tlb_entry_at(tlbEntry, Random->getFieldValue(, EeCoreCop0Register_Random::Random));
}

