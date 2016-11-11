#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"

class Register32_t;
class DeadMemory_t;

class IPU_t : public PS2ResourcesSubobject
{
public:
	explicit IPU_t(const PS2Resources_t *const PS2Resources);

	/*
	IPU memory mapped registers. See page 21 of EE Users Manual.
	*/
	// 0x10002000
	std::shared_ptr<Register32_t> REGISTER_CMD;
	std::shared_ptr<Register32_t> REGISTER_CTRL;
	std::shared_ptr<Register32_t> REGISTER_BP;
	std::shared_ptr<Register32_t> REGISTER_TOP;
	std::shared_ptr<DeadMemory_t> MEMORY_2040;
};

