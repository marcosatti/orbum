#include "Resources/Iop/Core/IopCoreInstruction.hpp"

MipsInstructionInfo IOP_CORE_INSTRUCTION_TABLE[90] =
    {
        {"SLL", 29, IopCoreInstruction::CPI_R3000_DEFAULT},
        {"SRL", 30, IopCoreInstruction::CPI_R3000_DEFAULT},
        {"SRA", 31, IopCoreInstruction::CPI_R3000_DEFAULT},
        {"SLLV", 32, IopCoreInstruction::CPI_R3000_DEFAULT},
        {"SRLV", 33, IopCoreInstruction::CPI_R3000_DEFAULT},
        {"SRAV", 34, IopCoreInstruction::CPI_R3000_DEFAULT},
        {"JR", 35, IopCoreInstruction::CPI_R3000_BRANCH},
        {"JALR", 36, IopCoreInstruction::CPI_R3000_BRANCH},
        {"SYSCALL", 37, IopCoreInstruction::CPI_R3000_DEFAULT},
        {"BREAK", 38, IopCoreInstruction::CPI_R3000_DEFAULT},
        {"MFHI", 39, IopCoreInstruction::CPI_R3000_DEFAULT},
        {"MTHI", 40, IopCoreInstruction::CPI_R3000_DEFAULT},
        {"MFLO", 41, IopCoreInstruction::CPI_R3000_DEFAULT},
        {"MTLO", 42, IopCoreInstruction::CPI_R3000_DEFAULT},
        {"MULT", 43, IopCoreInstruction::CPI_R3000_MULTIPLY},
        {"MULTU", 44, IopCoreInstruction::CPI_R3000_MULTIPLY},
        {"DIV", 45, IopCoreInstruction::CPI_R3000_DIVIDE},
        {"DIVU", 46, IopCoreInstruction::CPI_R3000_DIVIDE},
        {"ADD", 47, IopCoreInstruction::CPI_R3000_DEFAULT},
        {"ADDU", 48, IopCoreInstruction::CPI_R3000_DEFAULT},
        {"SUB", 49, IopCoreInstruction::CPI_R3000_DEFAULT},
        {"SUBU", 50, IopCoreInstruction::CPI_R3000_DEFAULT},
        {"AND", 51, IopCoreInstruction::CPI_R3000_DEFAULT},
        {"OR", 52, IopCoreInstruction::CPI_R3000_DEFAULT},
        {"XOR", 53, IopCoreInstruction::CPI_R3000_DEFAULT},
        {"NOR", 54, IopCoreInstruction::CPI_R3000_DEFAULT},
        {"SLT", 55, IopCoreInstruction::CPI_R3000_DEFAULT},
        {"SLTU", 56, IopCoreInstruction::CPI_R3000_DEFAULT},
        {"BLTZ", 57, IopCoreInstruction::CPI_R3000_BRANCH},
        {"BGEZ", 58, IopCoreInstruction::CPI_R3000_BRANCH},
        {"BLTZAL", 59, IopCoreInstruction::CPI_R3000_BRANCH},
        {"BGEZAL", 60, IopCoreInstruction::CPI_R3000_BRANCH},
        {"MFC0", 61, IopCoreInstruction::CPI_COP_DEFAULT},
        {"CFC0", 62, IopCoreInstruction::CPI_COP_DEFAULT},
        {"MTC0", 63, IopCoreInstruction::CPI_COP_DEFAULT},
        {"CTC0", 64, IopCoreInstruction::CPI_COP_DEFAULT},
        {"RFE", 65, IopCoreInstruction::CPI_COP_DEFAULT},
        {"MFC2", 87, IopCoreInstruction::CPI_COP_DEFAULT},
        {"CFC2", 88, IopCoreInstruction::CPI_COP_DEFAULT},
        {"MTC2", 89, IopCoreInstruction::CPI_COP_DEFAULT},
        {"CTC2", 90, IopCoreInstruction::CPI_COP_DEFAULT},
        {"RTPS", 66, IopCoreInstruction::CPI_COP_DEFAULT},
        {"NCLIP", 67, IopCoreInstruction::CPI_COP_DEFAULT},
        {"OP", 68, IopCoreInstruction::CPI_COP_DEFAULT},
        {"DPCS", 69, IopCoreInstruction::CPI_COP_DEFAULT},
        {"INTPL", 70, IopCoreInstruction::CPI_COP_DEFAULT},
        {"MVMVA", 71, IopCoreInstruction::CPI_COP_DEFAULT},
        {"NCDS", 72, IopCoreInstruction::CPI_COP_DEFAULT},
        {"CDP", 73, IopCoreInstruction::CPI_COP_DEFAULT},
        {"NCDT", 74, IopCoreInstruction::CPI_COP_DEFAULT},
        {"NCCS", 75, IopCoreInstruction::CPI_COP_DEFAULT},
        {"CC", 76, IopCoreInstruction::CPI_COP_DEFAULT},
        {"NCS", 77, IopCoreInstruction::CPI_COP_DEFAULT},
        {"NCT", 78, IopCoreInstruction::CPI_COP_DEFAULT},
        {"SQR", 79, IopCoreInstruction::CPI_COP_DEFAULT},
        {"DCPL", 80, IopCoreInstruction::CPI_COP_DEFAULT},
        {"DPCT", 81, IopCoreInstruction::CPI_COP_DEFAULT},
        {"AVSZ3", 82, IopCoreInstruction::CPI_COP_DEFAULT},
        {"AVSZ4", 83, IopCoreInstruction::CPI_COP_DEFAULT},
        {"RTPT", 84, IopCoreInstruction::CPI_COP_DEFAULT},
        {"GPF", 85, IopCoreInstruction::CPI_COP_DEFAULT},
        {"GPL", 86, IopCoreInstruction::CPI_COP_DEFAULT},
        {"J", 1, IopCoreInstruction::CPI_R3000_BRANCH},
        {"JAL", 2, IopCoreInstruction::CPI_R3000_BRANCH},
        {"BEQ", 3, IopCoreInstruction::CPI_R3000_BRANCH},
        {"BNE", 4, IopCoreInstruction::CPI_R3000_BRANCH},
        {"BLEZ", 5, IopCoreInstruction::CPI_R3000_BRANCH},
        {"BGTZ", 6, IopCoreInstruction::CPI_R3000_BRANCH},
        {"ADDI", 7, IopCoreInstruction::CPI_R3000_DEFAULT},
        {"ADDIU", 8, IopCoreInstruction::CPI_R3000_DEFAULT},
        {"SLTI", 9, IopCoreInstruction::CPI_R3000_DEFAULT},
        {"SLTIU", 10, IopCoreInstruction::CPI_R3000_DEFAULT},
        {"ANDI", 11, IopCoreInstruction::CPI_R3000_DEFAULT},
        {"ORI", 12, IopCoreInstruction::CPI_R3000_DEFAULT},
        {"XORI", 13, IopCoreInstruction::CPI_R3000_DEFAULT},
        {"LUI", 14, IopCoreInstruction::CPI_R3000_DEFAULT},
        {"LB", 15, IopCoreInstruction::CPI_R3000_LOAD},
        {"LH", 16, IopCoreInstruction::CPI_R3000_LOAD},
        {"LWL", 17, IopCoreInstruction::CPI_R3000_LOAD},
        {"LW", 18, IopCoreInstruction::CPI_R3000_LOAD},
        {"LBU", 19, IopCoreInstruction::CPI_R3000_LOAD},
        {"LHU", 20, IopCoreInstruction::CPI_R3000_LOAD},
        {"LWR", 21, IopCoreInstruction::CPI_R3000_LOAD},
        {"SB", 22, IopCoreInstruction::CPI_R3000_STORE},
        {"SH", 23, IopCoreInstruction::CPI_R3000_STORE},
        {"SWL", 24, IopCoreInstruction::CPI_R3000_STORE},
        {"SW", 25, IopCoreInstruction::CPI_R3000_STORE},
        {"SWR", 26, IopCoreInstruction::CPI_R3000_STORE},
        {"LWC2", 27, IopCoreInstruction::CPI_R3000_LOAD},
        {"SWC2", 28, IopCoreInstruction::CPI_R3000_STORE},
};

IopCoreInstruction::IopCoreInstruction(const uword value) :
    MipsInstruction(value),
    info(nullptr)
{
}

MipsInstructionInfo* IopCoreInstruction::lookup() const
{
    switch (opcode())
    {
    case 0:
    {
        switch (funct())
        {
        case 0:
            return &IOP_CORE_INSTRUCTION_TABLE[0];
        case 2:
            return &IOP_CORE_INSTRUCTION_TABLE[1];
        case 3:
            return &IOP_CORE_INSTRUCTION_TABLE[2];
        case 4:
            return &IOP_CORE_INSTRUCTION_TABLE[3];
        case 6:
            return &IOP_CORE_INSTRUCTION_TABLE[4];
        case 7:
            return &IOP_CORE_INSTRUCTION_TABLE[5];
        case 8:
            return &IOP_CORE_INSTRUCTION_TABLE[6];
        case 9:
            return &IOP_CORE_INSTRUCTION_TABLE[7];
        case 12:
            return &IOP_CORE_INSTRUCTION_TABLE[8];
        case 13:
            return &IOP_CORE_INSTRUCTION_TABLE[9];
        case 16:
            return &IOP_CORE_INSTRUCTION_TABLE[10];
        case 17:
            return &IOP_CORE_INSTRUCTION_TABLE[11];
        case 18:
            return &IOP_CORE_INSTRUCTION_TABLE[12];
        case 19:
            return &IOP_CORE_INSTRUCTION_TABLE[13];
        case 24:
            return &IOP_CORE_INSTRUCTION_TABLE[14];
        case 25:
            return &IOP_CORE_INSTRUCTION_TABLE[15];
        case 26:
            return &IOP_CORE_INSTRUCTION_TABLE[16];
        case 27:
            return &IOP_CORE_INSTRUCTION_TABLE[17];
        case 32:
            return &IOP_CORE_INSTRUCTION_TABLE[18];
        case 33:
            return &IOP_CORE_INSTRUCTION_TABLE[19];
        case 34:
            return &IOP_CORE_INSTRUCTION_TABLE[20];
        case 35:
            return &IOP_CORE_INSTRUCTION_TABLE[21];
        case 36:
            return &IOP_CORE_INSTRUCTION_TABLE[22];
        case 37:
            return &IOP_CORE_INSTRUCTION_TABLE[23];
        case 38:
            return &IOP_CORE_INSTRUCTION_TABLE[24];
        case 39:
            return &IOP_CORE_INSTRUCTION_TABLE[25];
        case 42:
            return &IOP_CORE_INSTRUCTION_TABLE[26];
        case 43:
            return &IOP_CORE_INSTRUCTION_TABLE[27];
        default:
            throw std::runtime_error("Could not determine instruction");
        }
    }
    case 1:
    {
        switch (rt())
        {
        case 0:
            return &IOP_CORE_INSTRUCTION_TABLE[28];
        case 1:
            return &IOP_CORE_INSTRUCTION_TABLE[29];
        case 15:
            return &IOP_CORE_INSTRUCTION_TABLE[30];
        case 16:
            return &IOP_CORE_INSTRUCTION_TABLE[31];
        default:
            throw std::runtime_error("Could not determine instruction");
        }
    }
    case 16:
    {
        switch (rs())
        {
        case 0:
            return &IOP_CORE_INSTRUCTION_TABLE[32];
        case 2:
            return &IOP_CORE_INSTRUCTION_TABLE[33];
        case 4:
            return &IOP_CORE_INSTRUCTION_TABLE[34];
        case 6:
            return &IOP_CORE_INSTRUCTION_TABLE[35];
        case 16:
            return &IOP_CORE_INSTRUCTION_TABLE[36];
        default:
            throw std::runtime_error("Could not determine instruction");
        }
    }
    case 18:
    {
        switch (funct())
        {
        case 0:
        {
            switch (rs())
            {
            case 0:
                return &IOP_CORE_INSTRUCTION_TABLE[37];
            case 2:
                return &IOP_CORE_INSTRUCTION_TABLE[38];
            case 4:
                return &IOP_CORE_INSTRUCTION_TABLE[39];
            case 6:
                return &IOP_CORE_INSTRUCTION_TABLE[40];
            default:
                throw std::runtime_error("Could not determine instruction");
            }
        }
        case 1:
            return &IOP_CORE_INSTRUCTION_TABLE[41];
        case 6:
            return &IOP_CORE_INSTRUCTION_TABLE[42];
        case 12:
            return &IOP_CORE_INSTRUCTION_TABLE[43];
        case 16:
            return &IOP_CORE_INSTRUCTION_TABLE[44];
        case 17:
            return &IOP_CORE_INSTRUCTION_TABLE[45];
        case 18:
            return &IOP_CORE_INSTRUCTION_TABLE[46];
        case 19:
            return &IOP_CORE_INSTRUCTION_TABLE[47];
        case 20:
            return &IOP_CORE_INSTRUCTION_TABLE[48];
        case 21:
            return &IOP_CORE_INSTRUCTION_TABLE[49];
        case 27:
            return &IOP_CORE_INSTRUCTION_TABLE[50];
        case 28:
            return &IOP_CORE_INSTRUCTION_TABLE[51];
        case 30:
            return &IOP_CORE_INSTRUCTION_TABLE[52];
        case 32:
            return &IOP_CORE_INSTRUCTION_TABLE[53];
        case 40:
            return &IOP_CORE_INSTRUCTION_TABLE[54];
        case 41:
            return &IOP_CORE_INSTRUCTION_TABLE[55];
        case 42:
            return &IOP_CORE_INSTRUCTION_TABLE[56];
        case 45:
            return &IOP_CORE_INSTRUCTION_TABLE[57];
        case 46:
            return &IOP_CORE_INSTRUCTION_TABLE[58];
        case 48:
            return &IOP_CORE_INSTRUCTION_TABLE[59];
        case 61:
            return &IOP_CORE_INSTRUCTION_TABLE[60];
        case 62:
            return &IOP_CORE_INSTRUCTION_TABLE[61];
        default:
            throw std::runtime_error("Could not determine instruction");
        }
    }
    case 2:
        return &IOP_CORE_INSTRUCTION_TABLE[62];
    case 3:
        return &IOP_CORE_INSTRUCTION_TABLE[63];
    case 4:
        return &IOP_CORE_INSTRUCTION_TABLE[64];
    case 5:
        return &IOP_CORE_INSTRUCTION_TABLE[65];
    case 6:
        return &IOP_CORE_INSTRUCTION_TABLE[66];
    case 7:
        return &IOP_CORE_INSTRUCTION_TABLE[67];
    case 8:
        return &IOP_CORE_INSTRUCTION_TABLE[68];
    case 9:
        return &IOP_CORE_INSTRUCTION_TABLE[69];
    case 10:
        return &IOP_CORE_INSTRUCTION_TABLE[70];
    case 11:
        return &IOP_CORE_INSTRUCTION_TABLE[71];
    case 12:
        return &IOP_CORE_INSTRUCTION_TABLE[72];
    case 13:
        return &IOP_CORE_INSTRUCTION_TABLE[73];
    case 14:
        return &IOP_CORE_INSTRUCTION_TABLE[74];
    case 15:
        return &IOP_CORE_INSTRUCTION_TABLE[75];
    case 32:
        return &IOP_CORE_INSTRUCTION_TABLE[76];
    case 33:
        return &IOP_CORE_INSTRUCTION_TABLE[77];
    case 34:
        return &IOP_CORE_INSTRUCTION_TABLE[78];
    case 35:
        return &IOP_CORE_INSTRUCTION_TABLE[79];
    case 36:
        return &IOP_CORE_INSTRUCTION_TABLE[80];
    case 37:
        return &IOP_CORE_INSTRUCTION_TABLE[81];
    case 38:
        return &IOP_CORE_INSTRUCTION_TABLE[82];
    case 40:
        return &IOP_CORE_INSTRUCTION_TABLE[83];
    case 41:
        return &IOP_CORE_INSTRUCTION_TABLE[84];
    case 42:
        return &IOP_CORE_INSTRUCTION_TABLE[85];
    case 43:
        return &IOP_CORE_INSTRUCTION_TABLE[86];
    case 46:
        return &IOP_CORE_INSTRUCTION_TABLE[87];
    case 50:
        return &IOP_CORE_INSTRUCTION_TABLE[88];
    case 58:
        return &IOP_CORE_INSTRUCTION_TABLE[89];
    default:
        throw std::runtime_error("Could not determine instruction");
    }
}
