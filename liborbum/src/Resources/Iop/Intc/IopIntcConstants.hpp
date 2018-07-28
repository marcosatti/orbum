#pragma once

#include "Common/Constants.hpp"

struct IopIntcConstants
{
    static constexpr const char* MNEMONICS[Constants::IOP::INTC::NUMBER_IRQ_LINES] =
        {
            "VBLANK",
            "GPU",
            "CDROM",
            "DMAC",
            "TMR0",
            "TMR1",
            "TMR2",
            "SIO0",
            "SIO1",
            "SPU",
            "PIO",
            "EVBLANK",
            "DVD",
            "PCMCIA",
            "TMR3",
            "TMR4",
            "TMR5",
            "SIO2",
            "HTR0",
            "HTR1",
            "HTR2",
            "HTR3",
            "USB",
            "EXTR",
            "FWRE",
            "FDMA"};
};