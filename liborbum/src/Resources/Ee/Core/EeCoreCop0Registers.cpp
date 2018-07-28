#include "Resources/Ee/Core/EeCoreCop0Registers.hpp"

EeCoreCop0Register_Random::EeCoreCop0Register_Random() :
    SizedWordRegister(INITIAL_VALUE)
{
}

EeCoreCop0Register_Status::EeCoreCop0Register_Status() :
    SizedWordRegister(INITIAL_VALUE),
    interrupts_masked(true),
    operating_context(MipsCoprocessor0::OperatingContext::Kernel),
    count_interrupts_enabled(false)
{
}

void EeCoreCop0Register_Status::handle_interrupts_masked_update()
{
    interrupts_masked = !((extract_field(ERL) == 0)
                          && (extract_field(EXL) == 0)
                          && (extract_field(IE) > 0)
                          && (extract_field(EIE) > 0));
}

void EeCoreCop0Register_Status::handle_operating_context_update()
{
    const uword KSU = extract_field(EeCoreCop0Register_Status::KSU);
    const uword ERL = extract_field(EeCoreCop0Register_Status::ERL);
    const uword EXL = extract_field(EeCoreCop0Register_Status::EXL);

    if (KSU == 2 && ERL == 0 && EXL == 0)
        operating_context = MipsCoprocessor0::OperatingContext::User;
    else if (KSU == 0 || ERL == 1 || EXL == 1)
        operating_context = MipsCoprocessor0::OperatingContext::Kernel;
    else if (KSU == 1 && ERL == 0 && EXL == 0)
        operating_context = MipsCoprocessor0::OperatingContext::Supervisor;
    else
        throw std::runtime_error("EE COP0 could not determine CPU operating context! Please debug.");
}

void EeCoreCop0Register_Status::handle_count_interrupt_state_update()
{
    // 0x8000 is bit IM[7].
    count_interrupts_enabled = (!interrupts_masked) && (read_uword() & 0x8000);
}

void EeCoreCop0Register_Status::write_uword(const uword value)
{
    SizedWordRegister::write_uword(value);
    handle_interrupts_masked_update();
    handle_operating_context_update();
    handle_count_interrupt_state_update(); // Depends on interrupts masked update.
}

EeCoreCop0Register_Cause::EeCoreCop0Register_Cause() :
    irq_lines{false}
{
}

void EeCoreCop0Register_Cause::clear_all_irq()
{
    for (auto& line : irq_lines)
        line = false;
}

void EeCoreCop0Register_Cause::set_irq_line(const int irq)
{
    irq_lines[irq] = true;
}

void EeCoreCop0Register_Cause::clear_irq_line(const int irq)
{
    irq_lines[irq] = false;
}

uword EeCoreCop0Register_Cause::read_uword()
{
    uword value = SizedWordRegister::read_uword();

    uword ip = 0;
    for (int i = 0; i < 8; i++)
        if (irq_lines[i])
            ip |= (1 << i);

    value = IP.insert_into(value, ip);

    // Maybe no point in writing it back...
    SizedWordRegister::write_uword(value);
    return value;
}

EeCoreCop0Register_Prid::EeCoreCop0Register_Prid() :
    SizedWordRegister(INITIAL_VALUE, true)
{
}

EeCoreCop0Register_Config::EeCoreCop0Register_Config() :
    SizedWordRegister(INITIAL_VALUE)
{
}

EeCoreCop0Register_Compare::EeCoreCop0Register_Compare() :
    cause(nullptr)
{
}

void EeCoreCop0Register_Compare::write_uword(const uword value)
{
    cause->clear_irq_line(8);
}
