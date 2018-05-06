#pragma once

#include "Common/Types/FifoQueue/DmaFifoQueue.hpp"

#include "Resources/Ee/Vpu/Vif/VifUnitRegisters.hpp"

// A base class for a VIF core.
class VifUnit_Base
{
public:
	VifUnit_Base(const int core_id);

	/// ID of the VIF unit.
	int core_id;

	/// DMA FIFO queue.
	DmaFifoQueue<> * dma_fifo_queue;

	/// VIF registers. See page 124 of EE Users Manual.
	SizedWordRegister     r0;
	SizedWordRegister     r1;
	SizedWordRegister     r2;
	SizedWordRegister     r3;
	SizedWordRegister     c0;
	SizedWordRegister     c1;
	SizedWordRegister     c2;
	SizedWordRegister     c3;
	VifUnitRegister_Cycle cycle;
	VifUnitRegister_Mask  mask;
	VifUnitRegister_Mode  mode;
	VifUnitRegister_Itop  itop;
	VifUnitRegister_Itops itops;
	VifUnitRegister_Base  base;
	VifUnitRegister_Ofst  ofst;
	VifUnitRegister_Top   top;
	VifUnitRegister_Tops  tops;
	VifUnitRegister_Mask  mark;
	VifUnitRegister_Num   num;
	VifUnitRegister_Code  code;
	VifUnitRegister_Stat  stat;
	VifUnitRegister_Fbrst fbrst;
	VifUnitRegister_Err   err;
};