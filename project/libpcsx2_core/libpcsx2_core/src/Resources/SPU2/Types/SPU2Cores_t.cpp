#include "Common/Types/Register/Register16_t.h"
#include "Common/Types/Register/PairRegister16_t.h"
#include "Common/Types/Memory/ByteMemory_t.h"

#include "Resources/SPU2/Types/SPU2Cores_t.h"
#include "Resources/SPU2/Types/SPU2CoreRegisters_t.h"
#include "Resources/SPU2/Types/SPU2CoreVoices_t.h"
#include "Resources/IOP/DMAC/Types/IOPDmacChannels_t.h"

SPU2Core_t::SPU2Core_t(const int coreID, const std::shared_ptr<IOPDmacChannel_t> & dmaChannel) :
	PMON0(nullptr),
	PMON1(nullptr),
	NON0(nullptr),
	NON1(nullptr),
	VMIXL0(nullptr),
	VMIXL1(nullptr),
	VMIXEL0(nullptr),
	VMIXEL1(nullptr),
	VMIXR0(nullptr),
	VMIXR1(nullptr),
	VMIXER0(nullptr),
	VMIXER1(nullptr),
	MMIX(nullptr),
	ATTR(nullptr),
	IRQAH(nullptr),
	IRQAL(nullptr),
	KON0(nullptr),
	KON1(nullptr),
	KOF0(nullptr),
	KOF1(nullptr),
	TSAH(nullptr),
	TSAL(nullptr),
	DATA0(nullptr),
	DATA1(nullptr),
	ADMAS(nullptr),
	ESAH(nullptr),
	ESAL(nullptr),
	APF1_SIZEH(nullptr),
	APF1_SIZEL(nullptr),
	APF2_SIZEH(nullptr),
	APF2_SIZEL(nullptr),
	SAME_L_DSTH(nullptr),
	SAME_L_DSTL(nullptr),
	SAME_R_DSTH(nullptr),
	SAME_R_DSTL(nullptr),
	COMB1_L_SRCH(nullptr),
	COMB1_L_SRCL(nullptr),
	COMB1_R_SRCH(nullptr),
	COMB1_R_SRCL(nullptr),
	COMB2_L_SRCH(nullptr),
	COMB2_L_SRCL(nullptr),
	COMB2_R_SRCH(nullptr),
	COMB2_R_SRCL(nullptr),
	SAME_L_SRCH(nullptr),
	SAME_L_SRCL(nullptr),
	SAME_R_SRCH(nullptr),
	SAME_R_SRCL(nullptr),
	DIFF_L_DSTH(nullptr),
	DIFF_L_DSTL(nullptr),
	DIFF_R_DSTH(nullptr),
	DIFF_R_DSTL(nullptr),
	COMB3_L_SRCH(nullptr),
	COMB3_L_SRCL(nullptr),
	COMB3_R_SRCH(nullptr),
	COMB3_R_SRCL(nullptr),
	COMB4_L_SRCH(nullptr),
	COMB4_L_SRCL(nullptr),
	COMB4_R_SRCH(nullptr),
	COMB4_R_SRCL(nullptr),
	DIFF_L_SRCH(nullptr),
	DIFF_L_SRCL(nullptr),
	DIFF_R_SRCH(nullptr),
	DIFF_R_SRCL(nullptr),
	APF1_L_DSTH(nullptr),
	APF1_L_DSTL(nullptr),
	APF1_R_DSTH(nullptr),
	APF1_R_DSTL(nullptr),
	APF2_L_DSTH(nullptr),
	APF2_L_DSTL(nullptr),
	APF2_R_DSTH(nullptr),
	APF2_R_DSTL(nullptr),
	EEAH(nullptr),
	EEAL(nullptr),
	ENDX0(nullptr),
	ENDX1(nullptr),
	STATX(nullptr),
	MVOLL(nullptr),
	MVOLR(nullptr),
	EVOLL(nullptr),
	EVOLR(nullptr),
	AVOLL(nullptr),
	AVOLR(nullptr),
	BVOLL(nullptr),
	BVOLR(nullptr),
	MVOLXL(nullptr),
	MVOLXR(nullptr),
	IIR_VOL(nullptr),
	COMB1_VOL(nullptr),
	COMB2_VOL(nullptr),
	COMB3_VOL(nullptr),
	COMB4_VOL(nullptr),
	WALL_VOL(nullptr),
	APF1_VOL(nullptr),
	APF2_VOL(nullptr),
	IN_COEF_L(nullptr),
	IN_COEF_R(nullptr),
	VOICE_0(nullptr),
	VOICE_1(nullptr),
	VOICE_2(nullptr),
	VOICE_3(nullptr),
	VOICE_4(nullptr),
	VOICE_5(nullptr),
	VOICE_6(nullptr),
	VOICE_7(nullptr),
	VOICE_8(nullptr),
	VOICE_9(nullptr),
	VOICE_10(nullptr),
	VOICE_11(nullptr),
	VOICE_12(nullptr),
	VOICE_13(nullptr),
	VOICE_14(nullptr),
	VOICE_15(nullptr),
	VOICE_16(nullptr),
	VOICE_17(nullptr),
	VOICE_18(nullptr),
	VOICE_19(nullptr),
	VOICE_20(nullptr),
	VOICE_21(nullptr),
	VOICE_22(nullptr),
	VOICE_23(nullptr),
	VOICES{ nullptr },
	DMAChannel(dmaChannel),
	FIFOQueue(dmaChannel->FIFOQueue),
	mCoreID(coreID)
{
}

int SPU2Core_t::getCoreID() const
{
	return mCoreID;
}

const SPU2CoreTable::SPU2CoreInfo_t* SPU2Core_t::getInfo() const
{
	return SPU2CoreTable::getInfo(this);
}

SPU2Core_C0_t::SPU2Core_C0_t(const std::shared_ptr<IOPDmacChannel_t> & dmaChannel) :
	SPU2Core_t(CORE_ID, dmaChannel)
{
	PMON0 = std::make_shared<SPU2CoreRegister_CHAN0_t>("SPU2 C0 PMON0", false, false);
	PMON1 = std::make_shared<SPU2CoreRegister_CHAN1_t>("SPU2 C0 PMON1", false, false);
	NON0 = std::make_shared<SPU2CoreRegister_CHAN0_t>("SPU2 C0 NON0", false, false);
	NON1 = std::make_shared<SPU2CoreRegister_CHAN1_t>("SPU2 C0 NON1", false, false);
	VMIXL0 = std::make_shared<SPU2CoreRegister_CHAN0_t>("SPU2 C0 VMIXL0", false, false);
	VMIXL1 = std::make_shared<SPU2CoreRegister_CHAN1_t>("SPU2 C0 VMIXL1", false, false);
	VMIXEL0 = std::make_shared<SPU2CoreRegister_CHAN0_t>("SPU2 C0 VMIXEL0", false, false);
	VMIXEL1 = std::make_shared<SPU2CoreRegister_CHAN1_t>("SPU2 C0 VMIXEL1", false, false);
	VMIXR0 = std::make_shared<SPU2CoreRegister_CHAN0_t>("SPU2 C0 VMIXR0", false, false);
	VMIXR1 = std::make_shared<SPU2CoreRegister_CHAN1_t>("SPU2 C0 VMIXR1", false, false);
	VMIXER0 = std::make_shared<SPU2CoreRegister_CHAN0_t>("SPU2 C0 VMIXER0", false, false);
	VMIXER1 = std::make_shared<SPU2CoreRegister_CHAN1_t>("SPU2 C0 VMIXER1", false, false);
	MMIX = std::make_shared<SPU2CoreRegister_MMIX_t>("SPU2 C0 MMIX", false, false);
	ATTR = std::make_shared<SPU2CoreRegister_ATTR_t>("SPU2 C0 ATTR", false, false);
	IRQAH = std::make_shared<Register16_t>("SPU2 C0 IRQAH", false, true);
	IRQAL = std::make_shared<PairRegister16_t>("SPU2 C0 IRQAL", false, true, IRQAH);
	KON0 = std::make_shared<SPU2CoreRegister_CHAN0_t>("SPU2 C0 KON0", false, false);
	KON1 = std::make_shared<SPU2CoreRegister_CHAN1_t>("SPU2 C0 KON1", false, false);
	KOF0 = std::make_shared<SPU2CoreRegister_CHAN0_t>("SPU2 C0 KOF0", false, false);
	KOF1 = std::make_shared<SPU2CoreRegister_CHAN1_t>("SPU2 C0 KOF1", false, false);
	TSAH = std::make_shared<Register16_t>("SPU2 C0 TSAH", false, true);
	TSAL = std::make_shared<PairRegister16_t>("SPU2 C0 TSAL", false, true, TSAH);
	DATA0 = std::make_shared<Register16_t>("SPU2 C0 DATA0", false, false);
	DATA1 = std::make_shared<Register16_t>("SPU2 C0 DATA1", false, false);
	ADMAS = std::make_shared<SPU2CoreRegister_ADMAS_t>("SPU2 C0 ADMAS", false, true, CORE_ID);
	ESAH = std::make_shared<Register16_t>("SPU2 C0 ESAH", false, false);
	ESAL = std::make_shared<Register16_t>("SPU2 C0 ESAL", false, false);
	APF1_SIZEH = std::make_shared<Register16_t>("SPU2 C0 APF1_SIZEH", false, false);
	APF1_SIZEL = std::make_shared<Register16_t>("SPU2 C0 APF1_SIZEL", false, false);
	APF2_SIZEH = std::make_shared<Register16_t>("SPU2 C0 APF2_SIZEH", false, false);
	APF2_SIZEL = std::make_shared<Register16_t>("SPU2 C0 APF2_SIZEL", false, false);
	SAME_L_DSTH = std::make_shared<Register16_t>("SPU2 C0 SAME_L_DSTH", false, false);
	SAME_L_DSTL = std::make_shared<Register16_t>("SPU2 C0 SAME_L_DSTL", false, false);
	SAME_R_DSTH = std::make_shared<Register16_t>("SPU2 C0 SAME_R_DSTH", false, false);
	SAME_R_DSTL = std::make_shared<Register16_t>("SPU2 C0 SAME_R_DSTL", false, false);
	COMB1_L_SRCH = std::make_shared<Register16_t>("SPU2 C0 COMB1_L_SRCH", false, false);
	COMB1_L_SRCL = std::make_shared<Register16_t>("SPU2 C0 COMB1_L_SRCL", false, false);
	COMB1_R_SRCH = std::make_shared<Register16_t>("SPU2 C0 COMB1_R_SRCH", false, false);
	COMB1_R_SRCL = std::make_shared<Register16_t>("SPU2 C0 COMB1_R_SRCL", false, false);
	COMB2_L_SRCH = std::make_shared<Register16_t>("SPU2 C0 COMB2_L_SRCH", false, false);
	COMB2_L_SRCL = std::make_shared<Register16_t>("SPU2 C0 COMB2_L_SRCL", false, false);
	COMB2_R_SRCH = std::make_shared<Register16_t>("SPU2 C0 COMB2_R_SRCH", false, false);
	COMB2_R_SRCL = std::make_shared<Register16_t>("SPU2 C0 COMB2_R_SRCL", false, false);
	SAME_L_SRCH = std::make_shared<Register16_t>("SPU2 C0 SAME_L_SRCH", false, false);
	SAME_L_SRCL = std::make_shared<Register16_t>("SPU2 C0 SAME_L_SRCL", false, false);
	SAME_R_SRCH = std::make_shared<Register16_t>("SPU2 C0 SAME_R_SRCH", false, false);
	SAME_R_SRCL = std::make_shared<Register16_t>("SPU2 C0 SAME_R_SRCL", false, false);
	DIFF_L_DSTH = std::make_shared<Register16_t>("SPU2 C0 DIFF_L_DSTH", false, false);
	DIFF_L_DSTL = std::make_shared<Register16_t>("SPU2 C0 DIFF_L_DSTL", false, false);
	DIFF_R_DSTH = std::make_shared<Register16_t>("SPU2 C0 DIFF_R_DSTH", false, false);
	DIFF_R_DSTL = std::make_shared<Register16_t>("SPU2 C0 DIFF_R_DSTL", false, false);
	COMB3_L_SRCH = std::make_shared<Register16_t>("SPU2 C0 COMB3_L_SRCH", false, false);
	COMB3_L_SRCL = std::make_shared<Register16_t>("SPU2 C0 COMB3_L_SRCL", false, false);
	COMB3_R_SRCH = std::make_shared<Register16_t>("SPU2 C0 COMB3_R_SRCH", false, false);
	COMB3_R_SRCL = std::make_shared<Register16_t>("SPU2 C0 COMB3_R_SRCL", false, false);
	COMB4_L_SRCH = std::make_shared<Register16_t>("SPU2 C0 COMB4_L_SRCH", false, false);
	COMB4_L_SRCL = std::make_shared<Register16_t>("SPU2 C0 COMB4_L_SRCL", false, false);
	COMB4_R_SRCH = std::make_shared<Register16_t>("SPU2 C0 COMB4_R_SRCH", false, false);
	COMB4_R_SRCL = std::make_shared<Register16_t>("SPU2 C0 COMB4_R_SRCL", false, false);
	DIFF_L_SRCH = std::make_shared<Register16_t>("SPU2 C0 DIFF_L_SRCH", false, false);
	DIFF_L_SRCL = std::make_shared<Register16_t>("SPU2 C0 DIFF_L_SRCL", false, false);
	DIFF_R_SRCH = std::make_shared<Register16_t>("SPU2 C0 DIFF_R_SRCH", false, false);
	DIFF_R_SRCL = std::make_shared<Register16_t>("SPU2 C0 DIFF_R_SRCL", false, false);
	APF1_L_DSTH = std::make_shared<Register16_t>("SPU2 C0 APF1_L_DSTH", false, false);
	APF1_L_DSTL = std::make_shared<Register16_t>("SPU2 C0 APF1_L_DSTL", false, false);
	APF1_R_DSTH = std::make_shared<Register16_t>("SPU2 C0 APF1_R_DSTH", false, false);
	APF1_R_DSTL = std::make_shared<Register16_t>("SPU2 C0 APF1_R_DSTL", false, false);
	APF2_L_DSTH = std::make_shared<Register16_t>("SPU2 C0 APF2_L_DSTH", false, false);
	APF2_L_DSTL = std::make_shared<Register16_t>("SPU2 C0 APF2_L_DSTL", false, false);
	APF2_R_DSTH = std::make_shared<Register16_t>("SPU2 C0 APF2_R_DSTH", false, false);
	APF2_R_DSTL = std::make_shared<Register16_t>("SPU2 C0 APF2_R_DSTL", false, false);
	EEAH = std::make_shared<Register16_t>("SPU2 C0 EEAH", false, false);
	EEAL = std::make_shared<Register16_t>("SPU2 C0 EEAL", false, false);
	ENDX0 = std::make_shared<Register16_t>("SPU2 C0 ENDX0", false, false);
	ENDX1 = std::make_shared<Register16_t>("SPU2 C0 ENDX1", false, false);
	STATX = std::make_shared<SPU2CoreRegister_STATX_t>("SPU2 C0 STATX", true, false);
	MVOLL = std::make_shared<SPU2CoreRegister_VOL_t>("SPU2 C0 MVOLL", false, false);
	MVOLR = std::make_shared<SPU2CoreRegister_VOL_t>("SPU2 C0 MVOLR", false, false);
	EVOLL = std::make_shared<Register16_t>("SPU2 C0 EVOLL", false, false);
	EVOLR = std::make_shared<Register16_t>("SPU2 C0 EVOLR", false, false);
	AVOLL = std::make_shared<Register16_t>("SPU2 C0 AVOLL", false, false);
	AVOLR = std::make_shared<Register16_t>("SPU2 C0 AVOLR", false, false);
	BVOLL = std::make_shared<Register16_t>("SPU2 C0 BVOLL", false, false);
	BVOLR = std::make_shared<Register16_t>("SPU2 C0 BVOLR", false, false);
	MVOLXL = std::make_shared<Register16_t>("SPU2 C0 MVOLXL", false, false);
	MVOLXR = std::make_shared<Register16_t>("SPU2 C0 MVOLXR", false, false);
	IIR_VOL = std::make_shared<Register16_t>("SPU2 C0 IIR_VOL", false, false);
	COMB1_VOL = std::make_shared<Register16_t>("SPU2 C0 COMB1_VOL", false, false);
	COMB2_VOL = std::make_shared<Register16_t>("SPU2 C0 COMB2_VOL", false, false);
	COMB3_VOL = std::make_shared<Register16_t>("SPU2 C0 COMB3_VOL", false, false);
	COMB4_VOL = std::make_shared<Register16_t>("SPU2 C0 COMB4_VOL", false, false);
	WALL_VOL = std::make_shared<Register16_t>("SPU2 C0 WALL_VOL", false, false);
	APF1_VOL = std::make_shared<Register16_t>("SPU2 C0 APF1_VOL", false, false);
	APF2_VOL = std::make_shared<Register16_t>("SPU2 C0 APF2_VOL", false, false);
	IN_COEF_L = std::make_shared<Register16_t>("SPU2 C0 IN_COEF_L", false, false);
	IN_COEF_R = std::make_shared<Register16_t>("SPU2 C0 IN_COEF_R", false, false);
	VOICE_0 = std::make_shared<SPU2CoreVoice_C0V0_t>();
	VOICE_1 = std::make_shared<SPU2CoreVoice_C0V1_t>();
	VOICE_2 = std::make_shared<SPU2CoreVoice_C0V2_t>();
	VOICE_3 = std::make_shared<SPU2CoreVoice_C0V3_t>();
	VOICE_4 = std::make_shared<SPU2CoreVoice_C0V4_t>();
	VOICE_5 = std::make_shared<SPU2CoreVoice_C0V5_t>();
	VOICE_6 = std::make_shared<SPU2CoreVoice_C0V6_t>();
	VOICE_7 = std::make_shared<SPU2CoreVoice_C0V7_t>();
	VOICE_8 = std::make_shared<SPU2CoreVoice_C0V8_t>();
	VOICE_9 = std::make_shared<SPU2CoreVoice_C0V9_t>();
	VOICE_10 = std::make_shared<SPU2CoreVoice_C0V10_t>();
	VOICE_11 = std::make_shared<SPU2CoreVoice_C0V11_t>();
	VOICE_12 = std::make_shared<SPU2CoreVoice_C0V12_t>();
	VOICE_13 = std::make_shared<SPU2CoreVoice_C0V13_t>();
	VOICE_14 = std::make_shared<SPU2CoreVoice_C0V14_t>();
	VOICE_15 = std::make_shared<SPU2CoreVoice_C0V15_t>();
	VOICE_16 = std::make_shared<SPU2CoreVoice_C0V16_t>();
	VOICE_17 = std::make_shared<SPU2CoreVoice_C0V17_t>();
	VOICE_18 = std::make_shared<SPU2CoreVoice_C0V18_t>();
	VOICE_19 = std::make_shared<SPU2CoreVoice_C0V19_t>();
	VOICE_20 = std::make_shared<SPU2CoreVoice_C0V20_t>();
	VOICE_21 = std::make_shared<SPU2CoreVoice_C0V21_t>();
	VOICE_22 = std::make_shared<SPU2CoreVoice_C0V22_t>();
	VOICE_23 = std::make_shared<SPU2CoreVoice_C0V23_t>();
	VOICES[0] = VOICE_0;
	VOICES[1] = VOICE_1;
	VOICES[2] = VOICE_2;
	VOICES[3] = VOICE_3;
	VOICES[4] = VOICE_4;
	VOICES[5] = VOICE_5;
	VOICES[6] = VOICE_6;
	VOICES[7] = VOICE_7;
	VOICES[8] = VOICE_8;
	VOICES[9] = VOICE_9;
	VOICES[10] = VOICE_10;
	VOICES[11] = VOICE_11;
	VOICES[12] = VOICE_12;
	VOICES[13] = VOICE_13;
	VOICES[14] = VOICE_14;
	VOICES[15] = VOICE_15;
	VOICES[16] = VOICE_16;
	VOICES[17] = VOICE_17;
	VOICES[18] = VOICE_18;
	VOICES[19] = VOICE_19;
	VOICES[20] = VOICE_20;
	VOICES[21] = VOICE_21;
	VOICES[22] = VOICE_22;
	VOICES[23] = VOICE_23;
}

SPU2Core_C1_t::SPU2Core_C1_t(const std::shared_ptr<IOPDmacChannel_t> & dmaChannel):
	SPU2Core_t(CORE_ID, dmaChannel)
{
	PMON0 = std::make_shared<SPU2CoreRegister_CHAN0_t>("SPU2 C1 PMON0", false, false);
	PMON1 = std::make_shared<SPU2CoreRegister_CHAN1_t>("SPU2 C1 PMON1", false, false);
	NON0 = std::make_shared<SPU2CoreRegister_CHAN0_t>("SPU2 C1 NON0", false, false);
	NON1 = std::make_shared<SPU2CoreRegister_CHAN1_t>("SPU2 C1 NON1", false, false);
	VMIXL0 = std::make_shared<SPU2CoreRegister_CHAN0_t>("SPU2 C1 VMIXL0", false, false);
	VMIXL1 = std::make_shared<SPU2CoreRegister_CHAN1_t>("SPU2 C1 VMIXL1", false, false);
	VMIXEL0 = std::make_shared<SPU2CoreRegister_CHAN0_t>("SPU2 C1 VMIXEL0", false, false);
	VMIXEL1 = std::make_shared<SPU2CoreRegister_CHAN1_t>("SPU2 C1 VMIXEL1", false, false);
	VMIXR0 = std::make_shared<SPU2CoreRegister_CHAN0_t>("SPU2 C1 VMIXR0", false, false);
	VMIXR1 = std::make_shared<SPU2CoreRegister_CHAN1_t>("SPU2 C1 VMIXR1", false, false);
	VMIXER0 = std::make_shared<SPU2CoreRegister_CHAN0_t>("SPU2 C1 VMIXER0", false, false);
	VMIXER1 = std::make_shared<SPU2CoreRegister_CHAN1_t>("SPU2 C1 VMIXER1", false, false);
	MMIX = std::make_shared<SPU2CoreRegister_MMIX_t>("SPU2 C1 MMIX", false, false);
	ATTR = std::make_shared<SPU2CoreRegister_ATTR_t>("SPU2 C1 ATTR", false, false);
	IRQAH = std::make_shared<Register16_t>("SPU2 C1 IRQAH", false, true);
	IRQAL = std::make_shared<PairRegister16_t>("SPU2 C1 IRQAL", false, true, IRQAH);
	KON0 = std::make_shared<SPU2CoreRegister_CHAN0_t>("SPU2 C1 KON0", false, false);
	KON1 = std::make_shared<SPU2CoreRegister_CHAN1_t>("SPU2 C1 KON1", false, false);
	KOF0 = std::make_shared<SPU2CoreRegister_CHAN0_t>("SPU2 C1 KOF0", false, false);
	KOF1 = std::make_shared<SPU2CoreRegister_CHAN1_t>("SPU2 C1 KOF1", false, false);
	TSAH = std::make_shared<Register16_t>("SPU2 C1 TSAH", false, true);
	TSAL = std::make_shared<PairRegister16_t>("SPU2 C1 TSAL", false, true, TSAH);
	DATA0 = std::make_shared<Register16_t>("SPU2 C1 DATA0", false, false);
	DATA1 = std::make_shared<Register16_t>("SPU2 C1 DATA1", false, false);
	ADMAS = std::make_shared<SPU2CoreRegister_ADMAS_t>("SPU2 C1 ADMAS", false, true, CORE_ID);
	ESAH = std::make_shared<Register16_t>("SPU2 C1 ESAH", false, false);
	ESAL = std::make_shared<Register16_t>("SPU2 C1 ESAL", false, false);
	APF1_SIZEH = std::make_shared<Register16_t>("SPU2 C1 APF1_SIZEH", false, false);
	APF1_SIZEL = std::make_shared<Register16_t>("SPU2 C1 APF1_SIZEL", false, false);
	APF2_SIZEH = std::make_shared<Register16_t>("SPU2 C1 APF2_SIZEH", false, false);
	APF2_SIZEL = std::make_shared<Register16_t>("SPU2 C1 APF2_SIZEL", false, false);
	SAME_L_DSTH = std::make_shared<Register16_t>("SPU2 C1 SAME_L_DSTH", false, false);
	SAME_L_DSTL = std::make_shared<Register16_t>("SPU2 C1 SAME_L_DSTL", false, false);
	SAME_R_DSTH = std::make_shared<Register16_t>("SPU2 C1 SAME_R_DSTH", false, false);
	SAME_R_DSTL = std::make_shared<Register16_t>("SPU2 C1 SAME_R_DSTL", false, false);
	COMB1_L_SRCH = std::make_shared<Register16_t>("SPU2 C1 COMB1_L_SRCH", false, false);
	COMB1_L_SRCL = std::make_shared<Register16_t>("SPU2 C1 COMB1_L_SRCL", false, false);
	COMB1_R_SRCH = std::make_shared<Register16_t>("SPU2 C1 COMB1_R_SRCH", false, false);
	COMB1_R_SRCL = std::make_shared<Register16_t>("SPU2 C1 COMB1_R_SRCL", false, false);
	COMB2_L_SRCH = std::make_shared<Register16_t>("SPU2 C1 COMB2_L_SRCH", false, false);
	COMB2_L_SRCL = std::make_shared<Register16_t>("SPU2 C1 COMB2_L_SRCL", false, false);
	COMB2_R_SRCH = std::make_shared<Register16_t>("SPU2 C1 COMB2_R_SRCH", false, false);
	COMB2_R_SRCL = std::make_shared<Register16_t>("SPU2 C1 COMB2_R_SRCL", false, false);
	SAME_L_SRCH = std::make_shared<Register16_t>("SPU2 C1 SAME_L_SRCH", false, false);
	SAME_L_SRCL = std::make_shared<Register16_t>("SPU2 C1 SAME_L_SRCL", false, false);
	SAME_R_SRCH = std::make_shared<Register16_t>("SPU2 C1 SAME_R_SRCH", false, false);
	SAME_R_SRCL = std::make_shared<Register16_t>("SPU2 C1 SAME_R_SRCL", false, false);
	DIFF_L_DSTH = std::make_shared<Register16_t>("SPU2 C1 DIFF_L_DSTH", false, false);
	DIFF_L_DSTL = std::make_shared<Register16_t>("SPU2 C1 DIFF_L_DSTL", false, false);
	DIFF_R_DSTH = std::make_shared<Register16_t>("SPU2 C1 DIFF_R_DSTH", false, false);
	DIFF_R_DSTL = std::make_shared<Register16_t>("SPU2 C1 DIFF_R_DSTL", false, false);
	COMB3_L_SRCH = std::make_shared<Register16_t>("SPU2 C1 COMB3_L_SRCH", false, false);
	COMB3_L_SRCL = std::make_shared<Register16_t>("SPU2 C1 COMB3_L_SRCL", false, false);
	COMB3_R_SRCH = std::make_shared<Register16_t>("SPU2 C1 COMB3_R_SRCH", false, false);
	COMB3_R_SRCL = std::make_shared<Register16_t>("SPU2 C1 COMB3_R_SRCL", false, false);
	COMB4_L_SRCH = std::make_shared<Register16_t>("SPU2 C1 COMB4_L_SRCH", false, false);
	COMB4_L_SRCL = std::make_shared<Register16_t>("SPU2 C1 COMB4_L_SRCL", false, false);
	COMB4_R_SRCH = std::make_shared<Register16_t>("SPU2 C1 COMB4_R_SRCH", false, false);
	COMB4_R_SRCL = std::make_shared<Register16_t>("SPU2 C1 COMB4_R_SRCL", false, false);
	DIFF_L_SRCH = std::make_shared<Register16_t>("SPU2 C1 DIFF_L_SRCH", false, false);
	DIFF_L_SRCL = std::make_shared<Register16_t>("SPU2 C1 DIFF_L_SRCL", false, false);
	DIFF_R_SRCH = std::make_shared<Register16_t>("SPU2 C1 DIFF_R_SRCH", false, false);
	DIFF_R_SRCL = std::make_shared<Register16_t>("SPU2 C1 DIFF_R_SRCL", false, false);
	APF1_L_DSTH = std::make_shared<Register16_t>("SPU2 C1 APF1_L_DSTH", false, false);
	APF1_L_DSTL = std::make_shared<Register16_t>("SPU2 C1 APF1_L_DSTL", false, false);
	APF1_R_DSTH = std::make_shared<Register16_t>("SPU2 C1 APF1_R_DSTH", false, false);
	APF1_R_DSTL = std::make_shared<Register16_t>("SPU2 C1 APF1_R_DSTL", false, false);
	APF2_L_DSTH = std::make_shared<Register16_t>("SPU2 C1 APF2_L_DSTH", false, false);
	APF2_L_DSTL = std::make_shared<Register16_t>("SPU2 C1 APF2_L_DSTL", false, false);
	APF2_R_DSTH = std::make_shared<Register16_t>("SPU2 C1 APF2_R_DSTH", false, false);
	APF2_R_DSTL = std::make_shared<Register16_t>("SPU2 C1 APF2_R_DSTL", false, false);
	EEAH = std::make_shared<Register16_t>("SPU2 C1 EEAH", false, false);
	EEAL = std::make_shared<Register16_t>("SPU2 C1 EEAL", false, false);
	ENDX0 = std::make_shared<Register16_t>("SPU2 C1 ENDX0", false, false);
	ENDX1 = std::make_shared<Register16_t>("SPU2 C1 ENDX1", false, false);
	STATX = std::make_shared<SPU2CoreRegister_STATX_t>("SPU2 C1 STATX", true, false);
	MVOLL = std::make_shared<SPU2CoreRegister_VOL_t>("SPU2 C1 MVOLL", false, false);
	MVOLR = std::make_shared<SPU2CoreRegister_VOL_t>("SPU2 C1 MVOLR", false, false);
	EVOLL = std::make_shared<Register16_t>("SPU2 C1 EVOLL", false, false);
	EVOLR = std::make_shared<Register16_t>("SPU2 C1 EVOLR", false, false);
	AVOLL = std::make_shared<Register16_t>("SPU2 C1 AVOLL", false, false);
	AVOLR = std::make_shared<Register16_t>("SPU2 C1 AVOLR", false, false);
	BVOLL = std::make_shared<Register16_t>("SPU2 C1 BVOLL", false, false);
	BVOLR = std::make_shared<Register16_t>("SPU2 C1 BVOLR", false, false);
	MVOLXL = std::make_shared<Register16_t>("SPU2 C1 MVOLXL", false, false);
	MVOLXR = std::make_shared<Register16_t>("SPU2 C1 MVOLXR", false, false);
	IIR_VOL = std::make_shared<Register16_t>("SPU2 C1 IIR_VOL", false, false);
	COMB1_VOL = std::make_shared<Register16_t>("SPU2 C1 COMB1_VOL", false, false);
	COMB2_VOL = std::make_shared<Register16_t>("SPU2 C1 COMB2_VOL", false, false);
	COMB3_VOL = std::make_shared<Register16_t>("SPU2 C1 COMB3_VOL", false, false);
	COMB4_VOL = std::make_shared<Register16_t>("SPU2 C1 COMB4_VOL", false, false);
	WALL_VOL = std::make_shared<Register16_t>("SPU2 C1 WALL_VOL", false, false);
	APF1_VOL = std::make_shared<Register16_t>("SPU2 C1 APF1_VOL", false, false);
	APF2_VOL = std::make_shared<Register16_t>("SPU2 C1 APF2_VOL", false, false);
	IN_COEF_L = std::make_shared<Register16_t>("SPU2 C1 IN_COEF_L", false, false);
	IN_COEF_R = std::make_shared<Register16_t>("SPU2 C1 IN_COEF_R", false, false);
	VOICE_0 = std::make_shared<SPU2CoreVoice_C1V0_t>();
	VOICE_1 = std::make_shared<SPU2CoreVoice_C1V1_t>();
	VOICE_2 = std::make_shared<SPU2CoreVoice_C1V2_t>();
	VOICE_3 = std::make_shared<SPU2CoreVoice_C1V3_t>();
	VOICE_4 = std::make_shared<SPU2CoreVoice_C1V4_t>();
	VOICE_5 = std::make_shared<SPU2CoreVoice_C1V5_t>();
	VOICE_6 = std::make_shared<SPU2CoreVoice_C1V6_t>();
	VOICE_7 = std::make_shared<SPU2CoreVoice_C1V7_t>();
	VOICE_8 = std::make_shared<SPU2CoreVoice_C1V8_t>();
	VOICE_9 = std::make_shared<SPU2CoreVoice_C1V9_t>();
	VOICE_10 = std::make_shared<SPU2CoreVoice_C1V10_t>();
	VOICE_11 = std::make_shared<SPU2CoreVoice_C1V11_t>();
	VOICE_12 = std::make_shared<SPU2CoreVoice_C1V12_t>();
	VOICE_13 = std::make_shared<SPU2CoreVoice_C1V13_t>();
	VOICE_14 = std::make_shared<SPU2CoreVoice_C1V14_t>();
	VOICE_15 = std::make_shared<SPU2CoreVoice_C1V15_t>();
	VOICE_16 = std::make_shared<SPU2CoreVoice_C1V16_t>();
	VOICE_17 = std::make_shared<SPU2CoreVoice_C1V17_t>();
	VOICE_18 = std::make_shared<SPU2CoreVoice_C1V18_t>();
	VOICE_19 = std::make_shared<SPU2CoreVoice_C1V19_t>();
	VOICE_20 = std::make_shared<SPU2CoreVoice_C1V20_t>();
	VOICE_21 = std::make_shared<SPU2CoreVoice_C1V21_t>();
	VOICE_22 = std::make_shared<SPU2CoreVoice_C1V22_t>();
	VOICE_23 = std::make_shared<SPU2CoreVoice_C1V23_t>();
	VOICES[0] = VOICE_0;
	VOICES[1] = VOICE_1;
	VOICES[2] = VOICE_2;
	VOICES[3] = VOICE_3;
	VOICES[4] = VOICE_4;
	VOICES[5] = VOICE_5;
	VOICES[6] = VOICE_6;
	VOICES[7] = VOICE_7;
	VOICES[8] = VOICE_8;
	VOICES[9] = VOICE_9;
	VOICES[10] = VOICE_10;
	VOICES[11] = VOICE_11;
	VOICES[12] = VOICE_12;
	VOICES[13] = VOICE_13;
	VOICES[14] = VOICE_14;
	VOICES[15] = VOICE_15;
	VOICES[16] = VOICE_16;
	VOICES[17] = VOICE_17;
	VOICES[18] = VOICE_18;
	VOICES[19] = VOICE_19;
	VOICES[20] = VOICE_20;
	VOICES[21] = VOICE_21;
	VOICES[22] = VOICE_22;
	VOICES[23] = VOICE_23;
}