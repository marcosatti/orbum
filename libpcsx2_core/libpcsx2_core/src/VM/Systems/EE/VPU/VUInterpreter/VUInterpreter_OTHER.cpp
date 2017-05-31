#include "Common/Global/Globals.h"

#include "VM/Systems/EE/VPU/VUInterpreter/VUInterpreter_s.h"

void VUInterpreter_s::NOP()
{
}

void VUInterpreter_s::CLIP()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) CLIP: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("CLIP: Not implemented.");
#endif
}

void VUInterpreter_s::RINIT()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) RINIT: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("RINIT: Not implemented.");
#endif
}

void VUInterpreter_s::RGET()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) RGET: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("RGET: Not implemented.");
#endif
}

void VUInterpreter_s::RNEXT()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) RNEXT: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("RNEXT: Not implemented.");
#endif
}

void VUInterpreter_s::RXOR()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) RXOR: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("RXOR: Not implemented.");
#endif
}

void VUInterpreter_s::WAITQ()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) WAITQ: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("WAITQ: Not implemented.");
#endif
}

void VUInterpreter_s::IBEQ()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) IBEQ: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("IBEQ: Not implemented.");
#endif
}

void VUInterpreter_s::IBGEZ()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) IBGEZ: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("IBGEZ: Not implemented.");
#endif
}

void VUInterpreter_s::IBGTZ()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) IBGTZ: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("IBGTZ: Not implemented.");
#endif
}

void VUInterpreter_s::IBLEZ()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) IBLEZ: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("IBLEZ: Not implemented.");
#endif
}

void VUInterpreter_s::IBLTZ()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) IBLTZ: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("IBLTZ: Not implemented.");
#endif
}

void VUInterpreter_s::IBNE()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) IBNE: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("IBNE: Not implemented.");
#endif
}

void VUInterpreter_s::B()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) B: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("B: Not implemented.");
#endif
}

void VUInterpreter_s::BAL()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) BAL: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("BAL: Not implemented.");
#endif
}

void VUInterpreter_s::JR()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) JR: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("JR: Not implemented.");
#endif
}

void VUInterpreter_s::JALR()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) JALR: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("JALR: Not implemented.");
#endif
}

void VUInterpreter_s::WAITP()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) WAITP: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("WAITP: Not implemented.");
#endif
}

void VUInterpreter_s::XGKICK()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) XGKICK: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("XGKICK: Not implemented.");
#endif
}

void VUInterpreter_s::XTOP()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) XTOP: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("XTOP: Not implemented.");
#endif
}

void VUInterpreter_s::XITOP()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) XITOP: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("XITOP: Not implemented.");
#endif
}
