#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/FPRegister128_t.h"
#include "Common/Types/Registers/Register128_t.h"
#include "Common/Types/Registers/Register32_t.h"

#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter_s.h"
#include "VM/Systems/EE/VPU/VUInterpreter/VUInterpreter_s.h"

#include "Resources/EE/EECore/EECore_t.h"
#include "Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "Resources/EE/VPU/VU/Types/VUCores_t.h"

void EECoreInterpreter_s::QMFC2()
{
	// GPR = VU0.VF. Coprocessor unusable exception.
	if (handleCOP2Usable())
        return;

	// Check for the interlock bit.
	if (mEECoreInstruction.getVI())
	{
		throw std::runtime_error("COP2 (VU0) interlock bit set, but not implemented");
	}

	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& source1Reg = mVU0->VF[mEECoreInstruction.getRRd()];

	destReg->writeDword(getContext(), 0, source1Reg->readDword(getContext(), 0));
	destReg->writeDword(getContext(), 1, source1Reg->readDword(getContext(), 1));
}

void EECoreInterpreter_s::QMTC2()
{
	// VU0.VF = GPR. Coprocessor unusable exception.
	if (handleCOP2Usable())
        return;

	// Check for the interlock bit.
	if (mEECoreInstruction.getVI())
	{
		throw std::runtime_error("COP2 (VU0) interlock bit set, but not implemented");
	}

	auto& destReg = mVU0->VF[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];

	destReg->writeDword(getContext(), 0, source1Reg->readDword(getContext(), 0));
	destReg->writeDword(getContext(), 1, source1Reg->readDword(getContext(), 1));
}

void EECoreInterpreter_s::CFC2()
{
	if (handleCOP2Usable())
        return;

	// Check for the interlock bit.
	if (mEECoreInstruction.getVI())
	{
		throw std::runtime_error("COP2 (VU0) interlock bit set, but not implemented");
	}

	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& source1Reg = mVU0->CCR[mEECoreInstruction.getRRd()];

	destReg->writeDword(getContext(), 0, static_cast<s64>(source1Reg->readWord(getContext())));
}

void EECoreInterpreter_s::CTC2()
{
	if (handleCOP2Usable())
        return;

	// Check for the interlock bit.
	if (mEECoreInstruction.getVI())
	{
		throw std::runtime_error("COP2 (VU0) interlock bit set, but not implemented");
	}

	auto& destReg = mVU0->CCR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];

	destReg->writeWord(getContext(), static_cast<u32>(source1Reg->readWord(getContext(), 0)));
}

void EECoreInterpreter_s::BC2F()
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

void EECoreInterpreter_s::BC2FL()
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

void EECoreInterpreter_s::BC2T()
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

void EECoreInterpreter_s::BC2TL()
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

void EECoreInterpreter_s::VCALLMS()
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

void EECoreInterpreter_s::VCALLMSR()
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

void EECoreInterpreter_s::VABS()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ABS();
}

void EECoreInterpreter_s::VADD()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADD();
}

void EECoreInterpreter_s::VADDi()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDi();
}

void EECoreInterpreter_s::VADDq()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDq();
}

void EECoreInterpreter_s::VADDbc_0()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDbc_0();
}

void EECoreInterpreter_s::VADDbc_1()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDbc_1();
}

void EECoreInterpreter_s::VADDbc_2()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDbc_2();
}

void EECoreInterpreter_s::VADDbc_3()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDbc_3();
}

void EECoreInterpreter_s::VADDA()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDA();
}

void EECoreInterpreter_s::VADDAi()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDAi();
}

void EECoreInterpreter_s::VADDAq()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDAq();
}

void EECoreInterpreter_s::VADDAbc_0()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDAbc_0();
}

void EECoreInterpreter_s::VADDAbc_1()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDAbc_1();
}

void EECoreInterpreter_s::VADDAbc_2()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDAbc_2();
}

void EECoreInterpreter_s::VADDAbc_3()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ADDAbc_3();
}

void EECoreInterpreter_s::VSUB()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUB();
}

void EECoreInterpreter_s::VSUBi()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBi();
}

void EECoreInterpreter_s::VSUBq()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBq();
}

void EECoreInterpreter_s::VSUBbc_0()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBbc_0();
}

void EECoreInterpreter_s::VSUBbc_1()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBbc_1();
}

void EECoreInterpreter_s::VSUBbc_2()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBbc_2();
}

void EECoreInterpreter_s::VSUBbc_3()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBbc_3();
}

void EECoreInterpreter_s::VSUBA()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBA();
}

void EECoreInterpreter_s::VSUBAi()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBAi();
}

void EECoreInterpreter_s::VSUBAq()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBAq();
}

void EECoreInterpreter_s::VSUBAbc_0()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBAbc_0();
}

void EECoreInterpreter_s::VSUBAbc_1()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBAbc_1();
}

void EECoreInterpreter_s::VSUBAbc_2()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBAbc_2();
}

void EECoreInterpreter_s::VSUBAbc_3()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SUBAbc_3();
}

void EECoreInterpreter_s::VMUL()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MUL();
}

void EECoreInterpreter_s::VMULi()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULi();
}

void EECoreInterpreter_s::VMULq()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULq();
}

void EECoreInterpreter_s::VMULbc_0()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULbc_0();
}

void EECoreInterpreter_s::VMULbc_1()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULbc_1();
}

void EECoreInterpreter_s::VMULbc_2()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULbc_2();
}

void EECoreInterpreter_s::VMULbc_3()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULbc_3();
}

void EECoreInterpreter_s::VMULA()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULA();
}

void EECoreInterpreter_s::VMULAi()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULAi();
}

void EECoreInterpreter_s::VMULAq()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULAq();
}

void EECoreInterpreter_s::VMULAbc_0()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULAbc_0();
}

void EECoreInterpreter_s::VMULAbc_1()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULAbc_1();
}

void EECoreInterpreter_s::VMULAbc_2()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULAbc_2();
}

void EECoreInterpreter_s::VMULAbc_3()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MULAbc_3();
}

void EECoreInterpreter_s::VMADD()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADD();
}

void EECoreInterpreter_s::VMADDi()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDi();
}

void EECoreInterpreter_s::VMADDq()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDq();
}

void EECoreInterpreter_s::VMADDbc_0()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDbc_0();
}

void EECoreInterpreter_s::VMADDbc_1()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDbc_1();
}

void EECoreInterpreter_s::VMADDbc_2()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDbc_2();
}

void EECoreInterpreter_s::VMADDbc_3()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDbc_3();
}

void EECoreInterpreter_s::VMADDA()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDA();
}

void EECoreInterpreter_s::VMADDAi()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDAi();
}

void EECoreInterpreter_s::VMADDAq()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDAq();
}

void EECoreInterpreter_s::VMADDAbc_0()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDAbc_0();
}

void EECoreInterpreter_s::VMADDAbc_1()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDAbc_1();
}

void EECoreInterpreter_s::VMADDAbc_2()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDAbc_2();
}

void EECoreInterpreter_s::VMADDAbc_3()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MADDAbc_3();
}

void EECoreInterpreter_s::VMSUB()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUB();
}

void EECoreInterpreter_s::VMSUBi()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBi();
}

void EECoreInterpreter_s::VMSUBq()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBq();
}

void EECoreInterpreter_s::VMSUBbc_0()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBbc_0();
}

void EECoreInterpreter_s::VMSUBbc_1()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBbc_1();
}

void EECoreInterpreter_s::VMSUBbc_2()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBbc_2();
}

void EECoreInterpreter_s::VMSUBbc_3()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBbc_3();
}

void EECoreInterpreter_s::VMSUBA()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBA();
}

void EECoreInterpreter_s::VMSUBAi()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBAi();
}

void EECoreInterpreter_s::VMSUBAq()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBAq();
}

void EECoreInterpreter_s::VMSUBAbc_0()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBAbc_0();
}

void EECoreInterpreter_s::VMSUBAbc_1()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBAbc_1();
}

void EECoreInterpreter_s::VMSUBAbc_2()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBAbc_2();
}

void EECoreInterpreter_s::VMSUBAbc_3()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MSUBAbc_3();
}

void EECoreInterpreter_s::VMAX()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MAX();
}

void EECoreInterpreter_s::VMAXi()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MAXi();
}

void EECoreInterpreter_s::VMAXbc_0()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MAXbc_0();
}

void EECoreInterpreter_s::VMAXbc_1()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MAXbc_1();
}

void EECoreInterpreter_s::VMAXbc_2()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MAXbc_2();
}

void EECoreInterpreter_s::VMAXbc_3()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MAXbc_3();
}

void EECoreInterpreter_s::VMINI()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MINI();
}

void EECoreInterpreter_s::VMINIi()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MINIi();
}

void EECoreInterpreter_s::VMINIbc_0()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MINIbc_0();
}

void EECoreInterpreter_s::VMINIbc_1()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MINIbc_1();
}

void EECoreInterpreter_s::VMINIbc_2()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MINIbc_2();
}

void EECoreInterpreter_s::VMINIbc_3()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MINIbc_3();
}

void EECoreInterpreter_s::VOPMULA()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->OPMULA();
}

void EECoreInterpreter_s::VOPMSUB()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->OPMSUB();
}

void EECoreInterpreter_s::VNOP()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->NOP();
}

void EECoreInterpreter_s::VFTOI0()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->FTOI0();
}

void EECoreInterpreter_s::VFTOI4()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->FTOI4();
}

void EECoreInterpreter_s::VFTOI12()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->FTOI12();
}

void EECoreInterpreter_s::VFTOI15()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->FTOI15();
}

void EECoreInterpreter_s::VITOF0()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ITOF0();
}

void EECoreInterpreter_s::VITOF4()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ITOF4();
}

void EECoreInterpreter_s::VITOF12()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ITOF12();
}

void EECoreInterpreter_s::VITOF15()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ITOF15();
}

void EECoreInterpreter_s::VCLIP()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->CLIP();
}

void EECoreInterpreter_s::VDIV()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->DIV();
}

void EECoreInterpreter_s::VSQRT()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SQRT();
}

void EECoreInterpreter_s::VRSQRT()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->RSQRT();
}

void EECoreInterpreter_s::VIADD()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->IADD();
}

void EECoreInterpreter_s::VIADDI()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->IADDI();
}

void EECoreInterpreter_s::VIAND()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->IAND();
}

void EECoreInterpreter_s::VIOR()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->IOR();
}

void EECoreInterpreter_s::VISUB()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ISUB();
}

void EECoreInterpreter_s::VMOVE()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MOVE();
}

void EECoreInterpreter_s::VMFIR()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MFIR();
}

void EECoreInterpreter_s::VMTIR()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MTIR();
}

void EECoreInterpreter_s::VMR32()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->MR32();
}

void EECoreInterpreter_s::VLQD()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->LQD();
}

void EECoreInterpreter_s::VLQI()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->LQI();
}

void EECoreInterpreter_s::VSQD()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SQD();
}

void EECoreInterpreter_s::VSQI()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->SQI();
}

void EECoreInterpreter_s::VILWR()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->ILWR();
}

void EECoreInterpreter_s::VISWR()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->mVUInstruction = VUInstruction_t(mEECoreInstruction.getValue());
	mVU0Interpreter->ISWR();
}

void EECoreInterpreter_s::VRINIT()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->RINIT();
}

void EECoreInterpreter_s::VRGET()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->RGET();
}

void EECoreInterpreter_s::VRNEXT()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->RNEXT();
}

void EECoreInterpreter_s::VRXOR()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->RXOR();
}

void EECoreInterpreter_s::VWAITQ()
{
	if (handleCOP2Usable())
        return;

	// Delegate to the VU0 system.
	mVU0Interpreter->WAITQ();
}

