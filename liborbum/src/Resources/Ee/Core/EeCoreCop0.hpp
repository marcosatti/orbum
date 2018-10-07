#pragma once

#include <cereal/cereal.hpp>

#include "Common/Constants.hpp"
#include "Common/Types/Mips/MipsCoprocessor0.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"
#include "Resources/Ee/Core/EeCoreCop0Registers.hpp"

/// COP0 refers to the system control coprocessor (used for manipulating the memory management and exception handling facilities of the processor, etc).
/// See EE Core Users Manual page 62 onwards.
class EeCoreCop0 : public MipsCoprocessor0
{
public:
    EeCoreCop0();

    /// Checks if the EECore COP0 coprocessor is usable.
    /// Can be used by the component calling this to raise a EeCoreException(coprocessor unusable) if not available.
    bool is_usable() override;

    /// Determine the CPU context. Uses the Status register.
    MipsCoprocessor0::OperatingContext operating_context() override;

    /// COP0 General registers.
    EeCoreCop0Register_Index index;       // r0:  Index that specifies TLB entry for reading for writing.
    EeCoreCop0Register_Random random;     // r1:  Pseudo-random index for TLB replacement.
    EeCoreCop0Register_EntryLo0 entrylo0; // r2:  Low half of TLB entry (for even PFN).
    EeCoreCop0Register_EntryLo1 entrylo1; // r3:  Low half of TLB entry (for odd PFN).
    EeCoreCop0Register_System context;    // r4:  Pointer to PTE table.
    EeCoreCop0Register_PageMask pagemask; // r5:  Most significant part of the TLB entry (page size mark).
    EeCoreCop0Register_Wired wired;       // r6:  Number of wired TLB entries.
    SizedWordRegister reserved7;          // r7:  Reserved.
    SizedWordRegister badvaddr;           // r8:  Bad virtual address value (for exceptions).
    SizedWordRegister count;              // r9:  Timer Compare.
    EeCoreCop0Register_EntryHi entryhi;   // r10: High half (Virtual page number and ASID) of TLB entry.
    EeCoreCop0Register_Cause cause;       // r13: Result of last exception taken. NEED TO BE INITALISED BEFORE COMPARE!
    EeCoreCop0Register_Compare compare;   // r11: Timer reference value.
    EeCoreCop0Register_Status status;     // r12: Processor Status Register.
    SizedWordRegister epc;                // r14: Exception Program Counter.
    EeCoreCop0Register_Prid prid;         // r15: Processor Revision Identifier.
    EeCoreCop0Register_Config config;     // r16: Configuration Register.
    SizedWordRegister reserved17;         // r17: Reserved.
    SizedWordRegister reserved18;         // r18: Reserved.
    SizedWordRegister reserved19;         // r19: Reserved.
    SizedWordRegister reserved20;         // r20: Reserved.
    SizedWordRegister reserved21;         // r21: Reserved.
    SizedWordRegister reserved22;         // r22: Reserved.
    EeCoreCop0Register_BadPAddr badpaddr; // r23: Bad Physical Address value (for exceptions).
                                          // r24: See below for r24.
                                          // r25: See below for r25.
    SizedWordRegister reserved26;         // r26: Reserved.
    SizedWordRegister reserved27;         // r27: Reserved.
    EeCoreCop0Register_TagLo taglo;       // r28: Low bits of the Cache Tag.
    EeCoreCop0Register_TagHi taghi;       // r29: High bits of the Cache Tag.
    SizedWordRegister errorepc;           // r30: Error Exception Program Counter.
    SizedWordRegister reserved31;         // r31: Reserved.

    /// Debug registers.
    EeCoreCop0Register_Bpc bpc; // r24: Registers related to debug function.
    SizedWordRegister iab;      // r32: Instruction address breakpoint settings.
    SizedWordRegister iabm;     // r33: Instruction address breakpoint settings.
    SizedWordRegister dab;      // r34: Data address breakpoint settings.
    SizedWordRegister dabm;     // r35: Data address breakpoint settings.
    SizedWordRegister dvb;      // r36: Data value breakpoint settings.
    SizedWordRegister dvbm;     // r37: Data value breakpoint settings.

    /// Performance registers.
    EeCoreCop0Register_Pccr pccr; // r25: Performance counter and control register.
    EeCoreCop0Register_Pcr0 pcr0; // r38: Performance counter.
    EeCoreCop0Register_Pcr1 pcr1; // r39: Performance counter.

    /// Array of above registers (needed by some EECore instructions to access by index).
    /// Generally you will never access registers directly through this, only the PS2 OS will.
    SizedWordRegister* registers[Constants::EE::EECore::COP0::NUMBER_REGISTERS];

    /// Array of PCR0/PCR1, used by the MFPC/MTPC instructions.
    SizedWordRegister* pcr_registers[Constants::EE::EECore::COP0::NUMBER_PCR_REGISTERS];

public:
    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(
            CEREAL_NVP(index),
            CEREAL_NVP(random),
            CEREAL_NVP(entrylo0),
            CEREAL_NVP(entrylo1),
            CEREAL_NVP(context),
            CEREAL_NVP(pagemask),
            CEREAL_NVP(wired),
            CEREAL_NVP(reserved7),
            CEREAL_NVP(badvaddr),
            CEREAL_NVP(count),
            CEREAL_NVP(entryhi),
            CEREAL_NVP(cause),
            CEREAL_NVP(compare),
            CEREAL_NVP(status),
            CEREAL_NVP(epc),
            CEREAL_NVP(prid),
            CEREAL_NVP(config),
            CEREAL_NVP(reserved17),
            CEREAL_NVP(reserved18),
            CEREAL_NVP(reserved19),
            CEREAL_NVP(reserved20),
            CEREAL_NVP(reserved21),
            CEREAL_NVP(reserved22),
            CEREAL_NVP(badpaddr),
            CEREAL_NVP(reserved26),
            CEREAL_NVP(reserved27),
            CEREAL_NVP(taglo),
            CEREAL_NVP(taghi),
            CEREAL_NVP(errorepc),
            CEREAL_NVP(reserved31),
            CEREAL_NVP(bpc),
            CEREAL_NVP(iab),
            CEREAL_NVP(iabm),
            CEREAL_NVP(dab),
            CEREAL_NVP(dabm),
            CEREAL_NVP(dvb),
            CEREAL_NVP(dvbm),
            CEREAL_NVP(pccr),
            CEREAL_NVP(pcr0),
            CEREAL_NVP(pcr1));
    }
};
