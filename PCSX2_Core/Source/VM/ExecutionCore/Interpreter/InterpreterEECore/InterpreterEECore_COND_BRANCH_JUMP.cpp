#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/InterpreterEECore/InterpreterEECore.h"
#include "Common/Util/EECoreInstructionUtil/EECoreInstructionUtil.h"

void InterpreterEECore::BEQ()
{
	// BRANCH(Rs == Rt). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) == source2Reg->readDwordS(0))
		;// branch; 
}

void InterpreterEECore::BEQL()
{
	// BRANCH(Rs == Rt). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) == source2Reg->readDwordS(0))
		;// branch likely 
}

void InterpreterEECore::BGEZ()
{
	// BRANCH(Rs >= 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) >= 0)
		;// branch; 
}

void InterpreterEECore::BGEZL()
{
	// BRANCH(Rs >= 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) >= 0)
		;// branch likely; 
}

void InterpreterEECore::BGTZ()
{
	// BRANCH(Rs > 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) > 0)
		;// branch; 
}

void InterpreterEECore::BGTZL()
{
	// BRANCH(Rs > 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) > 0)
		;// branch likely; 
}

void InterpreterEECore::BLEZ()
{
	// BRANCH(Rs <= 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) <= 0)
		;// branch; 
}

void InterpreterEECore::BLEZL()
{
	// BRANCH(Rs <= 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) <= 0)
		;// branch likely; 
}

void InterpreterEECore::BLTZ()
{
	// BRANCH(Rs < 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) < 0)
		;// branch; 
}

void InterpreterEECore::BLTZL()
{
	// BRANCH(Rs < 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) < 0)
		;// branch likely; 
}

void InterpreterEECore::BNE()
{
	// BRANCH(Rs != 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) != 0)
		;// branch; 
}

void InterpreterEECore::BNEL()
{
	// BRANCH(Rs != 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) != 0)
		;// branch likely;
}

void InterpreterEECore::BC0F()
{
	// TODO: Implement.
	// BRANCH(CPCOND0 == false). Coprocessor Unusable exception.
	const s16 offset = getInstruction().getIImmS();

	// if (CPCOND0 == false)
		// branch; 
	throw std::runtime_error("BC0F: Not implemented.");
}

void InterpreterEECore::BC0FL()
{
	// TODO: Implement.
	// BRANCH(CPCOND0 == false). Coprocessor Unusable exception.
	const s16 offset = getInstruction().getIImmS();

	// if (CPCOND0 == false)
		// branch likely; 
	throw std::runtime_error("BC0F: Not implemented.");
}

void InterpreterEECore::BC0T()
{
	// TODO: Implement.
	// BRANCH(CPCOND0 == true). Coprocessor Unusable exception.
	const s16 offset = getInstruction().getIImmS();

	// if (CPCOND0 == true)
	// branch; 
	throw std::runtime_error("BC0T: Not implemented.");
}

void InterpreterEECore::BC0TL()
{
	// TODO: Implement.
	// BRANCH(CPCOND0 == true). Coprocessor Unusable exception.
	const s16 offset = getInstruction().getIImmS();

	// if (CPCOND0 == true)
	// branch likely; 
	throw std::runtime_error("BC0TL: Not implemented.");
}

void InterpreterEECore::BC1F()
{
	// BRANCH(FCR31[C flag] == 0). Coprocessor Unusable exception.
	const s16 offset = getInstruction().getIImmS();

	if (getVM()->getResources()->EE->EECore->COP1->CSR->getFieldValue(RegisterCSR_t::Fields::C) == 0)
		;// branch;
}

void InterpreterEECore::BC1FL()
{
	// BRANCH(FCR31[C flag] == 0). Coprocessor Unusable exception.
	const s16 offset = getInstruction().getIImmS();

	if (getVM()->getResources()->EE->EECore->COP1->CSR->getFieldValue(RegisterCSR_t::Fields::C) == 0)
		;// branch likely;
}

void InterpreterEECore::BC1T()
{
	// BRANCH(FCR31[C flag] == 1). Coprocessor Unusable exception.
	const s16 offset = getInstruction().getIImmS();

	if (getVM()->getResources()->EE->EECore->COP1->CSR->getFieldValue(RegisterCSR_t::Fields::C) == 1)
		;// branch;
}

void InterpreterEECore::BC1TL()
{
	// BRANCH(FCR31[C flag] == 1). Coprocessor Unusable exception.
	const s16 offset = getInstruction().getIImmS();

	if (getVM()->getResources()->EE->EECore->COP1->CSR->getFieldValue(RegisterCSR_t::Fields::C) == 1)
		;// branch likely;
}

void InterpreterEECore::BC2F()
{
	// TODO: Implement.
	throw std::runtime_error("BC2F: Not implemented.");
}

void InterpreterEECore::BC2FL()
{
	// TODO: Implement.
	throw std::runtime_error("BC2FL: Not implemented.");
}

void InterpreterEECore::BC2T()
{
	// TODO: Implement.
	throw std::runtime_error("BC2T: Not implemented.");
}

void InterpreterEECore::BC2TL()
{
	// TODO: Implement.
	throw std::runtime_error("BC2TL: Not implemented.");
}

void InterpreterEECore::J()
{
	// JUMP(). No Exceptions.
	const s32 offset = getInstruction().getJOffsetAddress();
	// branch; 
}

void InterpreterEECore::JR()
{
	// JUMP(). Exceptions generated by other components.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	// branch to address in source1Reg->readWordU(0);
}
