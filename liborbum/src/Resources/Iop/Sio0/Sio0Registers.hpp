#include "Common/Types/Bitfield.hpp"
#include "Common/Types/ScopeLock.hpp"
#include "Common/Types/Register/SizedHwordRegister.hpp"

/// SIO0 ctrl register.
/// Needs to be accessed atomically by the SIO0 and SIO2 within emulator.
class Sio0Register_Ctrl : public SizedHwordRegister, public ScopeLock
{
public:    
    static constexpr Bitfield TX_PERM   = Bitfield(0, 1);
    static constexpr Bitfield DTR       = Bitfield(1, 1);
    static constexpr Bitfield RX_PERM   = Bitfield(2, 1);
    static constexpr Bitfield BREAK     = Bitfield(3, 1);
    static constexpr Bitfield RESET_IRQ = Bitfield(4, 1); // This is like a "master controller has acknowledged IRQ" bit, don't be confused with SIO_RESET.
    static constexpr Bitfield RTS       = Bitfield(5, 1);
    static constexpr Bitfield SIO_RESET = Bitfield(6, 1); // This is like a global SIO reset (see no$psx docs).

    /// Scope locked bus writes.
	void byte_bus_write_uhword(const BusContext context, const usize offset, const uhword value) override;
};

/// SIO0 ctrl register.
/// Needs to be accessed atomically by the SIO2 within emulator.
class Sio0Register_Stat : public SizedHwordRegister, public ScopeLock
{
public:
    static constexpr Bitfield TX_RDY      = Bitfield(0, 1);
    static constexpr Bitfield RX_RDY      = Bitfield(1, 1);
    static constexpr Bitfield TX_EMPTY    = Bitfield(2, 1);
    static constexpr Bitfield PARITY_ERR  = Bitfield(3, 1);
    static constexpr Bitfield RX_OVERRUN  = Bitfield(4, 1);
    static constexpr Bitfield FRAMING_ERR = Bitfield(5, 1);
    static constexpr Bitfield SYNC_DETECT = Bitfield(6, 1);
    static constexpr Bitfield DSR         = Bitfield(7, 1);
    static constexpr Bitfield CTS         = Bitfield(8, 1);
    static constexpr Bitfield IRQ         = Bitfield(9, 1);

    /// Scope locked bus writes.
	void byte_bus_write_uhword(const BusContext context, const usize offset, const uhword value) override;
};