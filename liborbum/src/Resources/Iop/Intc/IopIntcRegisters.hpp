#pragma once

#include "Common/Constants.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"
#include "Common/Types/ScopeLock.hpp"

/// IOP INTC I_CTRL register.
/// Functionality is largely unknown, however upon reading (through IOP), the register value is set to 0.
/// Seems to be the master control for masking interrupts.
/// See https://fossies.org/linux/audacious-plugins/src/psf/peops2/registers.h (line 249), and PCSX2's IopHwRead/Write.cpp.
class IopIntcRegister_Ctrl : public SizedWordRegister
{
public:
    /// Returns the register value, and sets it to 0 after (IOP context only).
    uword byte_bus_read_uword(const BusContext context, const usize offset) override;
};

/// The IOP INTC I_MASK register, which holds a set of flags determining if the interrupt source is masked.
/// Names from here, not sure if accurate: https://github.com/kode54/Highly_Experimental/blob/master/Core/iop.c.
class IopIntcRegister_Mask : public SizedWordRegister
{
public:
    static constexpr Bitfield VBLANK = Bitfield(0, 1);
    static constexpr Bitfield GPU = Bitfield(1, 1);
    static constexpr Bitfield CDROM = Bitfield(2, 1);
    static constexpr Bitfield DMAC = Bitfield(3, 1);
    static constexpr Bitfield TMR0 = Bitfield(4, 1);
    static constexpr Bitfield TMR1 = Bitfield(5, 1);
    static constexpr Bitfield TMR2 = Bitfield(6, 1);
    static constexpr Bitfield SIO0 = Bitfield(7, 1);
    static constexpr Bitfield SIO1 = Bitfield(8, 1);
    static constexpr Bitfield SPU = Bitfield(9, 1);
    static constexpr Bitfield PIO = Bitfield(10, 1);
    static constexpr Bitfield EVBLANK = Bitfield(11, 1); // End of VBLANK.
    static constexpr Bitfield DVD = Bitfield(12, 1);
    static constexpr Bitfield PCMCIA = Bitfield(13, 1);
    static constexpr Bitfield TMR3 = Bitfield(14, 1);
    static constexpr Bitfield TMR4 = Bitfield(15, 1);
    static constexpr Bitfield TMR5 = Bitfield(16, 1);
    static constexpr Bitfield SIO2 = Bitfield(17, 1);
    static constexpr Bitfield HTR0 = Bitfield(18, 1);
    static constexpr Bitfield HTR1 = Bitfield(19, 1);
    static constexpr Bitfield HTR2 = Bitfield(20, 1);
    static constexpr Bitfield HTR3 = Bitfield(21, 1);
    static constexpr Bitfield USB = Bitfield(22, 1);
    static constexpr Bitfield EXTR = Bitfield(23, 1);
    static constexpr Bitfield FWRE = Bitfield(24, 1);
    static constexpr Bitfield FDMA = Bitfield(25, 1);
};

/// The IOP INTC I_STAT register, which holds a set of flags determining if a component caused an interrupt.
/// When written to, AND's the previous value with the new value (see IopHwWrite.cpp in PCSX2).
/// Names from here, not sure if accurate: https://github.com/kode54/Highly_Experimental/blob/master/Core/iop.c.
/// (Assumed) The INTC is edge triggered (ie: only need to pulse line), see the EE INTC equivilant.
/// STAT writes needs to be scope locked by the peripherals.
class IopIntcRegister_Stat : public SizedWordRegister, public ScopeLock
{
public:
    static constexpr Bitfield VBLANK = Bitfield(0, 1);
    static constexpr Bitfield GPU = Bitfield(1, 1);
    static constexpr Bitfield CDROM = Bitfield(2, 1);
    static constexpr Bitfield DMAC = Bitfield(3, 1);
    static constexpr Bitfield TMR0 = Bitfield(4, 1);
    static constexpr Bitfield TMR1 = Bitfield(5, 1);
    static constexpr Bitfield TMR2 = Bitfield(6, 1);
    static constexpr Bitfield SIO0 = Bitfield(7, 1);
    static constexpr Bitfield SIO1 = Bitfield(8, 1);
    static constexpr Bitfield SPU = Bitfield(9, 1);
    static constexpr Bitfield PIO = Bitfield(10, 1);
    static constexpr Bitfield EVBLANK = Bitfield(11, 1); // End of VBLANK.
    static constexpr Bitfield DVD = Bitfield(12, 1);
    static constexpr Bitfield PCMCIA = Bitfield(13, 1);
    static constexpr Bitfield TMR3 = Bitfield(14, 1);
    static constexpr Bitfield TMR4 = Bitfield(15, 1);
    static constexpr Bitfield TMR5 = Bitfield(16, 1);
    static constexpr Bitfield SIO2 = Bitfield(17, 1);
    static constexpr Bitfield HTR0 = Bitfield(18, 1);
    static constexpr Bitfield HTR1 = Bitfield(19, 1);
    static constexpr Bitfield HTR2 = Bitfield(20, 1);
    static constexpr Bitfield HTR3 = Bitfield(21, 1);
    static constexpr Bitfield USB = Bitfield(22, 1);
    static constexpr Bitfield EXTR = Bitfield(23, 1);
    static constexpr Bitfield FWRE = Bitfield(24, 1);
    static constexpr Bitfield FDMA = Bitfield(25, 1);

    static constexpr Bitfield IRQ_KEYS[Constants::IOP::INTC::NUMBER_IRQ_LINES] = {VBLANK, GPU, CDROM, DMAC, TMR0, TMR1, TMR2, SIO0, SIO1, SPU, PIO, EVBLANK, DVD, PCMCIA, TMR3, TMR4, TMR5, SIO2, HTR0, HTR1, HTR2, HTR3, USB, EXTR, FWRE, FDMA};
    static constexpr Bitfield TMR_KEYS[Constants::IOP::Timers::NUMBER_TIMERS] = {TMR0, TMR1, TMR2, TMR3, TMR4, TMR5};

    /// AND's the new value with old value (IOP context only).
    /// Scope locked.
    void byte_bus_write_uword(const BusContext context, const usize offset, const uword value) override;
};