#pragma once

#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

#include "Common/Types/Mips/MipsCoprocessor0.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"

/// IOP Core COP0 registers.
/// See here where you can find more information: http://hitmen.c02.at/files/docs/psx/psx.pdf (thanks to Joshua Walker).

/// Context register of the IOP COP0.
class IopCoreCop0Register_Context : public SizedWordRegister
{
public:
    static constexpr Bitfield BADVPN2 = Bitfield(2, 19);
    static constexpr Bitfield PTEBASE = Bitfield(21, 11);
};

/// Status register of the IOP COP0.
class IopCoreCop0Register_Status : public SizedWordRegister
{
public:
    static constexpr Bitfield IEC = Bitfield(0, 1);
    static constexpr Bitfield KUC = Bitfield(1, 1);
    static constexpr Bitfield IEP = Bitfield(2, 1);
    static constexpr Bitfield KUP = Bitfield(3, 1);
    static constexpr Bitfield IEO = Bitfield(4, 1);
    static constexpr Bitfield KUO = Bitfield(5, 1);
    static constexpr Bitfield IM = Bitfield(8, 8);
    static constexpr Bitfield ISC = Bitfield(16, 1);
    static constexpr Bitfield SWC = Bitfield(17, 1);
    static constexpr Bitfield PZ = Bitfield(18, 1);
    static constexpr Bitfield CM = Bitfield(19, 1);
    static constexpr Bitfield PE = Bitfield(20, 1);
    static constexpr Bitfield TS = Bitfield(21, 1);
    static constexpr Bitfield BEV = Bitfield(22, 1);
    static constexpr Bitfield RE = Bitfield(25, 1);
    static constexpr Bitfield CU = Bitfield(28, 4);

    static constexpr uword INITIAL_VALUE = 0x00400000;

    IopCoreCop0Register_Status();

    /// Pushes/Pops the IE & KU bits (used in exception handling) to an older or earlier level (similar to a stack).
    /// In the bitfield names for those bits,
    /// "c" refers to the current status.
    /// "p" refers to the previous status.
    /// "o" refers to the oldest status.
    /// When pushing, clears the expunged bits to 0 (poping contains old values).
    void push_exception_stack();
    void pop_exception_stack();

    /// Upon writes:
    /// - Caches the operating context for COP0.
    /// - Caches the interrupt masked state for the CPU.
    void write_uword(const uword value) override;

    /// Current cached CPU interrupts masked state.
    bool interrupts_masked;

    /// Current cached COP0 operating context state.
    MipsCoprocessor0::OperatingContext operating_context;

private:
    /// Updates the cached interrupt masked state.
    /// Does so by checking the master ERL, EXL, EIE and IE bit.
    void handle_interrupts_masked_update();

    /// Updates the operation context state.
    /// Uses the KSU, ERL and EXL bits.
    void handle_operating_context_update();

public:
    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(
            cereal::base_class<SizedWordRegister>(this),
            CEREAL_NVP(interrupts_masked),
            CEREAL_NVP(operating_context)
        );
    }
};

/// Cause register of the IOP COP0.
class IopCoreCop0Register_Cause : public SizedWordRegister
{
public:
    static constexpr Bitfield EXCCODE = Bitfield(2, 5);
    static constexpr Bitfield IP = Bitfield(8, 8);
    static constexpr Bitfield CE = Bitfield(28, 2);
    static constexpr Bitfield BD = Bitfield(31, 1);

    IopCoreCop0Register_Cause();

    /// Clears all of the IRQ lines.
    void clear_all_irq();

    /// Sets the given IRQ line.
    void set_irq_line(const int irq);

    /// Clears the given IRQ line.
    void clear_irq_line(const int irq);

    /// Syncs the register state with the IRQ flags and returns the register value.
    uword read_uword() override;

private:
    /// IRQ line flags.
    bool irq_lines[8];

public:
    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(
            cereal::base_class<SizedWordRegister>(this),
            CEREAL_NVP(irq_lines)
        );
    }
};

/// The PRId register of the IOP COP0.
/// Some different initial values to EE Core implementation, same structure.
class IopCoreCop0Register_Prid : public SizedWordRegister
{
public:
    static constexpr Bitfield REV = Bitfield(0, 8);
    static constexpr Bitfield IMP = Bitfield(8, 8);

    static constexpr uword INITIAL_VALUE = 0x1F;

    IopCoreCop0Register_Prid();
};