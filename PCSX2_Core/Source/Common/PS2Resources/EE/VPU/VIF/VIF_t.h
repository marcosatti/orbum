#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"

class Register32_t;
class DeadMMemory_t;

class VIF_t : public PS2ResourcesSubobject
{
public:
	explicit VIF_t(const PS2Resources_t *const PS2Resources);

	/*
	VIF memory mapped registers. See page 22 of EE Users Manual.
	*/
	// 0x10003800 (VIF0).
	std::shared_ptr<Register32_t>  VIF0_REGISTER_STAT;
	std::shared_ptr<Register32_t>  VIF0_REGISTER_FBRST;
	std::shared_ptr<Register32_t>  VIF0_REGISTER_ERR;
	std::shared_ptr<Register32_t>  VIF0_REGISTER_MARK;
	std::shared_ptr<Register32_t>  VIF0_REGISTER_CYCLE;
	std::shared_ptr<Register32_t>  VIF0_REGISTER_MODE;
	std::shared_ptr<Register32_t>  VIF0_REGISTER_NUM;
	std::shared_ptr<Register32_t>  VIF0_REGISTER_MASK;
	std::shared_ptr<Register32_t>  VIF0_REGISTER_CODE;
	std::shared_ptr<Register32_t>  VIF0_REGISTER_ITOPS;
	std::shared_ptr<DeadMMemory_t> VIF0_MEMORY_38a0;
	std::shared_ptr<DeadMMemory_t> VIF0_MEMORY_38b0;
	std::shared_ptr<DeadMMemory_t> VIF0_MEMORY_38c0;
	std::shared_ptr<Register32_t>  VIF0_REGISTER_ITOP;
	std::shared_ptr<DeadMMemory_t> VIF0_MEMORY_38e0;
	std::shared_ptr<DeadMMemory_t> VIF0_MEMORY_38f0;
	std::shared_ptr<Register32_t>  VIF0_REGISTER_R0;
	std::shared_ptr<Register32_t>  VIF0_REGISTER_R1;
	std::shared_ptr<Register32_t>  VIF0_REGISTER_R2;
	std::shared_ptr<Register32_t>  VIF0_REGISTER_R3;
	std::shared_ptr<Register32_t>  VIF0_REGISTER_C0;
	std::shared_ptr<Register32_t>  VIF0_REGISTER_C1;
	std::shared_ptr<Register32_t>  VIF0_REGISTER_C2;
	std::shared_ptr<Register32_t>  VIF0_REGISTER_C3;
	std::shared_ptr<DeadMMemory_t> VIF0_MEMORY_3980;

	// 0x10003E00 (VIF1).
	std::shared_ptr<Register32_t>  VIF1_REGISTER_STAT;
	std::shared_ptr<Register32_t>  VIF1_REGISTER_FBRST;
	std::shared_ptr<Register32_t>  VIF1_REGISTER_ERR;
	std::shared_ptr<Register32_t>  VIF1_REGISTER_MARK;
	std::shared_ptr<Register32_t>  VIF1_REGISTER_CYCLE;
	std::shared_ptr<Register32_t>  VIF1_REGISTER_MODE;
	std::shared_ptr<Register32_t>  VIF1_REGISTER_NUM;
	std::shared_ptr<Register32_t>  VIF1_REGISTER_MASK;
	std::shared_ptr<Register32_t>  VIF1_REGISTER_CODE;
	std::shared_ptr<Register32_t>  VIF1_REGISTER_ITOPS;
	std::shared_ptr<Register32_t>  VIF1_REGISTER_BASE;
	std::shared_ptr<Register32_t>  VIF1_REGISTER_OFST;
	std::shared_ptr<Register32_t>  VIF1_REGISTER_TOPS;
	std::shared_ptr<Register32_t>  VIF1_REGISTER_ITOP;
	std::shared_ptr<Register32_t>  VIF1_REGISTER_TOP;
	std::shared_ptr<DeadMMemory_t> VIF1_MEMORY_3cf0;
	std::shared_ptr<Register32_t>  VIF1_REGISTER_R0;
	std::shared_ptr<Register32_t>  VIF1_REGISTER_R1;
	std::shared_ptr<Register32_t>  VIF1_REGISTER_R2;
	std::shared_ptr<Register32_t>  VIF1_REGISTER_R3;
	std::shared_ptr<Register32_t>  VIF1_REGISTER_C0;
	std::shared_ptr<Register32_t>  VIF1_REGISTER_C1;
	std::shared_ptr<Register32_t>  VIF1_REGISTER_C2;
	std::shared_ptr<Register32_t>  VIF1_REGISTER_C3;
	std::shared_ptr<DeadMMemory_t> VIF1_MEMORY_3d80;
};

