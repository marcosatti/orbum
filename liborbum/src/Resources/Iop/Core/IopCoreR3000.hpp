#pragma once

#include <cereal/cereal.hpp>

#include "Common/Constants.hpp"
#include "Common/Types/Mips/BranchDelaySlot.hpp"
#include "Common/Types/Register/PcRegisters.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"

/// The IOP MIPS R3000 CPU (used as the IOP / PSX CPU).
/// It uses a little-endian configuration.
/// There is no official documentation from Sony on any of the IOP - implementation is based off PCSX2's code, and other documents available online.
/// There are many user-submitted documents about the PSX architecture, which has been used to aid implementation.
class IopCoreR3000
{
public:
    IopCoreR3000();

    /// The 32-bit Program Counter (PC) register.
    /// Points to the current instruction virtual address.
    WordPcRegister pc;

    /// Branch delay slot holding area.
    BranchDelaySlot<> bdelay;

    /// The 32 general purpose registers. They are each 32-bits long.
    /// GPR[0] is hardwired to 0.
    SizedWordRegister gpr[Constants::IOP::IOPCore::R3000::NUMBER_GP_REGISTERS];

    /// The HI and LO registers.
    /// These registers are used to hold the results of integer multiply and divide operations.
    /// They are 32-bit long.
    SizedWordRegister hi;
    SizedWordRegister lo;

public:
    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(
            CEREAL_NVP(pc),
            CEREAL_NVP(bdelay),
            CEREAL_NVP(gpr),
            CEREAL_NVP(hi),
            CEREAL_NVP(lo)
        );
    }
};
