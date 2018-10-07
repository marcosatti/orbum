#pragma once

#include "Common/Types/Mips/MipsPipeline.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"

struct VuPipeline
{
    enum
    {
        FMAC = 0,
        FDIV = 1,
        EFU = 2,
        IALU = 3,
        LSU = 4,
        Basic = 5, // BRU, RANDU etc follow this. Similar to FMAC, but doesn't use FMAC units
    };
};

/// The FMAC pipeline.
///
/// There are in total 4 FMAC units in a VU, therefore resource hazard is not
/// generated for the FMAC pipeline, only data hazards - when the same field of
/// the same register is accessed by 2 different FMAC units stalling occurs.
struct FmacPipeline : public MipsPipeline
{
    // FmacPipeline uses the using_register variable to store the register and its
    // field(s) being used by the pipeline.
    // The first 4 bits are used for fields, and the 5 bits after it are used
    // for registers. (The rest are paddings)
    // For example, VF[8]xyz would be stored as [0000000 01000 1110].

    FmacPipeline(uhword cycles = 0, uhword reg = 0, ubyte field = 0) :
        MipsPipeline(cycles, (reg << 4) | field)
    {
    }

    bool is_using_register(uhword reg) const override
    {
        return is_using_register(reg >> 4, reg & 0b1111);
    }

    bool is_using_register(ubyte reg, size_t field) const
    {
        const uhword using_reg = using_register >> 4;
        const uhword reg_field = using_register & 0b1111;

        // True if the pipeline is running, is using the same register, and is using the same fields
        // Also true if it is VF00 that is being written into (it is hardwired to 0)
        return is_running() && (using_reg == reg) && ((reg_field ^ field) != 0b1111);
    }
};

/// The FDIV pipeline.
///
/// When a DIV instruction is executed while the pipeline is still running, a
/// resource hazard is generated and the instruction is stalled until the write-back
/// stage. Furthermore, when a Upper Instruction uses the Q register while the
/// pipeline is still running, FMAC will not stall and will use the original
/// Q register instead.
struct FdivPipeline : public MipsPipeline
{
    using MipsPipeline::MipsPipeline;

    SizedWordRegister new_q;
};

/// The EFU pipeline.
///
/// The EFU pipeline is pretty similar to the FDIV pipeline, except that the
/// instruction is stalled until the last stage of the execution, not write-back.
/// (NOTE: the next instruction starts during the write-back stage!)
struct EfuPipeline : public MipsPipeline
{
    using MipsPipeline::MipsPipeline;

    SizedWordRegister new_p;
};

/// The IALU pipeline.
///
/// IALU takes only one cycle to execute, but there are 2 dummy stages needed
/// to go through before the result is written back to the registers, though
/// the result can bypass directly to other pipelines and stalls do not occur
/// except when it is transferred with CFC2.
struct IaluPipeline : public MipsPipeline
{
    using MipsPipeline::MipsPipeline;
};

/// The LSU "pipeline".
///
/// Not documentated in the manual, it is responsible for the integer load/store
/// operations. Has a 4-cycle-long latency before the register it uses is available
/// for other instructions to use.
struct LsuPipeline : public MipsPipeline
{
    using MipsPipeline::MipsPipeline;
};
