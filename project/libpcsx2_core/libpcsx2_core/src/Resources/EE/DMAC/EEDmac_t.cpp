#include "Common/Types/Memory/ByteMemory_t.h"
#include "Common/Types/Memory/ConstantByteMemory_t.h"

#include "Resources/EE/DMAC/EEDmac_t.h"
#include "Resources/EE/DMAC/Types/EEDmacRegisters_t.h"

EEDmac_t::EEDmac_t() :
	CHANNEL_VIF0(nullptr),
	CHANNEL_VIF1(nullptr),
	CHANNEL_GIF(nullptr),
	CHANNEL_fromIPU(nullptr),
	CHANNEL_toIPU(nullptr),
	CHANNEL_SIF0(nullptr),
	CHANNEL_SIF1(nullptr),
	CHANNEL_SIF2(nullptr),
	CHANNEL_fromSPR(nullptr),
	CHANNEL_toSPR(nullptr),
	CHANNELS{ nullptr },
	CTRL(std::make_shared<EEDmacRegister_CTRL_t>("EE DMAC CTRL", false, false)),
	STAT(std::make_shared<EEDmacRegister_STAT_t>("EE DMAC STAT", false, false)),
	PCR(std::make_shared<EEDmacRegister_PCR_t>("EE DMAC PCR", false, false)),
	SQWC(std::make_shared<EEDmacRegister_SWQC_t>("EE DMAC SWQC", false, false)),
	RBSR(std::make_shared<EEDmacRegister_RBSR_t>("EE DMAC RBSR", false, false)),
	RBOR(std::make_shared<EEDmacRegister_RBOR_t>("EE DMAC RBOR", false, false)),
	STADR(std::make_shared<EEDmacRegister_STADR_t>("EE DMAC STADR", false, false)),
	MEMORY_E070(std::make_shared<ConstantByteMemory_t>("EE DMAC E070", false, false, 0xF90)),
	MEMORY_F500(std::make_shared<ByteMemory_t>("EE DMAC F500", false, false, 0x20)),
	ENABLER(std::make_shared<EEDmacRegister_ENABLER_t>("EE DMAC ENABLER", false, false)),
	MEMORY_F530(std::make_shared<ConstantByteMemory_t>("EE DMAC F530", false, false, 0x60)),
	ENABLEW(std::make_shared<EEDmacRegister_ENABLEW_t>("EE DMAC ENABLEW", false, false)),
	MEMORY_F5A0(std::make_shared<ConstantByteMemory_t>("EE DMAC F5A0", false, false, 0x60))
{
}