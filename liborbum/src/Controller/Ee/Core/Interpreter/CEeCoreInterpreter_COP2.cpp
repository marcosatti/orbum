#include <boost/format.hpp>

#include "Core.hpp"
#include "Utilities/Utilities.hpp"

#include "Controller/Ee/Vpu/Vu/Interpreter/CVuInterpreter.hpp"
#include "Controller/Ee/Core/Interpreter/CEeCoreInterpreter.hpp"

#include "Resources/RResources.hpp"
#include "Resources/Ee/Vpu/Vu/VuInstruction.hpp"

void CEeCoreInterpreter::QMFC2(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// GPR = VU0.vf. Coprocessor unusable exception.
	if (!handle_cop2_usable())
        return;

	// Check for the interlock bit.
	if (inst.i())
	{
		throw std::runtime_error("COP2 (VU0) interlock bit set, but not implemented");
	}

	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source1 = r.ee.vpu.vu.unit_0.vf[inst.rd()];

	reg_dest.write_udword(0, reg_source1.read_udword(0));
	reg_dest.write_udword(1, reg_source1.read_udword(1));
}

void CEeCoreInterpreter::QMTC2(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// VU0.vf = GPR. Coprocessor unusable exception.
	if (!handle_cop2_usable())
        return;

	// Check for the interlock bit.
	if (inst.i())
	{
		throw std::runtime_error("COP2 (VU0) interlock bit set, but not implemented");
	}

	auto& reg_dest = r.ee.vpu.vu.unit_0.vf[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];

	reg_dest.write_udword(0, reg_source1.read_udword(0));
	reg_dest.write_udword(1, reg_source1.read_udword(1));
}

void CEeCoreInterpreter::CFC2(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	if (!handle_cop2_usable())
        return;

	// Check for the interlock bit.
	if (inst.i())
	{
		throw std::runtime_error("COP2 (VU0) interlock bit set, but not implemented");
	}

	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source1 = r.ee.vpu.vu.unit_0.ccr[inst.rd()];

	reg_dest.write_udword(0, static_cast<sdword>(reg_source1->read_uword()));
}

void CEeCoreInterpreter::CTC2(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	if (!handle_cop2_usable())
        return;

	// Check for the interlock bit.
	if (inst.i())
	{
		throw std::runtime_error("COP2 (VU0) interlock bit set, but not implemented");
	}

	auto& reg_dest = r.ee.vpu.vu.unit_0.ccr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];

	reg_dest->write_uword(static_cast<uword>(reg_source1.read_uword(0)));
}

void CEeCoreInterpreter::BC2F(const EeCoreInstruction inst)
{
	if (!handle_cop2_usable())
        return;

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) BC2F: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("BC2F: Not implemented.");
#endif
}

void CEeCoreInterpreter::BC2FL(const EeCoreInstruction inst)
{
	if (!handle_cop2_usable())
        return;

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) BC2FL: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("BC2FL: Not implemented.");
#endif
}

void CEeCoreInterpreter::BC2T(const EeCoreInstruction inst)
{
	if (!handle_cop2_usable())
        return;

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) BC2T: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("BC2T: Not implemented.");
#endif
}

void CEeCoreInterpreter::BC2TL(const EeCoreInstruction inst)
{
	if (!handle_cop2_usable())
        return;

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) BC2TL: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("BC2TL: Not implemented.");
#endif
}

void CEeCoreInterpreter::VCALLMS(const EeCoreInstruction inst)
{
	if (!handle_cop2_usable())
		return;

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) BC2TL: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("BC2TL: Not implemented.");
#endif
}

void CEeCoreInterpreter::VCALLMSR(const EeCoreInstruction inst)
{
	if (!handle_cop2_usable())
		return;

	// TODO: Implement.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) BC2TL: Not implemented.") % __FILENAME__ % __LINE__;
#else
	throw std::runtime_error("BC2TL: Not implemented.");
#endif
}

void CEeCoreInterpreter::VABS(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.ABS(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VADD(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.ADD(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VADDi(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.ADDi(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VADDq(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.ADDq(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VADDbc_0(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.ADDbc_0(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VADDbc_1(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.ADDbc_1(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VADDbc_2(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.ADDbc_2(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VADDbc_3(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.ADDbc_3(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VADDA(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.ADDA(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VADDAi(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.ADDAi(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VADDAq(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.ADDAq(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VADDAbc_0(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.ADDAbc_0(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VADDAbc_1(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.ADDAbc_1(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VADDAbc_2(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.ADDAbc_2(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VADDAbc_3(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.ADDAbc_3(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VSUB(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.SUB(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VSUBi(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.SUBi(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VSUBq(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.SUBq(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VSUBbc_0(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.SUBbc_0(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VSUBbc_1(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.SUBbc_1(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VSUBbc_2(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.SUBbc_2(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VSUBbc_3(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.SUBbc_3(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VSUBA(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.SUBA(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VSUBAi(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.SUBAi(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VSUBAq(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.SUBAq(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VSUBAbc_0(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.SUBAbc_0(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VSUBAbc_1(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.SUBAbc_1(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VSUBAbc_2(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.SUBAbc_2(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VSUBAbc_3(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.SUBAbc_3(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMUL(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MUL(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMULi(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MULi(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMULq(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MULq(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMULbc_0(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MULbc_0(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMULbc_1(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MULbc_1(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMULbc_2(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MULbc_2(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMULbc_3(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MULbc_3(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMULA(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MULA(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMULAi(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MULAi(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMULAq(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MULAq(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMULAbc_0(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MULAbc_0(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMULAbc_1(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MULAbc_1(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMULAbc_2(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MULAbc_2(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMULAbc_3(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MULAbc_3(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMADD(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MADD(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMADDi(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MADDi(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMADDq(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MADDq(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMADDbc_0(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MADDbc_0(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMADDbc_1(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MADDbc_1(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMADDbc_2(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MADDbc_2(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMADDbc_3(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MADDbc_3(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMADDA(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MADDA(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMADDAi(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MADDAi(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMADDAq(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MADDAq(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMADDAbc_0(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MADDAbc_0(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMADDAbc_1(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MADDAbc_1(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMADDAbc_2(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MADDAbc_2(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMADDAbc_3(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MADDAbc_3(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMSUB(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MSUB(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMSUBi(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MSUBi(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMSUBq(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MSUBq(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMSUBbc_0(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MSUBbc_0(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMSUBbc_1(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MSUBbc_1(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMSUBbc_2(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MSUBbc_2(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMSUBbc_3(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MSUBbc_3(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMSUBA(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MSUBA(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMSUBAi(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MSUBAi(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMSUBAq(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MSUBAq(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMSUBAbc_0(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MSUBAbc_0(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMSUBAbc_1(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MSUBAbc_1(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMSUBAbc_2(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MSUBAbc_2(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMSUBAbc_3(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MSUBAbc_3(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMAX(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MAX(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMAXi(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MAXi(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMAXbc_0(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MAXbc_0(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMAXbc_1(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MAXbc_1(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMAXbc_2(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MAXbc_2(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMAXbc_3(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MAXbc_3(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMINI(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MINI(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMINIi(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MINIi(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMINIbc_0(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MINIbc_0(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMINIbc_1(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MINIbc_1(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMINIbc_2(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MINIbc_2(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMINIbc_3(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MINIbc_3(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VOPMULA(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.OPMULA(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VOPMSUB(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.OPMSUB(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VNOP(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.NOP(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VFTOI0(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.FTOI0(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VFTOI4(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.FTOI4(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VFTOI12(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.FTOI12(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VFTOI15(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.FTOI15(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VITOF0(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.ITOF0(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VITOF4(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.ITOF4(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VITOF12(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.ITOF12(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VITOF15(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.ITOF15(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VCLIP(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.CLIP(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VDIV(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.DIV(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VSQRT(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.SQRT(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VRSQRT(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.RSQRT(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VIADD(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.IADD(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VIADDI(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.IADDI(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VIAND(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.IAND(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VIOR(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.IOR(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VISUB(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.ISUB(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMOVE(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MOVE(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMFIR(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MFIR(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMTIR(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MTIR(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VMR32(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.MR32(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VLQD(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.LQD(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VLQI(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.LQI(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VSQD(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.SQD(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VSQI(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.SQI(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VILWR(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.ILWR(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VISWR(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.ISWR(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VRINIT(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.RINIT(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VRGET(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.RGET(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VRNEXT(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.RNEXT(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VRXOR(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.RXOR(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

void CEeCoreInterpreter::VWAITQ(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();

	if (!handle_cop2_usable())
        return;

	// Delegate to the VU0 system.
	c_vu_interpreter.WAITQ(&r.ee.vpu.vu.unit_0, VuInstruction(inst.value));
}

