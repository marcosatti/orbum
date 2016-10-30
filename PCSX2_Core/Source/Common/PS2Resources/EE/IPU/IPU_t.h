#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"

class Register32_t;
class DeadMMemory_t;

class IPU_t : public PS2ResourcesSubobject
{
public:
	explicit IPU_t(const PS2Resources_t *const PS2Resources);

	/*
	IPU memory mapped registers. See page 21 of EE Users Manual.
	*/
	// 0x10002000
	std::shared_ptr<Register32_t>  IPU_REGISTER_CMD;
	std::shared_ptr<Register32_t>  IPU_REGISTER_CTRL;
	std::shared_ptr<Register32_t>  IPU_REGISTER_BP;
	std::shared_ptr<Register32_t>  IPU_REGISTER_TOP;
	std::shared_ptr<DeadMMemory_t> IPU_MEMORY_2040;
};

