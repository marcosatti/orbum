#pragma once

#include <memory>

#include "Common/PS2 Resources/EE/EECore/EECore_t.h"
#include "Common/Interfaces/PS2ResourcesSubobject.h"

/*
TODO: finish writing documentation.
EE_t delares the EE structure of the PS2.
It encompasses everything seen on the diagram on page 22 of the EE Overview Manual.
*/
class EE_t : public PS2ResourcesSubobject
{
public:
	explicit EE_t(const PS2Resources_t *const PS2Resources) :
		PS2ResourcesSubobject(PS2Resources)
	{
	}

	// The EECore structure.
	std::shared_ptr<EECore_t> EECore = std::make_shared<EECore_t>(getRootResources());
};