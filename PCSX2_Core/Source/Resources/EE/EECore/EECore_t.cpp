#include "stdafx.h"

#include "Common/Types/Memory/ByteMemory_t.h"

#include "Resources/EE/EECore/EECore_t.h"
#include "Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "Resources/EE/EECore/Types/EECoreCOP0_t.h"
#include "Resources/EE/EECore/Types/EECoreFPU_t.h"
#include "Resources/EE/EECore/Types/EECoreTLB_t.h"

EECore_t::EECore_t() : 
	R5900(std::make_shared<EECoreR5900_t>()),
	COP0(std::make_shared<EECoreCOP0_t>()),
	FPU(std::make_shared<EECoreFPU_t>(COP0)),
	ScratchpadMemory(std::make_shared<ByteMemory_t>(Constants::EE::EECore::ScratchpadMemory::SIZE_SCRATCHPAD_MEMORY, "EE Core Scratchpad Memory")),
	TLB(std::make_shared<EECoreTLB_t>())
{
}