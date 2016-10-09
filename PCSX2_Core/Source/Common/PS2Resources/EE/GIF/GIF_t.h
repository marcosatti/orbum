#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"

class MappedMemory32_t;
class DeadMMemory_t;

class GIF_t : public PS2ResourcesSubobject
{
public:
	explicit GIF_t(const PS2Resources_t *const PS2Resources);

	/*
	GIF memory mapped registers. See page 21 of EE Users Manual.
	*/
	// 0x10003000
	std::shared_ptr<MappedMemory32_t> GIF_REGISTER_CTRL;
	std::shared_ptr<MappedMemory32_t> GIF_REGISTER_MODE;
	std::shared_ptr<MappedMemory32_t> GIF_REGISTER_STAT;
	std::shared_ptr<DeadMMemory_t>    GIF_REGISTER_3030;
	std::shared_ptr<MappedMemory32_t> GIF_REGISTER_TAG0;
	std::shared_ptr<MappedMemory32_t> GIF_REGISTER_TAG1;
	std::shared_ptr<MappedMemory32_t> GIF_REGISTER_TAG2;
	std::shared_ptr<MappedMemory32_t> GIF_REGISTER_TAG3;
	std::shared_ptr<MappedMemory32_t> GIF_REGISTER_CNT;
	std::shared_ptr<MappedMemory32_t> GIF_REGISTER_P3CNT;
	std::shared_ptr<MappedMemory32_t> GIF_REGISTER_P3TAG;
	std::shared_ptr<DeadMMemory_t>    GIF_REGISTER_30b0;
};

