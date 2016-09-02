#include "stdafx.h"

#include <string>

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/EE/EECore/COP0/Types/COP0_BitfieldRegisters_t.h"
#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/EE/EECore/EECore_t.h"
#include "Common/PS2Resources/EE/EECore/COP0/COP0_t.h"

RegisterReserved_t::RegisterReserved_t()
{
}

RegisterIndex_t::RegisterIndex_t()
{
	registerField(Fields::Index, 0, 6, 0);
	registerField(Fields::P, 31, 1, 0);
}

RegisterRandom_t::RegisterRandom_t()
{
	registerField(Fields::Random, 0, 6, 47);
}

RegisterEntryLo0_t::RegisterEntryLo0_t()
{
	registerField(Fields::G, 0, 1, 0);
	registerField(Fields::V, 1, 1, 0);
	registerField(Fields::D, 2, 1, 0);
	registerField(Fields::C, 3, 3, 0);
	registerField(Fields::PFN, 6, 20, 0);
	registerField(Fields::S, 31, 1, 0);
}

RegisterEntryLo1_t::RegisterEntryLo1_t()
{
	registerField(Fields::G, 0, 1, 0);
	registerField(Fields::V, 1, 1, 0);
	registerField(Fields::D, 2, 1, 0);
	registerField(Fields::C, 3, 3, 0);
	registerField(Fields::PFN, 6, 20, 0);
}

RegisterContext_t::RegisterContext_t()
{
	registerField(Fields::BadVPN2, 4, 19, 0);
	registerField(Fields::PTEBase, 23, 9, 0);
}

RegisterPageMask_t::RegisterPageMask_t()
{
	registerField(Fields::MASK, 13, 12, 0);
}

RegisterWired_t::RegisterWired_t()
{
	registerField(Fields::Wired, 0, 6, 0);
}

RegisterBadVAddr_t::RegisterBadVAddr_t()
{
	registerField(Fields::BadVAddr, 0, 32, 0);
}

RegisterCount_t::RegisterCount_t()
{
	registerField(Fields::Count, 0, 32, 0);
}

void RegisterCount_t::increment(u32 value)
{
	setFieldValue(RegisterCount_t::Fields::Count, getFieldValue(RegisterCount_t::Fields::Count) + value);
}

RegisterEntryHi_t::RegisterEntryHi_t()
{
	registerField(Fields::ASID, 0, 8, 0);
	registerField(Fields::VPN2, 13, 19, 0);
}

RegisterCompare_t::RegisterCompare_t(const PS2Resources_t* const PS2Resources): PS2ResourcesSubobject(PS2Resources)
{
	registerField(Fields::Compare, 0, 32, 0);
}

void RegisterCompare_t::setFieldValue(const std::string& fieldName, const u32& value)
{
	getRootResources()->EE->EECore->COP0->Cause->setFieldValue(RegisterCause_t::Fields::IP7, 0);
	BitfieldRegister32_t::setFieldValue(fieldName, value);
}

void RegisterCompare_t::setRegisterValue(u32 value)
{
	getRootResources()->EE->EECore->COP0->Cause->setFieldValue(RegisterCause_t::Fields::IP7, 0);
	BitfieldRegister32_t::setRegisterValue(value);
}

RegisterStatus_t::RegisterStatus_t()
{
	registerField(Fields::IE, 0, 1, 0);
	registerField(Fields::EXL, 1, 1, 0);
	registerField(Fields::ERL, 2, 1, 1);
	registerField(Fields::KSU, 3, 2, 0);
	registerField(Fields::IM, 5, 5, 0);
	registerField(Fields::BEM, 12, 1, 0);
	registerField(Fields::IM7, 15, 1, 0);
	registerField(Fields::EIE, 16, 1, 0);
	registerField(Fields::EDI, 17, 1, 0);
	registerField(Fields::CH, 18, 1, 0);
	registerField(Fields::BEV, 22, 1, 1);
	registerField(Fields::DEV, 23, 1, 0);
	registerField(Fields::CU, 28, 4, 0);
}

RegisterCause_t::RegisterCause_t()
{
	registerField(Fields::ExcCode, 2, 5, 0);
	registerField(Fields::IP2, 10, 1, 0);
	registerField(Fields::IP3, 11, 1, 0);
	registerField(Fields::IP7, 15, 1, 0);
	registerField(Fields::EXC2, 16, 3, 0);
	registerField(Fields::CE, 28, 2, 0);
	registerField(Fields::BD2, 30, 1, 0);
	registerField(Fields::BD, 31, 1, 0);
}

RegisterEPC_t::RegisterEPC_t()
{
	registerField(Fields::EPC, 0, 32, 0);
}

RegisterPRId_t::RegisterPRId_t()
{
	registerField(Fields::Rev, 0, 8, 0x20); // Same as old PCSX2.
	registerField(Fields::Imp, 8, 15, 0x2E);
}

RegisterConfig_t::RegisterConfig_t()
{
	registerField(Fields::K0, 0, 3, 0);
	registerField(Fields::DC, 6, 3, 1);
	registerField(Fields::IC, 9, 3, 2);
	registerField(Fields::BPE, 12, 1, 0);
	registerField(Fields::NBE, 13, 1, 0);
	registerField(Fields::DCE, 16, 1, 0);
	registerField(Fields::ICE, 17, 1, 0);
	registerField(Fields::DIE, 18, 1, 0);
	registerField(Fields::EC, 28, 3, 0);
}

RegisterBadPAddr_t::RegisterBadPAddr_t()
{
	registerField(Fields::BadPAddr, 4, 28, 0);
}

RegisterBPC_t::RegisterBPC_t()
{
	registerField(Fields::IAB, 0, 1, 0);
	registerField(Fields::DRB, 1, 1, 0);
	registerField(Fields::DWB, 2, 1, 0);
	registerField(Fields::BED, 15, 1, 0);
	registerField(Fields::DTE, 16, 1, 0);
	registerField(Fields::ITE, 17, 1, 0);
	registerField(Fields::DXE, 18, 1, 0);
	registerField(Fields::DKE, 19, 1, 0);
	registerField(Fields::DSE, 20, 1, 0);
	registerField(Fields::DUE, 21, 1, 0);
	registerField(Fields::IXE, 23, 1, 0);
	registerField(Fields::IKE, 24, 1, 0);
	registerField(Fields::ISE, 25, 1, 0);
	registerField(Fields::IUE, 26, 1, 0);
	registerField(Fields::DVE, 28, 1, 0);
	registerField(Fields::DWE, 29, 1, 0);
	registerField(Fields::DRE, 30, 1, 0);
	registerField(Fields::IAE, 31, 1, 0);
}

RegisterIAB_t::RegisterIAB_t()
{
	registerField(Fields::IAB, 0, 32, 0);
}

RegisterIABM_t::RegisterIABM_t()
{
	registerField(Fields::IABM, 0, 32, 0);
}

RegisterDAB_t::RegisterDAB_t()
{
	registerField(Fields::DAB, 0, 32, 0);
}

RegisterDABM_t::RegisterDABM_t()
{
	registerField(Fields::DABM, 0, 32, 0);
}

RegisterDVB_t::RegisterDVB_t()
{
	registerField(Fields::DVB, 0, 32, 0);
}

RegisterDVBM_t::RegisterDVBM_t()
{
	registerField(Fields::DVBM, 0, 32, 0);
}

RegisterPCCR_t::RegisterPCCR_t()
{
	registerField(Fields::EXL0, 1, 1, 0);
	registerField(Fields::K0, 2, 1, 0);
	registerField(Fields::S0, 3, 1, 0);
	registerField(Fields::U0, 4, 1, 0);
	registerField(Fields::EVENT0, 5, 5, 0);
	registerField(Fields::EXL1, 11, 1, 0);
	registerField(Fields::K1, 12, 1, 0);
	registerField(Fields::S1, 13, 1, 0);
	registerField(Fields::U1, 14, 1, 0);
	registerField(Fields::EVENT1, 15, 5, 0);
	registerField(Fields::CTE, 31, 1, 0);
}

RegisterPCR0_t::RegisterPCR0_t()
{
	registerField(Fields::VALUE, 0, 31, 0);
	registerField(Fields::OVFL, 31, 1, 0);
}

RegisterPCR1_t::RegisterPCR1_t()
{
	registerField(Fields::VALUE, 0, 31, 0);
	registerField(Fields::OVFL, 31, 1, 0);
}

RegisterTagLo_t::RegisterTagLo_t()
{
	registerField(Fields::L, 3, 1, 0);
	registerField(Fields::R, 4, 1, 0);
	registerField(Fields::V, 5, 1, 0);
	registerField(Fields::D, 6, 1, 0);
	registerField(Fields::PTagLo, 12, 31, 0);
}

RegisterTagHi_t::RegisterTagHi_t()
{
	registerField(Fields::L, 3, 1, 0);
	registerField(Fields::R, 4, 1, 0);
	registerField(Fields::V, 5, 1, 0);
	registerField(Fields::D, 6, 1, 0);
	registerField(Fields::PTagHi, 12, 31, 0);
}

RegisterErrorEPC_t::RegisterErrorEPC_t()
{
	registerField(Fields::ErrorEPC, 0, 32, 0);
}
