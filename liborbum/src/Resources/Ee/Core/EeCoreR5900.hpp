#pragma once

#include "Common/Constants.hpp"
#include "Common/Types/Mips/BranchDelaySlot.hpp"
#include "Common/Types/Register/PcRegisters.hpp"
#include "Common/Types/Register/SizedQwordRegister.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"

/// The R5900 is the EE Core's CPU.
/// It has been modified from a stock R5900 to include Sony specific instructions
/// (multimedia instructions targeting 128-bit operations etc).
/// Uses a little-endian configuration.
class EeCoreR5900
{
public:
    EeCoreR5900();

    /// The 32-bit Program Counter (PC) register. See EE Core Users manual, pg 61.
    /// Points to the current instruction virtual address.
    WordPcRegister pc;

    /// Branch delay slot holding area.
    BranchDelaySlot<> bdelay;

    /// The R5900 general purpose registers (GPR's) are 128-bit long.
    /// The upper 64-bits are only used when specific instructions are run, such as
    /// using the EE Core specific multimedia instructions (parallel instructions). Example: PADDB.
    /// See EE Core Users Manual, pg 60.
    SizedQwordRegister gpr[Constants::EE::EECore::R5900::NUMBER_GP_REGISTERS];

    /// The HI and LO registers. See EE Core Users manual, pg 60.
    /// These registers are used to hold the results of integer multiply and divide operations.
    SizedQwordRegister hi;
    SizedQwordRegister lo;

    /// The Shift Amount (SA) register. See EE Core Users manual, pg 61.
    /// The SA register is used for holding funnel shift instruction results.
    /// See the EE Core instruction QFSRV for more details (SA is only used for this instruction).
    SizedWordRegister sa;

    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(
            CEREAL_NVP(pc),
            CEREAL_NVP(bdelay),
            CEREAL_NVP(gpr),
            CEREAL_NVP(hi),
            CEREAL_NVP(lo),
            CEREAL_NVP(sa)
        );
    }
};