#pragma once

#include <cereal/cereal.hpp>

#include "Common/Types/Mips/BranchDelaySlot.hpp"
#include "Common/Types/Primitive.hpp"
#include "Common/Types/Register/PcRegisters.hpp"

/// BranchDelaySlot, modified slightly for the VUs.
/// See BranchDelaySlot for more documentation.
template <size_t slots = 1>
class VuBranchDelaySlot : public BranchDelaySlot<slots>
{
public:
    VuBranchDelaySlot() :
        second_branch_pc(0),
        second_branch_pending(false),
        BranchDelaySlot<slots>()
    {
    }

    /// is_branch_pending() in VuBranchDelaySlot has the same behaviour as the
    /// one in BranchDelaySlot.
    using BranchDelaySlot<slots>::is_branch_pending;

    /// Obtains the PC of which the VU is branching to.
    /// This is used by the *AL* (link register) branching/jumping instructions.
    uptr get_branch_pc()
    {
        return branch_pc;
    }

    /// Sets the offset of the PC address of the VUs, with a delay slot.
    /// See BranchDelaySlot::set_branch_itype for more documentation.
    /// The only difference is the size of the instruction - VU instructions are 8 bytes long
    /// whereas EE Core instructions are only 4.
    void set_branch_itype(WordPcRegister& pc, const shword imm)
    {
        // If we are branching in the delay slot, the original branch runs for only one cycle
        if (is_branch_pending())
        {
            second_branch_pending = true;
            second_branch_pc = (pc.read_uword() + Constants::EE::VPU::SIZE_VU_INSTRUCTION + imm * 8) & 0x3FFF;
        }
        else
        {
            current_slot = slots + 1;

            // VU can hold 16KB of instructions only (and 4KB in VU0), so AND it with 0x3FFF
            branch_pc = (pc.read_uword() + Constants::EE::VPU::SIZE_VU_INSTRUCTION + imm * 8) & 0x3FFF;
        }
    }

    /// Sets the PC address of the VUs, with a delay slot.
    /// The VUs' jumping range is much smaller than the EE Core's
    /// (just 16KB is sufficient for the VUs), and so this method behaves
    /// differently from the original set_branch_jtype.
    void set_branch_jtype(WordPcRegister& pc, const uptr jump_to)
    {
        if (is_branch_pending())
        {
            second_branch_pending = true;
            second_branch_pc = (jump_to * 8) & 0x3FFF;
        }
        else
        {
            current_slot = slots + 1;
            branch_pc = (jump_to * 8) & 0x3FFF;
        }
    }

    void advance_pc(WordPcRegister& pc)
    {
        if (current_slot)
        {
            current_slot--;
            if (!current_slot)
            {
                pc.write_uword(branch_pc);
                if (second_branch_pending)
                {
                    second_branch_pending = false;
                    branch_pc = second_branch_pc;
                    current_slot = 1;
                }
                return;
            }
        }

        pc.offset(Constants::EE::VPU::SIZE_VU_INSTRUCTION);
    }

private:
    // introduces the base class variables to this class
    using BranchDelaySlot<slots>::branch_pc;
    using BranchDelaySlot<slots>::current_slot;

    uptr second_branch_pc;
    bool second_branch_pending;

    // Serialization
public:
    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(
            CEREAL_NVP(current_slot),
            CEREAL_NVP(branch_pc),
            CEREAL_NVP(second_branch_pc),
            CEREAL_NVP(second_branch_pending));
    }
};