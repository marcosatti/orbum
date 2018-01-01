#include "Core.hpp"
#include "Utilities/Utilities.hpp"

#include "Controller/Ee/Core/Interpreter/CEeCoreInterpreter.hpp"

#include "Resources/RResources.hpp"

void CEeCoreInterpreter::SYNC_STYPE(const EeCoreInstruction inst) const
{
	// TODO: not sure I need to implement anything, since there is no hardware to be synced.
}

void CEeCoreInterpreter::PREF(const EeCoreInstruction inst) const
{
	// TODO: Probably dont need to implement, as its just a prefetch which is meaningless in an emulator.
}

void CEeCoreInterpreter::DI(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Disable Interrupts. No Exceptions.
	auto& reg_status = r.ee.core.cop0.status;

	if ((reg_status.extract_field(EeCoreCop0Register_Status::EDI) == 1) ||
		(reg_status.extract_field(EeCoreCop0Register_Status::EXL) == 1) ||
		(reg_status.extract_field(EeCoreCop0Register_Status::ERL) == 1) || 
		(reg_status.extract_field(EeCoreCop0Register_Status::KSU) == 0))
	{
		reg_status.insert_field(EeCoreCop0Register_Status::EIE, 0);
	}
}

void CEeCoreInterpreter::EI(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Enable Interrupts. No Exceptions.
	auto& reg_status = r.ee.core.cop0.status;

	if ((reg_status.extract_field(EeCoreCop0Register_Status::EDI) == 1) ||
		(reg_status.extract_field(EeCoreCop0Register_Status::EXL) == 1) ||
		(reg_status.extract_field(EeCoreCop0Register_Status::ERL) == 1) ||
		(reg_status.extract_field(EeCoreCop0Register_Status::KSU) == 0))
	{
		reg_status.insert_field(EeCoreCop0Register_Status::EIE, 1);
	}
}

void CEeCoreInterpreter::CACHE(const EeCoreInstruction inst) const
{
	// TODO: Probably dont need to implement, as cache is not implemented in an emulator.
}

void CEeCoreInterpreter::TLBP(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// PROBE_TLB(index). Coprocessor unusable exception.
	if (handle_cop0_usable())
        return;

	uword value = 0x80000000; // Only set index if an entry is found, otherwise return with the sign bit = 1, indicating not found..
	auto& index = r.ee.core.cop0.index;
	auto& tlb = r.ee.core.tlb;
	auto& entryhi = r.ee.core.cop0.entryhi;

	// Find by VPN2 first.
	uword searchVpn2 = entryhi.extract_field(EeCoreCop0Register_EntryHi::VPN2) << 13;
	int tlb_index = tlb.find_tlb_entry_index(searchVpn2);

	if (tlb_index == -1)
		index.insert_field(EeCoreCop0Register_Index::INDEX, value);
	else
	{
		// A match was found, but need to check ASID or G bit.
		if (tlb.tlb_entry_at(tlb_index).asid == entryhi.extract_field(EeCoreCop0Register_EntryHi::ASID) 
			|| tlb.tlb_entry_at(tlb_index).g > 0)
		{
			// Entry was found.
			value = static_cast<uword>(tlb_index);
			index.insert_field(EeCoreCop0Register_Index::INDEX, value);
		}
	}
}

void CEeCoreInterpreter::TLBR(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// COP0{PageMask, entryhi/Lo} = GET_TLB(index). Coprocessor unusable exception.
	if (handle_cop0_usable())
        return;

	auto& index = r.ee.core.cop0.index;
	auto& tlb = r.ee.core.tlb;
	auto& pagemask = r.ee.core.cop0.pagemask;
	auto& entryhi = r.ee.core.cop0.entryhi;
	auto& entrylo0 = r.ee.core.cop0.entrylo0;
	auto& entrylo1 = r.ee.core.cop0.entrylo1;

	auto& tlb_entry = tlb.tlb_entry_at(static_cast<sword>(index.extract_field(EeCoreCop0Register_Index::INDEX)));

	// PageMask.
	pagemask.insert_field(EeCoreCop0Register_PageMask::MASK, tlb_entry.mask);

	// entryhi.
	entryhi.insert_field(EeCoreCop0Register_EntryHi::ASID, tlb_entry.asid);
	entryhi.insert_field(EeCoreCop0Register_EntryHi::VPN2, tlb_entry.vpn2);

	// EntryLo0 (even).
	entrylo0.insert_field(EeCoreCop0Register_EntryLo0::S, tlb_entry.s);
	entrylo0.insert_field(EeCoreCop0Register_EntryLo0::PFN, tlb_entry.physical_info[0].pfn);
	entrylo0.insert_field(EeCoreCop0Register_EntryLo0::C, tlb_entry.physical_info[0].c);
	entrylo0.insert_field(EeCoreCop0Register_EntryLo0::D, tlb_entry.physical_info[0].d);
	entrylo0.insert_field(EeCoreCop0Register_EntryLo0::V, tlb_entry.physical_info[0].v);
	entrylo0.insert_field(EeCoreCop0Register_EntryLo0::G, tlb_entry.g);

	// EntryLo1 (odd).
	entrylo1.insert_field(EeCoreCop0Register_EntryLo1::PFN, tlb_entry.physical_info[1].pfn);
	entrylo1.insert_field(EeCoreCop0Register_EntryLo1::C, tlb_entry.physical_info[1].c);
	entrylo1.insert_field(EeCoreCop0Register_EntryLo1::D, tlb_entry.physical_info[1].d);
	entrylo1.insert_field(EeCoreCop0Register_EntryLo1::V, tlb_entry.physical_info[1].v);
	entrylo1.insert_field(EeCoreCop0Register_EntryLo1::G, tlb_entry.g);
}

void CEeCoreInterpreter::TLBWI(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// TLB[Index] = COP0{PageMask, entryhi/Lo}. Coprocessor unusable exception.
	if (handle_cop0_usable())
        return;

	auto& index = r.ee.core.cop0.index;
	auto& tlb = r.ee.core.tlb;
	auto& pagemask = r.ee.core.cop0.pagemask;
	auto& entryhi = r.ee.core.cop0.entryhi;
	auto& entrylo0 = r.ee.core.cop0.entrylo0;
	auto& entrylo1 = r.ee.core.cop0.entrylo1;

	EeCoreTlbEntry tlb_entry;

	// PageMask.
	tlb_entry.mask = pagemask.extract_field(EeCoreCop0Register_PageMask::MASK);

	// entryhi.
	tlb_entry.asid = entryhi.extract_field(EeCoreCop0Register_EntryHi::ASID);
	tlb_entry.vpn2 = entryhi.extract_field(EeCoreCop0Register_EntryHi::VPN2);

	// EntryLo0 (even).
	tlb_entry.s = entrylo0.extract_field(EeCoreCop0Register_EntryLo0::S);
	tlb_entry.physical_info[0].pfn = entrylo0.extract_field(EeCoreCop0Register_EntryLo0::PFN);
	tlb_entry.physical_info[0].c = entrylo0.extract_field(EeCoreCop0Register_EntryLo0::C);
	tlb_entry.physical_info[0].d = entrylo0.extract_field(EeCoreCop0Register_EntryLo0::D);
	tlb_entry.physical_info[0].v = entrylo0.extract_field(EeCoreCop0Register_EntryLo0::V);
	
	// EntryLo1 (odd).
	tlb_entry.physical_info[1].pfn = entrylo1.extract_field(EeCoreCop0Register_EntryLo1::PFN);
	tlb_entry.physical_info[1].c = entrylo1.extract_field(EeCoreCop0Register_EntryLo1::C);
	tlb_entry.physical_info[1].d = entrylo1.extract_field(EeCoreCop0Register_EntryLo1::D);
	tlb_entry.physical_info[1].v = entrylo1.extract_field(EeCoreCop0Register_EntryLo1::V);
	
	// G bit (and of Lo0 and Lo1)
	tlb_entry.g = entrylo0.extract_field(EeCoreCop0Register_EntryLo0::G) & entrylo1.extract_field(EeCoreCop0Register_EntryLo1::G);

	// Write to TLB.
	tlb.set_tlb_entry_at(tlb_entry, index.extract_field(EeCoreCop0Register_Index::INDEX));
}

void CEeCoreInterpreter::TLBWR(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// TLB[random] = COP0{PageMask, entryhi/Lo}. Coprocessor unusable exception.
	if (handle_cop0_usable())
        return;

	auto& random = r.ee.core.cop0.random;
	auto& tlb = r.ee.core.tlb;
	auto& pagemask = r.ee.core.cop0.pagemask;
	auto& entryhi = r.ee.core.cop0.entryhi;
	auto& entrylo0 = r.ee.core.cop0.entrylo0;
	auto& entrylo1 = r.ee.core.cop0.entrylo1;

	EeCoreTlbEntry tlb_entry;

	// PageMask.
	tlb_entry.mask = pagemask.extract_field(EeCoreCop0Register_PageMask::MASK);

	// entryhi.
	tlb_entry.asid = entryhi.extract_field(EeCoreCop0Register_EntryHi::ASID);
	tlb_entry.vpn2 = entryhi.extract_field(EeCoreCop0Register_EntryHi::VPN2);

	// EntryLo0 (even).
	tlb_entry.s = entrylo0.extract_field(EeCoreCop0Register_EntryLo0::S);
	tlb_entry.physical_info[0].pfn = entrylo0.extract_field(EeCoreCop0Register_EntryLo0::PFN);
	tlb_entry.physical_info[0].c = entrylo0.extract_field(EeCoreCop0Register_EntryLo0::C);
	tlb_entry.physical_info[0].d = entrylo0.extract_field(EeCoreCop0Register_EntryLo0::D);
	tlb_entry.physical_info[0].v = entrylo0.extract_field(EeCoreCop0Register_EntryLo0::V);

	// EntryLo1 (odd).
	tlb_entry.physical_info[1].pfn = entrylo1.extract_field(EeCoreCop0Register_EntryLo1::PFN);
	tlb_entry.physical_info[1].c = entrylo1.extract_field(EeCoreCop0Register_EntryLo1::C);
	tlb_entry.physical_info[1].d = entrylo1.extract_field(EeCoreCop0Register_EntryLo1::D);
	tlb_entry.physical_info[1].v = entrylo1.extract_field(EeCoreCop0Register_EntryLo1::V);

	// G bit (and of Lo0 and Lo1)
	tlb_entry.g = entrylo0.extract_field(EeCoreCop0Register_EntryLo0::G) & entrylo1.extract_field(EeCoreCop0Register_EntryLo1::G);

	// Write to TLB.
	tlb.set_tlb_entry_at(tlb_entry, random.extract_field(EeCoreCop0Register_Random::RANDOM));
}

