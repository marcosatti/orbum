#include "Resources/Ee/Core/EeCoreR5900.hpp"

EeCoreR5900::EeCoreR5900() :
	pc(Constants::MIPS::Exceptions::Imp46::VADDRESS_EXCEPTION_BASE_V_RESET_NMI),
	zero_register(0, true),
	gpr{nullptr}
{
}