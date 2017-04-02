#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/Register16_t.h"
#include "Common/Types/Registers/FPRegister128_t.h"

#include "VM/Systems/EE/VPU/VUInterpreter/VUInterpreter_s.h"

#include "Resources/EE/VPU/VU/Types/VUCores_t.h"

void VUInterpreter_s::IADD()
{
	// ID = IS + IT.
	auto& source1Reg = mVUCore->VI[mVUInstruction.getFs()]; // IS.
	auto& source2Reg = mVUCore->VI[mVUInstruction.getFt()]; // IT.
	auto& destReg = mVUCore->VI[mVUInstruction.getFd()]; // ID.

	destReg->writeHword(getContext(), source1Reg->readHword(getContext()) + source2Reg->readHword(getContext()));
}

void VUInterpreter_s::IADDI()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) IADDI: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("IADDI: Not implemented.");
#endif
}

void VUInterpreter_s::IADDIU()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) IADDIU: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("IADDIU: Not implemented.");
#endif
}

void VUInterpreter_s::IAND()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) IAND: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("IAND: Not implemented.");
#endif
}

void VUInterpreter_s::IOR()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) IOR: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("IOR: Not implemented.");
#endif
}

void VUInterpreter_s::ISUB()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) ISUB: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("ISUB: Not implemented.");
#endif
}

void VUInterpreter_s::ISUBIU()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) ISUBIU: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("ISUBIU: Not implemented.");
#endif
}
