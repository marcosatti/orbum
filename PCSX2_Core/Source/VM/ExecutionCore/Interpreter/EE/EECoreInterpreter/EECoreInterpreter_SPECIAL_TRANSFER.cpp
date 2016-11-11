#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreInterpreter.h"
#include "Common/Types/Registers/Register128_t.h"
#include "Common/Types/Registers/Register32_t.h"
#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreExceptions_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreException_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreCOP0_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreCOP0Registers_t.h"
#include "Common/Types/MIPSCoprocessor/COP0_BitfieldRegisters_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreFPU_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreFPURegisters_t.h"

void EECoreInterpreter::MFSA()
{
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->SA;

	destReg->writeDwordU(0, static_cast<u64>(sourceReg->readWordU()));
}

void EECoreInterpreter::MTSA()
{
	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->SA;

	destReg->writeWordU(sourceReg->readWordU(0));
}

void EECoreInterpreter::MTSAB()
{
	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->SA;
	s16 imm = getInstruction().getIImmS();

	destReg->writeWordU(((sourceReg->readWordU(0) & 0xF) ^ (imm & 0xF)) * 8);
}

void EECoreInterpreter::MTSAH()
{
	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->SA;
	s16 imm = getInstruction().getIImmS();

	destReg->writeWordU(((sourceReg->readWordU(0) & 0x7) ^ (imm & 0x7)) * 16);
}

void EECoreInterpreter::MFBPC()
{
	if (!getVM()->getResources()->EE->EECore->COP0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 0 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& sourceReg = getVM()->getResources()->EE->EECore->COP0->BPC;

	destReg->writeDwordU(0, static_cast<u64>(sourceReg->readWordU()));
}

void EECoreInterpreter::MFC0()
{
	if (!getVM()->getResources()->EE->EECore->COP0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 0 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& sourceReg = getVM()->getResources()->EE->EECore->COP0->Registers[getInstruction().getRRd()];

	destReg->writeDwordU(0, static_cast<u64>(sourceReg->readWordU()));
}

void EECoreInterpreter::MFDAB()
{
	if (!getVM()->getResources()->EE->EECore->COP0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 0 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& sourceReg = getVM()->getResources()->EE->EECore->COP0->DAB;

	destReg->writeDwordU(0, static_cast<u64>(sourceReg->readWordU()));
}

void EECoreInterpreter::MFDABM()
{
	if (!getVM()->getResources()->EE->EECore->COP0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 0 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& sourceReg = getVM()->getResources()->EE->EECore->COP0->DABM;

	destReg->writeDwordU(0, static_cast<u64>(sourceReg->readWordU()));
}

void EECoreInterpreter::MFDVB()
{
	if (!getVM()->getResources()->EE->EECore->COP0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 0 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& sourceReg = getVM()->getResources()->EE->EECore->COP0->DVB;

	destReg->writeDwordU(0, static_cast<u64>(sourceReg->readWordU()));
}

void EECoreInterpreter::MFDVBM()
{
	if (!getVM()->getResources()->EE->EECore->COP0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 0 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& sourceReg = getVM()->getResources()->EE->EECore->COP0->DVBM;

	destReg->writeDwordU(0, static_cast<u64>(sourceReg->readWordU()));
}

void EECoreInterpreter::MFIAB()
{
	if (!getVM()->getResources()->EE->EECore->COP0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 0 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& sourceReg = getVM()->getResources()->EE->EECore->COP0->IAB;

	destReg->writeDwordU(0, static_cast<u64>(sourceReg->readWordU()));
}

void EECoreInterpreter::MFIABM()
{
	if(!getVM()->getResources()->EE->EECore->COP0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 0 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
	}

	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& sourceReg = getVM()->getResources()->EE->EECore->COP0->IABM;

	destReg->writeDwordU(0, static_cast<u64>(sourceReg->readWordU()));
}

void EECoreInterpreter::MFPC()
{
	if (!getVM()->getResources()->EE->EECore->COP0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 0 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	u8 perfRegisterIndex = getInstruction().getRFunct() & 0x3E; // Last 5 bits of the funct field contain the performace counter register number to use. Must be 0 or 1 (but not checked).
	auto& sourceReg = getVM()->getResources()->EE->EECore->COP0->PCRRegisters[perfRegisterIndex];

	destReg->writeDwordU(0, static_cast<u64>(sourceReg->readWordU()));
}

void EECoreInterpreter::MFPS()
{
	if (!getVM()->getResources()->EE->EECore->COP0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 0 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& sourceReg = getVM()->getResources()->EE->EECore->COP0->PCCR; // The reg field in the documentation must be 0, meaning the PCCR register.

	destReg->writeDwordU(0, static_cast<u64>(sourceReg->readWordU()));
}

void EECoreInterpreter::MTBPC()
{
	if (!getVM()->getResources()->EE->EECore->COP0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 0 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->COP0->BPC;

	destReg->writeWordU(sourceReg->readWordU(0));
}

void EECoreInterpreter::MTC0()
{
	if (!getVM()->getResources()->EE->EECore->COP0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 0 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->COP0->Registers[getInstruction().getRRd()];

	destReg->writeWordU(sourceReg->readWordU(0));
}

void EECoreInterpreter::MTDAB()
{
	if (!getVM()->getResources()->EE->EECore->COP0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 0 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->COP0->DAB;

	destReg->writeWordU(sourceReg->readWordU(0));
}

void EECoreInterpreter::MTDABM()
{
	if (!getVM()->getResources()->EE->EECore->COP0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 0 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->COP0->DABM;

	destReg->writeWordU(sourceReg->readWordU(0));
}

void EECoreInterpreter::MTDVB()
{
	if (!getVM()->getResources()->EE->EECore->COP0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 0 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->COP0->DVB;

	destReg->writeWordU(sourceReg->readWordU(0));
}

void EECoreInterpreter::MTDVBM()
{
	if (!getVM()->getResources()->EE->EECore->COP0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 0 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->COP0->DVBM;

	destReg->writeWordU(sourceReg->readWordU(0));
}

void EECoreInterpreter::MTIAB()
{
	if (!getVM()->getResources()->EE->EECore->COP0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 0 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->COP0->IAB;

	destReg->writeWordU(sourceReg->readWordU(0));
}

void EECoreInterpreter::MTIABM()
{
	if (!getVM()->getResources()->EE->EECore->COP0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 0 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->COP0->IABM;

	destReg->writeWordU(sourceReg->readWordU(0));
}

void EECoreInterpreter::MTPC()
{
	if (!getVM()->getResources()->EE->EECore->COP0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 0 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	u8 perfRegisterIndex = getInstruction().getRFunct() & 0x3E; // Last 5 bits of the funct field contain the performace counter register number to use. Must be 0 or 1 (but not checked).
	auto& destReg = getVM()->getResources()->EE->EECore->COP0->PCRRegisters[perfRegisterIndex];

	destReg->writeWordU(sourceReg->readWordU(0));
}

void EECoreInterpreter::MTPS()
{
	if (!getVM()->getResources()->EE->EECore->COP0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 0 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->COP0->PCCR; // The reg field in the documentation must be 0, meaning the PCCR register.

	destReg->writeWordU(sourceReg->readWordU(0));
}

void EECoreInterpreter::CFC1()
{
	if (!getVM()->getResources()->EE->EECore->FPU->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 1 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& sourceReg = getVM()->getResources()->EE->EECore->FPU->BitfieldRegisters[getInstruction().getRRd()]; // Fs, can only be 0 or 31.

	destReg->writeDwordU(0, static_cast<u64>(sourceReg->readWordU()));
}

void EECoreInterpreter::CTC1()
{
	if (!getVM()->getResources()->EE->EECore->FPU->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 1 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->FPU->BitfieldRegisters[getInstruction().getRRd()];

	destReg->writeWordU(sourceReg->readWordU(0));
}