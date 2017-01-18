#include "stdafx.h"

#include "Common/Types/Registers/Register32_t.h"
#include "Common/Types/FIFOQueue/FIFOQueue_t.h"

#include "PS2Resources/Common/Common_t.h"
#include "PS2Resources/Common/Types/Sif2FIFOQueue_t.h"

Common_t::Common_t(const PS2Resources_t* PS2Resources) :
	PS2ResourcesSubcategory(PS2Resources),
	MSCOM(std::make_shared<Register32_t>("SIF: MSCOM")),
	SMCOM(std::make_shared<Register32_t>("SIF: SMCOM")),
	MSFLG(std::make_shared<Register32_t>("SIF: MSFLG")),
	SMFLG(std::make_shared<Register32_t>("SIF: SMFLG")),
	SBUS_REGISTER_F240(std::make_shared<Register32_t>()),
	SBUS_REGISTER_F250(std::make_shared<Register32_t>()),
	SBUS_REGISTER_F260(std::make_shared<Register32_t>()),
	SBUS_REGISTER_F300(std::make_shared<Register32_t>()),
	SBUS_REGISTER_F380(std::make_shared<Register32_t>()),
	FIFO_VIF0(std::make_shared<FIFOQueue_t>("FIFO: VIF0", 128 * 4)),
	FIFO_VIF1(std::make_shared<FIFOQueue_t>("FIFO: VIF1", 128 * 4)),
	FIFO_GIF(std::make_shared<FIFOQueue_t>("FIFO: GIF", 128 * 4)),
	FIFO_fromIPU(std::make_shared<FIFOQueue_t>("FIFO: fromIPU", 128 * 4)),
	FIFO_toIPU(std::make_shared<FIFOQueue_t>("FIFO: toIPU", 128 * 4)),
	FIFO_SIF0(std::make_shared<FIFOQueue_t>("FIFO: SIF0", 128 * 4)),
	FIFO_SIF1(std::make_shared<FIFOQueue_t>("FIFO: SIF1", 128 * 4)),
	FIFO_SIF2(std::make_shared<Sif2FIFOQueue_t>("FIFO: SIF2", 128 * 4, SBUS_REGISTER_F300)),
	FIFO_DEBUG(std::make_shared<FIFOQueue_t>("FIFO: Debug", 128 * 128))
{
}
