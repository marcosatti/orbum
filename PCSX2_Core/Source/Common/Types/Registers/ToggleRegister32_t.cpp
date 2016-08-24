#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/Types/Registers/ToggleRegister32_t.h"

void ToggleRegister32_t::setToggle()
{
	writeWordU(static_cast<u32>(true));
}

bool ToggleRegister32_t::getToggle()
{
	bool temp = static_cast<bool>(readWordU());
	writeWordU(static_cast<u32>(false));
	return temp;
}
