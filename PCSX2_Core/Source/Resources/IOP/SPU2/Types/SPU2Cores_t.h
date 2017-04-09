#pragma once

#include <memory>

#include "Common/Global/Globals.h"

class SPU2CoreVoice_t;
class SPU2CoreRegister_CHAN0_t;
class SPU2CoreRegister_CHAN1_t;
class SPU2CoreRegister_MMIX_t;
class SPU2CoreRegister_ATTR_t;
class ByteMemory_t;
class Register16_t;

/*
Base class representing a SPU2 core.
There are 2 individual cores in the SPU2, each with 24 voice channels.
*/
class SPU2Core_t
{
public:
	SPU2Core_t();

	/*
	SPU2 Core registers.
	*/
	std::shared_ptr<SPU2CoreRegister_CHAN0_t> PMON0;
	std::shared_ptr<SPU2CoreRegister_CHAN1_t> PMON1;
	std::shared_ptr<SPU2CoreRegister_CHAN0_t> NON0;
	std::shared_ptr<SPU2CoreRegister_CHAN1_t> NON1;
	std::shared_ptr<SPU2CoreRegister_CHAN0_t> VMIXL0;
	std::shared_ptr<SPU2CoreRegister_CHAN1_t> VMIXL1;
	std::shared_ptr<SPU2CoreRegister_CHAN0_t> VMIXEL0;
	std::shared_ptr<SPU2CoreRegister_CHAN1_t> VMIXEL1;
	std::shared_ptr<SPU2CoreRegister_CHAN0_t> VMIXR0;
	std::shared_ptr<SPU2CoreRegister_CHAN1_t> VMIXR1;
	std::shared_ptr<SPU2CoreRegister_CHAN0_t> VMIXER0;
	std::shared_ptr<SPU2CoreRegister_CHAN1_t> VMIXER1;
	std::shared_ptr<SPU2CoreRegister_MMIX_t>  MMIX;
	std::shared_ptr<SPU2CoreRegister_ATTR_t>  ATTR;
	std::shared_ptr<Register16_t>             IRQAL;
	std::shared_ptr<Register16_t>             IRQAH;
	std::shared_ptr<SPU2CoreRegister_CHAN0_t> KON0;
	std::shared_ptr<SPU2CoreRegister_CHAN1_t> KON1;
	std::shared_ptr<SPU2CoreRegister_CHAN0_t> KOF0;
	std::shared_ptr<SPU2CoreRegister_CHAN1_t> KOF1;
	std::shared_ptr<Register16_t>             TSAL;
	std::shared_ptr<Register16_t>             TSAH;
	std::shared_ptr<Register16_t>             DATA0;
	std::shared_ptr<Register16_t>             DATA1;
	std::shared_ptr<Register16_t>             DATA2;
	std::shared_ptr<Register16_t>             ESAL;
	std::shared_ptr<Register16_t>             ESAH;
	std::shared_ptr<Register16_t>             APF1_SIZEL;
	std::shared_ptr<Register16_t>             APF1_SIZEH;
	std::shared_ptr<Register16_t>             APF2_SIZEL;
	std::shared_ptr<Register16_t>             APF2_SIZEH;
	std::shared_ptr<Register16_t>             SAME_L_DSTL;
	std::shared_ptr<Register16_t>             SAME_L_DSTH;
	std::shared_ptr<Register16_t>             SAME_R_DSTL;
	std::shared_ptr<Register16_t>             SAME_R_DSTH;
	std::shared_ptr<Register16_t>             COMB1_L_SRCL;
	std::shared_ptr<Register16_t>             COMB1_L_SRCH;
	std::shared_ptr<Register16_t>             COMB1_R_SRCL;
	std::shared_ptr<Register16_t>             COMB1_R_SRCH;
	std::shared_ptr<Register16_t>             COMB2_L_SRCL;
	std::shared_ptr<Register16_t>             COMB2_L_SRCH;
	std::shared_ptr<Register16_t>             COMB2_R_SRCL;
	std::shared_ptr<Register16_t>             COMB2_R_SRCH;
	std::shared_ptr<Register16_t>             SAME_L_SRCL;
	std::shared_ptr<Register16_t>             SAME_L_SRCH;
	std::shared_ptr<Register16_t>             SAME_R_SRCL;
	std::shared_ptr<Register16_t>             SAME_R_SRCH;
	std::shared_ptr<Register16_t>             DIFF_L_DSTL;
	std::shared_ptr<Register16_t>             DIFF_L_DSTH;
	std::shared_ptr<Register16_t>             DIFF_R_DSTL;
	std::shared_ptr<Register16_t>             DIFF_R_DSTH;
	std::shared_ptr<Register16_t>             COMB3_L_SRCL;
	std::shared_ptr<Register16_t>             COMB3_L_SRCH;
	std::shared_ptr<Register16_t>             COMB3_R_SRCL;
	std::shared_ptr<Register16_t>             COMB3_R_SRCH;
	std::shared_ptr<Register16_t>             COMB4_L_SRCL;
	std::shared_ptr<Register16_t>             COMB4_L_SRCH;
	std::shared_ptr<Register16_t>             COMB4_R_SRCL;
	std::shared_ptr<Register16_t>             COMB4_R_SRCH;
	std::shared_ptr<Register16_t>             DIFF_L_SRCL;
	std::shared_ptr<Register16_t>             DIFF_L_SRCH;
	std::shared_ptr<Register16_t>             DIFF_R_SRCL;
	std::shared_ptr<Register16_t>             DIFF_R_SRCH;
	std::shared_ptr<Register16_t>             APF1_L_DSTL;
	std::shared_ptr<Register16_t>             APF1_L_DSTH;
	std::shared_ptr<Register16_t>             APF1_R_DSTL;
	std::shared_ptr<Register16_t>             APF1_R_DSTH;
	std::shared_ptr<Register16_t>             APF2_L_DSTL;
	std::shared_ptr<Register16_t>             APF2_L_DSTH;
	std::shared_ptr<Register16_t>             APF2_R_DSTL;
	std::shared_ptr<Register16_t>             APF2_R_DSTH;
	std::shared_ptr<Register16_t>             EEAL;
	std::shared_ptr<Register16_t>             EEAH;
	std::shared_ptr<Register16_t>             ENDX0;
	std::shared_ptr<Register16_t>             ENDX1;
	std::shared_ptr<Register16_t>             STATX;
	std::shared_ptr<ByteMemory_t>             MEMORY_0X46; // Memory for the rest of the mapped address space (unknown registers). 
	                                                       // For core 0, this is at 0x346 -> 0x3FF. For core 1, this is at 0x746 -> 0x7FF. Both are of size 0xBA.

	/*
	SPU2 Core voice channels.
	*/
	std::shared_ptr<SPU2CoreVoice_t>          VOICES[Constants::IOP::SPU2::NUMBER_CORE_VOICES];
};

class SPU2Core_C0_t : public SPU2Core_t
{
public:
	SPU2Core_C0_t();

	static constexpr int CORE_ID = 0;
};

class SPU2Core_C1_t : public SPU2Core_t
{
public:
	SPU2Core_C1_t();

	static constexpr int CORE_ID = 1;
};
