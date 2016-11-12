#pragma once

#include <memory>

#include "PS2Constants/PS2Constants.h"

class Memory_t;
class PhysicalMMU_t;
class FPRegister128_t;
class FPRegister32_t;
class Register16_t;

/*
A base class for an implementation of a VU resource. Common resources are initalised, all others set to nullptr (see below).
Extended by VU0_t and VU1_t.
*/
class VuUnit_t
{
public:
	explicit VuUnit_t(const u32 & unitID);

	/*
	ID of the VU unit. Currently used for debug.
	*/
	const u32 mUnitID;

	/*
	VU0 Floating Point Registers (VF) (128-bit) and Integer Registers (VI) (16-bit).
	See VU Users Manual page 18.
	*/
	std::shared_ptr<FPRegister128_t> VF[PS2Constants::EE::VPU::VU::NUMBER_VF_REGISTERS];
	std::shared_ptr<Register16_t> VI[PS2Constants::EE::VPU::VU::NUMBER_VI_REGISTERS];

	/*
	ACC register. Used by instructions such as ADDA and MULA.
	See VU Users Manual page 33.
	*/
	std::shared_ptr<FPRegister128_t> ACC;

	/*
	I register. Used to store immediate values.
	See VU Users Manual page 33.
	*/
	std::shared_ptr<FPRegister32_t> I;

	/*
	Q register. Used to store division/sqrt values.
	See VU Users Manual page 34.
	*/
	std::shared_ptr<FPRegister32_t> Q;

	/*
	P register. Used to store random numbers generated.
	See VU Users Manual page 34.
	*/
	std::shared_ptr<FPRegister32_t> R;

	/*
	P register. Used to store EFU result values.
	See VU Users Manual page 34.
	*/
	std::shared_ptr<FPRegister32_t> P;
	
	/*
	VU0 contains a physical memory map of its real working space (& mirrors) and the VU1 registers.
	For VU1, it is just a direct map of its real working space (needed to keep it OOP friendly).
	See EE Users Manual page 84.
	*/
	std::shared_ptr<PhysicalMMU_t> MemPhysicalMMU;

	/*
	VU memory, defined on page 25 of the EE Users Manual.
	Not initalised in class.
	Different for VU0 (4KB) and VU1 (16KB).
	*/
	std::shared_ptr<Memory_t> MEMORY_Micro;
	std::shared_ptr<Memory_t> MEMORY_Mem;
};

/*
Represents the VU0 unit.
*/
class VuUnit_0_t : public VuUnit_t
{
public:
	explicit VuUnit_0_t();

	static constexpr u32 UNIT_ID = 0;
};

/*
Represents the VU1 unit.
*/
class VuUnit_1_t : public VuUnit_t
{
public:
	explicit VuUnit_1_t();

	static constexpr u32 UNIT_ID = 1;
};
