#pragma once

/*
Describes the CPU operating context - see MIPSCoprocessor0_t
*/
enum class MIPSOperatingContext_t
{
	Kernel,
	Supervisor,
	User
};
