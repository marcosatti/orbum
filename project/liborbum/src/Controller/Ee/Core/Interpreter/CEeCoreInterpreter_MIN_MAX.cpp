#include <algorithm>

#include "Core.hpp"
#include "Utilities/Utilities.hpp"

#include "Controller/Ee/Core/Interpreter/CEeCoreInterpreter.hpp"

#include "Resources/RResources.hpp"

void CEeCoreInterpreter::PMAXH(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = MAX(Rs, Rt)
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto val_source1 = static_cast<shword>(reg_source1->read_uhword(i));
		auto val_source2 = static_cast<shword>(reg_source2->read_uhword(i));
		shword result = std::max(val_source2, val_source1); // Format parameters this way as std::max returns parameter 0 if they are equal, and value in Rt is returned according to docs if they are equal.
		reg_dest->write_uhword(i, result);
	}
}

void CEeCoreInterpreter::PMAXW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = MAX(Rs, Rt)
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
	{
		auto val_source1 = static_cast<sword>(reg_source1->read_uword(i));
		auto val_source2 = static_cast<sword>(reg_source2->read_uword(i));
		sword result = std::max(val_source2, val_source1); // Format parameters this way as std::max returns parameter 0 if they are equal, and value in Rt is returned according to docs if they are equal.
		reg_dest->write_uword(i, result);
	}
}

void CEeCoreInterpreter::PMINH(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = MIN(Rs, Rt)
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto val_source1 = static_cast<shword>(reg_source1->read_uhword(i));
		auto val_source2 = static_cast<shword>(reg_source2->read_uhword(i));
		shword result = std::min(val_source1, val_source2); // Format parameters this way as std::min returns parameter 0 if they are equal, and value in Rs is returned according to docs if they are equal.
		reg_dest->write_uhword(i, result);
	}
}

void CEeCoreInterpreter::PMINW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = MIN(Rs, Rt)
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
	{
		auto val_source1 = static_cast<sword>(reg_source1->read_uword(i));
		auto val_source2 = static_cast<sword>(reg_source2->read_uword(i));
		sword result = std::min(val_source1, val_source2); // Format parameters this way as std::min returns parameter 0 if they are equal, and value in Rs is returned according to docs if they are equal.
		reg_dest->write_uword(i, result);
	}
}

void CEeCoreInterpreter::MAX_S(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Fd = MAX(Fs, Ft), flags set.
	// No Exceptions generated, except for coprocessor unavailable.
	if (handle_cop1_usable())
		return;

	auto& reg_source1 = r.ee.core.fpu.fpr[inst.rd()]; // Fs
	auto& reg_source2 = r.ee.core.fpu.fpr[inst.rt()]; // Ft
	auto& reg_dest = r.ee.core.fpu.fpr[inst.shamt()]; // Fd
	auto& csr = r.ee.core.fpu.csr; // FCR[31] aka control status register.

	csr.clear_flags();
	f32 val_source1 = reg_source1.read_float();
	f32 val_source2 = reg_source2.read_float();
	f32 result = (val_source1 >= val_source2) ? val_source1 : val_source2; // Dont have to check for valid float as should already be valid from before.
	reg_dest.write_float(result);
}

void CEeCoreInterpreter::MIN_S(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Fd = MIN(Fs, Ft), flags set.
	// No Exceptions generated, except for coprocessor unavailable.
	if (handle_cop1_usable())
		return;

	auto& reg_source1 = r.ee.core.fpu.fpr[inst.rd()]; // Fs
	auto& reg_source2 = r.ee.core.fpu.fpr[inst.rt()]; // Ft
	auto& reg_dest = r.ee.core.fpu.fpr[inst.shamt()]; // Fd
	auto& csr = r.ee.core.fpu.csr; // FCR[31] aka control status register.

	csr.clear_flags();
	f32 val_source1 = reg_source1.read_float();
	f32 val_source2 = reg_source2.read_float();
	f32 result = (val_source1 <= val_source2) ? val_source1 : val_source2; // Dont have to check for valid float as should already be valid from before.
	reg_dest.write_float(result);
}

