#include <boost/format.hpp>

#include "Core.hpp"
#include "Utilities/Utilities.hpp"

#include "Controller/Ee/Vpu/Vu/Interpreter/CVuInterpreter.hpp"

#include "Resources/Ee/Vpu/Vu/VuUnits.hpp"
#include "Resources/Ee/Vpu/Vu/VuUnitRegisters.hpp"

void CVuInterpreter::ABS(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) ABS: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("ABS: Not implemented.");
#endif
}

void CVuInterpreter::ADD(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) ADD: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("ADD: Not implemented.");
#endif
}

void CVuInterpreter::ADDi(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) ADDi: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("ADDi: Not implemented.");
#endif
}

void CVuInterpreter::ADDq(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) ADDq: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("ADDq: Not implemented.");
#endif
}

void CVuInterpreter::ADDbc(VuUnit_Base * unit, const VuInstruction inst, const int idx) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) ADDbc: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("ADDbc: Not implemented.");
#endif
}

void CVuInterpreter::ADDbc_0(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	ADDbc(unit, inst, 0);
}

void CVuInterpreter::ADDbc_1(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	ADDbc(unit, inst, 1);
}

void CVuInterpreter::ADDbc_2(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	ADDbc(unit, inst, 2);
}

void CVuInterpreter::ADDbc_3(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	ADDbc(unit, inst, 3);
}

void CVuInterpreter::ADDA(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) ADDA: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("ADDA: Not implemented.");
#endif
}

void CVuInterpreter::ADDAi(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) ADDAi: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("ADDAi: Not implemented.");
#endif
}

void CVuInterpreter::ADDAq(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) ADDAq: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("ADDAq: Not implemented.");
#endif
}

void CVuInterpreter::ADDAbc(VuUnit_Base * unit, const VuInstruction inst, const int idx) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) ADDAbc: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("ADDAbc: Not implemented.");
#endif
}

void CVuInterpreter::ADDAbc_0(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	ADDAbc(unit, inst, 0);
}

void CVuInterpreter::ADDAbc_1(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	ADDAbc(unit, inst, 1);
}

void CVuInterpreter::ADDAbc_2(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	ADDAbc(unit, inst, 2);
}

void CVuInterpreter::ADDAbc_3(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	ADDAbc(unit, inst, 3);
}

void CVuInterpreter::SUB(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Fd = Fs - Ft.
	auto& reg_dest = unit->vf[inst.fd()];
	auto& reg_source1 = unit->vf[inst.fs()];
	auto& reg_source2 = unit->vf[inst.ft()];

	unit->status.clear_flags();

	FpuFlags flags;
	for (auto field : VuVectorField::VECTOR_FIELDS)
	{
		if (inst.test_dest_field(field))
		{
			f32 result = to_ps2_float(reg_source1.read_float(field) - reg_source2.read_float(field), flags);
			reg_dest.write_float(field, result);
			unit->mac.update_vector_field(field, flags);
		}
		else
			unit->mac.clear_vector_field(field);
	}
}

void CVuInterpreter::SUBi(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) SUBi: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("SUBi: Not implemented.");
#endif
}

void CVuInterpreter::SUBq(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) SUBq: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("SUBq: Not implemented.");
#endif
}

void CVuInterpreter::SUBbc(VuUnit_Base * unit, const VuInstruction inst, const int idx) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) SUBbc: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("SUBbc: Not implemented.");
#endif
}

void CVuInterpreter::SUBbc_0(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	SUBbc(unit, inst, 0);
}

void CVuInterpreter::SUBbc_1(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	SUBbc(unit, inst, 1);
}

void CVuInterpreter::SUBbc_2(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	SUBbc(unit, inst, 2);
}

void CVuInterpreter::SUBbc_3(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	SUBbc(unit, inst, 3);
}

void CVuInterpreter::SUBA(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) SUBA: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("SUBA: Not implemented.");
#endif
}

void CVuInterpreter::SUBAi(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) SUBAi: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("SUBAi: Not implemented.");
#endif
}

void CVuInterpreter::SUBAq(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) SUBAq: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("SUBAq: Not implemented.");
#endif
}

void CVuInterpreter::SUBAbc(VuUnit_Base * unit, const VuInstruction inst, const int idx) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) SUBAbc: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("SUBAbc: Not implemented.");
#endif
}

void CVuInterpreter::SUBAbc_0(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	SUBAbc(unit, inst, 0);
}

void CVuInterpreter::SUBAbc_1(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	SUBAbc(unit, inst, 1);
}

void CVuInterpreter::SUBAbc_2(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	SUBAbc(unit, inst, 2);
}

void CVuInterpreter::SUBAbc_3(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	SUBAbc(unit, inst, 3);
}

void CVuInterpreter::MUL(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) MUL: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("MUL: Not implemented.");
#endif
}

void CVuInterpreter::MULi(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) MULi: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("MULi: Not implemented.");
#endif
}

void CVuInterpreter::MULq(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) MULq: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("MULq: Not implemented.");
#endif
}

void CVuInterpreter::MULbc(VuUnit_Base * unit, const VuInstruction inst, const int idx) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) MULbc: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("MULbc: Not implemented.");
#endif
}

void CVuInterpreter::MULbc_0(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	MULbc(unit, inst, 0);
}

void CVuInterpreter::MULbc_1(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	MULbc(unit, inst, 1);
}

void CVuInterpreter::MULbc_2(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	MULbc(unit, inst, 2);
}

void CVuInterpreter::MULbc_3(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	MULbc(unit, inst, 3);
}

void CVuInterpreter::MULA(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) MULA: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("MULA: Not implemented.");
#endif
}

void CVuInterpreter::MULAi(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) MULAi: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("MULAi: Not implemented.");
#endif
}

void CVuInterpreter::MULAq(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) MULAq: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("MULAq: Not implemented.");
#endif
}

void CVuInterpreter::MULAbc(VuUnit_Base * unit, const VuInstruction inst, const int idx) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) MULAbc: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("MULAbc: Not implemented.");
#endif
}

void CVuInterpreter::MULAbc_0(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	MULAbc(unit, inst, 0);
}

void CVuInterpreter::MULAbc_1(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	MULAbc(unit, inst, 1);
}

void CVuInterpreter::MULAbc_2(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	MULAbc(unit, inst, 2);
}

void CVuInterpreter::MULAbc_3(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	MULAbc(unit, inst, 3);
}

void CVuInterpreter::MADD(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) MADD: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("MADD: Not implemented.");
#endif
}

void CVuInterpreter::MADDi(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) MADDi: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("MADDi: Not implemented.");
#endif
}

void CVuInterpreter::MADDq(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) MADDq: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("MADDq: Not implemented.");
#endif
}

void CVuInterpreter::MADDbc(VuUnit_Base * unit, const VuInstruction inst, const int idx) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) MADDbc: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("MADDbc: Not implemented.");
#endif
}

void CVuInterpreter::MADDbc_0(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	MADDbc(unit, inst, 0);
}

void CVuInterpreter::MADDbc_1(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	MADDbc(unit, inst, 1);
}

void CVuInterpreter::MADDbc_2(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	MADDbc(unit, inst, 2);
}

void CVuInterpreter::MADDbc_3(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	MADDbc(unit, inst, 3);
}

void CVuInterpreter::MADDA(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) MADDA: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("MADDA: Not implemented.");
#endif
}

void CVuInterpreter::MADDAi(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) MADDAi: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("MADDAi: Not implemented.");
#endif
}

void CVuInterpreter::MADDAq(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) MADDAq: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("MADDAq: Not implemented.");
#endif
}

void CVuInterpreter::MADDAbc(VuUnit_Base * unit, const VuInstruction inst, const int idx) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) MADDAbc: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("MADDAbc: Not implemented.");
#endif
}

void CVuInterpreter::MADDAbc_0(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	MADDAbc(unit, inst, 0);
}

void CVuInterpreter::MADDAbc_1(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	MADDAbc(unit, inst, 1);
}

void CVuInterpreter::MADDAbc_2(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	MADDAbc(unit, inst, 2);
}

void CVuInterpreter::MADDAbc_3(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	MADDAbc(unit, inst, 3);
}

void CVuInterpreter::MSUB(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) MSUB: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("MSUB: Not implemented.");
#endif
}

void CVuInterpreter::MSUBi(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) MSUBi: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("MSUBi: Not implemented.");
#endif
}

void CVuInterpreter::MSUBq(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) MSUBq: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("MSUBq: Not implemented.");
#endif
}

void CVuInterpreter::MSUBbc(VuUnit_Base * unit, const VuInstruction inst, const int idx) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) MSUBbc: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("MSUBbc: Not implemented.");
#endif
}

void CVuInterpreter::MSUBbc_0(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	MSUBbc(unit, inst, 0);
}

void CVuInterpreter::MSUBbc_1(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	MSUBbc(unit, inst, 1);
}

void CVuInterpreter::MSUBbc_2(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	MSUBbc(unit, inst, 2);
}

void CVuInterpreter::MSUBbc_3(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	MSUBbc(unit, inst, 3);
}

void CVuInterpreter::MSUBA(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) MSUBA: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("MSUBA: Not implemented.");
#endif
}

void CVuInterpreter::MSUBAi(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) MSUBAi: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("MSUBAi: Not implemented.");
#endif
}

void CVuInterpreter::MSUBAq(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) MSUBAq: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("MSUBAq: Not implemented.");
#endif
}

void CVuInterpreter::MSUBAbc(VuUnit_Base * unit, const VuInstruction inst, const int idx) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) MSUBAbc: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("MSUBAbc: Not implemented.");
#endif
}

void CVuInterpreter::MSUBAbc_0(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	MSUBAbc(unit, inst, 0);
}

void CVuInterpreter::MSUBAbc_1(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	MSUBAbc(unit, inst, 1);
}

void CVuInterpreter::MSUBAbc_2(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	MSUBAbc(unit, inst, 2);
}

void CVuInterpreter::MSUBAbc_3(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	MSUBAbc(unit, inst, 3);
}

void CVuInterpreter::MAX(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) MAX: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("MAX: Not implemented.");
#endif
}

void CVuInterpreter::MAXi(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) MAXi: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("MAXi: Not implemented.");
#endif
}

void CVuInterpreter::MAXbc(VuUnit_Base * unit, const VuInstruction inst, const int idx) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) MAXbc: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("MAXbc: Not implemented.");
#endif
}

void CVuInterpreter::MAXbc_0(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	MAXbc(unit, inst, 0);
}

void CVuInterpreter::MAXbc_1(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	MAXbc(unit, inst, 1);
}

void CVuInterpreter::MAXbc_2(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	MAXbc(unit, inst, 2);
}

void CVuInterpreter::MAXbc_3(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	MAXbc(unit, inst, 3);
}

void CVuInterpreter::MINI(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) MINI: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("MINI: Not implemented.");
#endif
}

void CVuInterpreter::MINIi(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) MINIi: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("MINIi: Not implemented.");
#endif
}

void CVuInterpreter::MINIbc(VuUnit_Base * unit, const VuInstruction inst, const int idx) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) MINIbc: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("MINIbc: Not implemented.");
#endif
}

void CVuInterpreter::MINIbc_0(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	MINIbc(unit, inst, 0);
}

void CVuInterpreter::MINIbc_1(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	MINIbc(unit, inst, 1);
}

void CVuInterpreter::MINIbc_2(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	MINIbc(unit, inst, 2);
}

void CVuInterpreter::MINIbc_3(VuUnit_Base * unit, const VuInstruction inst) const
{
	// Call base function.
	MINIbc(unit, inst, 3);
}

void CVuInterpreter::OPMULA(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) OPMULA: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("OPMULA: Not implemented.");
#endif
}

void CVuInterpreter::OPMSUB(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) OPMSUB: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("OPMSUB: Not implemented.");
#endif
}

void CVuInterpreter::DIV(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) DIV: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("DIV: Not implemented.");
#endif
}

void CVuInterpreter::SQRT(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) SQRT: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("SQRT: Not implemented.");
#endif
}

void CVuInterpreter::RSQRT(VuUnit_Base * unit, const VuInstruction inst) const
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) RSQRT: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("RSQRT: Not implemented.");
#endif
}
