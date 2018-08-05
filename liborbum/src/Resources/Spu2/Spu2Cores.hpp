#pragma once

#include "Common/Constants.hpp"
#include "Common/Types/FifoQueue/DmaFifoQueue.hpp"
#include "Resources/Spu2/Spu2CoreConstants.hpp"
#include "Resources/Spu2/Spu2CoreRegisters.hpp"
#include "Resources/Spu2/Spu2CoreVoice.hpp"

/// Base class representing a SPU2 core.
/// There are 2 individual cores in the SPU2, each with 24 voice channels.
class Spu2Core_Base
{
public:
    Spu2Core_Base(const int core_id);

    /// Associated DMA FIFO queue attached to this core.
    DmaFifoQueue<>* dma_fifo_queue;

    /// SPU2 Core ID.
    const int core_id;

    /// SPU2 Core registers.
    Spu2CoreRegister_Chan0 pmon0;
    Spu2CoreRegister_Chan1 pmon1;
    Spu2CoreRegister_Chan0 non0;
    Spu2CoreRegister_Chan1 non1;
    Spu2CoreRegister_Chan0 vmixl0;
    Spu2CoreRegister_Chan1 vmixl1;
    Spu2CoreRegister_Chan0 vmixel0;
    Spu2CoreRegister_Chan1 vmixel1;
    Spu2CoreRegister_Chan0 vmixr0;
    Spu2CoreRegister_Chan1 vmixr1;
    Spu2CoreRegister_Chan0 vmixer0;
    Spu2CoreRegister_Chan1 vmixer1;
    Spu2CoreRegister_Mmix mmix;
    Spu2CoreRegister_Attr attr;
    SizedHwordRegister irqah;
    SizedHwordRegister irqal;
    Spu2CoreRegister_Chan0 kon0;
    Spu2CoreRegister_Chan1 kon1;
    Spu2CoreRegister_Chan0 kof0;
    Spu2CoreRegister_Chan1 kof1;
    SizedHwordRegister tsah;
    SizedHwordRegister tsal;
    SizedHwordRegister data0;
    SizedHwordRegister data1;
    Spu2CoreRegister_Admas admas; // "AutoDMA Status".
    SizedHwordRegister esah;
    SizedHwordRegister esal;
    SizedHwordRegister apf1_sizeh;
    SizedHwordRegister apf1_sizel;
    SizedHwordRegister apf2_sizeh;
    SizedHwordRegister apf2_sizel;
    SizedHwordRegister same_l_dsth;
    SizedHwordRegister same_l_dstl;
    SizedHwordRegister same_r_dsth;
    SizedHwordRegister same_r_dstl;
    SizedHwordRegister comb1_l_srch;
    SizedHwordRegister comb1_l_srcl;
    SizedHwordRegister comb1_r_srch;
    SizedHwordRegister comb1_r_srcl;
    SizedHwordRegister comb2_l_srch;
    SizedHwordRegister comb2_l_srcl;
    SizedHwordRegister comb2_r_srch;
    SizedHwordRegister comb2_r_srcl;
    SizedHwordRegister same_l_srch;
    SizedHwordRegister same_l_srcl;
    SizedHwordRegister same_r_srch;
    SizedHwordRegister same_r_srcl;
    SizedHwordRegister diff_l_dsth;
    SizedHwordRegister diff_l_dstl;
    SizedHwordRegister diff_r_dsth;
    SizedHwordRegister diff_r_dstl;
    SizedHwordRegister comb3_l_srch;
    SizedHwordRegister comb3_l_srcl;
    SizedHwordRegister comb3_r_srch;
    SizedHwordRegister comb3_r_srcl;
    SizedHwordRegister comb4_l_srch;
    SizedHwordRegister comb4_l_srcl;
    SizedHwordRegister comb4_r_srch;
    SizedHwordRegister comb4_r_srcl;
    SizedHwordRegister diff_l_srch;
    SizedHwordRegister diff_l_srcl;
    SizedHwordRegister diff_r_srch;
    SizedHwordRegister diff_r_srcl;
    SizedHwordRegister apf1_l_dsth;
    SizedHwordRegister apf1_l_dstl;
    SizedHwordRegister apf1_r_dsth;
    SizedHwordRegister apf1_r_dstl;
    SizedHwordRegister apf2_l_dsth;
    SizedHwordRegister apf2_l_dstl;
    SizedHwordRegister apf2_r_dsth;
    SizedHwordRegister apf2_r_dstl;
    SizedHwordRegister eeah;
    SizedHwordRegister eeal;
    SizedHwordRegister endx0;
    SizedHwordRegister endx1;
    Spu2CoreRegister_Statx statx;
    Spu2CoreRegister_Vol mvoll;
    Spu2CoreRegister_Vol mvolr;
    SizedHwordRegister evoll;
    SizedHwordRegister evolr;
    SizedHwordRegister avoll;
    SizedHwordRegister avolr;
    SizedHwordRegister bvoll;
    SizedHwordRegister bvolr;
    SizedHwordRegister mvolxl;
    SizedHwordRegister mvolxr;
    SizedHwordRegister iir_vol;
    SizedHwordRegister comb1_vol;
    SizedHwordRegister comb2_vol;
    SizedHwordRegister comb3_vol;
    SizedHwordRegister comb4_vol;
    SizedHwordRegister wall_vol;
    SizedHwordRegister apf1_vol;
    SizedHwordRegister apf2_vol;
    SizedHwordRegister in_coef_l;
    SizedHwordRegister in_coef_r;

    /// SPU2 Core voice channels.
    /// There are 24 voices in total.
    Spu2CoreVoice voice_0;
    Spu2CoreVoice voice_1;
    Spu2CoreVoice voice_2;
    Spu2CoreVoice voice_3;
    Spu2CoreVoice voice_4;
    Spu2CoreVoice voice_5;
    Spu2CoreVoice voice_6;
    Spu2CoreVoice voice_7;
    Spu2CoreVoice voice_8;
    Spu2CoreVoice voice_9;
    Spu2CoreVoice voice_10;
    Spu2CoreVoice voice_11;
    Spu2CoreVoice voice_12;
    Spu2CoreVoice voice_13;
    Spu2CoreVoice voice_14;
    Spu2CoreVoice voice_15;
    Spu2CoreVoice voice_16;
    Spu2CoreVoice voice_17;
    Spu2CoreVoice voice_18;
    Spu2CoreVoice voice_19;
    Spu2CoreVoice voice_20;
    Spu2CoreVoice voice_21;
    Spu2CoreVoice voice_22;
    Spu2CoreVoice voice_23;
    Spu2CoreVoice* voices[Constants::SPU2::NUMBER_CORE_VOICES];

    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(
            CEREAL_NVP(core_id),
            CEREAL_NVP(pmon0),
            CEREAL_NVP(pmon1),
            CEREAL_NVP(non0),
            CEREAL_NVP(non1),
            CEREAL_NVP(vmixl0),
            CEREAL_NVP(vmixl1),
            CEREAL_NVP(vmixel0),
            CEREAL_NVP(vmixel1),
            CEREAL_NVP(vmixr0),
            CEREAL_NVP(vmixr1),
            CEREAL_NVP(vmixer0),
            CEREAL_NVP(vmixer1),
            CEREAL_NVP(mmix),
            CEREAL_NVP(attr),
            CEREAL_NVP(irqah),
            CEREAL_NVP(irqal),
            CEREAL_NVP(kon0),
            CEREAL_NVP(kon1),
            CEREAL_NVP(kof0),
            CEREAL_NVP(kof1),
            CEREAL_NVP(tsah),
            CEREAL_NVP(tsal),
            CEREAL_NVP(data0),
            CEREAL_NVP(data1),
            CEREAL_NVP(admas),
            CEREAL_NVP(esah),
            CEREAL_NVP(esal),
            CEREAL_NVP(apf1_sizeh),
            CEREAL_NVP(apf1_sizel),
            CEREAL_NVP(apf2_sizeh),
            CEREAL_NVP(apf2_sizel),
            CEREAL_NVP(same_l_dsth),
            CEREAL_NVP(same_l_dstl),
            CEREAL_NVP(same_r_dsth),
            CEREAL_NVP(same_r_dstl),
            CEREAL_NVP(comb1_l_srch),
            CEREAL_NVP(comb1_l_srcl),
            CEREAL_NVP(comb1_r_srch),
            CEREAL_NVP(comb1_r_srcl),
            CEREAL_NVP(comb2_l_srch),
            CEREAL_NVP(comb2_l_srcl),
            CEREAL_NVP(comb2_r_srch),
            CEREAL_NVP(comb2_r_srcl),
            CEREAL_NVP(same_l_srch),
            CEREAL_NVP(same_l_srcl),
            CEREAL_NVP(same_r_srch),
            CEREAL_NVP(same_r_srcl),
            CEREAL_NVP(diff_l_dsth),
            CEREAL_NVP(diff_l_dstl),
            CEREAL_NVP(diff_r_dsth),
            CEREAL_NVP(diff_r_dstl),
            CEREAL_NVP(comb3_l_srch),
            CEREAL_NVP(comb3_l_srcl),
            CEREAL_NVP(comb3_r_srch),
            CEREAL_NVP(comb3_r_srcl),
            CEREAL_NVP(comb4_l_srch),
            CEREAL_NVP(comb4_l_srcl),
            CEREAL_NVP(comb4_r_srch),
            CEREAL_NVP(comb4_r_srcl),
            CEREAL_NVP(diff_l_srch),
            CEREAL_NVP(diff_l_srcl),
            CEREAL_NVP(diff_r_srch),
            CEREAL_NVP(diff_r_srcl),
            CEREAL_NVP(apf1_l_dsth),
            CEREAL_NVP(apf1_l_dstl),
            CEREAL_NVP(apf1_r_dsth),
            CEREAL_NVP(apf1_r_dstl),
            CEREAL_NVP(apf2_l_dsth),
            CEREAL_NVP(apf2_l_dstl),
            CEREAL_NVP(apf2_r_dsth),
            CEREAL_NVP(apf2_r_dstl),
            CEREAL_NVP(eeah),
            CEREAL_NVP(eeal),
            CEREAL_NVP(endx0),
            CEREAL_NVP(endx1),
            CEREAL_NVP(statx),
            CEREAL_NVP(mvoll),
            CEREAL_NVP(mvolr),
            CEREAL_NVP(evoll),
            CEREAL_NVP(evolr),
            CEREAL_NVP(avoll),
            CEREAL_NVP(avolr),
            CEREAL_NVP(bvoll),
            CEREAL_NVP(bvolr),
            CEREAL_NVP(mvolxl),
            CEREAL_NVP(mvolxr),
            CEREAL_NVP(iir_vol),
            CEREAL_NVP(comb1_vol),
            CEREAL_NVP(comb2_vol),
            CEREAL_NVP(comb3_vol),
            CEREAL_NVP(comb4_vol),
            CEREAL_NVP(wall_vol),
            CEREAL_NVP(apf1_vol),
            CEREAL_NVP(apf2_vol),
            CEREAL_NVP(in_coef_l),
            CEREAL_NVP(in_coef_r),
            CEREAL_NVP(voice_0),
            CEREAL_NVP(voice_1),
            CEREAL_NVP(voice_2),
            CEREAL_NVP(voice_3),
            CEREAL_NVP(voice_4),
            CEREAL_NVP(voice_5),
            CEREAL_NVP(voice_6),
            CEREAL_NVP(voice_7),
            CEREAL_NVP(voice_8),
            CEREAL_NVP(voice_9),
            CEREAL_NVP(voice_10),
            CEREAL_NVP(voice_11),
            CEREAL_NVP(voice_12),
            CEREAL_NVP(voice_13),
            CEREAL_NVP(voice_14),
            CEREAL_NVP(voice_15),
            CEREAL_NVP(voice_16),
            CEREAL_NVP(voice_17),
            CEREAL_NVP(voice_18),
            CEREAL_NVP(voice_19),
            CEREAL_NVP(voice_20),
            CEREAL_NVP(voice_21),
            CEREAL_NVP(voice_22),
            CEREAL_NVP(voice_23)
        );
    }
};
