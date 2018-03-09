#include "Common/Types/Primitive.hpp"

/// Real time clock of the CDVD.
class CdvdRtc
{
public:
    CdvdRtc();

    /// Clock values, used by the CDVD.
    /// These are internal registers only accessible though the RTC commands.
    ubyte second;
    ubyte minute;
    ubyte hour;
    ubyte day;
    ubyte month;
    ubyte year;

    /// Increments the RTC internal registers by the number of microseconds.
    void increment(const double time_us);

private:
    /// Number of microseconds that have passed, used by emulator.
    double microseconds;
};