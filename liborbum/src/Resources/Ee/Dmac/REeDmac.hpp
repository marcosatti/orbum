#pragma once

#include "Common/Types/Memory/ArrayByteMemory.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"
#include "Resources/Ee/Dmac/EeDmacChannels.hpp"
#include "Resources/Ee/Dmac/EeDmacRegisters.hpp"

/// EE DMAC Resources. See page 41 onwards of the EE Users Manual.
struct REeDmac
{
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
};
