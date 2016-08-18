#include "stdafx.h"
#include "LinkRegister128_t.h"
#include "Common/PS2 Resources/PS2Resources_t.h"

void LinkRegister128_t::setLinkAddress()
{
	writeDwordU(0, static_cast<u64>(getRootResources()->EE->EECore->R5900->PC->getPCValue() + 8));
}