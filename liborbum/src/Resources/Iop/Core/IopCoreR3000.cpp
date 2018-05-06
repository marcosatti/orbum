#include "Resources/Iop/Core/IopCoreR3000.hpp"

IopCoreR3000::IopCoreR3000() :
	pc(Constants::MIPS::Exceptions::Imp0::VADDRESS_EXCEPTION_BASE_V_RESET_NMI),
	gpr{SizedWordRegister(0, true), SizedWordRegister(), SizedWordRegister(), SizedWordRegister(),
	    SizedWordRegister(),        SizedWordRegister(), SizedWordRegister(), SizedWordRegister(),
		SizedWordRegister(),        SizedWordRegister(), SizedWordRegister(), SizedWordRegister(),
		SizedWordRegister(),        SizedWordRegister(), SizedWordRegister(), SizedWordRegister(),
		SizedWordRegister(),        SizedWordRegister(), SizedWordRegister(), SizedWordRegister(),
		SizedWordRegister(),        SizedWordRegister(), SizedWordRegister(), SizedWordRegister(),
		SizedWordRegister(),        SizedWordRegister(), SizedWordRegister(), SizedWordRegister(),
		SizedWordRegister(),        SizedWordRegister(), SizedWordRegister(), SizedWordRegister()}
{
}