#include "stdafx.h"

#include "Common/PS2Resources/EE/EECore/R5900/Types/LinkRegister128_t.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/EE/EECore/EECore_t.h"
#include "Common/PS2Resources/EE/EECore/R5900/R5900_t.h"
#include "Common/PS2Resources/EE/EECore/R5900/Types/PCRegister32_t.h"

void LinkRegister128_t::setLinkAddress()
{
	writeDwordU(0, static_cast<u64>(getRootResources()->EE->EECore->R5900->PC->getPCValue() + 8));
}