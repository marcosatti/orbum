#include "stdafx.h"

#include "Common/Types/Context_t.h"
#include "Common/Types/Registers/Register32_t.h"
#include "Common/Types/Registers/BitfieldRegister32_t.h"

#include "VM/ExecutionCore/Interpreter/IOP/IOPCoreInterpreter/IOPCoreInterpreter.h"
#include "VM/ExecutionCore/Interpreter/IOP/IOPCoreInterpreter/IOPCoreMMUHandler/IOPCoreMMUHandler.h"
#include "VM/VMMain.h"

#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/IOP/IOP_t.h"
#include "PS2Resources/IOP/IOPCore/IOPCore_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreR3000_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreCOP0_t.h"

void IOPCoreInterpreter::MFC0()
{
	if (!checkCOP0Usable())
		return;

	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRt()];
	auto& sourceReg = getResources()->IOP->IOPCore->COP0->Registers[mInstruction.getRRd()];

	destReg->writeWord(Context_t::IOP, static_cast<u32>(sourceReg->readWord(Context_t::IOP)));
}

void IOPCoreInterpreter::MTC0()
{
	if (!checkCOP0Usable())
		return;

	auto& sourceReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->IOP->IOPCore->COP0->Registers[mInstruction.getRRd()];

	destReg->writeWord(Context_t::IOP, sourceReg->readWord(Context_t::IOP));
}

void IOPCoreInterpreter::MFHI()
{
	// Rd = HI. No exceptions.
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->HI;

	destReg->writeWord(Context_t::IOP, source1Reg->readWord(Context_t::IOP));
}

void IOPCoreInterpreter::MFLO()
{
	// Rd = LO. No exceptions.
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->LO;

	destReg->writeWord(Context_t::IOP, source1Reg->readWord(Context_t::IOP));
}

void IOPCoreInterpreter::MTHI()
{
	// HI = Rd. No exceptions.
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRd()];
	auto& destReg = getResources()->IOP->IOPCore->R3000->HI;

	destReg->writeWord(Context_t::IOP, source1Reg->readWord(Context_t::IOP));
}

void IOPCoreInterpreter::MTLO()
{
	// LO = Rd. No exceptions.
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRd()];
	auto& destReg = getResources()->IOP->IOPCore->R3000->LO;

	destReg->writeWord(Context_t::IOP, source1Reg->readWord(Context_t::IOP));
}
