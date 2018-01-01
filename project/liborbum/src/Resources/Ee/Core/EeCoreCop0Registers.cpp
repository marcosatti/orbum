#include "Resources/Ee/Core/EeCoreCop0Registers.hpp"

EeCoreCop0Register_Random::EeCoreCop0Register_Random() :
	SizedWordRegister(INITIAL_VALUE)
{
}

EeCoreCop0Register_Status::EeCoreCop0Register_Status() :
	SizedWordRegister(INITIAL_VALUE)
{
}

bool EeCoreCop0Register_Status::is_interrupts_masked()
{
	return !((extract_field(ERL) == 0)
		&& (extract_field(EXL) == 0)
		&& (extract_field(IE) > 0) 
		&& (extract_field(EIE) > 0));
}

EeCoreCop0Register_Cause::EeCoreCop0Register_Cause() :
	irq_lines{ false }
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