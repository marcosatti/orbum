#include "stdafx.h"

#include "Common/Types/Register/Register8_t.h"
#include "Common/Types/Register/ConstantRegister8_t.h"
#include "Common/Types/FIFOQueue/FIFOQueue8_t.h"

#include "Resources/CDVD/CDVD_t.h"

CDVD_t::CDVD_t() :
	N_2004(std::make_shared<Register8_t>("CDVD N_2004", true, true)),
	N_2005(std::make_shared<Register8_t>("CDVD N_2005", true, true, 0x4E)),
	N_2006(std::make_shared<Register8_t>("CDVD N_2006", true, true)),
	BREAK(std::make_shared<Register8_t>("CDVD BREAK", true, true)),
	INTR_STAT(std::make_shared<Register8_t>("CDVD INTR_STAT", true, true)),
	STATUS(std::make_shared<Register8_t>("CDVD STATUS", true, true, 0xA)),
	TRAY_STATE(std::make_shared<Register8_t>("CDVD TRAY_STATE", true, true)),
	CRT_MINUTE(std::make_shared<Register8_t>("CDVD CRT_MINUTE", true, true)),
	CRT_SECOND(std::make_shared<Register8_t>("CDVD CRT_SECOND", true, true)),
	CRT_FRAME(std::make_shared<Register8_t>("CDVD CRT_FRAME", true, true)),
	TYPE(std::make_shared<Register8_t>("CDVD TYPE", true, true)),
	REGISTER_2013(std::make_shared<Register8_t>("CDVD REGISTER_2013", true, true)),
	RSV(std::make_shared<Register8_t>("CDVD RSV", true, true)),
	S_2016(std::make_shared<Register8_t>("CDVD S_2016", true, true)),
	S_2017(std::make_shared<Register8_t>("CDVD S_2017", true, true, 16)),
	S_2018(std::make_shared<Register8_t>("CDVD S_2018", true, true, 16)),
	KEY_20(std::make_shared<Register8_t>("CDVD KEY_20", true, true)),
	KEY_21(std::make_shared<Register8_t>("CDVD KEY_21", true, true)),
	KEY_22(std::make_shared<Register8_t>("CDVD KEY_22", true, true)),
	KEY_23(std::make_shared<Register8_t>("CDVD KEY_23", true, true)),
	KEY_24(std::make_shared<Register8_t>("CDVD KEY_24", true, true)),
	KEY_28(std::make_shared<Register8_t>("CDVD KEY_28", true, true)),
	KEY_29(std::make_shared<Register8_t>("CDVD KEY_29", true, true)),
	KEY_2A(std::make_shared<Register8_t>("CDVD KEY_2A", true, true)),
	KEY_2B(std::make_shared<Register8_t>("CDVD KEY_2B", true, true)),
	KEY_2C(std::make_shared<Register8_t>("CDVD KEY_2C", true, true)),
	KEY_30(std::make_shared<Register8_t>("CDVD KEY_30", true, true)),
	KEY_31(std::make_shared<Register8_t>("CDVD KEY_31", true, true)),
	KEY_32(std::make_shared<Register8_t>("CDVD KEY_32", true, true)),
	KEY_33(std::make_shared<Register8_t>("CDVD KEY_33", true, true)),
	KEY_34(std::make_shared<Register8_t>("CDVD KEY_34", true, true)),
	KEY_38(std::make_shared<Register8_t>("CDVD KEY_38", true, true)),
	KEY_XOR(std::make_shared<Register8_t>("CDVD KEY_XOR", true, true)),
	DEC_SET(std::make_shared<Register8_t>("CDVD DEC_SET", true, true))
{
}
