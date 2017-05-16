#include "Common/Global/Globals.h"
#include "Common/Types/Register/Register128_t.h"
#include "Common/Util/FPUUtil/FPUUtil.h"

#include "VM/Systems/EE/VPU/VUInterpreter/VUInterpreter_s.h"

#include "Resources/EE/VPU/VU/Types/VUCores_t.h"
#include "Resources/EE/VPU/VU/Types/VUCoreRegisters_t.h"

void VUInterpreter_s::ABS()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) ABS: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("ABS: Not implemented.");
#endif
}

void VUInterpreter_s::ADD()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) ADD: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("ADD: Not implemented.");
#endif
}

void VUInterpreter_s::ADDi()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) ADDi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("ADDi: Not implemented.");
#endif
}

void VUInterpreter_s::ADDq()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) ADDq: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("ADDq: Not implemented.");
#endif
}

void VUInterpreter_s::ADDbc(const int idx)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) ADDbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("ADDbc: Not implemented.");
#endif
}

void VUInterpreter_s::ADDbc_0()
{
	// Call base function.
	ADDbc(0);
}

void VUInterpreter_s::ADDbc_1()
{
	// Call base function.
	ADDbc(1);
}

void VUInterpreter_s::ADDbc_2()
{
	// Call base function.
	ADDbc(2);
}

void VUInterpreter_s::ADDbc_3()
{
	// Call base function.
	ADDbc(3);
}

void VUInterpreter_s::ADDA()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) ADDA: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("ADDA: Not implemented.");
#endif
}

void VUInterpreter_s::ADDAi()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) ADDAi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("ADDAi: Not implemented.");
#endif
}

void VUInterpreter_s::ADDAq()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) ADDAq: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("ADDAq: Not implemented.");
#endif
}

void VUInterpreter_s::ADDAbc(const int idx)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) ADDAbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("ADDAbc: Not implemented.");
#endif
}

void VUInterpreter_s::ADDAbc_0()
{
	// Call base function.
	ADDAbc(0);
}

void VUInterpreter_s::ADDAbc_1()
{
	// Call base function.
	ADDAbc(1);
}

void VUInterpreter_s::ADDAbc_2()
{
	// Call base function.
	ADDAbc(2);
}

void VUInterpreter_s::ADDAbc_3()
{
	// Call base function.
	ADDAbc(3);
}

void VUInterpreter_s::SUB()
{
	// Fd = Fs - Ft.
	auto& destReg = mVUCore->VF[mVUInstruction.getFd()];
	auto& source1Reg = mVUCore->VF[mVUInstruction.getFs()];
	auto& source2Reg = mVUCore->VF[mVUInstruction.getFt()];
	auto& MAC = mVUCore->MAC;
	auto& Status = mVUCore->Status;

	Status->clearFlags(getContext());

	FPUFlags_t flags;
	for (auto i = 0; i < 4; i++)
	{
		if (mVUInstruction.testDestField(i))
		{
			f32 result = FPUUtil::formatIEEEToPS2Float(source1Reg->readFloat(getContext(), i) - source2Reg->readFloat(getContext(), i), flags);
			destReg->writeFloat(getContext(), i, result);
			MAC->updateVectorField(getContext(), i, flags);
		}
		else
			MAC->clearVectorField(getContext(), i);
	}
}

void VUInterpreter_s::SUBi()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) SUBi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("SUBi: Not implemented.");
#endif
}

void VUInterpreter_s::SUBq()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) SUBq: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("SUBq: Not implemented.");
#endif
}

void VUInterpreter_s::SUBbc(const int idx)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) SUBbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("SUBbc: Not implemented.");
#endif
}

void VUInterpreter_s::SUBbc_0()
{
	// Call base function.
	SUBbc(0);
}

void VUInterpreter_s::SUBbc_1()
{
	// Call base function.
	SUBbc(1);
}

void VUInterpreter_s::SUBbc_2()
{
	// Call base function.
	SUBbc(2);
}

void VUInterpreter_s::SUBbc_3()
{
	// Call base function.
	SUBbc(3);
}

void VUInterpreter_s::SUBA()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) SUBA: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("SUBA: Not implemented.");
#endif
}

void VUInterpreter_s::SUBAi()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) SUBAi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("SUBAi: Not implemented.");
#endif
}

void VUInterpreter_s::SUBAq()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) SUBAq: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("SUBAq: Not implemented.");
#endif
}

void VUInterpreter_s::SUBAbc(const int idx)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) SUBAbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("SUBAbc: Not implemented.");
#endif
}

void VUInterpreter_s::SUBAbc_0()
{
	// Call base function.
	SUBAbc(0);
}

void VUInterpreter_s::SUBAbc_1()
{
	// Call base function.
	SUBAbc(1);
}

void VUInterpreter_s::SUBAbc_2()
{
	// Call base function.
	SUBAbc(2);
}

void VUInterpreter_s::SUBAbc_3()
{
	// Call base function.
	SUBAbc(3);
}

void VUInterpreter_s::MUL()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MUL: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MUL: Not implemented.");
#endif
}

void VUInterpreter_s::MULi()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MULi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MULi: Not implemented.");
#endif
}

void VUInterpreter_s::MULq()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MULq: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MULq: Not implemented.");
#endif
}

void VUInterpreter_s::MULbc(const int idx)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MULbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MULbc: Not implemented.");
#endif
}

void VUInterpreter_s::MULbc_0()
{
	// Call base function.
	MULbc(0);
}

void VUInterpreter_s::MULbc_1()
{
	// Call base function.
	MULbc(1);
}

void VUInterpreter_s::MULbc_2()
{
	// Call base function.
	MULbc(2);
}

void VUInterpreter_s::MULbc_3()
{
	// Call base function.
	MULbc(3);
}

void VUInterpreter_s::MULA()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MULA: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MULA: Not implemented.");
#endif
}

void VUInterpreter_s::MULAi()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MULAi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MULAi: Not implemented.");
#endif
}

void VUInterpreter_s::MULAq()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MULAq: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MULAq: Not implemented.");
#endif
}

void VUInterpreter_s::MULAbc(const int idx)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MULAbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MULAbc: Not implemented.");
#endif
}

void VUInterpreter_s::MULAbc_0()
{
	// Call base function.
	MULAbc(0);
}

void VUInterpreter_s::MULAbc_1()
{
	// Call base function.
	MULAbc(1);
}

void VUInterpreter_s::MULAbc_2()
{
	// Call base function.
	MULAbc(2);
}

void VUInterpreter_s::MULAbc_3()
{
	// Call base function.
	MULAbc(3);
}

void VUInterpreter_s::MADD()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MADD: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MADD: Not implemented.");
#endif
}

void VUInterpreter_s::MADDi()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MADDi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MADDi: Not implemented.");
#endif
}

void VUInterpreter_s::MADDq()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MADDq: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MADDq: Not implemented.");
#endif
}

void VUInterpreter_s::MADDbc(const int idx)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MADDbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MADDbc: Not implemented.");
#endif
}

void VUInterpreter_s::MADDbc_0()
{
	// Call base function.
	MADDbc(0);
}

void VUInterpreter_s::MADDbc_1()
{
	// Call base function.
	MADDbc(1);
}

void VUInterpreter_s::MADDbc_2()
{
	// Call base function.
	MADDbc(2);
}

void VUInterpreter_s::MADDbc_3()
{
	// Call base function.
	MADDbc(3);
}

void VUInterpreter_s::MADDA()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MADDA: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MADDA: Not implemented.");
#endif
}

void VUInterpreter_s::MADDAi()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MADDAi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MADDAi: Not implemented.");
#endif
}

void VUInterpreter_s::MADDAq()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MADDAq: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MADDAq: Not implemented.");
#endif
}

void VUInterpreter_s::MADDAbc(const int idx)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MADDAbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MADDAbc: Not implemented.");
#endif
}

void VUInterpreter_s::MADDAbc_0()
{
	// Call base function.
	MADDAbc(0);
}

void VUInterpreter_s::MADDAbc_1()
{
	// Call base function.
	MADDAbc(1);
}

void VUInterpreter_s::MADDAbc_2()
{
	// Call base function.
	MADDAbc(2);
}

void VUInterpreter_s::MADDAbc_3()
{
	// Call base function.
	MADDAbc(3);
}

void VUInterpreter_s::MSUB()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MSUB: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MSUB: Not implemented.");
#endif
}

void VUInterpreter_s::MSUBi()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MSUBi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MSUBi: Not implemented.");
#endif
}

void VUInterpreter_s::MSUBq()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MSUBq: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MSUBq: Not implemented.");
#endif
}

void VUInterpreter_s::MSUBbc(const int idx)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MSUBbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MSUBbc: Not implemented.");
#endif
}

void VUInterpreter_s::MSUBbc_0()
{
	// Call base function.
	MSUBbc(0);
}

void VUInterpreter_s::MSUBbc_1()
{
	// Call base function.
	MSUBbc(1);
}

void VUInterpreter_s::MSUBbc_2()
{
	// Call base function.
	MSUBbc(2);
}

void VUInterpreter_s::MSUBbc_3()
{
	// Call base function.
	MSUBbc(3);
}

void VUInterpreter_s::MSUBA()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MSUBA: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MSUBA: Not implemented.");
#endif
}

void VUInterpreter_s::MSUBAi()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MSUBAi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MSUBAi: Not implemented.");
#endif
}

void VUInterpreter_s::MSUBAq()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MSUBAq: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MSUBAq: Not implemented.");
#endif
}

void VUInterpreter_s::MSUBAbc(const int idx)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MSUBAbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MSUBAbc: Not implemented.");
#endif
}

void VUInterpreter_s::MSUBAbc_0()
{
	// Call base function.
	MSUBAbc(0);
}

void VUInterpreter_s::MSUBAbc_1()
{
	// Call base function.
	MSUBAbc(1);
}

void VUInterpreter_s::MSUBAbc_2()
{
	// Call base function.
	MSUBAbc(2);
}

void VUInterpreter_s::MSUBAbc_3()
{
	// Call base function.
	MSUBAbc(3);
}

void VUInterpreter_s::MAX()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MAX: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MAX: Not implemented.");
#endif
}

void VUInterpreter_s::MAXi()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MAXi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MAXi: Not implemented.");
#endif
}

void VUInterpreter_s::MAXbc(const int idx)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MAXbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MAXbc: Not implemented.");
#endif
}

void VUInterpreter_s::MAXbc_0()
{
	// Call base function.
	MAXbc(0);
}

void VUInterpreter_s::MAXbc_1()
{
	// Call base function.
	MAXbc(1);
}

void VUInterpreter_s::MAXbc_2()
{
	// Call base function.
	MAXbc(2);
}

void VUInterpreter_s::MAXbc_3()
{
	// Call base function.
	MAXbc(3);
}

void VUInterpreter_s::MINI()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MINI: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MINI: Not implemented.");
#endif
}

void VUInterpreter_s::MINIi()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MINIi: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MINIi: Not implemented.");
#endif
}

void VUInterpreter_s::MINIbc(const int idx)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MINIbc: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MINIbc: Not implemented.");
#endif
}

void VUInterpreter_s::MINIbc_0()
{
	// Call base function.
	MINIbc(0);
}

void VUInterpreter_s::MINIbc_1()
{
	// Call base function.
	MINIbc(1);
}

void VUInterpreter_s::MINIbc_2()
{
	// Call base function.
	MINIbc(2);
}

void VUInterpreter_s::MINIbc_3()
{
	// Call base function.
	MINIbc(3);
}

void VUInterpreter_s::OPMULA()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) OPMULA: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("OPMULA: Not implemented.");
#endif
}

void VUInterpreter_s::OPMSUB()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) OPMSUB: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("OPMSUB: Not implemented.");
#endif
}

void VUInterpreter_s::DIV()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) DIV: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("DIV: Not implemented.");
#endif
}

void VUInterpreter_s::SQRT()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) SQRT: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("SQRT: Not implemented.");
#endif
}

void VUInterpreter_s::RSQRT()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) RSQRT: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("RSQRT: Not implemented.");
#endif
}
