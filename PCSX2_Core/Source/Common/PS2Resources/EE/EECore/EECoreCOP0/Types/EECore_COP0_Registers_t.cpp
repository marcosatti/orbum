#include "stdafx.h"

#include "Common/PS2Resources/EE/EECore/EECoreCOP0/Types/EECore_COP0_Registers_t.h"
#include "Common/PS2Resources/Types/MappedMemory/BitfieldMMemory32_t.h"

EECore_COP0RegisterIndex_t::EECore_COP0RegisterIndex_t()
{
	registerField(Fields::Index, "Index", 0, 6, 0);
	registerField(Fields::P, "P", 31, 1, 0);
}

EECore_COP0RegisterRandom_t::EECore_COP0RegisterRandom_t()
{
	registerField(Fields::Random, "Random", 0, 6, 47);
}

EECore_COP0RegisterEntryLo0_t::EECore_COP0RegisterEntryLo0_t()
{
	registerField(Fields::G, "G", 0, 1, 0);
	registerField(Fields::V, "V", 1, 1, 0);
	registerField(Fields::D, "D", 2, 1, 0);
	registerField(Fields::C, "C", 3, 3, 0);
	registerField(Fields::PFN, "PFN", 6, 20, 0);
	registerField(Fields::S, "S", 31, 1, 0);
}

EECore_COP0RegisterEntryLo1_t::EECore_COP0RegisterEntryLo1_t()
{
	registerField(Fields::G, "G", 0, 1, 0);
	registerField(Fields::V, "V", 1, 1, 0);
	registerField(Fields::D, "D", 2, 1, 0);
	registerField(Fields::C, "C", 3, 3, 0);
	registerField(Fields::PFN, "PFN", 6, 20, 0);
}

EECore_COP0RegisterContext_t::EECore_COP0RegisterContext_t()
{
	registerField(Fields::BadVPN2, "BadVPN2", 4, 19, 0);
	registerField(Fields::PTEBase, "PTEBase", 23, 9, 0);
}

EECore_COP0RegisterPageMask_t::EECore_COP0RegisterPageMask_t()
{
	registerField(Fields::MASK, "MASK", 13, 12, 0);
}

EECore_COP0RegisterWired_t::EECore_COP0RegisterWired_t()
{
	registerField(Fields::Wired, "Wired", 0, 6, 0);
}

EECore_COP0RegisterBadVAddr_t::EECore_COP0RegisterBadVAddr_t()
{
	registerField(Fields::BadVAddr, "BadVAddr", 0, 32, 0);
}

EECore_COP0RegisterCount_t::EECore_COP0RegisterCount_t()
{
	registerField(Fields::Count, "Count", 0, 32, 0);
}

void EECore_COP0RegisterCount_t::increment(u32 value)
{
	setFieldValue(EECore_COP0RegisterCount_t::Fields::Count, getFieldValue(EECore_COP0RegisterCount_t::Fields::Count) + value);
}

EECore_COP0RegisterEntryHi_t::EECore_COP0RegisterEntryHi_t()
{
	registerField(Fields::ASID, "ASID", 0, 8, 0);
	registerField(Fields::VPN2, "VPN2", 13, 19, 0);
}

EECore_COP0RegisterCompare_t::EECore_COP0RegisterCompare_t(std::shared_ptr<EECore_COP0RegisterCause_t> Cause) :
	mCause(Cause)
{
	registerField(Fields::Compare, "Compare", 0, 32, 0);
}

void EECore_COP0RegisterCompare_t::setFieldValue(const u8& fieldIndex, const u32& value)
{
	mCause->setFieldValue(EECore_COP0RegisterCause_t::Fields::IP7, 0);
	BitfieldRegister32_t::setFieldValue(fieldIndex, value);
}

void EECore_COP0RegisterCompare_t::setRegisterValue(const u32 & value)
{
	mCause->setFieldValue(EECore_COP0RegisterCause_t::Fields::IP7, 0);
	BitfieldRegister32_t::setRegisterValue(value);
}

EECore_COP0RegisterStatus_t::EECore_COP0RegisterStatus_t()
{
	registerField(Fields::IE, "IE", 0, 1, 0);
	registerField(Fields::EXL, "EXL", 1, 1, 0);
	registerField(Fields::ERL, "ERL", 2, 1, 1);
	registerField(Fields::KSU, "KSU", 3, 2, 0);
	registerField(Fields::IM, "IM", 5, 5, 0);
	registerField(Fields::BEM, "BEM", 12, 1, 0);
	registerField(Fields::IM7, "IM7", 15, 1, 0);
	registerField(Fields::EIE, "EIE", 16, 1, 0);
	registerField(Fields::EDI, "EDI", 17, 1, 0);
	registerField(Fields::CH, "CH", 18, 1, 0);
	registerField(Fields::BEV, "BEV", 22, 1, 1);
	registerField(Fields::DEV, "DEV", 23, 1, 0);
	registerField(Fields::CU, "CU", 28, 4, 0);
}

EECore_COP0RegisterCause_t::EECore_COP0RegisterCause_t()
{
	registerField(Fields::ExcCode, "ExcCode", 2, 5, 0);
	registerField(Fields::IP2, "IP2", 10, 1, 0);
	registerField(Fields::IP3, "IP3", 11, 1, 0);
	registerField(Fields::IP7, "IP7", 15, 1, 0);
	registerField(Fields::EXC2, "EXC2", 16, 3, 0);
	registerField(Fields::CE, "CE", 28, 2, 0);
	registerField(Fields::BD2, "BD2", 30, 1, 0);
	registerField(Fields::BD, "BD", 31, 1, 0);
}

EECore_COP0RegisterPRId_t::EECore_COP0RegisterPRId_t()
{
	registerField(Fields::Rev, "Rev", 0, 8, 0x20); // Same as old PCSX2.
	registerField(Fields::Imp, "Imp", 8, 8, 0x2E);
}

EECore_COP0RegisterConfig_t::EECore_COP0RegisterConfig_t()
{
	registerField(Fields::K0, "K0", 0, 3, 0);
	registerField(Fields::DC, "DC", 6, 3, 1);
	registerField(Fields::IC, "IC", 9, 3, 2);
	registerField(Fields::BPE, "BPE", 12, 1, 0);
	registerField(Fields::NBE, "NBE", 13, 1, 0);
	registerField(Fields::DCE, "DCE", 16, 1, 0);
	registerField(Fields::ICE, "ICE", 17, 1, 0);
	registerField(Fields::DIE, "DIE", 18, 1, 0);
	registerField(Fields::EC, "EC", 28, 3, 0);
}

EECore_COP0RegisterBadPAddr_t::EECore_COP0RegisterBadPAddr_t()
{
	registerField(Fields::BadPAddr, "BadPAddr", 4, 28, 0);
}

EECore_COP0RegisterBPC_t::EECore_COP0RegisterBPC_t()
{
	registerField(Fields::IAB, "IAB", 0, 1, 0);
	registerField(Fields::DRB, "DRB", 1, 1, 0);
	registerField(Fields::DWB, "DWB", 2, 1, 0);
	registerField(Fields::BED, "BED", 15, 1, 0);
	registerField(Fields::DTE, "DTE", 16, 1, 0);
	registerField(Fields::ITE, "ITE", 17, 1, 0);
	registerField(Fields::DXE, "DXE", 18, 1, 0);
	registerField(Fields::DKE, "DKE", 19, 1, 0);
	registerField(Fields::DSE, "DSE", 20, 1, 0);
	registerField(Fields::DUE, "DUE", 21, 1, 0);
	registerField(Fields::IXE, "IXE", 23, 1, 0);
	registerField(Fields::IKE, "IKE", 24, 1, 0);
	registerField(Fields::ISE, "ISE", 25, 1, 0);
	registerField(Fields::IUE, "IUE", 26, 1, 0);
	registerField(Fields::DVE, "DVE", 28, 1, 0);
	registerField(Fields::DWE, "DWE", 29, 1, 0);
	registerField(Fields::DRE, "DRE", 30, 1, 0);
	registerField(Fields::IAE, "IAE", 31, 1, 0);
}

EECore_COP0RegisterIAB_t::EECore_COP0RegisterIAB_t()
{
	registerField(Fields::IAB, "IAB", 0, 32, 0);
}

EECore_COP0RegisterIABM_t::EECore_COP0RegisterIABM_t()
{
	registerField(Fields::IABM, "IABM", 0, 32, 0);
}

EECore_COP0RegisterDAB_t::EECore_COP0RegisterDAB_t()
{
	registerField(Fields::DAB, "DAB", 0, 32, 0);
}

EECore_COP0RegisterDABM_t::EECore_COP0RegisterDABM_t()
{
	registerField(Fields::DABM, "DABM", 0, 32, 0);
}

EECore_COP0RegisterDVB_t::EECore_COP0RegisterDVB_t()
{
	registerField(Fields::DVB, "DVB", 0, 32, 0);
}

EECore_COP0RegisterDVBM_t::EECore_COP0RegisterDVBM_t()
{
	registerField(Fields::DVBM, "DVBM", 0, 32, 0);
}

EECore_COP0RegisterPCCR_t::EECore_COP0RegisterPCCR_t()
{
	registerField(Fields::EXL0, "EXL0", 1, 1, 0);
	registerField(Fields::K0, "K0", 2, 1, 0);
	registerField(Fields::S0, "S0", 3, 1, 0);
	registerField(Fields::U0, "U0", 4, 1, 0);
	registerField(Fields::EVENT0, "EVENT0", 5, 5, 0);
	registerField(Fields::EXL1, "EXL1", 11, 1, 0);
	registerField(Fields::K1, "K1", 12, 1, 0);
	registerField(Fields::S1, "S1", 13, 1, 0);
	registerField(Fields::U1, "U1", 14, 1, 0);
	registerField(Fields::EVENT1, "EVENT1", 15, 5, 0);
	registerField(Fields::CTE, "CTE", 31, 1, 0);
}

EECore_COP0RegisterPCR0_t::EECore_COP0RegisterPCR0_t()
{
	registerField(Fields::VALUE, "VALUE", 0, 31, 0);
	registerField(Fields::OVFL, "OVFL", 31, 1, 0);
}

EECore_COP0RegisterPCR1_t::EECore_COP0RegisterPCR1_t()
{
	registerField(Fields::VALUE, "VALUE", 0, 31, 0);
	registerField(Fields::OVFL, "OVFL", 31, 1, 0);
}

EECore_COP0RegisterTagLo_t::EECore_COP0RegisterTagLo_t()
{
	registerField(Fields::L, "L", 3, 1, 0);
	registerField(Fields::R, "R", 4, 1, 0);
	registerField(Fields::V, "V", 5, 1, 0);
	registerField(Fields::D, "D", 6, 1, 0);
	registerField(Fields::PTagLo, "PTagLo", 12, 31, 0);
}

EECore_COP0RegisterTagHi_t::EECore_COP0RegisterTagHi_t()
{
	registerField(Fields::L, "L", 3, 1, 0);
	registerField(Fields::R, "R", 4, 1, 0);
	registerField(Fields::V, "V", 5, 1, 0);
	registerField(Fields::D, "D", 6, 1, 0);
	registerField(Fields::PTagHi, "PTagHi", 12, 31, 0);
}

EECore_COP0RegisterErrorEPC_t::EECore_COP0RegisterErrorEPC_t()
{
	registerField(Fields::ErrorEPC, "ErrorEPC", 0, 32, 0);
}