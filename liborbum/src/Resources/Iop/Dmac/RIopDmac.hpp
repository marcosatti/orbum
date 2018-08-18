#pragma once

#include <cereal/cereal.hpp>

#include "Common/Constants.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"
#include "Resources/Iop/Dmac/IopDmacChannelRegisters.hpp"
#include "Resources/Iop/Dmac/IopDmacChannels.hpp"
#include "Resources/Iop/Dmac/IopDmacRegisters.hpp"

/// IOP DMAC resources.
/// See the no$psx docs and wisi and SP193's DMA docs for information.
class RIopDmac
{
public:
    RIopDmac();

    /// DMAC Common Registers.
    /// Wrappers are provided for the PCR and ICR registers, to appear as one.
    IopDmacRegister_Pcr0 pcr0;
    IopDmacRegister_Icr0 icr0;
    IopDmacRegister_Pcr1 pcr1;
    IopDmacRegister_Icr1 icr1;
    IopDmacRegister_Pcrw pcrw;
    IopDmacRegister_Icrw icrw;
    SizedWordRegister gctrl;

    /// DMAC Channels.
    IopDmacChannel_Base<IopDmacChannelRegister_Chcr> channel_tomdec;    // CH 0
    IopDmacChannel_Base<IopDmacChannelRegister_Chcr> channel_frommdec;  // CH 1
    IopDmacChannel_Base<IopDmacChannelRegister_Chcr_Sif2> channel_sif2; // CH 2 bidirectional w/ EE
    IopDmacChannel_Base<IopDmacChannelRegister_Chcr> channel_cdvd;      // CH 3
    IopDmacChannel_Tadr<IopDmacChannelRegister_Chcr> channel_spu2c0;    // CH 4
    IopDmacChannel_Base<IopDmacChannelRegister_Chcr> channel_pio;       // CH 5
    IopDmacChannel_Base<IopDmacChannelRegister_Chcr> channel_otclear;   // CH 6
    IopDmacChannel_Base<IopDmacChannelRegister_Chcr> channel_spu2c1;    // CH 7
    IopDmacChannel_Base<IopDmacChannelRegister_Chcr> channel_dev9;      // CH 8
    IopDmacChannel_Tadr<IopDmacChannelRegister_Chcr_Sif0> channel_sif0; // CH 9 to EE
    IopDmacChannel_Base<IopDmacChannelRegister_Chcr_Sif1> channel_sif1; // CH 10 from EE
    IopDmacChannel_Base<IopDmacChannelRegister_Chcr> channel_tosio2;    // CH 11
    IopDmacChannel_Base<IopDmacChannelRegister_Chcr> channel_fromsio2;  // CH 12

    /// IOP DMA channel abstrations.
    /// There are 14 channels in total (to make it even), with the last one being undefined.
    IopDmacChannel channels[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS - 1];

public:
    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(
            CEREAL_NVP(pcr0),
            CEREAL_NVP(icr0),
            CEREAL_NVP(pcr1),
            CEREAL_NVP(icr1),
            CEREAL_NVP(gctrl),
            CEREAL_NVP(channel_tomdec),
            CEREAL_NVP(channel_frommdec),
            CEREAL_NVP(channel_sif2),
            CEREAL_NVP(channel_cdvd),
            CEREAL_NVP(channel_spu2c0),
            CEREAL_NVP(channel_pio),
            CEREAL_NVP(channel_otclear),
            CEREAL_NVP(channel_spu2c1),
            CEREAL_NVP(channel_dev9),
            CEREAL_NVP(channel_sif0),
            CEREAL_NVP(channel_sif1),
            CEREAL_NVP(channel_tosio2),
            CEREAL_NVP(channel_fromsio2)
        );
    }
};