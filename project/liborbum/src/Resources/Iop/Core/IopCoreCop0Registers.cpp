#include "Common/Types/Register/SizedWordRegister.hpp"

#include "Resources/Iop/Core/IopCoreCop0Registers.hpp"


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

void IopCoreCop0Register_Cause::clear_ip()
{
	insert_field(IP, 0);
}

void IopCoreCop0Register_Cause::set_irq_line(const int irq)
{
	auto temp = extract_field(IP) | (1 << irq);
	insert_field(IP, temp);
}

void IopCoreCop0Register_Cause::clear_irq_line(const int irq)
{
	auto temp = (extract_field(IP) & (~(1 << irq))) & 0xFF; // 0xFF mask to strip off any other bits as a safety precaution.
	insert_field(IP, temp);
}

IopCoreCop0Register_Prid::IopCoreCop0Register_Prid() :
	SizedWordRegister(INITIAL_VALUE, true)
{
}
