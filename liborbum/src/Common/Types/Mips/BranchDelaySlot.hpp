#pragma once

#include "Common/Types/Primitive.hpp"
#include "Common/Types/Register/PcRegisters.hpp"

/// Contains functionallity for the branch delay slot featured in MIPS CPU's.
/// A branch delay occurs when a jump/branch instruction is hit,
/// and the subsequent instructions are known as the "branch slots".
/// These instructions in the branch slots are executed until the number of
/// configured branch slots have been run, and then the jump/branch occurs.
/// A default slot size of 1 is used by the EE and IOP cores.
/// slot + 1 is used internally as this is the real amount of instruction cycles.
template <size_t slots = 1>
class BranchDelaySlot
{
public:
    BranchDelaySlot() :
        current_slot(0),
        branch_pc(0)
    {
    }

    /// Sets a pending branch to the direct address given.
    void set_branch_direct(const uptr address)
    {
        current_slot = slots + 1;
        branch_pc = address;
    }

    /// Sets a pending branch which combines the current PC address with
    /// the offset specified. Used for I-type instructions (imm's).
    void set_branch_itype(WordPcRegister& pc, const shword imm)
    {
        current_slot = slots + 1;
        branch_pc = (pc.read_uword() + Constants::MIPS::SIZE_MIPS_INSTRUCTION) + (imm << 2);
    }

    /// Sets a pending branch which combines the current PC address with
    /// the region address. Used for J-type instructions.
    void set_branch_jtype(WordPcRegister& pc, const uptr j_region_addr)
    {
        current_slot = slots + 1;
        branch_pc = ((pc.read_uword() + Constants::MIPS::SIZE_MIPS_INSTRUCTION) & 0xF0000000) | (j_region_addr << 2);
    }

    /// Advances the PC by either incrementing by 1 instruction,
    /// or taking a branch if all slots have been used.
    void advance_pc(WordPcRegister& pc)
    {
        if (current_slot)
        {
            current_slot--;
            if (!current_slot)
            {
                // Do branch now.
                pc.write_uword(branch_pc);
                return;
            }
        }

        // Increment by 1 instruction.
        pc.offset(Constants::MIPS::SIZE_MIPS_INSTRUCTION);
    }

    /// Stops the current branch in progress (used by exception handler).
    void stop_branch()
    {
        current_slot = 0;
    }

    /// Returns if a branch is currently pending.
    bool is_branch_pending() const
    {
        return current_slot > 0;
    }

private:
    size_t current_slot;
    uptr branch_pc;
};