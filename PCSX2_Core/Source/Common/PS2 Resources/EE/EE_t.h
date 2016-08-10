#pragma once

#include <memory>

#include "Common/PS2 Resources/EE/EECore/EECore_t.h"

/*
TODO: finish writing documentation.
EE_t delares the EE structure of the PS2.
It encompasses everything seen on the diagram on page 22 of the EE Overview Manual.
*/
class EE_t
{
public:
	// The EECore structure.
	std::shared_ptr<EECore_t> EECore = std::make_shared<EECore_t>();
};