#include "stdafx.h"

#include "Common/PS2Resources/EE/Timers/Timers_t.h"
#include "Common/PS2Resources/EE/Timers/Types/Timers_Registers_t.h"
#include "Common/PS2Resources/Types/MappedMemory/DeadMMemory_t.h"
#include "Common/PS2Resources/Types/Registers/Register32_t.h"

Timers_t::Timers_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),

	// Registers
	TIMERS_REGISTER_T0_COUNT(std::make_shared<TimersRegisterCount_t>()),
	TIMERS_REGISTER_T0_MODE(std::make_shared<TimersRegisterMode_t>(getRootResources(), 0)),
	TIMERS_REGISTER_T0_COMP(std::make_shared<Register32_t>()),
	TIMERS_REGISTER_T0_HOLD(std::make_shared<Register32_t>()),
	TIMERS_MEMORY_TIMER_0040(std::make_shared<DeadMMemory_t>(0x7C0, "TIMER: TIMER_0040 (reserved)", 0x10000040)),
	TIMERS_REGISTER_T1_COUNT(std::make_shared<TimersRegisterCount_t>()),
	TIMERS_REGISTER_T1_MODE(std::make_shared<TimersRegisterMode_t>(getRootResources(), 1)),
	TIMERS_REGISTER_T1_COMP(std::make_shared<Register32_t>()),
	TIMERS_REGISTER_T1_HOLD(std::make_shared<Register32_t>()),
	TIMERS_MEMORY_TIMER_0840(std::make_shared<DeadMMemory_t>(0x7C0, "TIMER: TIMER_0840 (reserved)", 0x10000840)),
	TIMERS_REGISTER_T2_COUNT(std::make_shared<TimersRegisterCount_t>()),
	TIMERS_REGISTER_T2_MODE(std::make_shared<TimersRegisterMode_t>(getRootResources(), 2)),
	TIMERS_REGISTER_T2_COMP(std::make_shared<Register32_t>()),
	TIMERS_MEMORY_TIMER_1030(std::make_shared<DeadMMemory_t>(0x7D0, "TIMER: TIMER_1030 (reserved)", 0x10001030)),
	TIMERS_REGISTER_T3_COUNT(std::make_shared<TimersRegisterCount_t>()),
	TIMERS_REGISTER_T3_MODE(std::make_shared<TimersRegisterMode_t>(getRootResources(), 3)),
	TIMERS_REGISTER_T3_COMP(std::make_shared<Register32_t>()),
	TIMERS_MEMORY_TIMER_1830(std::make_shared<DeadMMemory_t>(0x7D0, "TIMER: TIMER_1830 (reserved)", 0x10001830)),
	TimerRegisters{
		{ TIMERS_REGISTER_T0_COUNT, TIMERS_REGISTER_T0_MODE, TIMERS_REGISTER_T0_COMP, TIMERS_REGISTER_T0_HOLD },
		{ TIMERS_REGISTER_T1_COUNT, TIMERS_REGISTER_T1_MODE, TIMERS_REGISTER_T1_COMP, TIMERS_REGISTER_T1_HOLD },
		{ TIMERS_REGISTER_T2_COUNT, TIMERS_REGISTER_T2_MODE, TIMERS_REGISTER_T2_COMP, nullptr },
		{ TIMERS_REGISTER_T3_COUNT, TIMERS_REGISTER_T3_MODE, TIMERS_REGISTER_T3_COMP, nullptr } }
{
}
