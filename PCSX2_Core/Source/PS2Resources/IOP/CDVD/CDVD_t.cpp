#include "stdafx.h"

#include "PS2Resources/IOP/CDVD/CDVD_t.h"
#include "Common/Types/Registers/Register8_t.h"
#include "Common/Types/Registers/ZeroRegister8_t.h"

CDVD_t::CDVD_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),
	NCommand(std::make_shared<Register8_t>()),
	NReady(std::make_shared<Register8_t>()),
	Error(std::make_shared<Register8_t>()),
	Break(std::make_shared<ZeroRegister8_t>()),
	Status(std::make_shared<Register8_t>()),
	TrayState(std::make_shared<Register8_t>()),
	CRTMinute(std::make_shared<Register8_t>()),
	CRTSecond(std::make_shared<Register8_t>()),
	CRTFrame(std::make_shared<Register8_t>()),
	Type(std::make_shared<Register8_t>()),
	Unknown13(std::make_shared<Register8_t>()),
	RSV(std::make_shared<Register8_t>()),
	SCommand(std::make_shared<Register8_t>()),
	SReady(std::make_shared<Register8_t>()),
	SDataOut(std::make_shared<Register8_t>()),
	Key20(std::make_shared<Register8_t>()),
	Key21(std::make_shared<Register8_t>()),
	Key22(std::make_shared<Register8_t>()),
	Key23(std::make_shared<Register8_t>()),
	Key24(std::make_shared<Register8_t>()),
	Key28(std::make_shared<Register8_t>()),
	Key29(std::make_shared<Register8_t>()),
	Key2A(std::make_shared<Register8_t>()),
	Key2B(std::make_shared<Register8_t>()),
	Key2C(std::make_shared<Register8_t>()),
	Key30(std::make_shared<Register8_t>()),
	Key31(std::make_shared<Register8_t>()),
	Key32(std::make_shared<Register8_t>()),
	Key33(std::make_shared<Register8_t>()),
	Key34(std::make_shared<Register8_t>()),
	Key38(std::make_shared<Register8_t>()),
	KeyXor(std::make_shared<Register8_t>()),
	DecSet(std::make_shared<Register8_t>())
{
}
