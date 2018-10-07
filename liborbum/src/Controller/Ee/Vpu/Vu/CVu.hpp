#pragma once

#include "Controller/CController.hpp"
#include "Controller/ControllerEvent.hpp"
#include "Core.hpp"

class Core;

class CVu : public CController
{
public:
    CVu(Core* core);

    void handle_event(const ControllerEvent& event) override;

    /// Steps through the VU core state, executing one macro and one micro instruction.
    virtual int time_step(const int ticks_available) = 0;

private:
    /// Converts a time duration into the number of ticks that would have occurred.
    int time_to_ticks(const double time_us);
};