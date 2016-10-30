#include "stdafx.h"

#include "Common/PS2Resources/IOP/IOPCore/IOPCoreCOP0/Types/IOPCore_COP0_Registers_t.h"
#include "Common/PS2Resources/Types/Registers/BitfieldRegister32_t.h"

IOPCore_COP0RegisterContext_t::IOPCore_COP0RegisterContext_t()
{
	registerField(Fields::BadVPN2, "BadVPN2", 2, 19, 0);
	registerField(Fields::PTEBase, "PTEBase", 21, 11, 0);
}

IOPCore_COP0RegisterStatus_t::IOPCore_COP0RegisterStatus_t()
{
	registerField(Fields::IEc, "IEc", 0, 1, 0);
	registerField(Fields::KUc, "KUc", 1, 1, 0);
	registerField(Fields::IEp, "IEp", 2, 1, 0);
	registerField(Fields::KUp, "KUp", 3, 1, 0);
	registerField(Fields::IEo, "IEo", 4, 1, 0);
	registerField(Fields::KUo, "KUo", 5, 1, 0);
	registerField(Fields::IM, "IM", 8, 8, 0);
	registerField(Fields::IsC, "IsC", 16, 1, 0);
	registerField(Fields::SwC, "SwC", 17, 1, 0);
	registerField(Fields::PZ, "PZ", 18, 1, 0);
	registerField(Fields::CM, "CM", 19, 1, 0);
	registerField(Fields::PE, "PE", 20, 1, 0);
	registerField(Fields::TS, "TS", 21, 1, 0);
	registerField(Fields::BEV, "BEV", 22, 1, 1);
	registerField(Fields::RE, "RE", 25, 1, 0);
	registerField(Fields::CU, "CU", 28, 4, 0);
}

IOPCore_COP0RegisterCause_t::IOPCore_COP0RegisterCause_t()
{
	registerField(Fields::ExcCode, "ExcCode", 2, 5, 0);
	registerField(Fields::IP, "IP", 8, 8, 0);
	registerField(Fields::CE, "CE", 28, 2, 0);
	registerField(Fields::BD, "BD", 31, 1, 0);
}

IOPCore_COP0RegisterPRId_t::IOPCore_COP0RegisterPRId_t()
{
	registerField(Fields::Rev, "Rev", 0, 8, 0x1F); // Same as old PCSX2.
	registerField(Fields::Imp, "Imp", 8, 8, 0x00);
}
