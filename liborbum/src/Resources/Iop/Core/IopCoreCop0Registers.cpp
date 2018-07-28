#include "Resources/Iop/Core/IopCoreCop0Registers.hpp"

#include "Common/Types/Register/SizedWordRegister.hpp"

IopCoreCop0Register_Status::IopCoreCop0Register_Status() :
    SizedWordRegister(INITIAL_VALUE),
    interrupts_masked(true),
    operating_context(MipsCoprocessor0::OperatingContext::Kernel)
{
}

void IopCoreCop0Register_Status::push_exception_stack()
{
    // New status = shift (KU|IP)(c|p) bits left by 2 then make (KU|IP)c bits = 0.
    uword value = read_uword();
    write_uword((value & (~0x3F)) | ((value & 0xF) << 2));
}

void IopCoreCop0Register_Status::pop_exception_stack()
{
    // New status = shift (KU|IP)(p|o) bits right by 2. Leave old bits unchanged after.
    uword value = read_uword();
    write_uword((value & (~0xF)) | ((value & 0x3C) >> 2));
}

void IopCoreCop0Register_Status::handle_interrupts_masked_update()
{
    interrupts_masked = !(extract_field(IEC) > 0);
}

void IopCoreCop0Register_Status::handle_operating_context_update()
{
    const uword KUc = extract_field(IopCoreCop0Register_Status::KUC);

    if (KUc == 1)
        operating_context = MipsCoprocessor0::OperatingContext::User;
    else if (KUc == 0)
        operating_context = MipsCoprocessor0::OperatingContext::Kernel;
    else
        throw std::runtime_error("IOP COP0 could not determine CPU operating context! Please debug.");
}

void IopCoreCop0Register_Status::write_uword(const uword value)
{
    SizedWordRegister::write_uword(value);
    handle_interrupts_masked_update();
    handle_operating_context_update();
}

IopCoreCop0Register_Cause::IopCoreCop0Register_Cause() :
    irq_lines{false}
{
}

void IopCoreCop0Register_Cause::clear_all_irq()
{
    for (auto& line : irq_lines)
        line = false;
}

void IopCoreCop0Register_Cause::set_irq_line(const int irq)
{
    irq_lines[irq] = true;
}

void IopCoreCop0Register_Cause::clear_irq_line(const int irq)
{
    irq_lines[irq] = false;
}

uword IopCoreCop0Register_Cause::read_uword()
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

IopCoreCop0Register_Prid::IopCoreCop0Register_Prid() :
    SizedWordRegister(INITIAL_VALUE, true)
{
}
