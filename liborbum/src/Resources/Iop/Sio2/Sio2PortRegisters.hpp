#include "Common/Types/Bitfield.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"
#include "Common/Types/ScopeLock.hpp"

class Sio2PortRegister_Ctrl1 : public SizedWordRegister
{
public:
};

class Sio2PortRegister_Ctrl2 : public SizedWordRegister
{
public:
};

class Sio2PortRegister_Ctrl3 : public SizedWordRegister, public ScopeLock
{
public:
    static constexpr Bitfield PADPORT   = Bitfield(0, 1);  // Port 0/1 that the SIO should be configured for.
    static constexpr Bitfield UNKNOWN1  = Bitfield(1, 7); 
    static constexpr Bitfield UNKNOWN6  = Bitfield(6, 1);  // TODO: not sure what this is, but seems special - is it a TXEN or start flag (probably wouldn't need write latch if this is case)?
    static constexpr Bitfield UNKNOWN7  = Bitfield(7, 1);
    static constexpr Bitfield CMDLEN    = Bitfield(8, 8);  // Pad/mc command length (send to SIO0 length)
    static constexpr Bitfield UNKNOWN15 = Bitfield(15, 1); 
    static constexpr Bitfield BUFSZ     = Bitfield(18, 8); // Pad/mc response length (receive from SIO0 length) (TODO: assumed to always interrupt after).
    static constexpr Bitfield UNKNOWN27 = Bitfield(27, 5); 

    Sio2PortRegister_Ctrl3();

    // Write latch, used to start/stop SIO2 transfers.
    // Set upon bus writes.
    bool write_latch;

    /// Scope locked bus writes.
	void byte_bus_write_uword(const BusContext context, const usize offset, const uword value) override;
};
