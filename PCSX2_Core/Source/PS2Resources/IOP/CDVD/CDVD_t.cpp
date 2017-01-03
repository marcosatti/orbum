#include "stdafx.h"

#include "PS2Resources/IOP/CDVD/CDVD_t.h"
#include "Common/Types/Registers/Register8_t.h"
#include "Common/Types/Registers/Constant/ConstantRegister8_t.h"

CDVD_t::CDVD_t(const PS2Resources_t* PS2Resources) :
	PS2ResourcesSubcategory(PS2Resources),
	N_COMMAND(std::make_shared<Register8_t>()),
	N_READY(std::make_shared<Register8_t>()),
	ERROR(std::make_shared<Register8_t>()),
	BREAK(std::make_shared<ConstantRegister8_t>()),
	STATUS(std::make_shared<Register8_t>()),
	TRAY_STATE(std::make_shared<Register8_t>()),
	CRT_MINUTE(std::make_shared<Register8_t>()),
	CRT_SECOND(std::make_shared<Register8_t>()),
	CRT_FRAME(std::make_shared<Register8_t>()),
	TYPE(std::make_shared<Register8_t>()),
	REGISTER_2013(std::make_shared<Register8_t>()),
	RSV(std::make_shared<Register8_t>()),
	S_COMMAND(std::make_shared<Register8_t>()),
	S_READY(std::make_shared<Register8_t>()),
	S_DATA_OUT(std::make_shared<Register8_t>()),
	KEY_20(std::make_shared<Register8_t>()),
	KEY_21(std::make_shared<Register8_t>()),
	KEY_22(std::make_shared<Register8_t>()),
	KEY_23(std::make_shared<Register8_t>()),
	KEY_24(std::make_shared<Register8_t>()),
	KEY_28(std::make_shared<Register8_t>()),
	KEY_29(std::make_shared<Register8_t>()),
	KEY_2A(std::make_shared<Register8_t>()),
	KEY_2B(std::make_shared<Register8_t>()),
	KEY_2C(std::make_shared<Register8_t>()),
	KEY_30(std::make_shared<Register8_t>()),
	KEY_31(std::make_shared<Register8_t>()),
	KEY_32(std::make_shared<Register8_t>()),
	KEY_33(std::make_shared<Register8_t>()),
	KEY_34(std::make_shared<Register8_t>()),
	KEY_38(std::make_shared<Register8_t>()),
	KEY_XOR(std::make_shared<Register8_t>()),
	DEC_SET(std::make_shared<Register8_t>())
{
}
