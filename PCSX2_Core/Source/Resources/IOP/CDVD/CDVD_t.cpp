#include "stdafx.h"

#include "Common/Types/Register/Register8_t.h"
#include "Common/Types/Register/ConstantRegister8_t.h"

#include "Resources/IOP/CDVD/CDVD_t.h"

CDVD_t::CDVD_t() :
	N_COMMAND(std::make_shared<Register8_t>("CDVD N_COMMAND", false, false)),
	N_READY(std::make_shared<Register8_t>("CDVD N_READY", false, false)),
	ERROR(std::make_shared<Register8_t>("CDVD ERROR", false, false)),
	BREAK(std::make_shared<ConstantRegister8_t>("CDVD BREAK", false, false)),
	STATUS(std::make_shared<Register8_t>("CDVD STATUS", false, false)),
	TRAY_STATE(std::make_shared<Register8_t>("CDVD TRAY_STATE", false, false)),
	CRT_MINUTE(std::make_shared<Register8_t>("CDVD CRT_MINUTE", false, false)),
	CRT_SECOND(std::make_shared<Register8_t>("CDVD CRT_SECOND", false, false)),
	CRT_FRAME(std::make_shared<Register8_t>("CDVD CRT_FRAME", false, false)),
	TYPE(std::make_shared<Register8_t>("CDVD TYPE", false, false)),
	REGISTER_2013(std::make_shared<Register8_t>("CDVD REGISTER_2013", false, false)),
	RSV(std::make_shared<Register8_t>("CDVD RSV", false, false)),
	S_COMMAND(std::make_shared<Register8_t>("CDVD S_COMMAND", false, false)),
	S_READY(std::make_shared<Register8_t>("CDVD S_READY", false, false)),
	S_DATA_OUT(std::make_shared<Register8_t>("CDVD S_DATA_OUT", false, false)),
	KEY_20(std::make_shared<Register8_t>("CDVD KEY_20", false, false)),
	KEY_21(std::make_shared<Register8_t>("CDVD KEY_21", false, false)),
	KEY_22(std::make_shared<Register8_t>("CDVD KEY_22", false, false)),
	KEY_23(std::make_shared<Register8_t>("CDVD KEY_23", false, false)),
	KEY_24(std::make_shared<Register8_t>("CDVD KEY_24", false, false)),
	KEY_28(std::make_shared<Register8_t>("CDVD KEY_28", false, false)),
	KEY_29(std::make_shared<Register8_t>("CDVD KEY_29", false, false)),
	KEY_2A(std::make_shared<Register8_t>("CDVD KEY_2A", false, false)),
	KEY_2B(std::make_shared<Register8_t>("CDVD KEY_2B", false, false)),
	KEY_2C(std::make_shared<Register8_t>("CDVD KEY_2C", false, false)),
	KEY_30(std::make_shared<Register8_t>("CDVD KEY_30", false, false)),
	KEY_31(std::make_shared<Register8_t>("CDVD KEY_31", false, false)),
	KEY_32(std::make_shared<Register8_t>("CDVD KEY_32", false, false)),
	KEY_33(std::make_shared<Register8_t>("CDVD KEY_33", false, false)),
	KEY_34(std::make_shared<Register8_t>("CDVD KEY_34", false, false)),
	KEY_38(std::make_shared<Register8_t>("CDVD KEY_38", false, false)),
	KEY_XOR(std::make_shared<Register8_t>("CDVD KEY_XOR", false, false)),
	DEC_SET(std::make_shared<Register8_t>("CDVD DEC_SET", false, false))
{
}
