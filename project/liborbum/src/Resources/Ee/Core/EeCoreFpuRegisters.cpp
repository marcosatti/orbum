#include "Common/Types/FpuFlags.hpp"

#include "Resources/Ee/Core/EeCoreFpuRegisters.hpp"

EeCoreFpuRegister_Irr::EeCoreFpuRegister_Irr() :
	SizedWordRegister(INITIAL_VALUE, true)
{
}

void EeCoreFpuRegister_Csr::set_u_flag_sticky(const uword value)
{
	uword su = extract_field(SU);
	insert_field(SU, su | value);
	insert_field(U, value);
}

void EeCoreFpuRegister_Csr::set_o_flag_sticky(const uword value)
{
	uword so = extract_field(SO);
	insert_field(SO, so | value);
	insert_field(O, value);
}

void EeCoreFpuRegister_Csr::set_d_flag_sticky(const uword value)
{
	uword sd = extract_field(SD);
	insert_field(SD, sd | value);
	insert_field(D, value);
}

void EeCoreFpuRegister_Csr::set_i_flag_sticky(const uword value)
{
	uword si = extract_field(SI);
	insert_field(SI, si | value);
	insert_field(I, value);
}

void EeCoreFpuRegister_Csr::update_result_flags(const FpuFlags & flags)
{
	set_u_flag_sticky(flags.UF ? 1 : 0);
	set_o_flag_sticky(flags.OF ? 1 : 0);
}

void EeCoreFpuRegister_Csr::clear_flags()
{
	insert_field(U, 0);
	insert_field(O, 0);
	insert_field(D, 0);
	insert_field(I, 0);
}
