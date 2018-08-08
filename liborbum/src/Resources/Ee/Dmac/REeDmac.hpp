#pragma once

#include "Common/Types/Memory/ArrayByteMemory.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"
#include "Resources/Ee/Dmac/EeDmacChannels.hpp"
#include "Resources/Ee/Dmac/EeDmacRegisters.hpp"

/// EE DMAC Resources. See page 41 onwards of the EE Users Manual.
class REeDmac
{
public:
    REeDmac();

    /// DMA Channels. See page 42 of the EE Users Manual.
    /// Each channel contains the set of registers defined on page 73 in the EE Users Manual.
    EeDmacChannel_Asr<EeDmacChannelRegister_Chcr> channel_vif0;        // CH 0
    EeDmacChannel_Asr<EeDmacChannelRegister_Chcr> channel_vif1;        // CH 1
    EeDmacChannel_Asr<EeDmacChannelRegister_Chcr> channel_gif;         // CH 2
    EeDmacChannel_Base<EeDmacChannelRegister_Chcr> channel_fromipu;    // CH 3
    EeDmacChannel_Tadr<EeDmacChannelRegister_Chcr> channel_toipu;      // CH 4
    EeDmacChannel_Base<EeDmacChannelRegister_Chcr_Sif0> channel_sif0;  // CH 5 from IOP
    EeDmacChannel_Tadr<EeDmacChannelRegister_Chcr_Sif1> channel_sif1;  // CH 6 to IOP
    EeDmacChannel_Base<EeDmacChannelRegister_Chcr_Sif2> channel_sif2;  // CH 7 bidirectional w/ IOP
    EeDmacChannel_Sadr<EeDmacChannelRegister_Chcr> channel_fromspr;    // CH 8
    EeDmacChannel_Tadr_Sadr<EeDmacChannelRegister_Chcr> channel_tospr; // CH 9

    /// Channel abstrations.
    EeDmacChannel channels[Constants::EE::DMAC::NUMBER_DMAC_CHANNELS];

    /// DMAC common registers. Defined on page 63 of the EE Users Manual.
    EeDmacRegister_Ctrl ctrl;
    EeDmacRegister_Stat stat;
    EeDmacRegister_Pcr pcr;
    EeDmacRegister_Swqc sqwc;
    EeDmacRegister_Rbsr rbsr;
    SizedWordRegister rbor;
    SizedWordRegister stadr;
    EeDmacRegister_EnableR enable_r;
    EeDmacRegister_EnableW enable_w;

    /// Misc registers/memory, unused but needed.
    /// See page 23 onwards of the EE Users Manual.
    ArrayByteMemory memory_8060;
    ArrayByteMemory memory_9060;
    ArrayByteMemory memory_a060;
    ArrayByteMemory memory_b030;
    ArrayByteMemory memory_b440;
    ArrayByteMemory memory_c030;
    ArrayByteMemory memory_c440;
    ArrayByteMemory memory_c830;
    ArrayByteMemory memory_d030;
    ArrayByteMemory memory_d090;
    ArrayByteMemory memory_d440;
    ArrayByteMemory memory_d490;
    ArrayByteMemory memory_e070;
    ArrayByteMemory memory_f500;
    ArrayByteMemory memory_f530;
    ArrayByteMemory memory_f5a0;

public:
    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(
            CEREAL_NVP(channel_vif0),
            CEREAL_NVP(channel_vif1),
            CEREAL_NVP(channel_gif),
            CEREAL_NVP(channel_fromipu),
            CEREAL_NVP(channel_toipu),
            CEREAL_NVP(channel_sif0),
            CEREAL_NVP(channel_sif1),
            CEREAL_NVP(channel_sif2),
            CEREAL_NVP(channel_fromspr),
            CEREAL_NVP(channel_tospr),
            CEREAL_NVP(ctrl),
            CEREAL_NVP(stat),
            CEREAL_NVP(pcr),
            CEREAL_NVP(sqwc),
            CEREAL_NVP(rbsr),
            CEREAL_NVP(rbor),
            CEREAL_NVP(stadr),
            CEREAL_NVP(enable_r),
            CEREAL_NVP(enable_w),
            CEREAL_NVP(memory_8060),
            CEREAL_NVP(memory_9060),
            CEREAL_NVP(memory_a060),
            CEREAL_NVP(memory_b030),
            CEREAL_NVP(memory_b440),
            CEREAL_NVP(memory_c030),
            CEREAL_NVP(memory_c440),
            CEREAL_NVP(memory_c830),
            CEREAL_NVP(memory_d030),
            CEREAL_NVP(memory_d090),
            CEREAL_NVP(memory_d440),
            CEREAL_NVP(memory_d490),
            CEREAL_NVP(memory_e070),
            CEREAL_NVP(memory_f500),
            CEREAL_NVP(memory_f530),
            CEREAL_NVP(memory_f5a0)
        );
    }
};
