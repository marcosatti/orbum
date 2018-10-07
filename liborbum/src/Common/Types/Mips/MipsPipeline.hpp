#pragma once

#include "Common/Types/Primitive.hpp"

/// The base class for representing the MIPS pipeline.
struct MipsPipeline
{
    MipsPipeline(uhword cycles = 0, uhword reg = 0) :
        finish_in(cycles),
        using_register(reg)
    {
    }

public:
    /// Consumes specified cycle. The amount of cycles to be consumed is 1 by
    /// default.
    void consume_cycle(uhword cycles = 1)
    {
        finish_in -= cycles;
    }

    /// Flushes the pipeline, returning the amount of cycles it would had taken
    /// to finish the pipeline
    uhword flush_pipeline()
    {
        uhword cycles_consumed = finish_in;
        finish_in = 0;
        return cycles_consumed;
    }

    /// Checks whether the pipeline is still running.
    bool is_running() const
    {
        return finish_in > 0;
    }

    virtual bool is_using_register(uhword reg) const
    {
        // R0 is hardwired to 0.
        return reg != 0 && using_register == reg;
    }

protected:
    // The cycles it takes to finish the pipeline execution
    uhword finish_in;

    // The register that is being used by the pipeline
    uhword using_register;
};
