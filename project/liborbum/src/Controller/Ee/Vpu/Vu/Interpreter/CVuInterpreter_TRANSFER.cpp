#include <boost/format.hpp>

#include "Core.hpp"

#include "Controller/Ee/Vpu/Vu/Interpreter/CVuInterpreter.hpp"

#include "Resources/Ee/Vpu/Vu/VuUnits.hpp"

void CVuInterpreter::MOVE(VuUnit_Base * unit, const VuInstruction inst)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) MOVE: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("MOVE: Not implemented.");
#endif
}

void CVuInterpreter::MFIR(VuUnit_Base * unit, const VuInstruction inst)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) MFIR: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("MFIR: Not implemented.");
#endif
}

void CVuInterpreter::MTIR(VuUnit_Base * unit, const VuInstruction inst)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) MTIR: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("MTIR: Not implemented.");
#endif
}

void CVuInterpreter::MR32(VuUnit_Base * unit, const VuInstruction inst)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) MR32: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("MR32: Not implemented.");
#endif
}

void CVuInterpreter::LQ(VuUnit_Base * unit, const VuInstruction inst)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) LQ: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("LQ: Not implemented.");
#endif
}

void CVuInterpreter::LQD(VuUnit_Base * unit, const VuInstruction inst)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) LQD: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("LQD: Not implemented.");
#endif
}

void CVuInterpreter::LQI(VuUnit_Base * unit, const VuInstruction inst)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) LQI: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("LQI: Not implemented.");
#endif
}

void CVuInterpreter::SQ(VuUnit_Base * unit, const VuInstruction inst)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) SQ: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("SQ: Not implemented.");
#endif
}

void CVuInterpreter::SQD(VuUnit_Base * unit, const VuInstruction inst)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) SQD: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("SQD: Not implemented.");
#endif
}

void CVuInterpreter::SQI(VuUnit_Base * unit, const VuInstruction inst)
{
	// MEM(Ft) = Fs
	auto& reg_source1 = unit->vf[inst.fs()];
	auto& reg_source2 = unit->vi[inst.ft()]; // Mem Addr.

	// Real address obtained by VI * 16 (qword addressing).
	uword address = reg_source2->read_uhword() * NUMBER_BYTES_IN_QWORD;

	// 32-bit write for each dest subfield.
	if (inst.test_dest_x()) unit->bus.write_uword(BusContext::Vu, address, reg_source1.read_uword(0));
	if (inst.test_dest_y()) unit->bus.write_uword(BusContext::Vu, address + 4, reg_source1.read_uword(1));
	if (inst.test_dest_z()) unit->bus.write_uword(BusContext::Vu, address + 8, reg_source1.read_uword(2));
	if (inst.test_dest_w()) unit->bus.write_uword(BusContext::Vu, address + 12, reg_source1.read_uword(3));

	// Post increment.
	reg_source2->write_uhword(reg_source2->read_uhword() + 1);
}

void CVuInterpreter::ILW(VuUnit_Base * unit, const VuInstruction inst)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) ILW: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("ILW: Not implemented.");
#endif
}

void CVuInterpreter::ISW(VuUnit_Base * unit, const VuInstruction inst)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) ISW: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("ISW: Not implemented.");
#endif
}

void CVuInterpreter::ILWR(VuUnit_Base * unit, const VuInstruction inst)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) ILWR: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("ILWR: Not implemented.");
#endif
}

void CVuInterpreter::ISWR(VuUnit_Base * unit, const VuInstruction inst)
{
	// MEM(Fs) = Ft.
	auto& reg_source1 = unit->vi[inst.ft()]; // Data.
	auto& reg_source2 = unit->vi[inst.fs()]; // Mem Addr.

	// Real address obtained by VI * 16.
	uword address = reg_source2->read_uhword() * NUMBER_BYTES_IN_QWORD;

	// 32-bit write for each dest subfield. Upper 16-bits of VI[Ft] value is set to 0.
	if (inst.test_dest_x()) unit->bus.write_uword(BusContext::Vu, address, static_cast<uword>(reg_source1->read_uhword()));
	if (inst.test_dest_y()) unit->bus.write_uword(BusContext::Vu, address + 4, static_cast<uword>(reg_source1->read_uhword()));
	if (inst.test_dest_z()) unit->bus.write_uword(BusContext::Vu, address + 8, static_cast<uword>(reg_source1->read_uhword()));
	if (inst.test_dest_w()) unit->bus.write_uword(BusContext::Vu, address + 12, static_cast<uword>(reg_source1->read_uhword()));
}

void CVuInterpreter::LOI(VuUnit_Base * unit, const VuInstruction inst)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) LOI: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("LOI: Not implemented.");
#endif
}

void CVuInterpreter::MFP(VuUnit_Base * unit, const VuInstruction inst)
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) MFP: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("MFP: Not implemented.");
#endif
}
