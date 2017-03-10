#include "stdafx.h"

#include "Common/Types/Registers/Register32_t.h"
#include "Common/Types/Registers/Constant/ConstantRegister32_t.h"
#include "Common/Types/FIFOQueue32/FIFOQueue32_t.h"

#include "Resources/Common/Common_t.h"
#include "Resources/Common/Types/SBUSFIFOQueues_t.h"
#include "Resources/Common/Types/SBUSRegisters_t.h"

Common_t::Common_t() :
	SBUS_MSCOM(std::make_shared<SBUSRegister_MSCOM_t>()),
	SBUS_SMCOM(std::make_shared<Register32_t>("SBUS: SMCOM")),
	SBUS_MSFLG(std::make_shared<SBUSRegister_MSFLG_t>()),
	SBUS_SMFLG(std::make_shared<SBUSRegister_SMFLG_t>()),
	SBUS_F240(std::make_shared<SBUSRegister_F240_t>()),
	SBUS_F250(std::make_shared<Register32_t>()),
	SBUS_F260(std::make_shared<ConstantRegister32_t>()),
	SBUS_F300(std::make_shared<SBUSRegister_F300_t>()),
	SBUS_F380(std::make_shared<Register32_t>()),
	FIFO_VIF0(std::make_shared<FIFOQueue32_t>("FIFO: VIF0", 128 * 4)),
	FIFO_VIF1(std::make_shared<FIFOQueue32_t>("FIFO: VIF1", 128 * 4)),
	FIFO_GIF(std::make_shared<FIFOQueue32_t>("FIFO: GIF", 128 * 4)),
	FIFO_fromIPU(std::make_shared<FIFOQueue32_t>("FIFO: fromIPU", 128 * 4)),
	FIFO_toIPU(std::make_shared<FIFOQueue32_t>("FIFO: toIPU", 128 * 4)),
	FIFO_SIF0(std::make_shared<FIFOQueue32_t>("FIFO: SIF0", 128 * 4)),
	FIFO_SIF1(std::make_shared<FIFOQueue32_t>("FIFO: SIF1", 128 * 4)),
	FIFO_SIF2(std::make_shared<SBUSFIFOQueue_SIF2_t>(128 * 4, SBUS_F300)),
	FIFO_DEBUG(std::make_shared<FIFOQueue32_t>("FIFO: Debug", 128 * 128))
{
}
