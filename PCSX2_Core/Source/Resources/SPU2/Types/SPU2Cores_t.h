#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Tables/SPU2CoreTable.h"
#include "Common/Types/System_t.h"

class SPU2CoreVoice_t;
class SPU2CoreRegister_CHAN0_t;
class SPU2CoreRegister_CHAN1_t;
class SPU2CoreRegister_MMIX_t;
class SPU2CoreRegister_ATTR_t;
class SPU2CoreRegister_VOL_t;
class SPU2CoreRegister_STATX_t;
class ByteMemory_t;
class Register16_t;
class PairRegister16_t;
class FIFOQueue_t;

/*
Base class representing a SPU2 core.
There are 2 individual cores in the SPU2, each with 24 voice channels.
*/
class SPU2Core_t
{
public:
	SPU2Core_t(const int coreID, const std::shared_ptr<FIFOQueue_t> & fifoQueue);

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
	std::shared_ptr<Register16_t>             IRQAH;
	std::shared_ptr<PairRegister16_t>         IRQAL;
	std::shared_ptr<SPU2CoreRegister_CHAN0_t> KON0;
	std::shared_ptr<SPU2CoreRegister_CHAN1_t> KON1;
	std::shared_ptr<SPU2CoreRegister_CHAN0_t> KOF0;
	std::shared_ptr<SPU2CoreRegister_CHAN1_t> KOF1;
	std::shared_ptr<Register16_t>             TSAH;
	std::shared_ptr<PairRegister16_t>         TSAL;
	std::shared_ptr<Register16_t>             DATA0;
	std::shared_ptr<Register16_t>             DATA1;
	std::shared_ptr<Register16_t>             ADMAS; // "AutoDMA Status".
	std::shared_ptr<Register16_t>             ESAH;
	std::shared_ptr<Register16_t>             ESAL;
	std::shared_ptr<Register16_t>             APF1_SIZEH;
	std::shared_ptr<Register16_t>             APF1_SIZEL;
	std::shared_ptr<Register16_t>             APF2_SIZEH;
	std::shared_ptr<Register16_t>             APF2_SIZEL;
	std::shared_ptr<Register16_t>             SAME_L_DSTH;
	std::shared_ptr<Register16_t>             SAME_L_DSTL;
	std::shared_ptr<Register16_t>             SAME_R_DSTH;
	std::shared_ptr<Register16_t>             SAME_R_DSTL;
	std::shared_ptr<Register16_t>             COMB1_L_SRCH;
	std::shared_ptr<Register16_t>             COMB1_L_SRCL;
	std::shared_ptr<Register16_t>             COMB1_R_SRCH;
	std::shared_ptr<Register16_t>             COMB1_R_SRCL;
	std::shared_ptr<Register16_t>             COMB2_L_SRCH;
	std::shared_ptr<Register16_t>             COMB2_L_SRCL;
	std::shared_ptr<Register16_t>             COMB2_R_SRCH;
	std::shared_ptr<Register16_t>             COMB2_R_SRCL;
	std::shared_ptr<Register16_t>             SAME_L_SRCH;
	std::shared_ptr<Register16_t>             SAME_L_SRCL;
	std::shared_ptr<Register16_t>             SAME_R_SRCH;
	std::shared_ptr<Register16_t>             SAME_R_SRCL;
	std::shared_ptr<Register16_t>             DIFF_L_DSTH;
	std::shared_ptr<Register16_t>             DIFF_L_DSTL;
	std::shared_ptr<Register16_t>             DIFF_R_DSTH;
	std::shared_ptr<Register16_t>             DIFF_R_DSTL;
	std::shared_ptr<Register16_t>             COMB3_L_SRCH;
	std::shared_ptr<Register16_t>             COMB3_L_SRCL;
	std::shared_ptr<Register16_t>             COMB3_R_SRCH;
	std::shared_ptr<Register16_t>             COMB3_R_SRCL;
	std::shared_ptr<Register16_t>             COMB4_L_SRCH;
	std::shared_ptr<Register16_t>             COMB4_L_SRCL;
	std::shared_ptr<Register16_t>             COMB4_R_SRCH;
	std::shared_ptr<Register16_t>             COMB4_R_SRCL;
	std::shared_ptr<Register16_t>             DIFF_L_SRCH;
	std::shared_ptr<Register16_t>             DIFF_L_SRCL;
	std::shared_ptr<Register16_t>             DIFF_R_SRCH;
	std::shared_ptr<Register16_t>             DIFF_R_SRCL;
	std::shared_ptr<Register16_t>             APF1_L_DSTH;
	std::shared_ptr<Register16_t>             APF1_L_DSTL;
	std::shared_ptr<Register16_t>             APF1_R_DSTH;
	std::shared_ptr<Register16_t>             APF1_R_DSTL;
	std::shared_ptr<Register16_t>             APF2_L_DSTH;
	std::shared_ptr<Register16_t>             APF2_L_DSTL;
	std::shared_ptr<Register16_t>             APF2_R_DSTH;
	std::shared_ptr<Register16_t>             APF2_R_DSTL;
	std::shared_ptr<Register16_t>             EEAH;
	std::shared_ptr<Register16_t>             EEAL;
	std::shared_ptr<Register16_t>             ENDX0;
	std::shared_ptr<Register16_t>             ENDX1;
	std::shared_ptr<SPU2CoreRegister_STATX_t> STATX;
	std::shared_ptr<SPU2CoreRegister_VOL_t>   MVOLL;
	std::shared_ptr<SPU2CoreRegister_VOL_t>   MVOLR;
	std::shared_ptr<Register16_t>             EVOLL;
	std::shared_ptr<Register16_t>             EVOLR;
	std::shared_ptr<Register16_t>             AVOLL;
	std::shared_ptr<Register16_t>             AVOLR;
	std::shared_ptr<Register16_t>             BVOLL;
	std::shared_ptr<Register16_t>             BVOLR;
	std::shared_ptr<Register16_t>             MVOLXL;
	std::shared_ptr<Register16_t>             MVOLXR;
	std::shared_ptr<Register16_t>             IIR_VOL;
	std::shared_ptr<Register16_t>             COMB1_VOL;
	std::shared_ptr<Register16_t>             COMB2_VOL;
	std::shared_ptr<Register16_t>             COMB3_VOL;
	std::shared_ptr<Register16_t>             COMB4_VOL;
	std::shared_ptr<Register16_t>             WALL_VOL;
	std::shared_ptr<Register16_t>             APF1_VOL;
	std::shared_ptr<Register16_t>             APF2_VOL;
	std::shared_ptr<Register16_t>             IN_COEF_L;
	std::shared_ptr<Register16_t>             IN_COEF_R;

	/*
	SPU2 Core voice channels.
	*/
	std::shared_ptr<SPU2CoreVoice_t> VOICE_0;
	std::shared_ptr<SPU2CoreVoice_t> VOICE_1;
	std::shared_ptr<SPU2CoreVoice_t> VOICE_2;
	std::shared_ptr<SPU2CoreVoice_t> VOICE_3;
	std::shared_ptr<SPU2CoreVoice_t> VOICE_4;
	std::shared_ptr<SPU2CoreVoice_t> VOICE_5;
	std::shared_ptr<SPU2CoreVoice_t> VOICE_6;
	std::shared_ptr<SPU2CoreVoice_t> VOICE_7;
	std::shared_ptr<SPU2CoreVoice_t> VOICE_8;
	std::shared_ptr<SPU2CoreVoice_t> VOICE_9;
	std::shared_ptr<SPU2CoreVoice_t> VOICE_10;
	std::shared_ptr<SPU2CoreVoice_t> VOICE_11;
	std::shared_ptr<SPU2CoreVoice_t> VOICE_12;
	std::shared_ptr<SPU2CoreVoice_t> VOICE_13;
	std::shared_ptr<SPU2CoreVoice_t> VOICE_14;
	std::shared_ptr<SPU2CoreVoice_t> VOICE_15;
	std::shared_ptr<SPU2CoreVoice_t> VOICE_16;
	std::shared_ptr<SPU2CoreVoice_t> VOICE_17;
	std::shared_ptr<SPU2CoreVoice_t> VOICE_18;
	std::shared_ptr<SPU2CoreVoice_t> VOICE_19;
	std::shared_ptr<SPU2CoreVoice_t> VOICE_20;
	std::shared_ptr<SPU2CoreVoice_t> VOICE_21;
	std::shared_ptr<SPU2CoreVoice_t> VOICE_22;
	std::shared_ptr<SPU2CoreVoice_t> VOICE_23;
	std::shared_ptr<SPU2CoreVoice_t> VOICES[Constants::SPU2::NUMBER_CORE_VOICES];

	/*
	Associated DMA FIFO queue attached to this core.
	*/
	std::shared_ptr<FIFOQueue_t> FIFOQueue;
	
	/*
	Returns the core ID.	
	*/
	int getCoreID() const;

	/*
	Returns the constant properties for this core.
	*/
	const SPU2CoreTable::SPU2CoreInfo_t * getInfo() const;

	/*
	Returns if the core is enabled for auto DMA transfers, by checking that ((coreIdx + 1) & ADMAS) > 0.
	From PCSX2's SPU2-X dma.cpp.
	TODO: Investigate more, this does not make much sense to me. The SPU2 overview manual mentions ADMA reads and writes, but only writes are ever used it seems.
	*/
	bool isADMAEnabled(const System_t context) const;

private:
	/*
	SPU2 Core ID.
	*/
	int mCoreID;
};

class SPU2Core_C0_t : public SPU2Core_t
{
public:
	SPU2Core_C0_t(const std::shared_ptr<FIFOQueue_t> & fifoQueue);

	/*
	Unknown memory/registers.
	*/
	std::shared_ptr<ByteMemory_t> MEMORY_0346;

	static constexpr int CORE_ID = 0;
};

class SPU2Core_C1_t : public SPU2Core_t
{
public:
	SPU2Core_C1_t(const std::shared_ptr<FIFOQueue_t> & fifoQueue);

	static constexpr int CORE_ID = 1;
};
