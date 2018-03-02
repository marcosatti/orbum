#include "Resources/Iop/Core/IopCoreR3000.hpp"

IopCoreR3000::IopCoreR3000() :
	pc(Constants::MIPS::Exceptions::Imp0::VADDRESS_EXCEPTION_BASE_V_RESET_NMI),
	zero_register(0, true),
	gpr{nullptr}
{
}