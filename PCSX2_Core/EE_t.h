#pragma once

#include <memory>

#include "Globals.h"
#include "EECore_t.h"
#include "MainMemory_t.h"

/*
TODO: finish writing documentation.
EE_t delares the EE structure of the PS2.
It encompasses everything seen on the diagram on page 22 of the EE Overview Manual.
*/
class EE_t
{
public:
	// The EECore structure.
	PS2::EE::EECore_t EECore;
};