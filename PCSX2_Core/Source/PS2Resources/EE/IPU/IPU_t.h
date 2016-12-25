#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubcategory.h"

class Register32_t;
class ConstantMemory_t;

class IPU_t : public PS2ResourcesSubcategory
{
public:
	explicit IPU_t(const PS2Resources_t * PS2Resources);

	/*
	IPU memory mapped registers. See page 21 of EE Users Manual.
	*/
	// 0x10002000
	std::shared_ptr<Register32_t>     CMD;
	std::shared_ptr<Register32_t>     CTRL;
	std::shared_ptr<Register32_t>     BP;
	std::shared_ptr<Register32_t>     TOP;
	std::shared_ptr<ConstantMemory_t> MEMORY_2040;
};

