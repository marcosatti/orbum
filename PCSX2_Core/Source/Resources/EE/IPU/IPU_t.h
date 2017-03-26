#pragma once

#include <memory>

class Register32_t;
class ConstantByteMemory_t;

class IPU_t
{
public:
	explicit IPU_t();

	/*
	IPU memory mapped registers. See page 21 of EE Users Manual.
	*/
	// 0x10002000
	std::shared_ptr<Register32_t>     CMD;
	std::shared_ptr<Register32_t>     CTRL;
	std::shared_ptr<Register32_t>     BP;
	std::shared_ptr<Register32_t>     TOP;
	std::shared_ptr<ConstantByteMemory_t> MEMORY_2040;
};

