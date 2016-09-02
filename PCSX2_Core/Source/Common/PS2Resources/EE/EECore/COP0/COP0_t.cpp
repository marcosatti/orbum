#include "stdafx.h"

#include "Common/PS2Resources/EE/EECore/COP0/COP0_t.h"
#include "Common/PS2Resources/EE/EECore/COP0/Types/COP0_BitfieldRegisters_t.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/EE/EECore/EECore_t.h"

COP0_t::COP0_t(const PS2Resources_t* const PS2Resources) : 
	PS2ResourcesSubobject(PS2Resources),
	Index(std::make_shared<RegisterIndex_t>()),
	Random(std::make_shared<RegisterRandom_t>()),
	EntryLo0(std::make_shared<RegisterEntryLo0_t>()),
	EntryLo1(std::make_shared<RegisterEntryLo1_t>()),
	Context(std::make_shared<RegisterContext_t>()),
	PageMask(std::make_shared<RegisterPageMask_t>()),
	Wired(std::make_shared<RegisterWired_t>()),
	reserved0(std::make_shared<RegisterReserved_t>()),
	BadVAddr(std::make_shared<RegisterBadVAddr_t>()),
	Count(std::make_shared<RegisterCount_t>()),
	EntryHi(std::make_shared<RegisterEntryHi_t>()),
	Compare(std::make_shared<RegisterCompare_t>(getRootResources())),
	Status(std::make_shared<RegisterStatus_t>()),
	Cause(std::make_shared<RegisterCause_t>()),
	EPC(std::make_shared<RegisterEPC_t>()),
	PRId(std::make_shared<RegisterPRId_t>()),
	Config(std::make_shared<RegisterConfig_t>()),
	reserved1(std::make_shared<RegisterReserved_t>()),
	reserved2(std::make_shared<RegisterReserved_t>()),
	reserved3(std::make_shared<RegisterReserved_t>()),
	reserved4(std::make_shared<RegisterReserved_t>()),
	reserved5(std::make_shared<RegisterReserved_t>()),
	reserved6(std::make_shared<RegisterReserved_t>()),
	BadPAddr(std::make_shared<RegisterBadPAddr_t>()),
	reserved7(std::make_shared<RegisterReserved_t>()),
	reserved8(std::make_shared<RegisterReserved_t>()),
	TagLo(std::make_shared<RegisterTagLo_t>()),
	TagHi(std::make_shared<RegisterTagHi_t>()),
	ErrorEPC(std::make_shared<RegisterErrorEPC_t>()),
	reserved9(std::make_shared<RegisterReserved_t>()),
	BPC(std::make_shared<RegisterBPC_t>()),
	IAB(std::make_shared<RegisterIAB_t>()),
	IABM(std::make_shared<RegisterIABM_t>()),
	DAB(std::make_shared<RegisterDAB_t>()),
	DABM(std::make_shared<RegisterDABM_t>()),
	DVB(std::make_shared<RegisterDVB_t>()),
	DVBM(std::make_shared<RegisterDVBM_t>()),
	PCCR(std::make_shared<RegisterPCCR_t>()),
	PCR0(std::make_shared<RegisterPCR0_t>()),
	PCR1(std::make_shared<RegisterPCR1_t>()),
	Registers{ Index, Random, EntryLo0, EntryLo1, Context, PageMask, Wired, reserved0, BadVAddr, Count, EntryHi, Compare, Status, Cause, EPC, PRId, Config, reserved1, reserved2, reserved3, reserved4, reserved5, reserved6, BadPAddr, BPC, PCCR, reserved7, reserved8, TagLo, TagHi, ErrorEPC, reserved9 },
	PCRRegisters{ PCR0, PCR1 }
{
}

bool COP0_t::isOperatingUserMode() const
{
	const u32& KSU = Status->getFieldValue(RegisterStatus_t::Fields::KSU);
	const u32& ERL = Status->getFieldValue(RegisterStatus_t::Fields::ERL);
	const u32& EXL = Status->getFieldValue(RegisterStatus_t::Fields::EXL);

	if (KSU == 2 && ERL == 0 && EXL == 0)
		return true;
	else
		return false;
}

bool COP0_t::isOperatingSupervisorMode() const
{
	const u32& KSU = Status->getFieldValue(RegisterStatus_t::Fields::KSU);
	const u32& ERL = Status->getFieldValue(RegisterStatus_t::Fields::ERL);
	const u32& EXL = Status->getFieldValue(RegisterStatus_t::Fields::EXL);

	if (KSU == 1 && ERL == 0 && EXL == 0)
		return true;
	else
		return false;
}

bool COP0_t::isOperatingKernelMode() const
{
	const u32& KSU = Status->getFieldValue(RegisterStatus_t::Fields::KSU);
	const u32& ERL = Status->getFieldValue(RegisterStatus_t::Fields::ERL);
	const u32& EXL = Status->getFieldValue(RegisterStatus_t::Fields::EXL);

	if (KSU == 0 || ERL == 1 || EXL == 1)
		return true;
	else
		return false;
}

bool COP0_t::isCOP0Usable() const
{
	// First check for kernel mode - the COP0 is always available in this mode. If not, then check that CU[bit 0] == 1 (ie: >0) in the status register.
	if (isOperatingKernelMode())
		return true;
	else if ((getRootResources()->EE->EECore->COP0->Status->getFieldValue(RegisterStatus_t::Fields::CU) & 0x1) > 0)
		return true;
	else
		return false;
}
