#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/MIPS/MIPSCoprocessor_t.h"

class ByteMemory_t;
class ByteMMU_t;
class Register128_t;
class Register32_t;
class Register16_t;
class Register32_t;
class PCRegister16_t;
class VUCoreRegister_MAC_t;
class VUCoreRegister_Status_t;
class VUCoreRegister_Clipping_t;
class VUCoreRegister_CMSAR_t;
class EECoreCOP0_t;

/*
A base class for an implementation of a VU unit resource. Common resources are initalised, all others set to nullptr (see below).
Extended by VUCore_VU0_t and VUCore_VU1_t.
*/
class VUCore_t
{
public:
	explicit VUCore_t(const int vuCoreID);

	/*
	ID of the VU. Currently used for debug.
	*/
	int mVUCoreID;

	/*
	VU floating point registers (VF) (128-bit) and integer registers (VI) (16-bit).
	See VU Users Manual page 18.
	*/
	std::shared_ptr<Register128_t> VF[Constants::EE::VPU::VU::NUMBER_VF_REGISTERS];
	std::shared_ptr<Register16_t> VI[Constants::EE::VPU::VU::NUMBER_VI_REGISTERS];

	/*
	ACC register. Used by instructions such as ADDA and MULA.
	See VU Users Manual page 33.
	*/
	std::shared_ptr<Register128_t> ACC;

	/*
	I register. Used to store immediate values.
	See VU Users Manual page 33.
	*/
	std::shared_ptr<Register32_t> I;

	/*
	Q register. Used to store division/sqrt values.
	See VU Users Manual page 34.
	*/
	std::shared_ptr<Register32_t> Q;

	/*
	R register. Used to store random numbers generated.
	See VU Users Manual page 34.
	*/
	std::shared_ptr<Register32_t> R;

	/*
	P register. Used to store EFU result values.
	See VU Users Manual page 34.
	*/
	std::shared_ptr<Register32_t> P;

	/*
	The Flag registers (MAC, Status and Clipping), used to hold special results from calculations.
	See VU Users Manual page 40.

	The MAC register is dependant on the Status register for special functionality.
	*/
	std::shared_ptr<VUCoreRegister_Status_t>   Status;
	std::shared_ptr<VUCoreRegister_MAC_t>      MAC;
	std::shared_ptr<VUCoreRegister_Clipping_t> Clipping;

	/*
	PC (program counter) register for micro subroutines.
	Also known as the TPC (termination PC).
	See VU Users Manual page 202 for the TPC definition, although there is no explicit definition for the PC register.
	*/
	std::shared_ptr<PCRegister16_t> PC;

	/*
	The CMSAR register used for micro subroutine execution.
	See VU Users Manual page 202.
	*/
	std::shared_ptr<VUCoreRegister_CMSAR_t> CMSAR;

	/*
	VU0 contains a physical memory map of its real working space (& mirrors) and the VU1 registers.
	For VU1, it is just a direct map of its real working space (needed to keep it OOP friendly).
	See EE Users Manual page 84.
	*/
	std::shared_ptr<ByteMMU_t> MemByteMMU;

	/*
	VU memory, defined on page 18 of the VU Users Manual.
	Initalised by subclasses; different for VU0 (4KB) and VU1 (16KB).
	*/
	std::shared_ptr<ByteMemory_t> MEMORY_Micro;
	std::shared_ptr<ByteMemory_t> MEMORY_Mem;
};

/*
Represents VU0.
It is attached as a MIPS coprocessor to the EE Core, as COP2.
*/
class VUCore_VU0_t : public VUCore_t, public MIPSCoprocessor_t
{
public:
	explicit VUCore_VU0_t(const std::shared_ptr<EECoreCOP0_t> & cop0);

	static constexpr int CORE_ID = 0;

	// COP2 (attached to EE Core) functionality.

	/*
	The CCR (control registers) array (32) needed for the CTC2 and CFC2 EE Core instructions.
	See VU Users Manual page 200 & 201.

	The first 16 registers are allocated to the VU0 VI registers, with the last 16 registers allocated to various control registers.
	Due to dependency on registers outside this class, initalisation is done on post PS2Resources initalsation.
	*/
	std::shared_ptr<Register32_t> CCR[Constants::EE::VPU::VU::NUMBER_VU0_CCR_REGISTERS];

	/*
	Check if this VU unit is usable in macro mode from the EE Core by checking the EE Core's COP0.Status.CU2 bit.
	*/
	bool isCoprocessorUsable(const System_t context) const override;

private:
	/*
	Pointer to the EE Core COP0 coprocessor, needed for the Status register.
	*/
	std::shared_ptr<EECoreCOP0_t> COP0;

};

/*
Represents VU1.
*/
class VUCore_VU1_t : public VUCore_t
{
public:
	explicit VUCore_VU1_t();

	static constexpr int CORE_ID = 1;
};
