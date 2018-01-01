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

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i += 2)
	{
		uhword packed_value = reg_source1->read_uhword(i);
		uword temp0 = ((packed_value & 0x1F) << 3);
		uword temp1 = ((packed_value & 0x3E0) >> 5) << 11;
		uword temp2 = ((packed_value & 0x7C00) >> 10) << 19;
		uword temp3 = ((packed_value & 0x8000) >> 16) << 31;
		uword extended_value = temp3 | temp2 | temp1 | temp0;
		reg_dest->write_uword(i / 2, extended_value);
	}
}

void CEeCoreInterpreter::PPAC5(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = PACK[32 -> 1-5-5-5](Rt)
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
	{
		uword extended_value = reg_source1->read_uword(i);
		ubyte temp0 = ((extended_value & 0xF8) >> 3);
		ubyte temp1 = ((extended_value & 0xF800) >> 11) << 5;
		ubyte temp2 = ((extended_value & 0xF80000) >> 19) << 10;
		ubyte temp3 = ((extended_value & 0x80000000) >> 31) << 15;
		uword packed_value = 0x0 | temp3 | temp2 | temp1 | temp0; // Slightly different to the above instruction - need to make sure the empty space is packed with 0's.
		reg_dest->write_uword(i, packed_value);
	}
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
