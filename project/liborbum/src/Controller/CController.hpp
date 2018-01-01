#pragma once

#include "Controller/ControllerEvent.hpp"

class Core;

/// Abstration for a controller, that is able to handle a controller event.
/// Contains a reference to the core, used to do callback operations.
class CController
{
public:
    CController(Core * core) :
        core(core)
    {
    }

    virtual ~CController()
    {
    }

	virtual void handle_event(const ControllerEvent & e) const = 0;

protected:
    Core * core;
};