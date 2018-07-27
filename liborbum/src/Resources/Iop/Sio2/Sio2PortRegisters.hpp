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

// Infomation used from PCSX2: Sio.cpp and IopSio2.cpp.
class Sio2PortRegister_Ctrl3 : public SizedWordRegister, public ScopeLock
{
public:
    static constexpr Bitfield PADPORT   = Bitfield(0, 1);  // Port 0/1 that the SIO should be configured for.
    static constexpr Bitfield CMDLEN    = Bitfield(8, 9);  // Pad/mc command length (send to SIO0 length)
    static constexpr Bitfield BUFSZ     = Bitfield(18, 9); // Pad/mc response length (receive from SIO0 length) (TODO: assumed to always interrupt after).
                                                           // Note that PCSX2 appears to not use this properly, so maybe this isn't correct.

    Sio2PortRegister_Ctrl3();

    /// Write latch, used to signal when a port transfer should start. 
    /// Set upon bus writes.
    bool write_latch;

    /// Port transfer status, used to signify if a transfer has started on this 
    /// port. Changed by the SIO2 controller.
    bool port_transfer_started;

    /// Scope locked bus writes.
	void byte_bus_write_uword(const BusContext context, const usize offset, const uword value) override;
};
