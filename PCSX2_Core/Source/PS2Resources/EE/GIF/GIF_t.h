#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"

class Register32_t;
class ZeroMemory_t;

class GIF_t : public PS2ResourcesSubobject
{
public:
	explicit GIF_t(const PS2Resources_t *const PS2Resources);

	/*
	GIF memory mapped registers. See page 21 of EE Users Manual.
	*/
	std::shared_ptr<Register32_t>  REGISTER_CTRL;
	std::shared_ptr<Register32_t>  REGISTER_MODE;
	std::shared_ptr<Register32_t>  REGISTER_STAT;
	std::shared_ptr<ZeroMemory_t> MEMORY_3030;
	std::shared_ptr<Register32_t>  REGISTER_TAG0;
	std::shared_ptr<Register32_t>  REGISTER_TAG1;
	std::shared_ptr<Register32_t>  REGISTER_TAG2;
	std::shared_ptr<Register32_t>  REGISTER_TAG3;
	std::shared_ptr<Register32_t>  REGISTER_CNT;
	std::shared_ptr<Register32_t>  REGISTER_P3CNT;
	std::shared_ptr<Register32_t>  REGISTER_P3TAG;
	std::shared_ptr<ZeroMemory_t> MEMORY_30b0;
};

