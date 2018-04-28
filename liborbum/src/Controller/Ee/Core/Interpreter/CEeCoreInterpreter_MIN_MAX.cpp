#include <algorithm>

#include "Core.hpp"
#include "Utilities/Utilities.hpp"

#include "Controller/Ee/Core/Interpreter/CEeCoreInterpreter.hpp"

#include "Resources/RResources.hpp"

void CEeCoreInterpreter::PMAXH(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = MAX(Rs, Rt)
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

    uhword value[NUMBER_HWORDS_IN_QWORD];

    auto max = [](const uhword a, const uhword b) -> uhword
    {
        shword sa = static_cast<shword>(a);
        shword sb = static_cast<shword>(b);
        return static_cast<uhword>(std::max(a, b));
    };

    for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
        value[i] = max(reg_source1.read_uhword(i), reg_source2.read_uhword(i));

    for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
        reg_dest.write_uhword(i, value[i]);
}

void CEeCoreInterpreter::PMAXW(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = MAX(Rs, Rt)
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

    uword value[NUMBER_WORDS_IN_QWORD];

    auto max = [](const uword a, const uword b) -> uword
    {
        sword sa = static_cast<sword>(a);
        sword sb = static_cast<sword>(b);
        return static_cast<uword>(std::max(a, b));
    };

    for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
        value[i] = max(reg_source1.read_uword(i), reg_source2.read_uword(i));

    for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
        reg_dest.write_uword(i, value[i]);
}

void CEeCoreInterpreter::PMINH(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = MIN(Rs, Rt)
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

    uhword value[NUMBER_HWORDS_IN_QWORD];

    auto max = [](const uhword a, const uhword b) -> uhword
    {
        shword sa = static_cast<shword>(a);
        shword sb = static_cast<shword>(b);
        return static_cast<uhword>(std::min(a, b));
    };

    for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
        value[i] = max(reg_source1.read_uhword(i), reg_source2.read_uhword(i));

    for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
        reg_dest.write_uhword(i, value[i]);
}

void CEeCoreInterpreter::PMINW(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = MIN(Rs, Rt)
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

    uword value[NUMBER_WORDS_IN_QWORD];

    auto max = [](const uword a, const uword b) -> uword
    {
        sword sa = static_cast<sword>(a);
        sword sb = static_cast<sword>(b);
        return static_cast<uword>(std::min(a, b));
    };

    for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
        value[i] = max(reg_source1.read_uword(i), reg_source2.read_uword(i));

    for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
        reg_dest.write_uword(i, value[i]);
}

void CEeCoreInterpreter::MAX_S(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Fd = MAX(Fs, Ft), flags set.
	// No Exceptions generated, except for coprocessor unavailable.
	if (!handle_cop1_usable())
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

void CEeCoreInterpreter::MIN_S(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Fd = MIN(Fs, Ft), flags set.
	// No Exceptions generated, except for coprocessor unavailable.
	if (!handle_cop1_usable())
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

