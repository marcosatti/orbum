#pragma once

#if defined(BUILD_DEBUG)
#include <atomic>
#endif

#include "Controller/ControllerEvent.hpp"

class Core;

/// Abstration for a controller, that is able to handle a controller event.
/// Contains a reference to the core, used to do callback operations.
class CController
{
public:
    CController(Core* core) :
        core(core)
    {
    }

    virtual ~CController()
    {
    }

    virtual void handle_event(const ControllerEvent& e) = 0;

    void handle_event_marshall_(const ControllerEvent& e)
    {
        // Used for inserting pre/post-event hooks (debugging).
        handle_event(e);
    }

protected:
    Core* core;
};