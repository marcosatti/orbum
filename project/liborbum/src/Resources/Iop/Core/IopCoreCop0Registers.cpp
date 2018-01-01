#include "Common/Types/Register/SizedWordRegister.hpp"

#include "Resources/Iop/Core/IopCoreCop0Registers.hpp"

IopCoreCop0Register_Status::IopCoreCop0Register_Status() :
	SizedWordRegister(INITIAL_VALUE)
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

bool IopCoreCop0Register_Status::is_exceptions_masked()
{
	return false;
}

bool IopCoreCop0Register_Status::is_interrupts_masked()
{
	return !(extract_field(IEC) > 0);
}

bool IopCoreCop0Register_Status::is_irq_masked(const int irq)
{
	return !((extract_field(IM) & (1 << irq)) > 0);
}

IopCoreCop0Register_Cause::IopCoreCop0Register_Cause() :
	irq_lines{ false }
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
