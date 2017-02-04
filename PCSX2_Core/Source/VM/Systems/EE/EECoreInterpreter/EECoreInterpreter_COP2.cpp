#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/FPRegister128_t.h"
#include "Common/Types/Registers/Register128_t.h"
#include "Common/Types/Registers/Register32_t.h"

#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter.h"
#include "VM/Systems/EE/VPU/VUInterpreter/VUInterpreter.h"

#include "Resources/EE/EECore/EECore_t.h"
#include "Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "Resources/EE/VPU/VU/Types/VuUnits_t.h"

void EECoreInterpreter::QMFC2()
{
	// GPR = VU0.VF. Coprocessor unusable exception.
	if (handleCOP2Usable())
        return;

	// Check for the interlock bit.
	if (mInstruction.getVI())
	{
		throw std::runtime_error("COP2 (VU0) interlock bit set, but not implemented");
	}

	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& source1Reg = mVU0->VF[mInstruction.getRRd()];

	destReg->writeDword(EE, 0, source1Reg->readDword(EE, 0));
	destReg->writeDword(EE, 1, source1Reg->readDword(EE, 1));
}

void EECoreInterpreter::QMTC2()
{
	// VU0.VF = GPR. Coprocessor unusable exception.
	if (handleCOP2Usable())
        return;

	// Check for the interlock bit.
	if (mInstruction.getVI())
	{
		throw std::runtime_error("COP2 (VU0) interlock bit set, but not implemented");
	}

	auto& destReg = mVU0->VF[mInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getRRt()];

	destReg->writeDword(EE, 0, source1Reg->readDword(EE, 0));
	destReg->writeDword(EE, 1, source1Reg->readDword(EE, 1));
}

void EECoreInterpreter::CFC2()
{
	if (handleCOP2Usable())
        return;

	// Check for the interlock bit.
	if (mInstruction.getVI())
	{
		throw std::runtime_error("COP2 (VU0) interlock bit set, but not implemented");
	}

	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& source1Reg = mVU0->CCR[mInstruction.getRRd()];

	destReg->writeDword(EE, 0, static_cast<s64>(source1Reg->readWord(EE)));
}

void EECoreInterpreter::CTC2()
{
	if (handleCOP2Usable())
        return;

	// Check for the interlock bit.
	if (mInstruction.getVI())
	{
		throw std::runtime_error("COP2 (VU0) interlock bit set, but not implemented");
	}

	auto& destReg = mVU0->CCR[mInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getRRt()];

	destReg->writeWord(EE, static_cast<u32>(source1Reg->readWord(EE, 0)));
}

void EECoreInterpreter::BC2F()
{
	if (handleCOP2Usable())
        return;

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) BC2F: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("BC2F: Not implemented.");
#endif
}

void EECoreInterpreter::BC2FL()
{
	if (handleCOP2Usable())
        return;

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) BC2FL: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("BC2FL: Not implemented.");
#endif
}

void EECoreInterpreter::BC2T()
{
	if (handleCOP2Usable())
        return;

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) BC2T: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("BC2T: Not implemented.");
#endif
}

void EECoreInterpreter::BC2TL()
{
	if (handleCOP2Usable())
        return;

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) BC2TL: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("BC2TL: Not implemented.");
#endif
}

void EECoreInterpreter::VCALLMS()
{
	if (handleCOP2Usable())
		return;

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) BC2TL: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("BC2TL: Not implemented.");
#endif
}

void EECoreInterpreter::VCALLMSR()
{
	if (handleCOP2Usable())
		return;

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) BC2TL: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("BC2TL: Not implemented.");
#endif
}

void EECoreInterpreter::VABS()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ABS();
}

void EECoreInterpreter::VADD()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADD();
}

void EECoreInterpreter::VADDi()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDi();
}

void EECoreInterpreter::VADDq()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDq();
}

void EECoreInterpreter::VADDbc_0()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDbc_0();
}

void EECoreInterpreter::VADDbc_1()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDbc_1();
}

void EECoreInterpreter::VADDbc_2()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDbc_2();
}

void EECoreInterpreter::VADDbc_3()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDbc_3();
}

void EECoreInterpreter::VADDA()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDA();
}

void EECoreInterpreter::VADDAi()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDAi();
}

void EECoreInterpreter::VADDAq()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDAq();
}

void EECoreInterpreter::VADDAbc_0()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDAbc_0();
}

void EECoreInterpreter::VADDAbc_1()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDAbc_1();
}

void EECoreInterpreter::VADDAbc_2()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDAbc_2();
}

void EECoreInterpreter::VADDAbc_3()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDAbc_3();
}

void EECoreInterpreter::VSUB()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUB();
}

void EECoreInterpreter::VSUBi()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBi();
}

void EECoreInterpreter::VSUBq()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBq();
}

void EECoreInterpreter::VSUBbc_0()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBbc_0();
}

void EECoreInterpreter::VSUBbc_1()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBbc_1();
}

void EECoreInterpreter::VSUBbc_2()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBbc_2();
}

void EECoreInterpreter::VSUBbc_3()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBbc_3();
}

void EECoreInterpreter::VSUBA()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBA();
}

void EECoreInterpreter::VSUBAi()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBAi();
}

void EECoreInterpreter::VSUBAq()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBAq();
}

void EECoreInterpreter::VSUBAbc_0()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBAbc_0();
}

void EECoreInterpreter::VSUBAbc_1()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBAbc_1();
}

void EECoreInterpreter::VSUBAbc_2()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBAbc_2();
}

void EECoreInterpreter::VSUBAbc_3()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBAbc_3();
}

void EECoreInterpreter::VMUL()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MUL();
}

void EECoreInterpreter::VMULi()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULi();
}

void EECoreInterpreter::VMULq()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULq();
}

void EECoreInterpreter::VMULbc_0()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULbc_0();
}

void EECoreInterpreter::VMULbc_1()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULbc_1();
}

void EECoreInterpreter::VMULbc_2()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULbc_2();
}

void EECoreInterpreter::VMULbc_3()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULbc_3();
}

void EECoreInterpreter::VMULA()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULA();
}

void EECoreInterpreter::VMULAi()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULAi();
}

void EECoreInterpreter::VMULAq()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULAq();
}

void EECoreInterpreter::VMULAbc_0()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULAbc_0();
}

void EECoreInterpreter::VMULAbc_1()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULAbc_1();
}

void EECoreInterpreter::VMULAbc_2()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULAbc_2();
}

void EECoreInterpreter::VMULAbc_3()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULAbc_3();
}

void EECoreInterpreter::VMADD()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADD();
}

void EECoreInterpreter::VMADDi()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDi();
}

void EECoreInterpreter::VMADDq()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDq();
}

void EECoreInterpreter::VMADDbc_0()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDbc_0();
}

void EECoreInterpreter::VMADDbc_1()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDbc_1();
}

void EECoreInterpreter::VMADDbc_2()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDbc_2();
}

void EECoreInterpreter::VMADDbc_3()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDbc_3();
}

void EECoreInterpreter::VMADDA()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDA();
}

void EECoreInterpreter::VMADDAi()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDAi();
}

void EECoreInterpreter::VMADDAq()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDAq();
}

void EECoreInterpreter::VMADDAbc_0()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDAbc_0();
}

void EECoreInterpreter::VMADDAbc_1()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDAbc_1();
}

void EECoreInterpreter::VMADDAbc_2()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDAbc_2();
}

void EECoreInterpreter::VMADDAbc_3()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDAbc_3();
}

void EECoreInterpreter::VMSUB()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUB();
}

void EECoreInterpreter::VMSUBi()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBi();
}

void EECoreInterpreter::VMSUBq()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBq();
}

void EECoreInterpreter::VMSUBbc_0()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBbc_0();
}

void EECoreInterpreter::VMSUBbc_1()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBbc_1();
}

void EECoreInterpreter::VMSUBbc_2()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBbc_2();
}

void EECoreInterpreter::VMSUBbc_3()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBbc_3();
}

void EECoreInterpreter::VMSUBA()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBA();
}

void EECoreInterpreter::VMSUBAi()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBAi();
}

void EECoreInterpreter::VMSUBAq()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBAq();
}

void EECoreInterpreter::VMSUBAbc_0()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBAbc_0();
}

void EECoreInterpreter::VMSUBAbc_1()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBAbc_1();
}

void EECoreInterpreter::VMSUBAbc_2()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBAbc_2();
}

void EECoreInterpreter::VMSUBAbc_3()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBAbc_3();
}

void EECoreInterpreter::VMAX()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MAX();
}

void EECoreInterpreter::VMAXi()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MAXi();
}

void EECoreInterpreter::VMAXbc_0()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MAXbc_0();
}

void EECoreInterpreter::VMAXbc_1()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MAXbc_1();
}

void EECoreInterpreter::VMAXbc_2()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MAXbc_2();
}

void EECoreInterpreter::VMAXbc_3()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MAXbc_3();
}

void EECoreInterpreter::VMINI()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MINI();
}

void EECoreInterpreter::VMINIi()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MINIi();
}

void EECoreInterpreter::VMINIbc_0()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MINIbc_0();
}

void EECoreInterpreter::VMINIbc_1()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MINIbc_1();
}

void EECoreInterpreter::VMINIbc_2()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MINIbc_2();
}

void EECoreInterpreter::VMINIbc_3()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MINIbc_3();
}

void EECoreInterpreter::VOPMULA()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->OPMULA();
}

void EECoreInterpreter::VOPMSUB()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->OPMSUB();
}

void EECoreInterpreter::VNOP()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->NOP();
}

void EECoreInterpreter::VFTOI0()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->FTOI0();
}

void EECoreInterpreter::VFTOI4()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->FTOI4();
}

void EECoreInterpreter::VFTOI12()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->FTOI12();
}

void EECoreInterpreter::VFTOI15()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->FTOI15();
}

void EECoreInterpreter::VITOF0()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ITOF0();
}

void EECoreInterpreter::VITOF4()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ITOF4();
}

void EECoreInterpreter::VITOF12()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ITOF12();
}

void EECoreInterpreter::VITOF15()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ITOF15();
}

void EECoreInterpreter::VCLIP()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->CLIP();
}

void EECoreInterpreter::VDIV()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->DIV();
}

void EECoreInterpreter::VSQRT()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SQRT();
}

void EECoreInterpreter::VRSQRT()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->RSQRT();
}

void EECoreInterpreter::VIADD()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->IADD();
}

void EECoreInterpreter::VIADDI()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->IADDI();
}

void EECoreInterpreter::VIAND()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->IAND();
}

void EECoreInterpreter::VIOR()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->IOR();
}

void EECoreInterpreter::VISUB()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ISUB();
}

void EECoreInterpreter::VMOVE()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MOVE();
}

void EECoreInterpreter::VMFIR()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MFIR();
}

void EECoreInterpreter::VMTIR()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MTIR();
}

void EECoreInterpreter::VMR32()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MR32();
}

void EECoreInterpreter::VLQD()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->LQD();
}

void EECoreInterpreter::VLQI()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->LQI();
}

void EECoreInterpreter::VSQD()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SQD();
}

void EECoreInterpreter::VSQI()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SQI();
}

void EECoreInterpreter::VILWR()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ILWR();
}

void EECoreInterpreter::VISWR()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->mInstruction.setValue(mInstruction.getInstructionValue());
	mVU0Interpreter->ISWR();
}

void EECoreInterpreter::VRINIT()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->RINIT();
}

void EECoreInterpreter::VRGET()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->RGET();
}

void EECoreInterpreter::VRNEXT()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->RNEXT();
}

void EECoreInterpreter::VRXOR()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->RXOR();
}

void EECoreInterpreter::VWAITQ()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->WAITQ();
}

