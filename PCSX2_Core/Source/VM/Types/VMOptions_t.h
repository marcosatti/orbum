#pragma once

#include <string>

enum class ExecutionCore_t
{
	Interpreter,
	Recompiler
};

struct VMOptions_t
{
	void            (*LOG_DELEGATE_FUNCPTR)(const char * buffer); // Log delegate function pointer.
	std::string     BOOT_ROM_PATH;                                // Boot ROM file path.
	ExecutionCore_t OPTION_EXECUTION_CORE;                        // Type of execution core to use.
};
