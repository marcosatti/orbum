#pragma once

/// All of the IOP core exceptions.
/// For reference, see MIPS R3000 docs.
enum class IopCoreException
{
    EX_INTERRUPT = 0,
    EX_TLB_MODIFIED = 1,
    EX_TLB_REFILL_INSTRUCTION_FETCH_LOAD = 2,
    EX_TLB_REFILL_STORE = 3,
    EX_ADDRESS_ERROR_INSTRUCTION_FETCH_LOAD = 4,
    EX_ADDRESS_ERROR_STORE = 5,
    EX_BUS_ERROR_INSTRUCTION_FETCH = 6,
    EX_BUS_ERROR_LOAD_STORE = 7,
    EX_SYSTEMCALL = 8,
    EX_BREAK = 9,
    EX_RESERVED_INSTRUCTION = 10,
    EX_COPROCESSOR_UNUSABLE = 11,
    EX_OVERFLOW = 12,
    EX_RESET // Not documented, but used for resetting within the emulator.
};