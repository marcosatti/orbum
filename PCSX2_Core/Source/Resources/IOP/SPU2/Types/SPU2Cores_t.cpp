#include "stdafx.h"

#include "Common/Types/Register/Register16_t.h"
#include "Common/Types/Memory/ByteMemory_t.h"

#include "Resources/IOP/SPU2/Types/SPU2Cores_t.h"
#include "Resources/IOP/SPU2/Types/SPU2CoreRegisters_t.h"
#include "Resources/IOP/SPU2/Types/SPU2CoreVoices_t.h"

SPU2Core_t::SPU2Core_t() :
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
	IRQAL(nullptr),
	IRQAH(nullptr),
	KON0(nullptr),
	KON1(nullptr),
	KOF0(nullptr),
	KOF1(nullptr),
	TSAL(nullptr),
	TSAH(nullptr),
	DATA0(nullptr),
	DATA1(nullptr),
	DATA2(nullptr),
	ESAL(nullptr),
	ESAH(nullptr),
	APF1_SIZEL(nullptr),
	APF1_SIZEH(nullptr),
	APF2_SIZEL(nullptr),
	APF2_SIZEH(nullptr),
	SAME_L_DSTL(nullptr),
	SAME_L_DSTH(nullptr),
	SAME_R_DSTL(nullptr),
	SAME_R_DSTH(nullptr),
	COMB1_L_SRCL(nullptr),
	COMB1_L_SRCH(nullptr),
	COMB1_R_SRCL(nullptr),
	COMB1_R_SRCH(nullptr),
	COMB2_L_SRCL(nullptr),
	COMB2_L_SRCH(nullptr),
	COMB2_R_SRCL(nullptr),
	COMB2_R_SRCH(nullptr),
	SAME_L_SRCL(nullptr),
	SAME_L_SRCH(nullptr),
	SAME_R_SRCL(nullptr),
	SAME_R_SRCH(nullptr),
	DIFF_L_DSTL(nullptr),
	DIFF_L_DSTH(nullptr),
	DIFF_R_DSTL(nullptr),
	DIFF_R_DSTH(nullptr),
	COMB3_L_SRCL(nullptr),
	COMB3_L_SRCH(nullptr),
	COMB3_R_SRCL(nullptr),
	COMB3_R_SRCH(nullptr),
	COMB4_L_SRCL(nullptr),
	COMB4_L_SRCH(nullptr),
	COMB4_R_SRCL(nullptr),
	COMB4_R_SRCH(nullptr),
	DIFF_L_SRCL(nullptr),
	DIFF_L_SRCH(nullptr),
	DIFF_R_SRCL(nullptr),
	DIFF_R_SRCH(nullptr),
	APF1_L_DSTL(nullptr),
	APF1_L_DSTH(nullptr),
	APF1_R_DSTL(nullptr),
	APF1_R_DSTH(nullptr),
	APF2_L_DSTL(nullptr),
	APF2_L_DSTH(nullptr),
	APF2_R_DSTL(nullptr),
	APF2_R_DSTH(nullptr),
	EEAL(nullptr),
	EEAH(nullptr),
	ENDX0(nullptr),
	ENDX1(nullptr),
	STATX(nullptr),
	MEMORY_0X46(nullptr),
	VOICES{ nullptr }
{
}

SPU2Core_C0_t::SPU2Core_C0_t()
{
	PMON0 = std::make_shared<SPU2CoreRegister_CHAN0_t>("SPU2 C0 PMON0", false, true);
	PMON1 = std::make_shared<SPU2CoreRegister_CHAN1_t>("SPU2 C0 PMON1", false, true);
	NON0 = std::make_shared<SPU2CoreRegister_CHAN0_t>("SPU2 C0 NON0", false, true);
	NON1 = std::make_shared<SPU2CoreRegister_CHAN1_t>("SPU2 C0 NON1", false, true);
	VMIXL0 = std::make_shared<SPU2CoreRegister_CHAN0_t>("SPU2 C0 VMIXL0", false, true);
	VMIXL1 = std::make_shared<SPU2CoreRegister_CHAN1_t>("SPU2 C0 VMIXL1", false, true);
	VMIXEL0 = std::make_shared<SPU2CoreRegister_CHAN0_t>("SPU2 C0 VMIXEL0", false, true);
	VMIXEL1 = std::make_shared<SPU2CoreRegister_CHAN1_t>("SPU2 C0 VMIXEL1", false, true);
	VMIXR0 = std::make_shared<SPU2CoreRegister_CHAN0_t>("SPU2 C0 VMIXR0", false, true);
	VMIXR1 = std::make_shared<SPU2CoreRegister_CHAN1_t>("SPU2 C0 VMIXR1", false, true);
	VMIXER0 = std::make_shared<SPU2CoreRegister_CHAN0_t>("SPU2 C0 VMIXER0", false, true);
	VMIXER1 = std::make_shared<SPU2CoreRegister_CHAN1_t>("SPU2 C0 VMIXER1", false, true);
	MMIX = std::make_shared<SPU2CoreRegister_MMIX_t>("SPU2 C0 MMIX", false, true);
	ATTR = std::make_shared<SPU2CoreRegister_ATTR_t>("SPU2 C0 ATTR", false, true);
	IRQAL = std::make_shared<Register16_t>("SPU2 C0 IRQAL", false, true);
	IRQAH = std::make_shared<Register16_t>("SPU2 C0 IRQAH", false, true);
	KON0 = std::make_shared<SPU2CoreRegister_CHAN0_t>("SPU2 C0 KON0", false, true);
	KON1 = std::make_shared<SPU2CoreRegister_CHAN1_t>("SPU2 C0 KON1", false, true);
	KOF0 = std::make_shared<SPU2CoreRegister_CHAN0_t>("SPU2 C0 KOF0", false, true);
	KOF1 = std::make_shared<SPU2CoreRegister_CHAN1_t>("SPU2 C0 KOF1", false, true);
	TSAL = std::make_shared<Register16_t>("SPU2 C0 TSAL", false, true);
	TSAH = std::make_shared<Register16_t>("SPU2 C0 TSAH", false, true);
	DATA0 = std::make_shared<Register16_t>("SPU2 C0 DATA0", false, true);
	DATA1 = std::make_shared<Register16_t>("SPU2 C0 DATA1", false, true);
	DATA2 = std::make_shared<Register16_t>("SPU2 C0 DATA2", false, true);
	ESAL = std::make_shared<Register16_t>("SPU2 C0 ESAL", false, true);
	ESAH = std::make_shared<Register16_t>("SPU2 C0 ESAH", false, true);
	APF1_SIZEL = std::make_shared<Register16_t>("SPU2 C0 APF1_SIZEL", false, true);
	APF1_SIZEH = std::make_shared<Register16_t>("SPU2 C0 APF1_SIZEH", false, true);
	APF2_SIZEL = std::make_shared<Register16_t>("SPU2 C0 APF2_SIZEL", false, true);
	APF2_SIZEH = std::make_shared<Register16_t>("SPU2 C0 APF2_SIZEH", false, true);
	SAME_L_DSTL = std::make_shared<Register16_t>("SPU2 C0 SAME_L_DSTL", false, true);
	SAME_L_DSTH = std::make_shared<Register16_t>("SPU2 C0 SAME_L_DSTH", false, true);
	SAME_R_DSTL = std::make_shared<Register16_t>("SPU2 C0 SAME_R_DSTL", false, true);
	SAME_R_DSTH = std::make_shared<Register16_t>("SPU2 C0 SAME_R_DSTH", false, true);
	COMB1_L_SRCL = std::make_shared<Register16_t>("SPU2 C0 COMB1_L_SRCL", false, true);
	COMB1_L_SRCH = std::make_shared<Register16_t>("SPU2 C0 COMB1_L_SRCH", false, true);
	COMB1_R_SRCL = std::make_shared<Register16_t>("SPU2 C0 COMB1_R_SRCL", false, true);
	COMB1_R_SRCH = std::make_shared<Register16_t>("SPU2 C0 COMB1_R_SRCH", false, true);
	COMB2_L_SRCL = std::make_shared<Register16_t>("SPU2 C0 COMB2_L_SRCL", false, true);
	COMB2_L_SRCH = std::make_shared<Register16_t>("SPU2 C0 COMB2_L_SRCH", false, true);
	COMB2_R_SRCL = std::make_shared<Register16_t>("SPU2 C0 COMB2_R_SRCL", false, true);
	COMB2_R_SRCH = std::make_shared<Register16_t>("SPU2 C0 COMB2_R_SRCH", false, true);
	SAME_L_SRCL = std::make_shared<Register16_t>("SPU2 C0 SAME_L_SRCL", false, true);
	SAME_L_SRCH = std::make_shared<Register16_t>("SPU2 C0 SAME_L_SRCH", false, true);
	SAME_R_SRCL = std::make_shared<Register16_t>("SPU2 C0 SAME_R_SRCL", false, true);
	SAME_R_SRCH = std::make_shared<Register16_t>("SPU2 C0 SAME_R_SRCH", false, true);
	DIFF_L_DSTL = std::make_shared<Register16_t>("SPU2 C0 DIFF_L_DSTL", false, true);
	DIFF_L_DSTH = std::make_shared<Register16_t>("SPU2 C0 DIFF_L_DSTH", false, true);
	DIFF_R_DSTL = std::make_shared<Register16_t>("SPU2 C0 DIFF_R_DSTL", false, true);
	DIFF_R_DSTH = std::make_shared<Register16_t>("SPU2 C0 DIFF_R_DSTH", false, true);
	COMB3_L_SRCL = std::make_shared<Register16_t>("SPU2 C0 COMB3_L_SRCL", false, true);
	COMB3_L_SRCH = std::make_shared<Register16_t>("SPU2 C0 COMB3_L_SRCH", false, true);
	COMB3_R_SRCL = std::make_shared<Register16_t>("SPU2 C0 COMB3_R_SRCL", false, true);
	COMB3_R_SRCH = std::make_shared<Register16_t>("SPU2 C0 COMB3_R_SRCH", false, true);
	COMB4_L_SRCL = std::make_shared<Register16_t>("SPU2 C0 COMB4_L_SRCL", false, true);
	COMB4_L_SRCH = std::make_shared<Register16_t>("SPU2 C0 COMB4_L_SRCH", false, true);
	COMB4_R_SRCL = std::make_shared<Register16_t>("SPU2 C0 COMB4_R_SRCL", false, true);
	COMB4_R_SRCH = std::make_shared<Register16_t>("SPU2 C0 COMB4_R_SRCH", false, true);
	DIFF_L_SRCL = std::make_shared<Register16_t>("SPU2 C0 DIFF_L_SRCL", false, true);
	DIFF_L_SRCH = std::make_shared<Register16_t>("SPU2 C0 DIFF_L_SRCH", false, true);
	DIFF_R_SRCL = std::make_shared<Register16_t>("SPU2 C0 DIFF_R_SRCL", false, true);
	DIFF_R_SRCH = std::make_shared<Register16_t>("SPU2 C0 DIFF_R_SRCH", false, true);
	APF1_L_DSTL = std::make_shared<Register16_t>("SPU2 C0 APF1_L_DSTL", false, true);
	APF1_L_DSTH = std::make_shared<Register16_t>("SPU2 C0 APF1_L_DSTH", false, true);
	APF1_R_DSTL = std::make_shared<Register16_t>("SPU2 C0 APF1_R_DSTL", false, true);
	APF1_R_DSTH = std::make_shared<Register16_t>("SPU2 C0 APF1_R_DSTH", false, true);
	APF2_L_DSTL = std::make_shared<Register16_t>("SPU2 C0 APF2_L_DSTL", false, true);
	APF2_L_DSTH = std::make_shared<Register16_t>("SPU2 C0 APF2_L_DSTH", false, true);
	APF2_R_DSTL = std::make_shared<Register16_t>("SPU2 C0 APF2_R_DSTL", false, true);
	APF2_R_DSTH = std::make_shared<Register16_t>("SPU2 C0 APF2_R_DSTH", false, true);
	EEAL = std::make_shared<Register16_t>("SPU2 C0 EEAL", false, true);
	EEAH = std::make_shared<Register16_t>("SPU2 C0 EEAH", false, true);
	ENDX0 = std::make_shared<Register16_t>("SPU2 C0 ENDX0", false, true);
	ENDX1 = std::make_shared<Register16_t>("SPU2 C0 ENDX1", false, true);
	STATX = std::make_shared<Register16_t>("SPU2 C0 STATX", false, true);
	MEMORY_0X46 = std::make_shared<ByteMemory_t>("SPU2 C0 MEMORY_0346", false, true, 0xBA);
	VOICES[0] = std::make_shared<SPU2CoreVoice_C0V0_t>();
	VOICES[1] = std::make_shared<SPU2CoreVoice_C0V1_t>();
	VOICES[2] = std::make_shared<SPU2CoreVoice_C0V2_t>();
	VOICES[3] = std::make_shared<SPU2CoreVoice_C0V3_t>();
	VOICES[4] = std::make_shared<SPU2CoreVoice_C0V4_t>();
	VOICES[5] = std::make_shared<SPU2CoreVoice_C0V5_t>();
	VOICES[6] = std::make_shared<SPU2CoreVoice_C0V6_t>();
	VOICES[7] = std::make_shared<SPU2CoreVoice_C0V7_t>();
	VOICES[8] = std::make_shared<SPU2CoreVoice_C0V8_t>();
	VOICES[9] = std::make_shared<SPU2CoreVoice_C0V9_t>();
	VOICES[10] = std::make_shared<SPU2CoreVoice_C0V10_t>();
	VOICES[11] = std::make_shared<SPU2CoreVoice_C0V11_t>();
	VOICES[12] = std::make_shared<SPU2CoreVoice_C0V12_t>();
	VOICES[13] = std::make_shared<SPU2CoreVoice_C0V13_t>();
	VOICES[14] = std::make_shared<SPU2CoreVoice_C0V14_t>();
	VOICES[15] = std::make_shared<SPU2CoreVoice_C0V15_t>();
	VOICES[16] = std::make_shared<SPU2CoreVoice_C0V16_t>();
	VOICES[17] = std::make_shared<SPU2CoreVoice_C0V17_t>();
	VOICES[18] = std::make_shared<SPU2CoreVoice_C0V18_t>();
	VOICES[19] = std::make_shared<SPU2CoreVoice_C0V19_t>();
	VOICES[20] = std::make_shared<SPU2CoreVoice_C0V20_t>();
	VOICES[21] = std::make_shared<SPU2CoreVoice_C0V21_t>();
	VOICES[22] = std::make_shared<SPU2CoreVoice_C0V22_t>();
	VOICES[23] = std::make_shared<SPU2CoreVoice_C0V23_t>();
}

SPU2Core_C1_t::SPU2Core_C1_t()
{
	PMON0 = std::make_shared<SPU2CoreRegister_CHAN0_t>("SPU2 C1 PMON0", false, true);
	PMON1 = std::make_shared<SPU2CoreRegister_CHAN1_t>("SPU2 C1 PMON1", false, true);
	NON0 = std::make_shared<SPU2CoreRegister_CHAN0_t>("SPU2 C1 NON0", false, true);
	NON1 = std::make_shared<SPU2CoreRegister_CHAN1_t>("SPU2 C1 NON1", false, true);
	VMIXL0 = std::make_shared<SPU2CoreRegister_CHAN0_t>("SPU2 C1 VMIXL0", false, true);
	VMIXL1 = std::make_shared<SPU2CoreRegister_CHAN1_t>("SPU2 C1 VMIXL1", false, true);
	VMIXEL0 = std::make_shared<SPU2CoreRegister_CHAN0_t>("SPU2 C1 VMIXEL0", false, true);
	VMIXEL1 = std::make_shared<SPU2CoreRegister_CHAN1_t>("SPU2 C1 VMIXEL1", false, true);
	VMIXR0 = std::make_shared<SPU2CoreRegister_CHAN0_t>("SPU2 C1 VMIXR0", false, true);
	VMIXR1 = std::make_shared<SPU2CoreRegister_CHAN1_t>("SPU2 C1 VMIXR1", false, true);
	VMIXER0 = std::make_shared<SPU2CoreRegister_CHAN0_t>("SPU2 C1 VMIXER0", false, true);
	VMIXER1 = std::make_shared<SPU2CoreRegister_CHAN1_t>("SPU2 C1 VMIXER1", false, true);
	MMIX = std::make_shared<SPU2CoreRegister_MMIX_t>("SPU2 C1 MMIX", false, true);
	ATTR = std::make_shared<SPU2CoreRegister_ATTR_t>("SPU2 C1 ATTR", false, true);
	IRQAL = std::make_shared<Register16_t>("SPU2 C1 IRQAL", false, true);
	IRQAH = std::make_shared<Register16_t>("SPU2 C1 IRQAH", false, true);
	KON0 = std::make_shared<SPU2CoreRegister_CHAN0_t>("SPU2 C1 KON0", false, true);
	KON1 = std::make_shared<SPU2CoreRegister_CHAN1_t>("SPU2 C1 KON1", false, true);
	KOF0 = std::make_shared<SPU2CoreRegister_CHAN0_t>("SPU2 C1 KOF0", false, true);
	KOF1 = std::make_shared<SPU2CoreRegister_CHAN1_t>("SPU2 C1 KOF1", false, true);
	TSAL = std::make_shared<Register16_t>("SPU2 C1 TSAL", false, true);
	TSAH = std::make_shared<Register16_t>("SPU2 C1 TSAH", false, true);
	DATA0 = std::make_shared<Register16_t>("SPU2 C1 DATA0", false, true);
	DATA1 = std::make_shared<Register16_t>("SPU2 C1 DATA1", false, true);
	DATA2 = std::make_shared<Register16_t>("SPU2 C1 DATA2", false, true);
	ESAL = std::make_shared<Register16_t>("SPU2 C1 ESAL", false, true);
	ESAH = std::make_shared<Register16_t>("SPU2 C1 ESAH", false, true);
	APF1_SIZEL = std::make_shared<Register16_t>("SPU2 C1 APF1_SIZEL", false, true);
	APF1_SIZEH = std::make_shared<Register16_t>("SPU2 C1 APF1_SIZEH", false, true);
	APF2_SIZEL = std::make_shared<Register16_t>("SPU2 C1 APF2_SIZEL", false, true);
	APF2_SIZEH = std::make_shared<Register16_t>("SPU2 C1 APF2_SIZEH", false, true);
	SAME_L_DSTL = std::make_shared<Register16_t>("SPU2 C1 SAME_L_DSTL", false, true);
	SAME_L_DSTH = std::make_shared<Register16_t>("SPU2 C1 SAME_L_DSTH", false, true);
	SAME_R_DSTL = std::make_shared<Register16_t>("SPU2 C1 SAME_R_DSTL", false, true);
	SAME_R_DSTH = std::make_shared<Register16_t>("SPU2 C1 SAME_R_DSTH", false, true);
	COMB1_L_SRCL = std::make_shared<Register16_t>("SPU2 C1 COMB1_L_SRCL", false, true);
	COMB1_L_SRCH = std::make_shared<Register16_t>("SPU2 C1 COMB1_L_SRCH", false, true);
	COMB1_R_SRCL = std::make_shared<Register16_t>("SPU2 C1 COMB1_R_SRCL", false, true);
	COMB1_R_SRCH = std::make_shared<Register16_t>("SPU2 C1 COMB1_R_SRCH", false, true);
	COMB2_L_SRCL = std::make_shared<Register16_t>("SPU2 C1 COMB2_L_SRCL", false, true);
	COMB2_L_SRCH = std::make_shared<Register16_t>("SPU2 C1 COMB2_L_SRCH", false, true);
	COMB2_R_SRCL = std::make_shared<Register16_t>("SPU2 C1 COMB2_R_SRCL", false, true);
	COMB2_R_SRCH = std::make_shared<Register16_t>("SPU2 C1 COMB2_R_SRCH", false, true);
	SAME_L_SRCL = std::make_shared<Register16_t>("SPU2 C1 SAME_L_SRCL", false, true);
	SAME_L_SRCH = std::make_shared<Register16_t>("SPU2 C1 SAME_L_SRCH", false, true);
	SAME_R_SRCL = std::make_shared<Register16_t>("SPU2 C1 SAME_R_SRCL", false, true);
	SAME_R_SRCH = std::make_shared<Register16_t>("SPU2 C1 SAME_R_SRCH", false, true);
	DIFF_L_DSTL = std::make_shared<Register16_t>("SPU2 C1 DIFF_L_DSTL", false, true);
	DIFF_L_DSTH = std::make_shared<Register16_t>("SPU2 C1 DIFF_L_DSTH", false, true);
	DIFF_R_DSTL = std::make_shared<Register16_t>("SPU2 C1 DIFF_R_DSTL", false, true);
	DIFF_R_DSTH = std::make_shared<Register16_t>("SPU2 C1 DIFF_R_DSTH", false, true);
	COMB3_L_SRCL = std::make_shared<Register16_t>("SPU2 C1 COMB3_L_SRCL", false, true);
	COMB3_L_SRCH = std::make_shared<Register16_t>("SPU2 C1 COMB3_L_SRCH", false, true);
	COMB3_R_SRCL = std::make_shared<Register16_t>("SPU2 C1 COMB3_R_SRCL", false, true);
	COMB3_R_SRCH = std::make_shared<Register16_t>("SPU2 C1 COMB3_R_SRCH", false, true);
	COMB4_L_SRCL = std::make_shared<Register16_t>("SPU2 C1 COMB4_L_SRCL", false, true);
	COMB4_L_SRCH = std::make_shared<Register16_t>("SPU2 C1 COMB4_L_SRCH", false, true);
	COMB4_R_SRCL = std::make_shared<Register16_t>("SPU2 C1 COMB4_R_SRCL", false, true);
	COMB4_R_SRCH = std::make_shared<Register16_t>("SPU2 C1 COMB4_R_SRCH", false, true);
	DIFF_L_SRCL = std::make_shared<Register16_t>("SPU2 C1 DIFF_L_SRCL", false, true);
	DIFF_L_SRCH = std::make_shared<Register16_t>("SPU2 C1 DIFF_L_SRCH", false, true);
	DIFF_R_SRCL = std::make_shared<Register16_t>("SPU2 C1 DIFF_R_SRCL", false, true);
	DIFF_R_SRCH = std::make_shared<Register16_t>("SPU2 C1 DIFF_R_SRCH", false, true);
	APF1_L_DSTL = std::make_shared<Register16_t>("SPU2 C1 APF1_L_DSTL", false, true);
	APF1_L_DSTH = std::make_shared<Register16_t>("SPU2 C1 APF1_L_DSTH", false, true);
	APF1_R_DSTL = std::make_shared<Register16_t>("SPU2 C1 APF1_R_DSTL", false, true);
	APF1_R_DSTH = std::make_shared<Register16_t>("SPU2 C1 APF1_R_DSTH", false, true);
	APF2_L_DSTL = std::make_shared<Register16_t>("SPU2 C1 APF2_L_DSTL", false, true);
	APF2_L_DSTH = std::make_shared<Register16_t>("SPU2 C1 APF2_L_DSTH", false, true);
	APF2_R_DSTL = std::make_shared<Register16_t>("SPU2 C1 APF2_R_DSTL", false, true);
	APF2_R_DSTH = std::make_shared<Register16_t>("SPU2 C1 APF2_R_DSTH", false, true);
	EEAL = std::make_shared<Register16_t>("SPU2 C1 EEAL", false, true);
	EEAH = std::make_shared<Register16_t>("SPU2 C1 EEAH", false, true);
	ENDX0 = std::make_shared<Register16_t>("SPU2 C1 ENDX0", false, true);
	ENDX1 = std::make_shared<Register16_t>("SPU2 C1 ENDX1", false, true);
	STATX = std::make_shared<Register16_t>("SPU2 C1 STATX", false, true);
	MEMORY_0X46 = std::make_shared<ByteMemory_t>("SPU2 C1 MEMORY_0746", false, true, 0xBA);
	VOICES[0] = std::make_shared<SPU2CoreVoice_C1V0_t>();
	VOICES[1] = std::make_shared<SPU2CoreVoice_C1V1_t>();
	VOICES[2] = std::make_shared<SPU2CoreVoice_C1V2_t>();
	VOICES[3] = std::make_shared<SPU2CoreVoice_C1V3_t>();
	VOICES[4] = std::make_shared<SPU2CoreVoice_C1V4_t>();
	VOICES[5] = std::make_shared<SPU2CoreVoice_C1V5_t>();
	VOICES[6] = std::make_shared<SPU2CoreVoice_C1V6_t>();
	VOICES[7] = std::make_shared<SPU2CoreVoice_C1V7_t>();
	VOICES[8] = std::make_shared<SPU2CoreVoice_C1V8_t>();
	VOICES[9] = std::make_shared<SPU2CoreVoice_C1V9_t>();
	VOICES[10] = std::make_shared<SPU2CoreVoice_C1V10_t>();
	VOICES[11] = std::make_shared<SPU2CoreVoice_C1V11_t>();
	VOICES[12] = std::make_shared<SPU2CoreVoice_C1V12_t>();
	VOICES[13] = std::make_shared<SPU2CoreVoice_C1V13_t>();
	VOICES[14] = std::make_shared<SPU2CoreVoice_C1V14_t>();
	VOICES[15] = std::make_shared<SPU2CoreVoice_C1V15_t>();
	VOICES[16] = std::make_shared<SPU2CoreVoice_C1V16_t>();
	VOICES[17] = std::make_shared<SPU2CoreVoice_C1V17_t>();
	VOICES[18] = std::make_shared<SPU2CoreVoice_C1V18_t>();
	VOICES[19] = std::make_shared<SPU2CoreVoice_C1V19_t>();
	VOICES[20] = std::make_shared<SPU2CoreVoice_C1V20_t>();
	VOICES[21] = std::make_shared<SPU2CoreVoice_C1V21_t>();
	VOICES[22] = std::make_shared<SPU2CoreVoice_C1V22_t>();
	VOICES[23] = std::make_shared<SPU2CoreVoice_C1V23_t>();
}
