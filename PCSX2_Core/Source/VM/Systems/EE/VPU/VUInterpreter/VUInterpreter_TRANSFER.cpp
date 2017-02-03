#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/PhysicalMMU/PhysicalMMU_t.h"
#include "Common/Types/Registers/Register16_t.h"
#include "Common/Types/Registers/FPRegister128_t.h"

#include "VM/VMMain.h"
#include "VM/Systems/EE/VPU/VUInterpreter/VUInterpreter.h"

#include "Resources/Resources_t.h"
#include "Resources/EE/EE_t.h"
#include "Resources/EE/VPU/VPU_t.h"
#include "Resources/EE/VPU/VU/VU_t.h"
#include "Resources/EE/VPU/VU/Types/VuUnits_t.h"

void VUInterpreter::MOVE()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	getVM()->log(Debug, "(%s, %d) MOVE: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MOVE: Not implemented.");
#endif
}

void VUInterpreter::MFIR()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	getVM()->log(Debug, "(%s, %d) MFIR: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MFIR: Not implemented.");
#endif
}

void VUInterpreter::MTIR()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	getVM()->log(Debug, "(%s, %d) MTIR: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MTIR: Not implemented.");
#endif
}

void VUInterpreter::MR32()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	getVM()->log(Debug, "(%s, %d) MR32: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MR32: Not implemented.");
#endif
}

void VUInterpreter::LQ()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	getVM()->log(Debug, "(%s, %d) LQ: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("LQ: Not implemented.");
#endif
}

void VUInterpreter::LQD()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	getVM()->log(Debug, "(%s, %d) LQD: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("LQD: Not implemented.");
#endif
}

void VUInterpreter::LQI()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	getVM()->log(Debug, "(%s, %d) LQI: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("LQI: Not implemented.");
#endif
}

void VUInterpreter::SQ()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	getVM()->log(Debug, "(%s, %d) SQ: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("SQ: Not implemented.");
#endif
}

void VUInterpreter::SQD()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	getVM()->log(Debug, "(%s, %d) SQD: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("SQD: Not implemented.");
#endif
}

void VUInterpreter::SQI()
{
	// MEM(Ft) = Fs
	auto& source1Reg = getResources()->EE->VPU->VU->VU_UNITS[mVUUnitIndex]->VF[mInstruction.getFs()];
	auto& source2Reg = getResources()->EE->VPU->VU->VU_UNITS[mVUUnitIndex]->VI[mInstruction.getFt()]; // Mem Addr.
	auto& Mem = getResources()->EE->VPU->VU->VU_UNITS[mVUUnitIndex]->MemPhysicalMMU;

	// Real address obtained by VI * 16.
	u32 realPhysicalAddress = source2Reg->readHword(EE) * 16;

	// 32-bit write for each dest subfield.
	if (mInstruction.testDestX()) Mem->writeWord(EE, realPhysicalAddress, source1Reg->readWord(EE, 0));
	if (mInstruction.testDestY()) Mem->writeWord(EE, realPhysicalAddress + 4, source1Reg->readWord(EE, 1));
	if (mInstruction.testDestZ()) Mem->writeWord(EE, realPhysicalAddress + 8, source1Reg->readWord(EE, 2));
	if (mInstruction.testDestW()) Mem->writeWord(EE, realPhysicalAddress + 12, source1Reg->readWord(EE, 3));

	// Post increment.
	source2Reg->writeHword(EE, source2Reg->readHword(EE) + 1);
}

void VUInterpreter::ILW()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	getVM()->log(Debug, "(%s, %d) ILW: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("ILW: Not implemented.");
#endif
}

void VUInterpreter::ISW()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	getVM()->log(Debug, "(%s, %d) ISW: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("ISW: Not implemented.");
#endif
}

void VUInterpreter::ILWR()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	getVM()->log(Debug, "(%s, %d) ILWR: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("ILWR: Not implemented.");
#endif
}

void VUInterpreter::ISWR()
{
	// MEM(Fs) = Ft.
	auto& source1Reg = getResources()->EE->VPU->VU->VU_UNITS[mVUUnitIndex]->VI[mInstruction.getFt()]; // Data.
	auto& source2Reg = getResources()->EE->VPU->VU->VU_UNITS[mVUUnitIndex]->VI[mInstruction.getFs()]; // Mem Addr.
	auto& Mem = getResources()->EE->VPU->VU->VU_UNITS[mVUUnitIndex]->MemPhysicalMMU;

	// Real address obtained by VI * 16.
	u32 realPhysicalAddress = source2Reg->readHword(EE) * 16;

	// 32-bit write for each dest subfield. Upper 16-bits of VI[Ft] value is set to 0.
	if (mInstruction.testDestX()) Mem->writeWord(EE, realPhysicalAddress, static_cast<u32>(source1Reg->readHword(EE)));
	if (mInstruction.testDestY()) Mem->writeWord(EE, realPhysicalAddress + 4, static_cast<u32>(source1Reg->readHword(EE)));
	if (mInstruction.testDestZ()) Mem->writeWord(EE, realPhysicalAddress + 8, static_cast<u32>(source1Reg->readHword(EE)));
	if (mInstruction.testDestW()) Mem->writeWord(EE, realPhysicalAddress + 12, static_cast<u32>(source1Reg->readHword(EE)));
}

void VUInterpreter::LOI()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	getVM()->log(Debug, "(%s, %d) LOI: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("LOI: Not implemented.");
#endif
}

void VUInterpreter::MFP()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	getVM()->log(Debug, "(%s, %d) MFP: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("MFP: Not implemented.");
#endif
}
