#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/ExecutionCore/Interpreter/EE/VPU/VUInterpreter/VUInterpreter.h"

void VUInterpreter::IADD()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) IADD: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("IADD: Not implemented.");
#endif
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
