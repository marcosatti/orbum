#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VMMain.h"
#include "VM/Systems/EE/VPU/VUInterpreter/VUInterpreter.h"

void VUInterpreter::NOP()
{
}

void VUInterpreter::CLIP()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	getVM()->log(Debug, "(%s, %d) CLIP: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("CLIP: Not implemented.");
#endif
}

void VUInterpreter::RINIT()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	getVM()->log(Debug, "(%s, %d) RINIT: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("RINIT: Not implemented.");
#endif
}

void VUInterpreter::RGET()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	getVM()->log(Debug, "(%s, %d) RGET: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("RGET: Not implemented.");
#endif
}

void VUInterpreter::RNEXT()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	getVM()->log(Debug, "(%s, %d) RNEXT: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("RNEXT: Not implemented.");
#endif
}

void VUInterpreter::RXOR()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	getVM()->log(Debug, "(%s, %d) RXOR: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("RXOR: Not implemented.");
#endif
}

void VUInterpreter::WAITQ()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	getVM()->log(Debug, "(%s, %d) WAITQ: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("WAITQ: Not implemented.");
#endif
}

void VUInterpreter::IBEQ()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	getVM()->log(Debug, "(%s, %d) IBEQ: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("IBEQ: Not implemented.");
#endif
}

void VUInterpreter::IBGEZ()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	getVM()->log(Debug, "(%s, %d) IBGEZ: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("IBGEZ: Not implemented.");
#endif
}

void VUInterpreter::IBGTZ()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	getVM()->log(Debug, "(%s, %d) IBGTZ: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("IBGTZ: Not implemented.");
#endif
}

void VUInterpreter::IBLEZ()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	getVM()->log(Debug, "(%s, %d) IBLEZ: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("IBLEZ: Not implemented.");
#endif
}

void VUInterpreter::IBLTZ()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	getVM()->log(Debug, "(%s, %d) IBLTZ: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("IBLTZ: Not implemented.");
#endif
}

void VUInterpreter::IBNE()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	getVM()->log(Debug, "(%s, %d) IBNE: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("IBNE: Not implemented.");
#endif
}

void VUInterpreter::B()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	getVM()->log(Debug, "(%s, %d) B: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("B: Not implemented.");
#endif
}

void VUInterpreter::BAL()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	getVM()->log(Debug, "(%s, %d) BAL: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("BAL: Not implemented.");
#endif
}

void VUInterpreter::JR()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	getVM()->log(Debug, "(%s, %d) JR: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("JR: Not implemented.");
#endif
}

void VUInterpreter::JALR()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	getVM()->log(Debug, "(%s, %d) JALR: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("JALR: Not implemented.");
#endif
}

void VUInterpreter::WAITP()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	getVM()->log(Debug, "(%s, %d) WAITP: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("WAITP: Not implemented.");
#endif
}

void VUInterpreter::XGKICK()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	getVM()->log(Debug, "(%s, %d) XGKICK: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("XGKICK: Not implemented.");
#endif
}

void VUInterpreter::XTOP()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	getVM()->log(Debug, "(%s, %d) XTOP: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("XTOP: Not implemented.");
#endif
}

void VUInterpreter::XITOP()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	getVM()->log(Debug, "(%s, %d) XITOP: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("XITOP: Not implemented.");
#endif
}
