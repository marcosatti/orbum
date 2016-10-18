#include "stdafx.h"

#include "Common/PS2Resources/Types/MIPSCoprocessor/MIPSCoprocessor0_t.h"
#include "Common/PS2Resources/Types/MIPSCoprocessor/COP0_BitfieldRegisters_t.h"
#include "Common/Global/Globals.h"

MIPSCoprocessor0_t::MIPSCoprocessor0_t() :
	Index(std::make_shared<COP0RegisterIndex_t>()),
	Random(std::make_shared<COP0RegisterRandom_t>()),
	EntryLo0(std::make_shared<COP0RegisterEntryLo0_t>()),
	EntryLo1(std::make_shared<COP0RegisterEntryLo1_t>()),
	Context(std::make_shared<COP0RegisterContext_t>()),
	PageMask(std::make_shared<COP0RegisterPageMask_t>()),
	Wired(std::make_shared<COP0RegisterWired_t>()),
	BadVAddr(std::make_shared<COP0RegisterBadVAddr_t>()),
	Count(std::make_shared<COP0RegisterCount_t>()),
	EntryHi(std::make_shared<COP0RegisterEntryHi_t>()),
	Cause(std::make_shared<COP0RegisterCause_t>()),
	Compare(std::make_shared<COP0RegisterCompare_t>(Cause)),
	Status(std::make_shared<COP0RegisterStatus_t>()),
	EPC(std::make_shared<COP0RegisterEPC_t>()),
	Config(std::make_shared<COP0RegisterConfig_t>()),
	TagLo(std::make_shared<COP0RegisterTagLo_t>()),
	TagHi(std::make_shared<COP0RegisterTagHi_t>()),
	ErrorEPC(std::make_shared<COP0RegisterErrorEPC_t>())
{
}

MIPSCoprocessor0_t::~MIPSCoprocessor0_t()
{
}

bool MIPSCoprocessor0_t::isOperatingUserMode() const
{
	const u32& KSU = Status->getFieldValue(COP0RegisterStatus_t::Fields::KSU);
	const u32& ERL = Status->getFieldValue(COP0RegisterStatus_t::Fields::ERL);
	const u32& EXL = Status->getFieldValue(COP0RegisterStatus_t::Fields::EXL);

	if (KSU == 2 && ERL == 0 && EXL == 0)
		return true;
	else
		return false;
}

bool MIPSCoprocessor0_t::isOperatingSupervisorMode() const
{
	const u32& KSU = Status->getFieldValue(COP0RegisterStatus_t::Fields::KSU);
	const u32& ERL = Status->getFieldValue(COP0RegisterStatus_t::Fields::ERL);
	const u32& EXL = Status->getFieldValue(COP0RegisterStatus_t::Fields::EXL);

	if (KSU == 1 && ERL == 0 && EXL == 0)
		return true;
	else
		return false;
}

bool MIPSCoprocessor0_t::isOperatingKernelMode() const
{
	const u32& KSU = Status->getFieldValue(COP0RegisterStatus_t::Fields::KSU);
	const u32& ERL = Status->getFieldValue(COP0RegisterStatus_t::Fields::ERL);
	const u32& EXL = Status->getFieldValue(COP0RegisterStatus_t::Fields::EXL);

	if (KSU == 0 || ERL == 1 || EXL == 1)
		return true;
	else
		return false;
}
