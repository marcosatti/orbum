#pragma once

#include "Common/Constants.hpp"
#include "Common/Types/Mips/MipsCoprocessor0.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"
#include "Resources/Iop/Core/IopCoreCop0Registers.hpp"

using OperatingContext = MipsCoprocessor0::OperatingContext;

/// COP0 refers to the system control coprocessor (used for manipulating the memory management and exception handling facilities of the processor, etc).
class IopCoreCop0 : public MipsCoprocessor0
{
public:
    IopCoreCop0();

    /// Checks if the IOP COP0 coprocessor is usable.
    /// Can be used by the component calling this to raise a IopCoreException(coprocessor unusable) if not available.
    bool is_usable() override;

    /// Determine the CPU context. Uses the Status register.
    OperatingContext operating_context() override;

    /// IOP COP0 register implementations.
    SizedWordRegister indx;              // r0: INDX.
    SizedWordRegister rand;              // r1: RAND.
    SizedWordRegister tlbl;              // r2: TLBL.
    SizedWordRegister bpc;               // r3: BPC.
    IopCoreCop0Register_Context context; // r4: Context.
    SizedWordRegister bda;               // r5: BDA.
    SizedWordRegister pidmask;           // r6: PIDMASK.
    SizedWordRegister dcic;              // r7: DCIC.
    SizedWordRegister badv;              // r8: BADV.
    SizedWordRegister bdam;              // r9: BDAM.
    SizedWordRegister tlbh;              // r10: TLBH.
    SizedWordRegister bpcm;              // r11: BPCM.
    IopCoreCop0Register_Status status;   // r12: Status.
    IopCoreCop0Register_Cause cause;     // r13: Cause.
    SizedWordRegister epc;               // r14: EPC.
    IopCoreCop0Register_Prid prid;       // r15: PRId.
    SizedWordRegister erreg;             // r16: ERREG.

    /// Array of COP0 registers.
    SizedWordRegister* registers[Constants::IOP::IOPCore::COP0::NUMBER_REGISTERS];
};
