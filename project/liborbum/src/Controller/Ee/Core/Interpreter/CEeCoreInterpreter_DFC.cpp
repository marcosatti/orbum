#include "Core.hpp"
#include "Utilities/Utilities.hpp"

#include "Controller/Ee/Core/Interpreter/CEeCoreInterpreter.hpp"

#include "Resources/RResources.hpp"

void CEeCoreInterpreter::PEXT5(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = EXTEND[1-5-5-5 -> 32](Rt)
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

	uword value[NUMBER_WORDS_IN_QWORD];

	auto unpack = [&](const uhword value) -> uword
	{
		uword temp0 = ((value & 0x1F) << 3);
		uword temp1 = ((value & 0x3E0) >> 5) << 11;
		uword temp2 = ((value & 0x7C00) >> 10) << 19;
		uword temp3 = ((value & 0x8000) >> 16) << 31;
		return (temp3 | temp2 | temp1 | temp0);
	};

	value[0] = unpack(reg_source1->read_uhword(0));
	value[1] = unpack(reg_source1->read_uhword(2));
	value[2] = unpack(reg_source1->read_uhword(4));
	value[3] = unpack(reg_source1->read_uhword(6));

	reg_dest->write_uword(0, value[0]);
	reg_dest->write_uword(1, value[1]);
	reg_dest->write_uword(2, value[2]);
	reg_dest->write_uword(3, value[3]);
}

void CEeCoreInterpreter::PPAC5(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = PACK[32 -> 1-5-5-5](Rt)
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

	uhword value[NUMBER_WORDS_IN_QWORD];

	auto pack = [&](const uword value) -> uhword
	{		
		uhword temp0 = ((value & 0xF8) >> 3);
		uhword temp1 = ((value & 0xF800) >> 11) << 5;
		uhword temp2 = ((value & 0xF80000) >> 19) << 10;
		uhword temp3 = ((value & 0x80000000) >> 31) << 15;
		return (temp3 | temp2 | temp1 | temp0);
	};

	value[0] = pack(reg_source1->read_uword(0));
	value[1] = pack(reg_source1->read_uword(1));
	value[2] = pack(reg_source1->read_uword(2));
	value[3] = pack(reg_source1->read_uword(3));

	// Upper 16 bits padded with 0's.
	reg_dest->write_uword(0, static_cast<uword>(value[0]));
	reg_dest->write_uword(2, static_cast<uword>(value[1]));
	reg_dest->write_uword(4, static_cast<uword>(value[2]));
	reg_dest->write_uword(6, static_cast<uword>(value[3]));
}

void CEeCoreInterpreter::CVT_S_W(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Fd = CONVERT_AND_ROUND<sword -> f32>(Fs) (Exception on FPU unusable).
	if (handle_cop1_usable())
        return;

	auto& reg_source1 = r.ee.core.fpu.fpr[inst.rd()]; // Fs
	auto& reg_dest = r.ee.core.fpu.fpr[inst.shamt()]; // Fd

	reg_dest.write_float(static_cast<f32>(reg_source1.read_uword()));
}

void CEeCoreInterpreter::CVT_W_S(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Fd = CONVERT_AND_ROUND<f32 -> sword>(Fs) (Exception on FPU unusable). Clamping occurs if exponent is > 0x9D.
	if (handle_cop1_usable())
        return;

	auto& reg_source1 = r.ee.core.fpu.fpr[inst.rd()]; // Fs
	auto& reg_dest = r.ee.core.fpu.fpr[inst.shamt()]; // Fd

	f32 val_source1 = reg_source1.read_float();

	if (get_float_exponent(val_source1) <= 0x9D)
		reg_dest.write_uword(static_cast<uword>(val_source1));
	else if (val_source1 < 0.0F) // Clamping has occured, write either S32_MIN or S32_MAX, depending on sign.
		reg_dest.write_uword(VALUE_SWORD_MIN);
	else
		reg_dest.write_uword(VALUE_SWORD_MAX);
}
