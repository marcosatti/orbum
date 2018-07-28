#include "Resources/Cdvd/CdvdRtc.hpp"

CdvdRtc::CdvdRtc() :
    second(0),
    minute(0),
    hour(0),
    day(4),
    month(11),
    year(2)
{
}

void CdvdRtc::increment(const double time_us)
{
    microseconds += time_us;

    // If a second has passed, update the internal register values.
    if (microseconds > 1e6)
    {
        second += 1;
        microseconds -= 1e6;

        if (second >= 60)
            minute += 1;

        if (minute >= 60)
            hour += 1;

        if (hour >= 24)
            day += 1;

        // TODO: fix logic for months... each month has 25 days for now :)
        if (day >= 25)
            month += 1;

        if (month >= 13)
            year += 1;
    }
}