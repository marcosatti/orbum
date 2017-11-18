
#include "Common/Types/Register/SizedWordRegister.hpp"

#include "VM/Systems/IOP/IOPCoreInterpreter/IOPCoreInterpreter_s.h"

#include "Resources/Iop/Core/RIopCore.h"
#include "Resources/Iop/Core/IopCoreR3000.h"
#include "Resources/Iop/Core/IopCoreCop0.h"

void IOPCoreInterpreter_s::MFC0()
{
	if (handleCOP0Usable())
		return;

	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	auto& sourceReg = mIOPCore->COP0->Registers[mIOPCoreInstruction.getRRd()];

	destReg->write_uword(static_cast<uword>(sourceReg->read_uword()));
}

void IOPCoreInterpreter_s::MTC0()
{
	if (handleCOP0Usable())
		return;

	auto& sourceReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	auto& destReg = mIOPCore->COP0->Registers[mIOPCoreInstruction.getRRd()];

	destReg->write_uword(sourceReg->read_uword());
}

void IOPCoreInterpreter_s::MFHI()
{
	// Rd = HI. No exceptions.
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];
	auto& source1Reg = mIOPCore->R3000->HI;

	destReg->write_uword(source1Reg->read_uword());
}

void IOPCoreInterpreter_s::MFLO()
{
	// Rd = LO. No exceptions.
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];
	auto& source1Reg = mIOPCore->R3000->LO;

	destReg->write_uword(source1Reg->read_uword());
}

void IOPCoreInterpreter_s::MTHI()
{
	// HI = Rd. No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];
	auto& destReg = mIOPCore->R3000->HI;

	destReg->write_uword(source1Reg->read_uword());
}

void IOPCoreInterpreter_s::MTLO()
{
	// LO = Rd. No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];
	auto& destReg = mIOPCore->R3000->LO;

	destReg->write_uword(source1Reg->read_uword());
}
