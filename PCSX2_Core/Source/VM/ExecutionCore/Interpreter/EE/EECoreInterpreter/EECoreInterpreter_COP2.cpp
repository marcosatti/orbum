#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreInterpreter.h"
#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreMMUHandler/EECoreMMUHandler.h"
#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreExceptions_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreException_t.h"
#include "PS2Resources/EE/VPU/VPU_t.h"
#include "PS2Resources/EE/VPU/Types/VuUnits_t.h"
#include "Common/Types/Registers/FPRegister128_t.h"
#include "Common/Types/Registers/Register128_t.h"

void EECoreInterpreter::QMFC2()
{
	// GPR = VU0.VF. Coprocessor unusable exception.
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// Check for the interlock bit.
	if (getInstruction().getRFunct() & 0x1)
	{
		throw std::runtime_error("COP2 (VU0) interlock bit set, but not implemented");
	}

	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& source1Reg = getVM()->getResources()->EE->VPU->VU0->VF[getInstruction().getRRd()];

	destReg->writeDwordU(0, source1Reg->readDwordU(0));
	destReg->writeDwordU(1, source1Reg->readDwordU(1));
}

void EECoreInterpreter::QMTC2()
{
	// VU0.VF = GPR. Coprocessor unusable exception.
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// Check for the interlock bit.
	if (getInstruction().getRFunct() & 0x1)
	{
		throw std::runtime_error("COP2 (VU0) interlock bit set, but not implemented");
	}

	auto& destReg = getVM()->getResources()->EE->VPU->VU0->VF[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	destReg->writeDwordU(0, source1Reg->readDwordU(0));
	destReg->writeDwordU(1, source1Reg->readDwordU(1));
}

void EECoreInterpreter::LQC2()
{
	// VU0.VF = GPR. Coprocessor unusable exception.
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& destReg = getVM()->getResources()->EE->VPU->VU0->VF[getInstruction().getIRt()];
	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()]; // "Base"
	const s16 imm = getInstruction().getIImmS();

	u32 PS2VirtualAddress = (sourceReg->readWordU(0) + imm) & (~static_cast<u32>(0xF)); // Strip the last 4 bits, as the access must be aligned (the documentation says to do this).
	u64 value;
	// TODO: Im not sure if this is correct for big-endian.

	value = getMMUHandler()->readDwordU(PS2VirtualAddress);
	// Check for MMU error (1).
	if (getMMUHandler()->hasExceptionOccurred())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		Exceptions->setException(getMMUHandler()->getExceptionInfo());
		return; // Return early, dont bother trying to load the second dword.
	}
	else
		destReg->writeDwordU(0, value); // Get first 8 bytes (bytes 0 -> 7).

	value = getMMUHandler()->readDwordU(PS2VirtualAddress + Constants::NUMBER_BYTES_IN_DWORD);
	// Check for MMU error (2).
	if (getMMUHandler()->hasExceptionOccurred())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		Exceptions->setException(getMMUHandler()->getExceptionInfo());
		return;
	}
	else
		destReg->writeDwordU(1, value); // Get second 8 bytes (bytes 8 -> 15).
}

void EECoreInterpreter::SQC2()
{
	// VU0.VF = GPR. Coprocessor unusable exception.
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()]; // "Base"
	auto& source2Reg = getVM()->getResources()->EE->VPU->VU0->VF[getInstruction().getIRt()];
	const s16 imm = getInstruction().getIImmS();

	u32 PS2VirtualAddress = source1Reg->readWordU(0) + imm;

	getMMUHandler()->writeDwordU(PS2VirtualAddress, source2Reg->readDwordU(0));
	// Check for MMU error.
	if (getMMUHandler()->hasExceptionOccurred())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		Exceptions->setException(getMMUHandler()->getExceptionInfo());
		return; // Return early, dont bother trying to write the second dword.
	}

	getMMUHandler()->writeDwordU(PS2VirtualAddress + Constants::NUMBER_BYTES_IN_DWORD, source2Reg->readDwordU(1));
	// Check for MMU error.
	if (getMMUHandler()->hasExceptionOccurred())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		Exceptions->setException(getMMUHandler()->getExceptionInfo());
		return;
	}
}

void EECoreInterpreter::CFC2()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}
	

}

void EECoreInterpreter::CTC2()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

}

void EECoreInterpreter::BC2F()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) BC2F: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("BC2F: Not implemented.");
#endif
}

void EECoreInterpreter::BC2FL()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) BC2FL: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("BC2FL: Not implemented.");
#endif
}

void EECoreInterpreter::BC2T()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) BC2T: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("BC2T: Not implemented.");
#endif
}

void EECoreInterpreter::BC2TL()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) BC2TL: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("BC2TL: Not implemented.");
#endif
}

void EECoreInterpreter::VABS()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VABS: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VABS: Not implemented.");
#endif
}

void EECoreInterpreter::VADD()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VADD: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VADD: Not implemented.");
#endif
}

void EECoreInterpreter::VADDi()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VADDi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VADDi: Not implemented.");
#endif
}

void EECoreInterpreter::VADDq()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VADDq: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VADDq: Not implemented.");
#endif
}

void EECoreInterpreter::VADDbc()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VADDbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VADDbc: Not implemented.");
#endif
}

void EECoreInterpreter::VADDbc_0()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VADDbc_0: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VADDbc_0: Not implemented.");
#endif
}

void EECoreInterpreter::VADDbc_1()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VADDbc_1: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VADDbc_1: Not implemented.");
#endif
}

void EECoreInterpreter::VADDbc_2()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VADDbc_2: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VADDbc_2: Not implemented.");
#endif
}

void EECoreInterpreter::VADDbc_3()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VADDbc_3: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VADDbc_3: Not implemented.");
#endif
}

void EECoreInterpreter::VADDA()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VADDA: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VADDA: Not implemented.");
#endif
}

void EECoreInterpreter::VADDAi()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VADDAi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VADDAi: Not implemented.");
#endif
}

void EECoreInterpreter::VADDAq()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VADDAq: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VADDAq: Not implemented.");
#endif
}

void EECoreInterpreter::VADDAbc()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VADDAbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VADDAbc: Not implemented.");
#endif
}

void EECoreInterpreter::VADDAbc_0()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VADDAbc_0: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VADDAbc_0: Not implemented.");
#endif
}

void EECoreInterpreter::VADDAbc_1()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VADDAbc_1: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VADDAbc_1: Not implemented.");
#endif
}

void EECoreInterpreter::VADDAbc_2()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VADDAbc_2: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VADDAbc_2: Not implemented.");
#endif
}

void EECoreInterpreter::VADDAbc_3()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VADDAbc_3: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VADDAbc_3: Not implemented.");
#endif
}

void EECoreInterpreter::VSUB()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VSUB: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VSUB: Not implemented.");
#endif
}

void EECoreInterpreter::VSUBi()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VSUBi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VSUBi: Not implemented.");
#endif
}

void EECoreInterpreter::VSUBq()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VSUBq: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VSUBq: Not implemented.");
#endif
}

void EECoreInterpreter::VSUBbc()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VSUBbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VSUBbc: Not implemented.");
#endif
}

void EECoreInterpreter::VSUBbc_0()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VSUBbc_0: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VSUBbc_0: Not implemented.");
#endif
}

void EECoreInterpreter::VSUBbc_1()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VSUBbc_1: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VSUBbc_1: Not implemented.");
#endif
}

void EECoreInterpreter::VSUBbc_2()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VSUBbc_2: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VSUBbc_2: Not implemented.");
#endif
}

void EECoreInterpreter::VSUBbc_3()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VSUBbc_3: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VSUBbc_3: Not implemented.");
#endif
}

void EECoreInterpreter::VSUBA()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VSUBA: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VSUBA: Not implemented.");
#endif
}

void EECoreInterpreter::VSUBAi()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VSUBAi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VSUBAi: Not implemented.");
#endif
}

void EECoreInterpreter::VSUBAq()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VSUBAq: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VSUBAq: Not implemented.");
#endif
}

void EECoreInterpreter::VSUBAbc()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VSUBAbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VSUBAbc: Not implemented.");
#endif
}

void EECoreInterpreter::VSUBAbc_0()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VSUBAbc_0: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VSUBAbc_0: Not implemented.");
#endif
}

void EECoreInterpreter::VSUBAbc_1()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VSUBAbc_1: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VSUBAbc_1: Not implemented.");
#endif
}

void EECoreInterpreter::VSUBAbc_2()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VSUBAbc_2: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VSUBAbc_2: Not implemented.");
#endif
}

void EECoreInterpreter::VSUBAbc_3()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VSUBAbc_3: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VSUBAbc_3: Not implemented.");
#endif
}

void EECoreInterpreter::VMUL()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMU: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMU: Not implemented.");
#endif
}

void EECoreInterpreter::VMULi()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMULi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMULi: Not implemented.");
#endif
}

void EECoreInterpreter::VMULq()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMULq: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMULq: Not implemented.");
#endif
}

void EECoreInterpreter::VMULbc()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMULbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMULbc: Not implemented.");
#endif
}

void EECoreInterpreter::VMULbc_0()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMULbc_0: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMULbc_0: Not implemented.");
#endif
}

void EECoreInterpreter::VMULbc_1()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMULbc_1: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMULbc_1: Not implemented.");
#endif
}

void EECoreInterpreter::VMULbc_2()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMULbc_2: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMULbc_2: Not implemented.");
#endif
}

void EECoreInterpreter::VMULbc_3()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMULbc_3: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMULbc_3: Not implemented.");
#endif
}

void EECoreInterpreter::VMULA()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMULA: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMULA: Not implemented.");
#endif
}

void EECoreInterpreter::VMULAi()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMULAi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMULAi: Not implemented.");
#endif
}

void EECoreInterpreter::VMULAq()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMULAq: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMULAq: Not implemented.");
#endif
}

void EECoreInterpreter::VMULAbc()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMULAbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMULAbc: Not implemented.");
#endif
}

void EECoreInterpreter::VMULAbc_0()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMULAbc_0: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMULAbc_0: Not implemented.");
#endif
}

void EECoreInterpreter::VMULAbc_1()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMULAbc_1: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMULAbc_1: Not implemented.");
#endif
}

void EECoreInterpreter::VMULAbc_2()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMULAbc_2: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMULAbc_2: Not implemented.");
#endif
}

void EECoreInterpreter::VMULAbc_3()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMULAbc_3: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMULAbc_3: Not implemented.");
#endif
}

void EECoreInterpreter::VMADD()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMADD: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMADD: Not implemented.");
#endif
}

void EECoreInterpreter::VMADDi()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMADDi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMADDi: Not implemented.");
#endif
}

void EECoreInterpreter::VMADDq()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMADDq: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMADDq: Not implemented.");
#endif
}

void EECoreInterpreter::VMADDbc()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMADDbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMADDbc: Not implemented.");
#endif
}

void EECoreInterpreter::VMADDbc_0()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMADDbc_0: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMADDbc_0: Not implemented.");
#endif
}

void EECoreInterpreter::VMADDbc_1()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMADDbc_1: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMADDbc_1: Not implemented.");
#endif
}

void EECoreInterpreter::VMADDbc_2()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMADDbc_2: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMADDbc_2: Not implemented.");
#endif
}

void EECoreInterpreter::VMADDbc_3()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMADDbc_3: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMADDbc_3: Not implemented.");
#endif
}

void EECoreInterpreter::VMADDA()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMADDA: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMADDA: Not implemented.");
#endif
}

void EECoreInterpreter::VMADDAi()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMADDAi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMADDAi: Not implemented.");
#endif
}

void EECoreInterpreter::VMADDAq()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMADDAq: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMADDAq: Not implemented.");
#endif
}

void EECoreInterpreter::VMADDAbc()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMADDAbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMADDAbc: Not implemented.");
#endif
}

void EECoreInterpreter::VMADDAbc_0()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMADDAbc_0: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMADDAbc_0: Not implemented.");
#endif
}

void EECoreInterpreter::VMADDAbc_1()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMADDAbc_1: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMADDAbc_1: Not implemented.");
#endif
}

void EECoreInterpreter::VMADDAbc_2()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMADDAbc_2: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMADDAbc_2: Not implemented.");
#endif
}

void EECoreInterpreter::VMADDAbc_3()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMADDAbc_3: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMADDAbc_3: Not implemented.");
#endif
}

void EECoreInterpreter::VMSUB()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMSUB: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMSUB: Not implemented.");
#endif
}

void EECoreInterpreter::VMSUBi()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMSUBi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMSUBi: Not implemented.");
#endif
}

void EECoreInterpreter::VMSUBq()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMSUBq: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMSUBq: Not implemented.");
#endif
}

void EECoreInterpreter::VMSUBbc()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMSUBbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMSUBbc: Not implemented.");
#endif
}

void EECoreInterpreter::VMSUBbc_0()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMSUBbc_0: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMSUBbc_0: Not implemented.");
#endif
}

void EECoreInterpreter::VMSUBbc_1()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMSUBbc_1: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMSUBbc_1: Not implemented.");
#endif
}

void EECoreInterpreter::VMSUBbc_2()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMSUBbc_2: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMSUBbc_2: Not implemented.");
#endif
}

void EECoreInterpreter::VMSUBbc_3()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMSUBbc_3: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMSUBbc_3: Not implemented.");
#endif
}

void EECoreInterpreter::VMSUBA()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMSUBA: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMSUBA: Not implemented.");
#endif
}

void EECoreInterpreter::VMSUBAi()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMSUBAi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMSUBAi: Not implemented.");
#endif
}

void EECoreInterpreter::VMSUBAq()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMSUBAq: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMSUBAq: Not implemented.");
#endif
}

void EECoreInterpreter::VMSUBAbc()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMSUBAbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMSUBAbc: Not implemented.");
#endif
}

void EECoreInterpreter::VMSUBAbc_0()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMSUBAbc_0: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMSUBAbc_0: Not implemented.");
#endif
}

void EECoreInterpreter::VMSUBAbc_1()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMSUBAbc_1: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMSUBAbc_1: Not implemented.");
#endif
}

void EECoreInterpreter::VMSUBAbc_2()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMSUBAbc_2: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMSUBAbc_2: Not implemented.");
#endif
}

void EECoreInterpreter::VMSUBAbc_3()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMSUBAbc_3: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMSUBAbc_3: Not implemented.");
#endif
}

void EECoreInterpreter::VMAX()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMAX: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMAX: Not implemented.");
#endif
}

void EECoreInterpreter::VMAXi()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMAXi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMAXi: Not implemented.");
#endif
}

void EECoreInterpreter::VMAXbc()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMAXbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMAXbc: Not implemented.");
#endif
}

void EECoreInterpreter::VMAXbc_0()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMAXbc_0: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMAXbc_0: Not implemented.");
#endif
}

void EECoreInterpreter::VMAXbc_1()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMAXbc_1: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMAXbc_1: Not implemented.");
#endif
}

void EECoreInterpreter::VMAXbc_2()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMAXbc_2: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMAXbc_2: Not implemented.");
#endif
}

void EECoreInterpreter::VMAXbc_3()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMAXbc_3: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMAXbc_3: Not implemented.");
#endif
}

void EECoreInterpreter::VMINI()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMINI: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMINI: Not implemented.");
#endif
}

void EECoreInterpreter::VMINIi()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMINIi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMINIi: Not implemented.");
#endif
}

void EECoreInterpreter::VMINIbc()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMINIbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMINIbc: Not implemented.");
#endif
}

void EECoreInterpreter::VMINIbc_0()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMINIbc_0: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMINIbc_0: Not implemented.");
#endif
}

void EECoreInterpreter::VMINIbc_1()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMINIbc_1: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMINIbc_1: Not implemented.");
#endif
}

void EECoreInterpreter::VMINIbc_2()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMINIbc_2: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMINIbc_2: Not implemented.");
#endif
}

void EECoreInterpreter::VMINIbc_3()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMINIbc_3: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMINIbc_3: Not implemented.");
#endif
}

void EECoreInterpreter::VOPMULA()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VOPMULA: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VOPMULA: Not implemented.");
#endif
}

void EECoreInterpreter::VOPMSUB()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VOPMSUB: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VOPMSUB: Not implemented.");
#endif
}

void EECoreInterpreter::VNOP()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VNOP: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VNOP: Not implemented.");
#endif
}

void EECoreInterpreter::VFTOI0()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VFTOI0: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VFTOI0: Not implemented.");
#endif
}

void EECoreInterpreter::VFTOI4()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VFTOI4: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VFTOI4: Not implemented.");
#endif
}

void EECoreInterpreter::VFTOI12()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VFTOI12: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VFTOI12: Not implemented.");
#endif
}

void EECoreInterpreter::VFTOI15()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VFTOI15: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VFTOI15: Not implemented.");
#endif
}

void EECoreInterpreter::VITOF0()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VITOF0: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VITOF0: Not implemented.");
#endif
}

void EECoreInterpreter::VITOF4()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VITOF4: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VITOF4: Not implemented.");
#endif
}

void EECoreInterpreter::VITOF12()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VITOF12: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VITOF12: Not implemented.");
#endif
}

void EECoreInterpreter::VITOF15()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VITOF15: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VITOF15: Not implemented.");
#endif
}

void EECoreInterpreter::VCLIP()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VCLIP: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VCLIP: Not implemented.");
#endif
}

void EECoreInterpreter::VDIV()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VDIV: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VDIV: Not implemented.");
#endif
}

void EECoreInterpreter::VSQRT()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VSQRT: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VSQRT: Not implemented.");
#endif
}

void EECoreInterpreter::VRSQRT()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VRSQRT: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VRSQRT: Not implemented.");
#endif
}

void EECoreInterpreter::VIADD()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VIADD: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VIADD: Not implemented.");
#endif
}

void EECoreInterpreter::VIADDI()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VIADDI: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VIADDI: Not implemented.");
#endif
}

void EECoreInterpreter::VIAND()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VIAND: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VIAND: Not implemented.");
#endif
}

void EECoreInterpreter::VIOR()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VIOR: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VIOR: Not implemented.");
#endif
}

void EECoreInterpreter::VISUB()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VISUB: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VISUB: Not implemented.");
#endif
}

void EECoreInterpreter::VMOVE()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMOVE: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMOVE: Not implemented.");
#endif
}

void EECoreInterpreter::VMFIR()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMFIR: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMFIR: Not implemented.");
#endif
}

void EECoreInterpreter::VMTIR()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMTIR: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMTIR: Not implemented.");
#endif
}

void EECoreInterpreter::VMR32()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VMR32: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VMR32: Not implemented.");
#endif
}

void EECoreInterpreter::VLQD()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VLQD: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VLQD: Not implemented.");
#endif
}

void EECoreInterpreter::VLQI()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VLQI: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VLQI: Not implemented.");
#endif
}

void EECoreInterpreter::VSQD()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VSQD: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VSQD: Not implemented.");
#endif
}

void EECoreInterpreter::VSQI()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VSQI: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VSQI: Not implemented.");
#endif
}

void EECoreInterpreter::VILWR()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VILWR: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VILWR: Not implemented.");
#endif
}

void EECoreInterpreter::VISWR()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VISWR: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VISWR: Not implemented.");
#endif
}

void EECoreInterpreter::VRINIT()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VRINIT: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VRINIT: Not implemented.");
#endif
}

void EECoreInterpreter::VRGET()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VRGET: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VRGET: Not implemented.");
#endif
}

void EECoreInterpreter::VRNEXT()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VRNEXT: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VRNEXT: Not implemented.");
#endif
}

void EECoreInterpreter::VRXOR()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VRXOR: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VRXOR: Not implemented.");
#endif
}

void EECoreInterpreter::VWAITQ()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VWAITQ: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VWAITQ: Not implemented.");
#endif
}

void EECoreInterpreter::VCALLMS()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VCALLMS: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VCALLMS: Not implemented.");
#endif
}

void EECoreInterpreter::VCALLMSR()
{
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) VCALLMSR: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("VCALLMSR: Not implemented.");
#endif
}

