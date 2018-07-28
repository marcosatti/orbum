#include <boost/format.hpp>

#include "Resources/Ee/EeRegisters.hpp"

#include "Common/Constants.hpp"
#include "Common/Types/Memory/ArrayByteMemory.hpp"
#include "Common/Types/Primitive.hpp"
#include "Core.hpp"

EeRegister_Sio::EeRegister_Sio() :
    ArrayByteMemory(SIZE_EE_REGISTER_SIO)
{
}

void EeRegister_Sio::write_ubyte(const size_t offset, const ubyte value)
{
    switch (offset)
    {
    case OFFSET_SIO_TXFIFO: // "SIO_TXFIFO"
    {
#if DEBUG_LOG_SIO_MESSAGES
        // Below logic adapted from the old PCSX2 code (see HwWrite.cpp).
        if (value == '\r')
        {
            // '\r' and sometimes after, '\n', are the last characters before the message is ready to be output.
            // Do not bother outputting the '\r' or '\n' characters, as this is done by the logging functions of the emulator.

            // Output the message.
            BOOST_LOG(Core::get_logger()) << boost::format("%s: %s") % SIO_BUFFER_PREFIX % sio_buffer.c_str();

            // Reset the buffer.
            sio_buffer.clear();
        }
        else if (value != '\n') // See above for why '\n' is not written to the buffer.
            sio_buffer.push_back(value);
#endif
        break;
    }
    default:
    {
        ArrayByteMemory::write_ubyte(offset, value);
        break;
    }
    }
}

uword EeRegister_Sio::read_uword(const size_t offset)
{
    switch (offset)
    {
    case OFFSET_SIO_ISR:
    {
        // From old PCSX2: 0x..F130 returns 0. Not sure why. From my own testing, BIOS requires this.
        return 0;
    }
    default:
    {
        return ArrayByteMemory::read_uword(offset);
    }
    }
}

void EeRegister_Sio::write_uword(const size_t offset, const uword value)
{
    switch (offset)
    {
    case OFFSET_SIO_TXFIFO:
    {
        // Below logic is from the old PCSX2. I guess it writes a message transmitted through the SIO_TXFIFO register..
        for (auto i = 0; i < NUMBER_BYTES_IN_WORD; i++)
            write_ubyte(offset, reinterpret_cast<const ubyte*>(&value)[i]);
        break;
    }
    default:
    {
        ArrayByteMemory::write_uword(offset, value);
        break;
    }
    }
}

EeRegister_Mch::EeRegister_Mch() :
    ArrayByteMemory(SIZE_EE_REGISTER_MCH)
{
}

uword EeRegister_Mch::read_uword(const size_t offset)
{
    switch (offset)
    {
    case OFFSET_MCH_DRD:
    {
        // Below logic is from the old PCSX2.
        if (!((ArrayByteMemory::read_uword(OFFSET_MCH_RICM) >> 6) & 0xF))
        {
            switch ((ArrayByteMemory::read_uword(OFFSET_MCH_RICM) >> 16) & 0xFFF)
            {
                // MCH_RICM: x:4|SA:12|x:5|SDEV:1|SOP:4|SBC:1|SDEV:5
            case 0x21: //INIT
                if (rdram_sdevid < rdram_devices)
                {
                    rdram_sdevid++;
                    return 0x1F;
                }
                return 0;

            case 0x23:         // CNFGA
                return 0x0D0D; // PVER=3 | MVER=16 | DBL=1 | REFBIT=5

            case 0x24: // CNFGB
                // 0x0110 for PSX  SVER=0 | CORG=8(5x9x7) | SPT=1 | DEVTYP=0 | BYTE=0
                return 0x0090; // SVER=0 | CORG=4(5x9x6) | SPT=1 | DEVTYP=0 | BYTE=0

            case 0x40:                                                      // DEVID
                return ArrayByteMemory::read_uword(OFFSET_MCH_RICM) & 0x1F; // =SDEV
            }
        }
    }
    case OFFSET_MCH_RICM:
    {
        return 0;
    }
    default:
    {
        return ArrayByteMemory::read_uword(offset);
    }
    }
}

void EeRegister_Mch::write_uword(const size_t offset, const uword value)
{
    switch (offset)
    {
    case OFFSET_MCH_RICM:
    {
        // Below logic is from the old PCSX2.
        // MCH_RICM: x:4|SA:12|x:5|SDEV:1|SOP:4|SBC:1|SDEV:5

        if ((((value >> 16) & 0xFFF) == 0x21) && (((value >> 6) & 0xF) == 1)
            && (((ArrayByteMemory::read_uword(OFFSET_MCH_DRD) >> 7) & 1) == 0)) // INIT & SRP=0
        {
            rdram_sdevid = 0; // If SIO repeater is cleared, reset sdevid
        }

        ArrayByteMemory::write_uword(OFFSET_MCH_RICM, value & ~0x80000000); // Kill the busy bit

        break;
    }
    default:
    {
        ArrayByteMemory::write_uword(offset, value);
        break;
    }
    }
}