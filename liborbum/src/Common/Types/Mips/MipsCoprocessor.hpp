#pragma once

/// MIPS coprocessor interface.
class MipsCoprocessor
{
public:
    /// Checks if this coprocessor is usable.
    virtual bool is_usable() = 0;
};