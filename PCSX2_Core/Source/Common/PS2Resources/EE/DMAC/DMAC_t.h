#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/PS2Constants/PS2Constants.h"
#include "Common/Interfaces/PS2ResourcesSubobject.h"

class MappedMemory_t;
class DeadMMemory_t;
class DmacRegisterChcr_t;
class DmacRegisterMadr_t;
class DmacRegisterTadr_t;
class DmacRegisterAsr_t;
class DmacRegisterSadr_t;
class DmacRegisterQwc_t;
class DmacRegisterCtrl_t;
class DmacRegisterStat_t;
class DmacRegisterPcr_t;
class DmacRegisterSqwc_t;
class DmacRegisterRbor_t;
class DmacRegisterRbsr_t;
class DmacRegisterStadr_t;
class DmacRegisterEnablew_t;
class DmacRegisterEnabler_t;

class DMAC_t : public PS2ResourcesSubobject
{
public:
	explicit DMAC_t(const PS2Resources_t *const PS2Resources);

	/*
	A DMAC channel transfer count save array, needed to determine how many data units (qwords) have been transfered since start, which is used to
	 determine if the DMAC should stop transferring in slice mode (after 8 units).
	Not all of the array will be used (only for slice channels).
	*/
	u32 SliceCountState[PS2Constants::EE::DMAC::NUMBER_DMA_CHANNELS];

	/*
	A chain mode exit status for each channel. When an exiting DMAtag instruction such as end is called, true is written to the appropriate index,
	 signaling that the DMAC should exit after the next packet transfer is completed.
	Not all of the array will be used (only for channels that support chain mode).
	*/
	bool ChainExitState[PS2Constants::EE::DMAC::NUMBER_DMA_CHANNELS];

	/*
	A stack level count, for chain mode (CALL / RET instructions). Used to check if the DMA transfer should end.
	Not all of the array will be used (only for channels that support chain mode).
	*/
	u8 ChainStackLevelState[PS2Constants::EE::DMAC::NUMBER_DMA_CHANNELS];

	/*
	Interleaved transfer state variables. Used to determine when to transfer data and when to skip data.
	*/
	bool InterleavedSkipState[PS2Constants::EE::DMAC::NUMBER_DMA_CHANNELS];
	u8 InterleavedCountState[PS2Constants::EE::DMAC::NUMBER_DMA_CHANNELS];

	/*
	DMAC memory mapped registers. See page 23 of EE Users Manual.
	*/
	// 0x10008000
	std::shared_ptr<DmacRegisterChcr_t>    DMAC_REGISTER_D0_CHCR;
	std::shared_ptr<DmacRegisterMadr_t>    DMAC_REGISTER_D0_MADR;
	std::shared_ptr<DmacRegisterQwc_t>     DMAC_REGISTER_D0_QWC;
	std::shared_ptr<DmacRegisterTadr_t>    DMAC_REGISTER_D0_TADR;
	std::shared_ptr<DmacRegisterAsr_t>     DMAC_REGISTER_D0_ASR0;
	std::shared_ptr<DmacRegisterAsr_t>     DMAC_REGISTER_D0_ASR1;
	std::shared_ptr<DeadMMemory_t>         DMAC_MEMORY_8060;

	// 0x10009000
	std::shared_ptr<DmacRegisterChcr_t>    DMAC_REGISTER_D1_CHCR;
	std::shared_ptr<DmacRegisterMadr_t>    DMAC_REGISTER_D1_MADR;
	std::shared_ptr<DmacRegisterQwc_t>     DMAC_REGISTER_D1_QWC;
	std::shared_ptr<DmacRegisterTadr_t>    DMAC_REGISTER_D1_TADR;
	std::shared_ptr<DmacRegisterAsr_t>     DMAC_REGISTER_D1_ASR0;
	std::shared_ptr<DmacRegisterAsr_t>     DMAC_REGISTER_D1_ASR1;
	std::shared_ptr<DeadMMemory_t>         DMAC_MEMORY_9060;

	// 0x1000A000
	std::shared_ptr<DmacRegisterChcr_t>    DMAC_REGISTER_D2_CHCR;
	std::shared_ptr<DmacRegisterMadr_t>    DMAC_REGISTER_D2_MADR;
	std::shared_ptr<DmacRegisterQwc_t>     DMAC_REGISTER_D2_QWC;
	std::shared_ptr<DmacRegisterTadr_t>    DMAC_REGISTER_D2_TADR;
	std::shared_ptr<DmacRegisterAsr_t>     DMAC_REGISTER_D2_ASR0;
	std::shared_ptr<DmacRegisterAsr_t>     DMAC_REGISTER_D2_ASR1;
	std::shared_ptr<DeadMMemory_t>         DMAC_MEMORY_a060;

	// 0x1000B000 
	std::shared_ptr<DmacRegisterChcr_t>    DMAC_REGISTER_D3_CHCR;
	std::shared_ptr<DmacRegisterMadr_t>    DMAC_REGISTER_D3_MADR;
	std::shared_ptr<DmacRegisterQwc_t>     DMAC_REGISTER_D3_QWC;
	std::shared_ptr<DeadMMemory_t>         DMAC_MEMORY_b030;

	// 0x1000B400
	std::shared_ptr<DmacRegisterChcr_t>    DMAC_REGISTER_D4_CHCR;
	std::shared_ptr<DmacRegisterMadr_t>    DMAC_REGISTER_D4_MADR;
	std::shared_ptr<DmacRegisterQwc_t>     DMAC_REGISTER_D4_QWC;
	std::shared_ptr<DmacRegisterTadr_t>    DMAC_REGISTER_D4_TADR;
	std::shared_ptr<DeadMMemory_t>         DMAC_MEMORY_b440;

	// 0x1000C000
	std::shared_ptr<DmacRegisterChcr_t>    DMAC_REGISTER_D5_CHCR;
	std::shared_ptr<DmacRegisterMadr_t>    DMAC_REGISTER_D5_MADR;
	std::shared_ptr<DmacRegisterQwc_t>     DMAC_REGISTER_D5_QWC;
	std::shared_ptr<DeadMMemory_t>         DMAC_MEMORY_c030;

	// 0x1000C400
	std::shared_ptr<DmacRegisterChcr_t>    DMAC_REGISTER_D6_CHCR;
	std::shared_ptr<DmacRegisterMadr_t>    DMAC_REGISTER_D6_MADR;
	std::shared_ptr<DmacRegisterQwc_t>     DMAC_REGISTER_D6_QWC;
	std::shared_ptr<DmacRegisterTadr_t>    DMAC_REGISTER_D6_TADR;
	std::shared_ptr<DeadMMemory_t>         DMAC_MEMORY_c440;

	// 0x1000C800
	std::shared_ptr<DmacRegisterChcr_t>    DMAC_REGISTER_D7_CHCR;
	std::shared_ptr<DmacRegisterMadr_t>    DMAC_REGISTER_D7_MADR;
	std::shared_ptr<DmacRegisterQwc_t>     DMAC_REGISTER_D7_QWC;
	std::shared_ptr<DeadMMemory_t>         DMAC_MEMORY_c830;

	// 0x1000D000
	std::shared_ptr<DmacRegisterChcr_t>    DMAC_REGISTER_D8_CHCR;
	std::shared_ptr<DmacRegisterMadr_t>    DMAC_REGISTER_D8_MADR;
	std::shared_ptr<DmacRegisterQwc_t>     DMAC_REGISTER_D8_QWC;
	std::shared_ptr<DeadMMemory_t>         DMAC_MEMORY_d030;
	std::shared_ptr<DmacRegisterSadr_t>    DMAC_REGISTER_D8_SADR;
	std::shared_ptr<DeadMMemory_t>         DMAC_MEMORY_d090;

	// 0x1000D400
	std::shared_ptr<DmacRegisterChcr_t>    DMAC_REGISTER_D9_CHCR;
	std::shared_ptr<DmacRegisterMadr_t>    DMAC_REGISTER_D9_MADR;
	std::shared_ptr<DmacRegisterQwc_t>     DMAC_REGISTER_D9_QWC;
	std::shared_ptr<DmacRegisterTadr_t>    DMAC_REGISTER_D9_TADR;
	std::shared_ptr<DeadMMemory_t>         DMAC_MEMORY_d440;
	std::shared_ptr<DmacRegisterSadr_t>    DMAC_REGISTER_D9_SADR;
	std::shared_ptr<DeadMMemory_t>         DMAC_MEMORY_d490;

	// Array of DMA channel objects, needed to perform iterations.
	struct DMACChannelRegisters_t
	{
		std::shared_ptr<DmacRegisterChcr_t> CHCR;
		std::shared_ptr<DmacRegisterMadr_t> MADR;
		std::shared_ptr<DmacRegisterQwc_t>  QWC;
		std::shared_ptr<DmacRegisterTadr_t> TADR;
		std::shared_ptr<DmacRegisterAsr_t>  ASR0;
		std::shared_ptr<DmacRegisterAsr_t>  ASR1;
		std::shared_ptr<DmacRegisterSadr_t> SADR;
		std::shared_ptr<DmacRegisterAsr_t>  ASR[2];
	} DMAChannelRegisters[PS2Constants::EE::DMAC::NUMBER_DMA_CHANNELS];

	// 0x1000E000
	std::shared_ptr<DmacRegisterCtrl_t>    DMAC_REGISTER_D_CTRL;
	std::shared_ptr<DmacRegisterStat_t>    DMAC_REGISTER_D_STAT;
	std::shared_ptr<DmacRegisterPcr_t>     DMAC_REGISTER_D_PCR;
	std::shared_ptr<DmacRegisterSqwc_t>    DMAC_REGISTER_D_SQWC;
	std::shared_ptr<DmacRegisterRbsr_t>    DMAC_REGISTER_D_RBSR;
	std::shared_ptr<DmacRegisterRbor_t>    DMAC_REGISTER_D_RBOR;
	std::shared_ptr<DmacRegisterStadr_t>   DMAC_REGISTER_D_STADR;
	std::shared_ptr<DeadMMemory_t>         DMAC_MEMORY_e070;

	// 0x1000F500
	std::shared_ptr<MappedMemory_t>        DMAC_MEMORY_F500;      // Register "Undocumented: F500" @ 0x1000F500 -> 0x1000F520.
	std::shared_ptr<DmacRegisterEnabler_t> DMAC_REGISTER_D_ENABLER;
	std::shared_ptr<DeadMMemory_t>         DMAC_MEMORY_F530;
	std::shared_ptr<DmacRegisterEnablew_t> DMAC_REGISTER_D_ENABLEW;
	std::shared_ptr<DeadMMemory_t>         DMAC_MEMORY_F5A0;
};

