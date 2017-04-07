#include "stdafx.h"

#include "Common/Types/Register/Register32_t.h"
#include "Common/Types/Register/ConstantRegister32_t.h"
#include "Common/Types/FIFOQueue/FIFOQueue32_t.h"

#include "Resources/Common/Common_t.h"
#include "Resources/Common/Types/SBUSFIFOQueues_t.h"
#include "Resources/Common/Types/SBUSRegisters_t.h"

Common_t::Common_t() :
	SBUS_MSCOM(std::make_shared<SBUSRegister_MSCOM_t>("SBUS MSCOM", false, false)),
	SBUS_SMCOM(std::make_shared<Register32_t>("SBUS SMCOM", false, false)),
	SBUS_MSFLG(std::make_shared<SBUSRegister_MSFLG_t>("SBUS MSFLG", false, false)),
	SBUS_SMFLG(std::make_shared<SBUSRegister_SMFLG_t>("SBUS SMFLG", false, false)),
	SBUS_F240(std::make_shared<SBUSRegister_F240_t>("SBUS F240", false, false)),
	SBUS_F250(std::make_shared<Register32_t>("SBUS F250", false, false)),
	SBUS_F260(std::make_shared<ConstantRegister32_t>("SBUS F260", false, false)),
	SBUS_F300(std::make_shared<SBUSRegister_F300_t>("SBUS F300", false, false)),
	SBUS_F380(std::make_shared<Register32_t>("SBUS F380", false, false)),
	FIFO_VIF0(std::make_shared<FIFOQueue32_t>("FIFO: VIF0", false, false, 128 * 4)),
	FIFO_VIF1(std::make_shared<FIFOQueue32_t>("FIFO: VIF1", false, false, 128 * 4)),
	FIFO_GIF(std::make_shared<FIFOQueue32_t>("FIFO: GIF", false, false, 128 * 4)),
	FIFO_fromIPU(std::make_shared<FIFOQueue32_t>("FIFO: fromIPU", false, false, 128 * 4)),
	FIFO_toIPU(std::make_shared<FIFOQueue32_t>("FIFO: toIPU", false, false, 128 * 4)),
	FIFO_SIF0(std::make_shared<FIFOQueue32_t>("FIFO: SIF0", false, false, 128 * 4)),
	FIFO_SIF1(std::make_shared<FIFOQueue32_t>("FIFO: SIF1", false, false, 128 * 4)),
	FIFO_SIF2(std::make_shared<SBUSFIFOQueue_SIF2_t>("FIFO: SIF1", false, false, 128 * 4, SBUS_F300)),
	FIFO_DEBUG(std::make_shared<FIFOQueue32_t>("FIFO: Debug", false, false, 128 * 128))
{
}
