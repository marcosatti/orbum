#include <boost/format.hpp>

#include "Core.hpp"

#include "Controller/Ee/Vpu/Vu/Interpreter/CVuInterpreter.hpp"

void CVuInterpreter::NOP(VuUnit_Base * unit, const VuInstruction inst) const
{
}

void CVuInterpreter::CLIP(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) CLIP: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("CLIP: Not implemented.");
#endif
}

void CVuInterpreter::RINIT(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) RINIT: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("RINIT: Not implemented.");
#endif
}

void CVuInterpreter::RGET(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) RGET: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("RGET: Not implemented.");
#endif
}

void CVuInterpreter::RNEXT(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) RNEXT: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("RNEXT: Not implemented.");
#endif
}

void CVuInterpreter::RXOR(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) RXOR: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("RXOR: Not implemented.");
#endif
}

void CVuInterpreter::WAITQ(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) WAITQ: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("WAITQ: Not implemented.");
#endif
}

void CVuInterpreter::IBEQ(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) IBEQ: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("IBEQ: Not implemented.");
#endif
}

void CVuInterpreter::IBGEZ(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) IBGEZ: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("IBGEZ: Not implemented.");
#endif
}

void CVuInterpreter::IBGTZ(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) IBGTZ: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("IBGTZ: Not implemented.");
#endif
}

void CVuInterpreter::IBLEZ(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) IBLEZ: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("IBLEZ: Not implemented.");
#endif
}

void CVuInterpreter::IBLTZ(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) IBLTZ: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("IBLTZ: Not implemented.");
#endif
}

void CVuInterpreter::IBNE(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) IBNE: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("IBNE: Not implemented.");
#endif
}

void CVuInterpreter::B(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) B: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("B: Not implemented.");
#endif
}

void CVuInterpreter::BAL(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) BAL: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("BAL: Not implemented.");
#endif
}

void CVuInterpreter::JR(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) JR: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("JR: Not implemented.");
#endif
}

void CVuInterpreter::JALR(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) JALR: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("JALR: Not implemented.");
#endif
}

void CVuInterpreter::WAITP(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) WAITP: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("WAITP: Not implemented.");
#endif
}

void CVuInterpreter::XGKICK(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) XGKICK: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("XGKICK: Not implemented.");
#endif
}

void CVuInterpreter::XTOP(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) XTOP: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("XTOP: Not implemented.");
#endif
}

void CVuInterpreter::XITOP(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) XITOP: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("XITOP: Not implemented.");
#endif
}
