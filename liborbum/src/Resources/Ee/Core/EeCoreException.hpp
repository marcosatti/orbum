#pragma once

/// All EE Core exceptions in terms of EXCCODE(2)
/// See page 94 of the EE Core Users Manual.
enum class EeCoreException
{
    // Level 1.
    EX_INTERRUPT = 0,
    EX_TLB_MODIFIED = 1,
    EX_TLB_REFILL_INVALID_INSTRUCTION_FETCH_LOAD = 2,
    EX_TLB_REFILL_INVALID_STORE = 3,
    EX_ADDRESS_ERROR_INSTRUCTION_FETCH_LOAD = 4,
    EX_ADDRESS_ERROR_STORE = 5,
    EX_BUS_ERROR_INSTRUCTION_FETCH = 6,
    EX_BUS_ERROR_LOAD_STORE = 7,
    EX_SYSTEMCALL = 8,
    EX_BREAK = 9,
    EX_RESERVED_INSTRUCTION = 10,
    EX_COPROCESSOR_UNUSABLE = 11,
    EX_OVERFLOW = 12,
    EX_TRAP = 13,

    // Level 2 (offset of 100).
    EX_RESET = 100,
    EX_NMI = 101,
    EX_PERFORMANCE_COUNTER = 102,
    EX_DEBUG = 104,
};