#include "Resources/Ee/Core/EeCoreCop0Registers.hpp"

bool EeCoreCop0Register_Status::is_interrupts_masked()
{
	return !((extract_field(ERL) == 0)
		&& (extract_field(EXL) == 0)
		&& (extract_field(IE) > 0) 
		&& (extract_field(EIE) > 0));
}

void EeCoreCop0Register_Cause::clear_ip()
{
	uword temp = read_uword() & 0xFFFF00FF;
	write_uword(temp);
}

void EeCoreCop0Register_Cause::set_irq_line(const int irq)
{
	auto temp = extract_field(IP) | (1 << irq);
	insert_field(IP, temp);
}

void EeCoreCop0Register_Cause::clear_irq_line(const int irq)
{
	auto temp = (extract_field(IP) & (~(1 << irq))) & 0xFF; // 0xFF mask to strip off any other bits as a safety precaution.
	insert_field(IP, temp);
}

EeCoreCop0Register_Prid::EeCoreCop0Register_Prid() :
	SizedWordRegister(INITIAL_VALUE, true)
{
}
