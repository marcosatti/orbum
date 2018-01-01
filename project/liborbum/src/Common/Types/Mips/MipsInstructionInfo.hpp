#pragma once

/// Encapsulates information about any MIPS instruction defined.
/// See comments below, next to each field.
struct MipsInstructionInfo
{
	const char * const mnemonic;   // A string representation of the instruction or subclass.
	const int          impl_index; // Implementation index.
	const int          cpi;        // Cycles per instruction, used for timing.
};