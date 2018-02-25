#include <boost/format.hpp>

#include "Core.hpp"

#include "Controller/Ee/Vpu/Vu/Interpreter/CVuInterpreter.hpp"

#include "Resources/Ee/Vpu/Vu/VuUnits.hpp"

void CVuInterpreter::IADD(VuUnit_Base * unit, const VuInstruction inst)
{
	// ID = IS + IT.
	auto& reg_source1 = unit->vi[inst.fs()]; // IS.
	auto& reg_source2 = unit->vi[inst.ft()]; // IT.
	auto& reg_dest = unit->vi[inst.fd()]; // ID.

	reg_dest->write_uhword(reg_source1->read_uhword() + reg_source2->read_uhword());
}

void CVuInterpreter::IADDI(VuUnit_Base * unit, const VuInstruction inst)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) IADDI: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("IADDI: Not implemented.");
#endif
}

void CVuInterpreter::IADDIU(VuUnit_Base * unit, const VuInstruction inst)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) IADDIU: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("IADDIU: Not implemented.");
#endif
}

void CVuInterpreter::IAND(VuUnit_Base * unit, const VuInstruction inst)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) IAND: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("IAND: Not implemented.");
#endif
}

void CVuInterpreter::IOR(VuUnit_Base * unit, const VuInstruction inst)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) IOR: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("IOR: Not implemented.");
#endif
}

void CVuInterpreter::ISUB(VuUnit_Base * unit, const VuInstruction inst)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) ISUB: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("ISUB: Not implemented.");
#endif
}

void CVuInterpreter::ISUBIU(VuUnit_Base * unit, const VuInstruction inst)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) ISUBIU: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("ISUBIU: Not implemented.");
#endif
}
