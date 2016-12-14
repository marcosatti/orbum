#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"

class Register32_t;

/*
INTC resources.
*/
class IOPIntc_t : public PS2ResourcesSubobject
{
public:
	explicit IOPIntc_t(const PS2Resources_t *const PS2Resources);
 
	std::shared_ptr<Register32_t> STAT; // Register "STAT" @ 0x1F801070 -> 0x1F801073.
	std::shared_ptr<Register32_t> MASK; // Register "MASK" @ 0x1F801074 -> 0x1F801077.
	std::shared_ptr<Register32_t> CTRL; // Register "CTRL" @ 0x1F801078 -> 0x1F80107B.
};

