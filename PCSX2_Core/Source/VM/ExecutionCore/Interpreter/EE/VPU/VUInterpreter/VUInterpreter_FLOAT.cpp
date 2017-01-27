#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Context_t.h"
#include "Common/Types/Registers/FPRegister128_t.h"
#include "Common/Util/FPUUtil/FPUUtil.h"

#include "VM/ExecutionCore/Interpreter/EE/VPU/VUInterpreter/VUInterpreter.h"

#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/VPU/VPU_t.h"
#include "PS2Resources/EE/VPU/VU/VU_t.h"
#include "PS2Resources/EE/VPU/VU/Types/VuUnits_t.h"
#include "PS2Resources/EE/VPU/VU/Types/VuUnitRegisters_t.h"

void VUInterpreter::ABS()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) ABS: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("ABS: Not implemented.");
#endif
}

void VUInterpreter::ADD()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) ADD: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("ADD: Not implemented.");
#endif
}

void VUInterpreter::ADDi()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) ADDi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("ADDi: Not implemented.");
#endif
}

void VUInterpreter::ADDq()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) ADDq: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("ADDq: Not implemented.");
#endif
}

void VUInterpreter::ADDbc(const u8 & idx)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) ADDbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("ADDbc: Not implemented.");
#endif
}

void VUInterpreter::ADDbc_0()
{
	// Call base function.
	ADDbc(0);
}

void VUInterpreter::ADDbc_1()
{
	// Call base function.
	ADDbc(1);
}

void VUInterpreter::ADDbc_2()
{
	// Call base function.
	ADDbc(2);
}

void VUInterpreter::ADDbc_3()
{
	// Call base function.
	ADDbc(3);
}

void VUInterpreter::ADDA()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) ADDA: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("ADDA: Not implemented.");
#endif
}

void VUInterpreter::ADDAi()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) ADDAi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("ADDAi: Not implemented.");
#endif
}

void VUInterpreter::ADDAq()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) ADDAq: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("ADDAq: Not implemented.");
#endif
}

void VUInterpreter::ADDAbc(const u8 & idx)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) ADDAbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("ADDAbc: Not implemented.");
#endif
}

void VUInterpreter::ADDAbc_0()
{
	// Call base function.
	ADDAbc(0);
}

void VUInterpreter::ADDAbc_1()
{
	// Call base function.
	ADDAbc(1);
}

void VUInterpreter::ADDAbc_2()
{
	// Call base function.
	ADDAbc(2);
}

void VUInterpreter::ADDAbc_3()
{
	// Call base function.
	ADDAbc(3);
}

void VUInterpreter::SUB()
{
	// Fd = Fs - Ft.
	auto& destReg = getResources()->EE->VPU->VU->VU_UNITS[mVUUnitIndex]->VF[mInstruction.getFd()];
	auto& source1Reg = getResources()->EE->VPU->VU->VU_UNITS[mVUUnitIndex]->VF[mInstruction.getFs()]; 
	auto& source2Reg = getResources()->EE->VPU->VU->VU_UNITS[mVUUnitIndex]->VF[mInstruction.getFt()]; 
	auto& MAC = getResources()->EE->VPU->VU->VU_UNITS[mVUUnitIndex]->MAC;
	auto& Status = getResources()->EE->VPU->VU->VU_UNITS[mVUUnitIndex]->Status;

	Status->clearFlags();

	FPUFlags_t flags;
	for (auto i = 0; i < 4; i++)
	{
		if (mInstruction.testDestField(i))
		{
			f32 result = FPUUtil::formatIEEEToPS2Float(source1Reg->readFloat(EE, i) - source2Reg->readFloat(EE, i), flags);
			destReg->writeFloat(EE, i, result);
			MAC->updateVectorField(i, flags);
		}
		else
			MAC->clearVectorField(i);
	}
}

void VUInterpreter::SUBi()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) SUBi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("SUBi: Not implemented.");
#endif
}

void VUInterpreter::SUBq()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) SUBq: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("SUBq: Not implemented.");
#endif
}

void VUInterpreter::SUBbc(const u8 & idx)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) SUBbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("SUBbc: Not implemented.");
#endif
}

void VUInterpreter::SUBbc_0()
{
	// Call base function.
	SUBbc(0);
}

void VUInterpreter::SUBbc_1()
{
	// Call base function.
	SUBbc(1);
}

void VUInterpreter::SUBbc_2()
{
	// Call base function.
	SUBbc(2);
}

void VUInterpreter::SUBbc_3()
{
	// Call base function.
	SUBbc(3);
}

void VUInterpreter::SUBA()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) SUBA: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("SUBA: Not implemented.");
#endif
}

void VUInterpreter::SUBAi()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) SUBAi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("SUBAi: Not implemented.");
#endif
}

void VUInterpreter::SUBAq()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) SUBAq: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("SUBAq: Not implemented.");
#endif
}

void VUInterpreter::SUBAbc(const u8 & idx)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) SUBAbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("SUBAbc: Not implemented.");
#endif
}

void VUInterpreter::SUBAbc_0()
{
	// Call base function.
	SUBAbc(0);
}

void VUInterpreter::SUBAbc_1()
{
	// Call base function.
	SUBAbc(1);
}

void VUInterpreter::SUBAbc_2()
{
	// Call base function.
	SUBAbc(2);
}

void VUInterpreter::SUBAbc_3()
{
	// Call base function.
	SUBAbc(3);
}

void VUInterpreter::MUL()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) MUL: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MUL: Not implemented.");
#endif
}

void VUInterpreter::MULi()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) MULi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MULi: Not implemented.");
#endif
}

void VUInterpreter::MULq()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) MULq: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MULq: Not implemented.");
#endif
}

void VUInterpreter::MULbc(const u8 & idx)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) MULbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MULbc: Not implemented.");
#endif
}

void VUInterpreter::MULbc_0()
{
	// Call base function.
	MULbc(0);
}

void VUInterpreter::MULbc_1()
{
	// Call base function.
	MULbc(1);
}

void VUInterpreter::MULbc_2()
{
	// Call base function.
	MULbc(2);
}

void VUInterpreter::MULbc_3()
{
	// Call base function.
	MULbc(3);
}

void VUInterpreter::MULA()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) MULA: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MULA: Not implemented.");
#endif
}

void VUInterpreter::MULAi()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) MULAi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MULAi: Not implemented.");
#endif
}

void VUInterpreter::MULAq()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) MULAq: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MULAq: Not implemented.");
#endif
}

void VUInterpreter::MULAbc(const u8 & idx)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) MULAbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MULAbc: Not implemented.");
#endif
}

void VUInterpreter::MULAbc_0()
{
	// Call base function.
	MULAbc(0);
}

void VUInterpreter::MULAbc_1()
{
	// Call base function.
	MULAbc(1);
}

void VUInterpreter::MULAbc_2()
{
	// Call base function.
	MULAbc(2);
}

void VUInterpreter::MULAbc_3()
{
	// Call base function.
	MULAbc(3);
}

void VUInterpreter::MADD()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) MADD: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MADD: Not implemented.");
#endif
}

void VUInterpreter::MADDi()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) MADDi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MADDi: Not implemented.");
#endif
}

void VUInterpreter::MADDq()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) MADDq: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MADDq: Not implemented.");
#endif
}

void VUInterpreter::MADDbc(const u8 & idx)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) MADDbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MADDbc: Not implemented.");
#endif
}

void VUInterpreter::MADDbc_0()
{
	// Call base function.
	MADDbc(0);
}

void VUInterpreter::MADDbc_1()
{
	// Call base function.
	MADDbc(1);
}

void VUInterpreter::MADDbc_2()
{
	// Call base function.
	MADDbc(2);
}

void VUInterpreter::MADDbc_3()
{
	// Call base function.
	MADDbc(3);
}

void VUInterpreter::MADDA()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) MADDA: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MADDA: Not implemented.");
#endif
}

void VUInterpreter::MADDAi()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) MADDAi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MADDAi: Not implemented.");
#endif
}

void VUInterpreter::MADDAq()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) MADDAq: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MADDAq: Not implemented.");
#endif
}

void VUInterpreter::MADDAbc(const u8 & idx)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) MADDAbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MADDAbc: Not implemented.");
#endif
}

void VUInterpreter::MADDAbc_0()
{
	// Call base function.
	MADDAbc(0);
}

void VUInterpreter::MADDAbc_1()
{
	// Call base function.
	MADDAbc(1);
}

void VUInterpreter::MADDAbc_2()
{
	// Call base function.
	MADDAbc(2);
}

void VUInterpreter::MADDAbc_3()
{
	// Call base function.
	MADDAbc(3);
}

void VUInterpreter::MSUB()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) MSUB: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MSUB: Not implemented.");
#endif
}

void VUInterpreter::MSUBi()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) MSUBi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MSUBi: Not implemented.");
#endif
}

void VUInterpreter::MSUBq()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) MSUBq: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MSUBq: Not implemented.");
#endif
}

void VUInterpreter::MSUBbc(const u8 & idx)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) MSUBbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MSUBbc: Not implemented.");
#endif
}

void VUInterpreter::MSUBbc_0()
{
	// Call base function.
	MSUBbc(0);
}

void VUInterpreter::MSUBbc_1()
{
	// Call base function.
	MSUBbc(1);
}

void VUInterpreter::MSUBbc_2()
{
	// Call base function.
	MSUBbc(2);
}

void VUInterpreter::MSUBbc_3()
{
	// Call base function.
	MSUBbc(3);
}

void VUInterpreter::MSUBA()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) MSUBA: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MSUBA: Not implemented.");
#endif
}

void VUInterpreter::MSUBAi()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) MSUBAi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MSUBAi: Not implemented.");
#endif
}

void VUInterpreter::MSUBAq()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) MSUBAq: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MSUBAq: Not implemented.");
#endif
}

void VUInterpreter::MSUBAbc(const u8 & idx)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) MSUBAbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MSUBAbc: Not implemented.");
#endif
}

void VUInterpreter::MSUBAbc_0()
{
	// Call base function.
	MSUBAbc(0);
}

void VUInterpreter::MSUBAbc_1()
{
	// Call base function.
	MSUBAbc(1);
}

void VUInterpreter::MSUBAbc_2()
{
	// Call base function.
	MSUBAbc(2);
}

void VUInterpreter::MSUBAbc_3()
{
	// Call base function.
	MSUBAbc(3);
}

void VUInterpreter::MAX()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) MAX: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MAX: Not implemented.");
#endif
}

void VUInterpreter::MAXi()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) MAXi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MAXi: Not implemented.");
#endif
}

void VUInterpreter::MAXbc(const u8 & idx)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) MAXbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MAXbc: Not implemented.");
#endif
}

void VUInterpreter::MAXbc_0()
{
	// Call base function.
	MAXbc(0);
}

void VUInterpreter::MAXbc_1()
{
	// Call base function.
	MAXbc(1);
}

void VUInterpreter::MAXbc_2()
{
	// Call base function.
	MAXbc(2);
}

void VUInterpreter::MAXbc_3()
{
	// Call base function.
	MAXbc(3);
}

void VUInterpreter::MINI()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) MINI: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MINI: Not implemented.");
#endif
}

void VUInterpreter::MINIi()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) MINIi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MINIi: Not implemented.");
#endif
}

void VUInterpreter::MINIbc(const u8 & idx)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) MINIbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MINIbc: Not implemented.");
#endif
}

void VUInterpreter::MINIbc_0()
{
	// Call base function.
	MINIbc(0);
}

void VUInterpreter::MINIbc_1()
{
	// Call base function.
	MINIbc(1);
}

void VUInterpreter::MINIbc_2()
{
	// Call base function.
	MINIbc(2);
}

void VUInterpreter::MINIbc_3()
{
	// Call base function.
	MINIbc(3);
}

void VUInterpreter::OPMULA()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) OPMULA: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("OPMULA: Not implemented.");
#endif
}

void VUInterpreter::OPMSUB()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) OPMSUB: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("OPMSUB: Not implemented.");
#endif
}

void VUInterpreter::DIV()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) DIV: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("DIV: Not implemented.");
#endif
}

void VUInterpreter::SQRT()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) SQRT: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("SQRT: Not implemented.");
#endif
}

void VUInterpreter::RSQRT()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) RSQRT: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("RSQRT: Not implemented.");
#endif
}
