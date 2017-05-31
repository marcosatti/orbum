#include "Common/Global/Globals.h"
#include "Common/Types/Register/Register32_t.h"

#include "VM/Systems/IOP/IOPCoreInterpreter/IOPCoreInterpreter_s.h"

#include "Resources/IOP/IOPCore/IOPCore_t.h"
#include "Resources/IOP/IOPCore/Types/IOPCoreR3000_t.h"
#include "Resources/IOP/IOPCore/Types/IOPCoreCOP0_t.h"

void IOPCoreInterpreter_s::MFC0()
{
	if (handleCOP0Usable())
		return;

	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	auto& sourceReg = mIOPCore->COP0->Registers[mIOPCoreInstruction.getRRd()];

	destReg->writeWord(getContext(), static_cast<u32>(sourceReg->readWord(getContext())));
}

void IOPCoreInterpreter_s::MTC0()
{
	if (handleCOP0Usable())
		return;

	auto& sourceReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	auto& destReg = mIOPCore->COP0->Registers[mIOPCoreInstruction.getRRd()];

	destReg->writeWord(getContext(), sourceReg->readWord(getContext()));
}

void IOPCoreInterpreter_s::MFHI()
{
	// Rd = HI. No exceptions.
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];
	auto& source1Reg = mIOPCore->R3000->HI;

	destReg->writeWord(getContext(), source1Reg->readWord(getContext()));
}

void IOPCoreInterpreter_s::MFLO()
{
	// Rd = LO. No exceptions.
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];
	auto& source1Reg = mIOPCore->R3000->LO;

	destReg->writeWord(getContext(), source1Reg->readWord(getContext()));
}

void IOPCoreInterpreter_s::MTHI()
{
	// HI = Rd. No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];
	auto& destReg = mIOPCore->R3000->HI;

	destReg->writeWord(getContext(), source1Reg->readWord(getContext()));
}

void IOPCoreInterpreter_s::MTLO()
{
	// LO = Rd. No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];
	auto& destReg = mIOPCore->R3000->LO;

	destReg->writeWord(getContext(), source1Reg->readWord(getContext()));
}
