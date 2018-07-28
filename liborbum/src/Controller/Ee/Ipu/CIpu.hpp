#pragma once

#include "Controller/CController.hpp"

class CIpu : public CController
{
public:
    CIpu(Core* core);

    void handle_event(const ControllerEvent& event) override;

    /// Converts a time duration into the number of ticks that would have occurred.
    int time_to_ticks(const double time_us);

    int time_step(const int ticks_available);
};
