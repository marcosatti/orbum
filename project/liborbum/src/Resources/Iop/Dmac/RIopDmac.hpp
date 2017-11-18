#pragma once

#include "Common/Constants.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"
#include "Resources/Iop/Dmac/IopDmacChannelRegisters.hpp"
#include "Resources/Iop/Dmac/IopDmacRegisters.hpp"
#include "Resources/Iop/Dmac/IopDmacChannels.hpp"

/// IOP DMAC resources.
/// See the no$psx docs and wisi and SP193's DMA docs for information.
struct RIopDmac
{
	RIopDmac();

	/// DMAC Common Registers.
	/// Wrappers are provided for the PCR and ICR registers, to appear as one.
	IopDmacRegister_Pcr0 pcr0;  
	IopDmacRegister_Icr0 icr0;  
	IopDmacRegister_Pcr1 pcr1;  
	IopDmacRegister_Icr1 icr1;  
	IopDmacRegister_Pcrw pcrw;
	IopDmacRegister_Icrw icrw;
	SizedWordRegister    gctrl; 

	/// DMAC Channels.
	IopDmacChannel_Base<IopDmacChannelRegister_Chcr>      channel_frommdec;
	IopDmacChannel_Base<IopDmacChannelRegister_Chcr>      channel_tomdec;
	IopDmacChannel_Base<IopDmacChannelRegister_Chcr_Sif2> channel_sif2;
	IopDmacChannel_Base<IopDmacChannelRegister_Chcr>      channel_cdvd;
	IopDmacChannel_Tadr<IopDmacChannelRegister_Chcr>      channel_spu2c0;
	IopDmacChannel_Base<IopDmacChannelRegister_Chcr>      channel_pio;
	IopDmacChannel_Base<IopDmacChannelRegister_Chcr>      channel_otclear;
	IopDmacChannel_Base<IopDmacChannelRegister_Chcr>      channel_spu2c1;
	IopDmacChannel_Base<IopDmacChannelRegister_Chcr>      channel_dev9;
	IopDmacChannel_Tadr<IopDmacChannelRegister_Chcr_Sif0> channel_sif0;
	IopDmacChannel_Base<IopDmacChannelRegister_Chcr_Sif1> channel_sif1;
	IopDmacChannel_Base<IopDmacChannelRegister_Chcr>      channel_fromsio2;
	IopDmacChannel_Base<IopDmacChannelRegister_Chcr>      channel_tosio2;

	/// IOP DMA channel abstrations. 
	/// There are 14 channels in total (to make it even), with the last one being undefined.
	IopDmacChannel * channels[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS - 1];
};