#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/ExecutionCore/Interpreter/EE/VPU/VUInterpreter/VUInterpreter.h"
#include "Common/Types/Registers/Register16_t.h"
#include "Common/Types/Registers/FPRegister128_t.h"
#include "VM/VMMain.h"
#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/VPU/VPU_t.h"
#include "PS2Resources/EE/VPU/VU/VU_t.h"
#include "PS2Resources/EE/VPU/VU/Types/VuUnits_t.h"

void VUInterpreter::IADD()
{
	// ID = IS + IT.
	auto& source1Reg = getResources()->EE->VPU->VU->VU_UNITS[mVUUnitIndex]->VI[mInstruction.getFs()]; // IS.
	auto& source2Reg = getResources()->EE->VPU->VU->VU_UNITS[mVUUnitIndex]->VI[mInstruction.getFt()]; // IT.
	auto& destReg = getResources()->EE->VPU->VU->VU_UNITS[mVUUnitIndex]->VI[mInstruction.getFd()]; // ID.

	destReg->writeHwordU(source1Reg->readHwordU() + source2Reg->readHwordU());
}

void VUInterpreter::IADDI()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) IADDI: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("IADDI: Not implemented.");
#endif
}

void VUInterpreter::IADDIU()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) IADDIU: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("IADDIU: Not implemented.");
#endif
}

void VUInterpreter::IAND()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) IAND: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("IAND: Not implemented.");
#endif
}

void VUInterpreter::IOR()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) IOR: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("IOR: Not implemented.");
#endif
}

void VUInterpreter::ISUB()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) ISUB: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("ISUB: Not implemented.");
#endif
}

void VUInterpreter::ISUBIU()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) ISUBIU: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("ISUBIU: Not implemented.");
#endif
}
