#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "Common/PS2Constants/PS2Constants.h"

class MappedMemory32_t;
class DeadMMemory_t;
class TimersRegisterMode_t;
class TimersRegisterCount_t;

class Timers_t : public PS2ResourcesSubobject
{
public:
	explicit Timers_t(const PS2Resources_t *const PS2Resources);

	/*
	Timers memory mapped registers. See page 21 of EE Users Manual.
	*/
	// 0x10000000 (Timers)
	std::shared_ptr<TimersRegisterCount_t> TIMERS_REGISTER_T0_COUNT;
	std::shared_ptr<TimersRegisterMode_t>  TIMERS_REGISTER_T0_MODE;
	std::shared_ptr<MappedMemory32_t>      TIMERS_REGISTER_T0_COMP;
	std::shared_ptr<MappedMemory32_t>      TIMERS_REGISTER_T0_HOLD;
	std::shared_ptr<DeadMMemory_t>         TIMERS_REGISTER_TIMER_0040;
	std::shared_ptr<TimersRegisterCount_t> TIMERS_REGISTER_T1_COUNT;
	std::shared_ptr<TimersRegisterMode_t>  TIMERS_REGISTER_T1_MODE;
	std::shared_ptr<MappedMemory32_t>      TIMERS_REGISTER_T1_COMP;
	std::shared_ptr<MappedMemory32_t>      TIMERS_REGISTER_T1_HOLD;
	std::shared_ptr<DeadMMemory_t>         TIMERS_REGISTER_TIMER_0840;
	std::shared_ptr<TimersRegisterCount_t> TIMERS_REGISTER_T2_COUNT;
	std::shared_ptr<TimersRegisterMode_t>  TIMERS_REGISTER_T2_MODE;
	std::shared_ptr<MappedMemory32_t>      TIMERS_REGISTER_T2_COMP;
	std::shared_ptr<DeadMMemory_t>         TIMERS_REGISTER_TIMER_1030;
	std::shared_ptr<TimersRegisterCount_t> TIMERS_REGISTER_T3_COUNT;
	std::shared_ptr<TimersRegisterMode_t>  TIMERS_REGISTER_T3_MODE;
	std::shared_ptr<MappedMemory32_t>      TIMERS_REGISTER_T3_COMP;
	std::shared_ptr<DeadMMemory_t>         TIMERS_REGISTER_TIMER_1830;

	// Array of timer objects, needed to perform iterations.
	struct TimerRegisters_t
	{
		std::shared_ptr<TimersRegisterCount_t> Count;
		std::shared_ptr<TimersRegisterMode_t>  Mode;
		std::shared_ptr<MappedMemory32_t>      Compare;
		std::shared_ptr<MappedMemory32_t>      Hold;
	} TimerRegisters[PS2Constants::EE::Timers::NUMBER_TIMERS];

};

