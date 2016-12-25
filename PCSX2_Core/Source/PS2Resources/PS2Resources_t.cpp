#include "stdafx.h"

#include <memory>

#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/Clock/Clock_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/GS/GS_t.h"
#include "PS2Resources/IOP/IOP_t.h"
#include "PS2Resources/Common/Common_t.h"

PS2Resources_t::PS2Resources_t() :
	Clock(std::make_shared<Clock_t>(this)),
	GS(std::make_shared<GS_t>(this)),
	EE(std::make_shared<EE_t>(this)),
	IOP(std::make_shared<IOP_t>(this)),
	Common(std::make_shared<Common_t>(this))
{
	postResourcesInit();
}

void PS2Resources_t::postResourcesInit() const
{
	Clock->postResourcesInit();
	GS->postResourcesInit();
	EE->postResourcesInit();
	IOP->postResourcesInit();
	Common->postResourcesInit();
}
