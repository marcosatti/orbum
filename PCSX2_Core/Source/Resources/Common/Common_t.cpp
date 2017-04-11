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
	FIFO_VIF0(std::make_shared<FIFOQueue32_t>("FIFO VIF0", false, false, DEBUG_FIFO_SIZE)),
	FIFO_VIF1(std::make_shared<FIFOQueue32_t>("FIFO VIF1", false, false, DEBUG_FIFO_SIZE)),
	FIFO_GIF(std::make_shared<FIFOQueue32_t>("FIFO GIF", false, false, DEBUG_FIFO_SIZE)),
	FIFO_fromIPU(std::make_shared<FIFOQueue32_t>("FIFO fromIPU", false, false, DEBUG_FIFO_SIZE)),
	FIFO_toIPU(std::make_shared<FIFOQueue32_t>("FIFO toIPU", false, false, DEBUG_FIFO_SIZE)),
	FIFO_SIF0(std::make_shared<FIFOQueue32_t>("FIFO SIF0", false, false, DEBUG_FIFO_SIZE)),
	FIFO_SIF1(std::make_shared<FIFOQueue32_t>("FIFO SIF1", false, false, DEBUG_FIFO_SIZE)),
	FIFO_SIF2(std::make_shared<SBUSFIFOQueue_SIF2_t>("FIFO SIF2", false, false, DEBUG_FIFO_SIZE, SBUS_F300)),
	FIFO_fromMDEC(std::make_shared<FIFOQueue32_t>("FIFO fromMDEC", false, false, DEBUG_FIFO_SIZE)),
	FIFO_toMDEC(std::make_shared<FIFOQueue32_t>("FIFO toMDEC", false, false, DEBUG_FIFO_SIZE)),
	FIFO_CDROM(std::make_shared<FIFOQueue32_t>("FIFO CDROM", false, false, DEBUG_FIFO_SIZE)),
	FIFO_SPU2C0(std::make_shared<FIFOQueue32_t>("FIFO SPU2C0", false, false, DEBUG_FIFO_SIZE)),
	FIFO_PIO(std::make_shared<FIFOQueue32_t>("FIFO PIO", false, false, DEBUG_FIFO_SIZE)),
	FIFO_OTClear(std::make_shared<FIFOQueue32_t>("FIFO OTClear", false, false, DEBUG_FIFO_SIZE)),
	FIFO_SPU2C1(std::make_shared<FIFOQueue32_t>("FIFO SPU2C1", false, false, DEBUG_FIFO_SIZE)),
	FIFO_DEV9(std::make_shared<FIFOQueue32_t>("FIFO DEV9", false, false, DEBUG_FIFO_SIZE)),
	FIFO_fromSIO2(std::make_shared<FIFOQueue32_t>("FIFO fromSIO2", false, false, DEBUG_FIFO_SIZE)),
	FIFO_toSIO2(std::make_shared<FIFOQueue32_t>("FIFO toSIO2", false, false, DEBUG_FIFO_SIZE))
{
}
