#include "stdafx.h"

#include "PS2Resources/Common/Common_t.h"
#include "Common/Types/Registers/Register32_t.h"
#include "Common/Types/FIFOQueue/FIFOQueue_t.h"

Common_t::Common_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),
	FIFO_VIF0(std::make_shared<FIFOQueue_t>("FIFO: VIF0", 128)),
	FIFO_VIF1(std::make_shared<FIFOQueue_t>("FIFO: VIF1", 128)),
	FIFO_GIF(std::make_shared<FIFOQueue_t>("FIFO: GIF", 128)),
	FIFO_IPU(std::make_shared<FIFOQueue_t>("FIFO: IPU", 128)),
	FIFO_SIF0(std::make_shared<FIFOQueue_t>("FIFO: SIF0", 128)),
	FIFO_SIF1(std::make_shared<FIFOQueue_t>("FIFO: SIF1", 128)),
	FIFO_SIF2(std::make_shared<FIFOQueue_t>("FIFO: SIF2", 128)),
	MSCOM(std::make_shared<Register32_t>("SIF: MSCOM")),
	SMCOM(std::make_shared<Register32_t>("SIF: SMCOM")),
	MSFLG(std::make_shared<Register32_t>("SIF: MSFLG")),
	SMFLG(std::make_shared<Register32_t>("SIF: SMFLG")),
	REGISTER_F240(std::make_shared<Register32_t>()),
	REGISTER_F250(std::make_shared<Register32_t>()),
	REGISTER_F260(std::make_shared<Register32_t>()),
	REGISTER_F300(std::make_shared<Register32_t>()),
	REGISTER_F380(std::make_shared<Register32_t>())
{
}
