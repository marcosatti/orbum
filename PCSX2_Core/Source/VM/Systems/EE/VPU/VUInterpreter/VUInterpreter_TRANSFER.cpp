#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/PhysicalMMU/PhysicalMMU_t.h"
#include "Common/Types/Registers/Register16_t.h"
#include "Common/Types/Registers/FPRegister128_t.h"

#include "VM/Systems/EE/VPU/VUInterpreter/VUInterpreter_s.h"

#include "Resources/EE/VPU/VU/Types/VUCores_t.h"

void VUInterpreter_s::MOVE()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MOVE: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MOVE: Not implemented.");
#endif
}

void VUInterpreter_s::MFIR()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MFIR: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MFIR: Not implemented.");
#endif
}

void VUInterpreter_s::MTIR()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MTIR: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MTIR: Not implemented.");
#endif
}

void VUInterpreter_s::MR32()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MR32: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MR32: Not implemented.");
#endif
}

void VUInterpreter_s::LQ()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) LQ: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("LQ: Not implemented.");
#endif
}

void VUInterpreter_s::LQD()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) LQD: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("LQD: Not implemented.");
#endif
}

void VUInterpreter_s::LQI()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) LQI: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("LQI: Not implemented.");
#endif
}

void VUInterpreter_s::SQ()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) SQ: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("SQ: Not implemented.");
#endif
}

void VUInterpreter_s::SQD()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) SQD: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("SQD: Not implemented.");
#endif
}

void VUInterpreter_s::SQI()
{
	// MEM(Ft) = Fs
	auto& source1Reg = mVUCore->VF[mVUInstruction.getFs()];
	auto& source2Reg = mVUCore->VI[mVUInstruction.getFt()]; // Mem Addr.
	auto& Mem = mVUCore->MemPhysicalMMU;

	// Real address obtained by VI * 16.
	u32 realPhysicalAddress = source2Reg->readHword(getContext()) * 16;

	// 32-bit write for each dest subfield.
	if (mVUInstruction.testDestX()) Mem->writeWord(getContext(), realPhysicalAddress, source1Reg->readWord(getContext(), 0));
	if (mVUInstruction.testDestY()) Mem->writeWord(getContext(), realPhysicalAddress + 4, source1Reg->readWord(getContext(), 1));
	if (mVUInstruction.testDestZ()) Mem->writeWord(getContext(), realPhysicalAddress + 8, source1Reg->readWord(getContext(), 2));
	if (mVUInstruction.testDestW()) Mem->writeWord(getContext(), realPhysicalAddress + 12, source1Reg->readWord(getContext(), 3));

	// Post increment.
	source2Reg->writeHword(getContext(), source2Reg->readHword(getContext()) + 1);
}

void VUInterpreter_s::ILW()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) ILW: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("ILW: Not implemented.");
#endif
}

void VUInterpreter_s::ISW()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) ISW: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("ISW: Not implemented.");
#endif
}

void VUInterpreter_s::ILWR()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) ILWR: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("ILWR: Not implemented.");
#endif
}

void VUInterpreter_s::ISWR()
{
	// MEM(Fs) = Ft.
	auto& source1Reg = mVUCore->VI[mVUInstruction.getFt()]; // Data.
	auto& source2Reg = mVUCore->VI[mVUInstruction.getFs()]; // Mem Addr.
	auto& Mem = mVUCore->MemPhysicalMMU;

	// Real address obtained by VI * 16.
	u32 realPhysicalAddress = source2Reg->readHword(getContext()) * 16;

	// 32-bit write for each dest subfield. Upper 16-bits of VI[Ft] value is set to 0.
	if (mVUInstruction.testDestX()) Mem->writeWord(getContext(), realPhysicalAddress, static_cast<u32>(source1Reg->readHword(getContext())));
	if (mVUInstruction.testDestY()) Mem->writeWord(getContext(), realPhysicalAddress + 4, static_cast<u32>(source1Reg->readHword(getContext())));
	if (mVUInstruction.testDestZ()) Mem->writeWord(getContext(), realPhysicalAddress + 8, static_cast<u32>(source1Reg->readHword(getContext())));
	if (mVUInstruction.testDestW()) Mem->writeWord(getContext(), realPhysicalAddress + 12, static_cast<u32>(source1Reg->readHword(getContext())));
}

void VUInterpreter_s::LOI()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) LOI: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("LOI: Not implemented.");
#endif
}

void VUInterpreter_s::MFP()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) MFP: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MFP: Not implemented.");
#endif
}
