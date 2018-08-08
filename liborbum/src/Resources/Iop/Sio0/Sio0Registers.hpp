#include "Common/Types/Bitfield.hpp"
#include "Common/Types/FifoQueue/DmaFifoQueue.hpp"
#include "Common/Types/Register/ByteRegister.hpp"
#include "Common/Types/Register/SizedHwordRegister.hpp"
#include "Common/Types/ScopeLock.hpp"

/// SIO0 ctrl register.
/// Needs to be accessed atomically by the SIO0 and SIO2 within emulator.
/// Assumed to be similar to the PSX SIO (pad/mc), consult no$psx docs.
class Sio0Register_Ctrl : public SizedHwordRegister, public ScopeLock
{
public:
    static constexpr Bitfield TXEN = Bitfield(0, 1);        // Enable SIO0 transmit.
    static constexpr Bitfield DTR = Bitfield(1, 1);         // (Data terminal ready) SIO is ready to receive data from pad/mc selected by PORT.
    static constexpr Bitfield RXEN = Bitfield(2, 1);        // 0 means normal operation, RXEN is always enabled otherwise? (not sure what 1: "force" means)
    static constexpr Bitfield RESET_IRQ = Bitfield(4, 1);   // This is like a "master controller has acknowledged IRQ" bit, don't be confused with SIO_RESET.
    static constexpr Bitfield SIO_RESET = Bitfield(6, 1);   // This is like a global SIO reset (see no$psx docs).
    static constexpr Bitfield RX_INT_MODE = Bitfield(8, 2); // Receive buffer interrupt mode, used with bit 11.
    static constexpr Bitfield TX_INT_EN = Bitfield(10, 1);  // Transmit interrupt enable.
    static constexpr Bitfield RX_INT_EN = Bitfield(11, 1);  // receive interrupt enable, interrupt when RX_INT_MODE bytes have been received.
    static constexpr Bitfield ACK_INT_EN = Bitfield(12, 1); // Pad/mc acknowledge line interrupt enable (used with STAT.DSR).
    static constexpr Bitfield PORT = Bitfield(13, 1);       // Currently selected port (0/1).

    /// Scope locked bus writes.
    void byte_bus_write_uhword(const BusContext context, const usize offset, const uhword value) override;
};

/// SIO0 stat register.
/// Needs to be accessed atomically by the SIO0 and SIO2 within emulator.
/// Assumed to be similar to the PSX SIO (pad/mc), consult no$psx docs.
class Sio0Register_Stat : public SizedHwordRegister, public ScopeLock
{
public:
    static constexpr Bitfield TX_RDY1 = Bitfield(0, 1);
    static constexpr Bitfield RX_NONEMPTY = Bitfield(1, 1); // RX FIFO non-empty.
    static constexpr Bitfield TX_RDY2 = Bitfield(2, 1);
    static constexpr Bitfield PARITY_ERR = Bitfield(3, 1);
    static constexpr Bitfield DSR = Bitfield(7, 1); // (Data set ready) Acknowledge input line level by pad/mc.
    static constexpr Bitfield IRQ = Bitfield(9, 1); // IRQ line, setting this causes an interrupt to fire.

    /// Scope locked bus writes.
    void byte_bus_write_uhword(const BusContext context, const usize offset, const uhword value) override;
};

/// SIO0 data "register".
/// This is a hybrid FIFO port, where writing and reading access 2 different
/// FIFO queues. Tx direction means from SIO2 to SIO0, Rx direction means from
/// SIO0 to SIO2.
class Sio0Register_Data : public ByteRegister
{
public:
    Sio0Register_Data();

    void initialize() override;

    ubyte read_ubyte() override;
    void write_ubyte(const ubyte value) override;

    /// FIFO queues.
    /// These queues are meant to be accessed directly from the SIO0 only, for
    /// all other components, this is meant to be accessed as a register.
    DmaFifoQueue<> command_queue;
    DmaFifoQueue<> response_queue;

    /// Reference to the SIO0 stat register, needed to change status bits
    /// depending on the different FIFO queue states (tx full/rx empty).
    Sio0Register_Stat* stat;

public:
    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(
            CEREAL_NVP(command_queue),
            CEREAL_NVP(response_queue)
        );
    }
};
