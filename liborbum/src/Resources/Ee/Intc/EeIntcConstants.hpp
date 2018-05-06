#pragma once

#include "Common/Constants.hpp"

struct EeIntcConstants
{
    static constexpr const char * MNEMONICS[Constants::EE::INTC::NUMBER_IRQ_LINES] = 
    {
        "GS",
        "SBUS",
        "VBON",
        "VBOF",
        "VIF0",
        "VIF1",
        "VU0",
        "VIF1",
        "IPU",
        "TIM0",
        "TIM1",
        "TIM2",
        "TIM3",
        "SFIFO",
        "VU0WD"
    };
};