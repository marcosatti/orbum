#include "Resources/Ee/Vpu/Vif/VifcodeInstruction.hpp"

MipsInstructionInfo VIFCODE_INSTRUCTION_TABLE[21] =
{
    { "NOP", 1, 1 },
    { "STCYCL", 2, 1 },
    { "OFFSET", 3, 1 },
    { "BASE", 4, 1 },
    { "ITOP", 5, 1 },
    { "STMOD", 6, 1 },
    { "MSKPATH3", 7, 1 },
    { "MARK", 8, 1 },
    { "FLUSHE", 9, 1 },
    { "FLUSH", 10, 1 },
    { "FLUSHA", 11, 1 },
    { "MSCAL", 12, 1 },
    { "MSCALF", 13, 1 },
    { "MSCNT", 14, 1 },
    { "STMASK", 15, 2 },
    { "STROW", 16, 5 },
    { "STCOL", 17, 5 },
    { "MPG", 18, 10 },
    { "DIRECT", 19, 10 },
    { "DIRECTHL", 20, 10 },
    { "UNPACK", 21, 100 }
};

VifcodeInstruction::VifcodeInstruction(const uword value) :
	MipsInstruction(value),
	info(nullptr)
{
}

MipsInstructionInfo * VifcodeInstruction::get_info()
{
	if (!info)
		info = lookup();
	return info;
}

MipsInstructionInfo * VifcodeInstruction::lookup() const
{
    switch (cmdhi())
    {
    case 0:
    {
        switch (cmdlo())
        {
        case 0:
            return &VIFCODE_INSTRUCTION_TABLE[0];
        case 1:
            return &VIFCODE_INSTRUCTION_TABLE[1];
        case 2:
            return &VIFCODE_INSTRUCTION_TABLE[2];
        case 3:
            return &VIFCODE_INSTRUCTION_TABLE[3];
        case 4:
            return &VIFCODE_INSTRUCTION_TABLE[4];
        case 5:
            return &VIFCODE_INSTRUCTION_TABLE[5];
        case 6:
            return &VIFCODE_INSTRUCTION_TABLE[6];
        case 7:
            return &VIFCODE_INSTRUCTION_TABLE[7];
        case 16:
            return &VIFCODE_INSTRUCTION_TABLE[8];
        case 17:
            return &VIFCODE_INSTRUCTION_TABLE[9];
        case 19:
            return &VIFCODE_INSTRUCTION_TABLE[10];
        case 20:
            return &VIFCODE_INSTRUCTION_TABLE[11];
        case 21:
            return &VIFCODE_INSTRUCTION_TABLE[12];
        case 23:
            return &VIFCODE_INSTRUCTION_TABLE[13];
        default:
            throw std::runtime_error("Could not determine instruction");
        }
    }
    case 1:
    {
        switch (cmdlo())
        {
        case 0:
            return &VIFCODE_INSTRUCTION_TABLE[14];
        case 16:
            return &VIFCODE_INSTRUCTION_TABLE[15];
        case 17:
            return &VIFCODE_INSTRUCTION_TABLE[16];
        default:
            throw std::runtime_error("Could not determine instruction");
        }
    }
    case 2:
    {
        switch (cmdlo())
        {
        case 10:
            return &VIFCODE_INSTRUCTION_TABLE[17];
        case 16:
            return &VIFCODE_INSTRUCTION_TABLE[18];
        case 17:
            return &VIFCODE_INSTRUCTION_TABLE[19];
        default:
            throw std::runtime_error("Could not determine instruction");
        }
    }
    case 3:
        return &VIFCODE_INSTRUCTION_TABLE[20];
    default:
        throw std::runtime_error("Could not determine instruction");
    }
}
