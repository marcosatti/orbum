#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/GS/GS_t.h"
#include "Common/PS2Resources/IOP/IOP_t.h"
#include "Common/PS2Resources/Clock/Clock_t.h"

PS2Resources_t::PS2Resources_t() :
	EE(std::make_shared<EE_t>(this)),
	GS(std::make_shared<GS_t>(this)),
	IOP(std::make_shared<IOP_t>(this)),
	Clock(std::make_shared<Clock_t>())
{
}
