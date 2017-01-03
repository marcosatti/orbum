#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Context_t.h"
#include "Common/Types/Registers/FPRegister128_t.h"
#include "Common/Types/Registers/Register128_t.h"
#include "Common/Types/Registers/Register32_t.h"

#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreInterpreter.h"
#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreMMUHandler/EECoreMMUHandler.h"
#include "VM/ExecutionCore/Interpreter/EE/VPU/VUInterpreter/VUInterpreter.h"

#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreExceptions_t.h"
#include "PS2Resources/EE/VPU/VPU_t.h"
#include "PS2Resources/EE/VPU/VU/VU_t.h"
#include "PS2Resources/EE/VPU/VU/Types/VuUnits_t.h"

void EECoreInterpreter::QMFC2()
{
	// GPR = VU0.VF. Coprocessor unusable exception.
	if (!checkCOP2Usable())
        return;

	// Check for the interlock bit.
	if (mInstruction.getVI())
	{
		throw std::runtime_error("COP2 (VU0) interlock bit set, but not implemented");
	}

	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& source1Reg = getResources()->EE->VPU->VU->VU0->VF[mInstruction.getRRd()];

	destReg->writeDword(Context_t::EE, 0, source1Reg->readDword(Context_t::EE, 0));
	destReg->writeDword(Context_t::EE, 1, source1Reg->readDword(Context_t::EE, 1));
}

void EECoreInterpreter::QMTC2()
{
	// VU0.VF = GPR. Coprocessor unusable exception.
	if (!checkCOP2Usable())
        return;

	// Check for the interlock bit.
	if (mInstruction.getVI())
	{
		throw std::runtime_error("COP2 (VU0) interlock bit set, but not implemented");
	}

	auto& destReg = getResources()->EE->VPU->VU->VU0->VF[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	destReg->writeDword(Context_t::EE, 0, source1Reg->readDword(Context_t::EE, 0));
	destReg->writeDword(Context_t::EE, 1, source1Reg->readDword(Context_t::EE, 1));
}

void EECoreInterpreter::LQC2()
{
	// VU0.VF = GPR. Coprocessor unusable exception.
	if (!checkCOP2Usable())
        return;

	auto& destReg = getResources()->EE->VPU->VU->VU0->VF[mInstruction.getIRt()];
	auto& sourceReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	const s16 imm = mInstruction.getIImmS();

	u32 PS2VirtualAddress = (sourceReg->readWord(Context_t::EE, 0) + imm) & (~static_cast<u32>(0xF)); // Strip the last 4 bits, as the access must be aligned (the documentation says to do this).
	u64 value;
	// TODO: Im not sure if this is correct for big-endian.

	value = mMMUHandler->readDword(PS2VirtualAddress);
	// Check for MMU error (1).
	if (mMMUHandler->hasExceptionOccurred())
	{
		auto& Exceptions = getResources()->EE->EECore->Exceptions;
		Exceptions->setException(mMMUHandler->getExceptionInfo());
		return; // Return early, dont bother trying to load the second dword.
	}
	else
		destReg->writeDword(Context_t::EE, 0, value); // Get first 8 bytes (bytes 0 -> 7).

	value = mMMUHandler->readDword(PS2VirtualAddress + Constants::NUMBER_BYTES_IN_DWORD);
	// Check for MMU error (2).
	if (!checkNoMMUError())
        return;
	else
		destReg->writeDword(Context_t::EE, 1, value); // Get second 8 bytes (bytes 8 -> 15).
}

void EECoreInterpreter::SQC2()
{
	// VU0.VF = GPR. Coprocessor unusable exception.
	if (!checkCOP2Usable())
        return;

	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	auto& source2Reg = getResources()->EE->VPU->VU->VU0->VF[mInstruction.getIRt()];
	const s16 imm = mInstruction.getIImmS();

	u32 PS2VirtualAddress = source1Reg->readWord(Context_t::EE, 0) + imm;

	mMMUHandler->writeDword(PS2VirtualAddress, source2Reg->readDword(Context_t::EE, 0));
	// Check for MMU error.
	if (!checkNoMMUError())
        return;

	mMMUHandler->writeDword(PS2VirtualAddress + Constants::NUMBER_BYTES_IN_DWORD, source2Reg->readDword(Context_t::EE, 1));
	// Check for MMU error.
	if (!checkNoMMUError())
        return;
}

void EECoreInterpreter::CFC2()
{
	if (!checkCOP2Usable())
        return;

	// Check for the interlock bit.
	if (mInstruction.getVI())
	{
		throw std::runtime_error("COP2 (VU0) interlock bit set, but not implemented");
	}

	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& source1Reg = getResources()->EE->VPU->VU->VU0->CCR[mInstruction.getRRd()];

	destReg->writeDword(Context_t::EE, 0, static_cast<s64>(source1Reg->readWord(Context_t::EE)));
}

void EECoreInterpreter::CTC2()
{
	if (!checkCOP2Usable())
        return;

	// Check for the interlock bit.
	if (mInstruction.getVI())
	{
		throw std::runtime_error("COP2 (VU0) interlock bit set, but not implemented");
	}

	auto& destReg = getResources()->EE->VPU->VU->VU0->CCR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	destReg->writeWord(Context_t::EE, static_cast<u32>(source1Reg->readWord(Context_t::EE, 0)));
}

void EECoreInterpreter::BC2F()
{
	if (!checkCOP2Usable())
        return;

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) BC2F: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("BC2F: Not implemented.");
#endif
}

void EECoreInterpreter::BC2FL()
{
	if (!checkCOP2Usable())
        return;

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) BC2FL: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("BC2FL: Not implemented.");
#endif
}

void EECoreInterpreter::BC2T()
{
	if (!checkCOP2Usable())
        return;

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) BC2T: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("BC2T: Not implemented.");
#endif
}

void EECoreInterpreter::BC2TL()
{
	if (!checkCOP2Usable())
        return;

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) BC2TL: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("BC2TL: Not implemented.");
#endif
}

void EECoreInterpreter::VCALLMS()
{
	if (!checkCOP2Usable())
		return;

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) BC2TL: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("BC2TL: Not implemented.");
#endif
}

void EECoreInterpreter::VCALLMSR()
{
	if (!checkCOP2Usable())
		return;

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) BC2TL: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("BC2TL: Not implemented.");
#endif
}

void EECoreInterpreter::VABS()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ABS();
}

void EECoreInterpreter::VADD()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADD();
}

void EECoreInterpreter::VADDi()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDi();
}

void EECoreInterpreter::VADDq()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDq();
}

void EECoreInterpreter::VADDbc_0()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDbc_0();
}

void EECoreInterpreter::VADDbc_1()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDbc_1();
}

void EECoreInterpreter::VADDbc_2()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDbc_2();
}

void EECoreInterpreter::VADDbc_3()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDbc_3();
}

void EECoreInterpreter::VADDA()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDA();
}

void EECoreInterpreter::VADDAi()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDAi();
}

void EECoreInterpreter::VADDAq()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDAq();
}

void EECoreInterpreter::VADDAbc_0()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDAbc_0();
}

void EECoreInterpreter::VADDAbc_1()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDAbc_1();
}

void EECoreInterpreter::VADDAbc_2()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDAbc_2();
}

void EECoreInterpreter::VADDAbc_3()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDAbc_3();
}

void EECoreInterpreter::VSUB()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUB();
}

void EECoreInterpreter::VSUBi()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBi();
}

void EECoreInterpreter::VSUBq()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBq();
}

void EECoreInterpreter::VSUBbc_0()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBbc_0();
}

void EECoreInterpreter::VSUBbc_1()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBbc_1();
}

void EECoreInterpreter::VSUBbc_2()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBbc_2();
}

void EECoreInterpreter::VSUBbc_3()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBbc_3();
}

void EECoreInterpreter::VSUBA()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBA();
}

void EECoreInterpreter::VSUBAi()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBAi();
}

void EECoreInterpreter::VSUBAq()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBAq();
}

void EECoreInterpreter::VSUBAbc_0()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBAbc_0();
}

void EECoreInterpreter::VSUBAbc_1()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBAbc_1();
}

void EECoreInterpreter::VSUBAbc_2()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBAbc_2();
}

void EECoreInterpreter::VSUBAbc_3()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBAbc_3();
}

void EECoreInterpreter::VMUL()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MUL();
}

void EECoreInterpreter::VMULi()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULi();
}

void EECoreInterpreter::VMULq()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULq();
}

void EECoreInterpreter::VMULbc_0()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULbc_0();
}

void EECoreInterpreter::VMULbc_1()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULbc_1();
}

void EECoreInterpreter::VMULbc_2()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULbc_2();
}

void EECoreInterpreter::VMULbc_3()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULbc_3();
}

void EECoreInterpreter::VMULA()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULA();
}

void EECoreInterpreter::VMULAi()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULAi();
}

void EECoreInterpreter::VMULAq()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULAq();
}

void EECoreInterpreter::VMULAbc_0()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULAbc_0();
}

void EECoreInterpreter::VMULAbc_1()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULAbc_1();
}

void EECoreInterpreter::VMULAbc_2()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULAbc_2();
}

void EECoreInterpreter::VMULAbc_3()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULAbc_3();
}

void EECoreInterpreter::VMADD()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADD();
}

void EECoreInterpreter::VMADDi()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDi();
}

void EECoreInterpreter::VMADDq()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDq();
}

void EECoreInterpreter::VMADDbc_0()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDbc_0();
}

void EECoreInterpreter::VMADDbc_1()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDbc_1();
}

void EECoreInterpreter::VMADDbc_2()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDbc_2();
}

void EECoreInterpreter::VMADDbc_3()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDbc_3();
}

void EECoreInterpreter::VMADDA()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDA();
}

void EECoreInterpreter::VMADDAi()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDAi();
}

void EECoreInterpreter::VMADDAq()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDAq();
}

void EECoreInterpreter::VMADDAbc_0()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDAbc_0();
}

void EECoreInterpreter::VMADDAbc_1()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDAbc_1();
}

void EECoreInterpreter::VMADDAbc_2()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDAbc_2();
}

void EECoreInterpreter::VMADDAbc_3()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDAbc_3();
}

void EECoreInterpreter::VMSUB()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUB();
}

void EECoreInterpreter::VMSUBi()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBi();
}

void EECoreInterpreter::VMSUBq()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBq();
}

void EECoreInterpreter::VMSUBbc_0()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBbc_0();
}

void EECoreInterpreter::VMSUBbc_1()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBbc_1();
}

void EECoreInterpreter::VMSUBbc_2()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBbc_2();
}

void EECoreInterpreter::VMSUBbc_3()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBbc_3();
}

void EECoreInterpreter::VMSUBA()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBA();
}

void EECoreInterpreter::VMSUBAi()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBAi();
}

void EECoreInterpreter::VMSUBAq()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBAq();
}

void EECoreInterpreter::VMSUBAbc_0()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBAbc_0();
}

void EECoreInterpreter::VMSUBAbc_1()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBAbc_1();
}

void EECoreInterpreter::VMSUBAbc_2()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBAbc_2();
}

void EECoreInterpreter::VMSUBAbc_3()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBAbc_3();
}

void EECoreInterpreter::VMAX()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MAX();
}

void EECoreInterpreter::VMAXi()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MAXi();
}

void EECoreInterpreter::VMAXbc_0()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MAXbc_0();
}

void EECoreInterpreter::VMAXbc_1()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MAXbc_1();
}

void EECoreInterpreter::VMAXbc_2()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MAXbc_2();
}

void EECoreInterpreter::VMAXbc_3()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MAXbc_3();
}

void EECoreInterpreter::VMINI()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MINI();
}

void EECoreInterpreter::VMINIi()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MINIi();
}

void EECoreInterpreter::VMINIbc_0()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MINIbc_0();
}

void EECoreInterpreter::VMINIbc_1()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MINIbc_1();
}

void EECoreInterpreter::VMINIbc_2()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MINIbc_2();
}

void EECoreInterpreter::VMINIbc_3()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MINIbc_3();
}

void EECoreInterpreter::VOPMULA()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->OPMULA();
}

void EECoreInterpreter::VOPMSUB()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->OPMSUB();
}

void EECoreInterpreter::VNOP()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->NOP();
}

void EECoreInterpreter::VFTOI0()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->FTOI0();
}

void EECoreInterpreter::VFTOI4()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->FTOI4();
}

void EECoreInterpreter::VFTOI12()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->FTOI12();
}

void EECoreInterpreter::VFTOI15()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->FTOI15();
}

void EECoreInterpreter::VITOF0()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ITOF0();
}

void EECoreInterpreter::VITOF4()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ITOF4();
}

void EECoreInterpreter::VITOF12()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ITOF12();
}

void EECoreInterpreter::VITOF15()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ITOF15();
}

void EECoreInterpreter::VCLIP()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->CLIP();
}

void EECoreInterpreter::VDIV()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->DIV();
}

void EECoreInterpreter::VSQRT()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SQRT();
}

void EECoreInterpreter::VRSQRT()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->RSQRT();
}

void EECoreInterpreter::VIADD()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->IADD();
}

void EECoreInterpreter::VIADDI()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->IADDI();
}

void EECoreInterpreter::VIAND()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->IAND();
}

void EECoreInterpreter::VIOR()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->IOR();
}

void EECoreInterpreter::VISUB()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ISUB();
}

void EECoreInterpreter::VMOVE()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MOVE();
}

void EECoreInterpreter::VMFIR()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MFIR();
}

void EECoreInterpreter::VMTIR()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MTIR();
}

void EECoreInterpreter::VMR32()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MR32();
}

void EECoreInterpreter::VLQD()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->LQD();
}

void EECoreInterpreter::VLQI()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->LQI();
}

void EECoreInterpreter::VSQD()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SQD();
}

void EECoreInterpreter::VSQI()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SQI();
}

void EECoreInterpreter::VILWR()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ILWR();
}

void EECoreInterpreter::VISWR()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->mInstruction.setValue(mInstruction.getInstructionValue());
	mVU0Interpreter->ISWR();
}

void EECoreInterpreter::VRINIT()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->RINIT();
}

void EECoreInterpreter::VRGET()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->RGET();
}

void EECoreInterpreter::VRNEXT()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->RNEXT();
}

void EECoreInterpreter::VRXOR()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->RXOR();
}

void EECoreInterpreter::VWAITQ()
{
	if (!checkCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->WAITQ();
}
