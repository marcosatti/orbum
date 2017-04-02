#pragma once

/*
Describes the CPU operating context - see MIPSCoprocessor0_t
*/
enum class MIPSCPUOperatingContext_t
{
	Kernel,
	Supervisor,
	User
};
