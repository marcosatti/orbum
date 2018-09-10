#include "Resources/Ee/Vpu/Vu/VuInstruction.hpp"

MipsInstructionInfo VU_INSTRUCTION_TABLE[Constants::EE::VPU::VU::NUMBER_VU_INSTRUCTIONS] =
    {
        // Most VU instructions (Upper Instructions, Flags, Integer Store/Load...) 
        // follow the basic FMAC pipeline, which has 3 execution stages. 
        // Stalls on data hazard (when the same field of the same register is accessed
        // by following instructions while the first instruction is still running).

        // Some instructions follow the FDIV pipeline, which has a significantly
        // longer execution time (up to 13 cycles).
        // Stalls on resource hazard (when two instructions attempt to use the FDIV
        // unit at the same time). There is no data hazard - the original Q register
        // (containing results from last FDIV operation) is used instead.

        // Instructions prefixed with "E" follow EFU pipeline, which is similar to 
        // FDIV pipeline, except that EFU is freed when it reaches the write-back
        // stage, whereas FDIV is freed when the register is actually written.

        // Instructions prefixed with "I" utilizes the IALU unit. While calculation
        // is done in 1 cycle, there are 2 dummy stages (made to follow the FMACs),
        // which shows up in macro mode (normally the results are bypassed)

        // Lower Instructions
        {"LQ", 109, 6},
        {"SQ", 112, 6},
        {"ILW", 115, 6},
        {"ISW", 116, 6},
        {"IADDIU", 100, 6},
        {"ISUBIU", 104, 6},
        {"FCEQ", 132, 6},
        {"FCSET", 134, 6},
        {"FCAND", 131, 6},
        {"FCOR", 133, 6},
        {"FSEQ", 125, 6},
        {"FSSET", 127, 6},
        {"FSAND", 124, 6},
        {"FSOR", 126, 6},
        {"FMEQ", 129, 6},
        {"FMAND", 128, 6},
        {"FMOR", 130, 6},
        {"FCGET", 135, 6},
        {"B", 142, 4},
        {"BAL", 143, 4},
        {"JR", 144, 4},
        {"JALR", 145, 4},
        {"IBEQ", 136, 4},
        {"IBNE", 141, 4},
        {"IBLTZ", 140, 4},
        {"IBGTZ", 138, 4},
        {"IBLEZ", 139, 4},
        {"IBGEZ", 137, 4},
        {"IADD", 98, 6},
        {"ISUB", 103, 6},
        {"IADDI", 99, 6},
        {"IAND", 101, 6},
        {"IOR", 102, 6},
        {"MOVE", 105, 6},
        {"LQI", 111, 6},
        {"DIV", 95, 9},
        {"MTIR", 107, 6},
        {"RNEXT", 121, 6},
        {"MFP", 146, 6},
        {"XTOP", 162, 6},
        {"XGKICK", 161, 6},
        {"ESADD", 148, 13},
        {"EATANxy", 152, 56},
        {"ESQRT", 156, 14},
        {"ESIN", 158, 31},
        {"MR32", 108, 6},
        {"SQI", 114, 6},
        {"SQRT", 96, 9},
        {"MFIR", 106, 6},
        {"RGET", 120, 6},
        {"XITOP", 163, 6},
        {"ERSADD", 149, 20},
        {"EATANxz", 153, 56},
        {"ERSQRT", 157, 20},
        {"EATAN", 159, 56},
        {"LQD", 110, 6},
        {"RSQRT", 97, 15},
        {"ILWR", 117, 6},
        {"RINIT", 119, 6},
        {"ELENG", 150, 20},
        {"ESUM", 154, 14},
        {"ERCPR", 155, 14},
        {"EEXP", 160, 46},
        {"SQD", 113, 6},
        {"WAITQ", 123, 6},
        {"ISWR", 118, 6},
        {"RXOR", 122, 6},
        {"ERLENG", 151, 26},
        {"WAITP", 147, 6},

        // Upper Instructions
        {"ADDbc_0", 4, 6},
        {"ADDbc_1", 5, 6},
        {"ADDbc_2", 6, 6},
        {"ADDbc_3", 7, 6},
        {"SUBbc_0", 18, 6},
        {"SUBbc_1", 19, 6},
        {"SUBbc_2", 20, 6},
        {"SUBbc_3", 21, 6},
        {"MADDbc_0", 46, 6},
        {"MADDbc_1", 47, 6},
        {"MADDbc_2", 48, 6},
        {"MADDbc_3", 49, 6},
        {"MSUBbc_0", 60, 6},
        {"MSUBbc_1", 61, 6},
        {"MSUBbc_2", 62, 6},
        {"MSUBbc_3", 63, 6},
        {"MAXbc_0", 73, 6},
        {"MAXbc_1", 74, 6},
        {"MAXbc_2", 75, 6},
        {"MAXbc_3", 76, 6},
        {"MINIbc_0", 79, 6},
        {"MINIbc_1", 80, 6},
        {"MINIbc_2", 81, 6},
        {"MINIbc_3", 82, 6},
        {"MULbc_0", 32, 6},
        {"MULbc_1", 33, 6},
        {"MULbc_2", 34, 6},
        {"MULbc_3", 35, 6},
        {"MULq", 31, 6},
        {"MAXi", 72, 6},
        {"MULi", 30, 6},
        {"MINIi", 78, 6},
        {"ADDq", 3, 6},
        {"MADDq", 45, 6},
        {"ADDi", 2, 6},
        {"MADDi", 44, 6},
        {"SUBq", 17, 6},
        {"MSUBq", 59, 6},
        {"SUBi", 16, 6},
        {"MSUBi", 58, 6},
        {"ADD", 1, 6},
        {"MADD", 43, 6},
        {"MUL", 29, 6},
        {"MAX", 71, 6},
        {"SUB", 15, 6},
        {"MSUB", 57, 6},
        {"OPMSUB", 84, 6},
        {"MINI", 77, 6},
        {"ADDAbc_0", 11, 6},
        {"SUBAbc_0", 25, 6},
        {"MADDAbc_0", 53, 6},
        {"MSUBAbc_0", 67, 6},
        {"ITOF0", 90, 6},
        {"FTOI0", 86, 6},
        {"MULAbc_0", 39, 6},
        {"MULAq", 38, 6},
        {"ADDAq", 10, 6},
        {"SUBAq", 24, 6},
        {"ADDA", 8, 6},
        {"SUBA", 22, 6},
        {"ADDAbc_1", 12, 6},
        {"SUBAbc_1", 26, 6},
        {"MADDAbc_1", 54, 6},
        {"MSUBAbc_1", 68, 6},
        {"ITOF4", 91, 6},
        {"FTOI4", 87, 6},
        {"MULAbc_1", 40, 6},
        {"ABS", 0, 6},
        {"MADDAq", 52, 6},
        {"MSUBAq", 66, 6},
        {"MADDA", 50, 6},
        {"MSUBA", 64, 6},
        {"ADDAbc_2", 13, 6},
        {"SUBAbc_2", 27, 6},
        {"MADDAbc_2", 55, 6},
        {"MSUBAbc_2", 69, 6},
        {"ITOF12", 92, 6},
        {"FTOI12", 88, 6},
        {"MULAbc_2", 41, 6},
        {"MULAi", 37, 6},
        {"ADDAi", 9, 6},
        {"SUBAi", 23, 6},
        {"MULA", 36, 6},
        {"OPMULA", 83, 6},
        {"ADDAbc_3", 14, 6},
        {"SUBAbc_3", 28, 6},
        {"MADDAbc_3", 56, 6},
        {"MSUBAbc_3", 70, 6},
        {"ITOF15", 93, 6},
        {"FTOI15", 89, 6},
        {"MULAbc_3", 42, 6},
        {"CLIP", 94, 6},
        {"MADDAi", 51, 6},
        {"MSUBAi", 65, 6},
        {"NOP", 85, 6}};

MipsInstructionInfo VuInstruction::lower_lookup() const
{
    switch (msb7())
    {
    case 0:
        return VU_INSTRUCTION_TABLE[0];
    case 1:
        return VU_INSTRUCTION_TABLE[1];
    case 4:
        return VU_INSTRUCTION_TABLE[2];
    case 5:
        return VU_INSTRUCTION_TABLE[3];
    case 8:
        return VU_INSTRUCTION_TABLE[4];
    case 9:
        return VU_INSTRUCTION_TABLE[5];
    case 16:
        return VU_INSTRUCTION_TABLE[6];
    case 17:
        return VU_INSTRUCTION_TABLE[7];
    case 18:
        return VU_INSTRUCTION_TABLE[8];
    case 19:
        return VU_INSTRUCTION_TABLE[9];
    case 20:
        return VU_INSTRUCTION_TABLE[10];
    case 21:
        return VU_INSTRUCTION_TABLE[11];
    case 22:
        return VU_INSTRUCTION_TABLE[12];
    case 23:
        return VU_INSTRUCTION_TABLE[13];
    case 24:
        return VU_INSTRUCTION_TABLE[14];
    case 25:
        // fmset theoretically... but it doesn't exist.
    case 26:
        return VU_INSTRUCTION_TABLE[15];
    case 27:
        return VU_INSTRUCTION_TABLE[16];
    case 28:
        return VU_INSTRUCTION_TABLE[17];
    case 32:
        return VU_INSTRUCTION_TABLE[18];
    case 33:
        return VU_INSTRUCTION_TABLE[19];
    case 36:
        return VU_INSTRUCTION_TABLE[20];
    case 37:
        return VU_INSTRUCTION_TABLE[21];
    case 40:
        return VU_INSTRUCTION_TABLE[22];
    case 41:
        return VU_INSTRUCTION_TABLE[23];
    case 44:
        return VU_INSTRUCTION_TABLE[24];
    case 45:
        return VU_INSTRUCTION_TABLE[25];
    case 46:
        return VU_INSTRUCTION_TABLE[26];
    case 47:
        return VU_INSTRUCTION_TABLE[27];
    case 64: // Lower OP
    {
        switch (opcode())
        {
        case 48:
            return VU_INSTRUCTION_TABLE[28];
        case 49:
            return VU_INSTRUCTION_TABLE[29];
        case 50:
            return VU_INSTRUCTION_TABLE[30];
        case 52:
            return VU_INSTRUCTION_TABLE[31];
        case 53:
            return VU_INSTRUCTION_TABLE[32];
        case 60:
        {
            switch (fd())
            {
            case 12:
                return VU_INSTRUCTION_TABLE[33];
            case 13:
                return VU_INSTRUCTION_TABLE[34];
            case 14:
                return VU_INSTRUCTION_TABLE[35];
            case 15:
                return VU_INSTRUCTION_TABLE[36];
            case 16:
                return VU_INSTRUCTION_TABLE[37];
            case 25:
                return VU_INSTRUCTION_TABLE[38];
            case 26:
                return VU_INSTRUCTION_TABLE[39];
            case 27:
                return VU_INSTRUCTION_TABLE[40];
            case 28:
                return VU_INSTRUCTION_TABLE[41];
            case 29:
                return VU_INSTRUCTION_TABLE[42];
            case 30:
                return VU_INSTRUCTION_TABLE[43];
            case 31:
                return VU_INSTRUCTION_TABLE[44];
            default:
                throw std::runtime_error("VU: Could not determine the lower instruction");
            }
        }
        case 61:
        {
            switch (fd())
            {
            case 12:
                return VU_INSTRUCTION_TABLE[45];
            case 13:
                return VU_INSTRUCTION_TABLE[46];
            case 14:
                return VU_INSTRUCTION_TABLE[47];
            case 15:
                return VU_INSTRUCTION_TABLE[48];
            case 16:
                return VU_INSTRUCTION_TABLE[49];
            case 26:
                return VU_INSTRUCTION_TABLE[50];
            case 28:
                return VU_INSTRUCTION_TABLE[51];
            case 29:
                return VU_INSTRUCTION_TABLE[52];
            case 30:
                return VU_INSTRUCTION_TABLE[53];
            case 31:
                return VU_INSTRUCTION_TABLE[54];
            default:
                throw std::runtime_error("VU: Could not determine the lower instruction");
            }
        }
        case 62:
        {
            switch (fd())
            {
            case 13:
                return VU_INSTRUCTION_TABLE[55];
            case 14:
                return VU_INSTRUCTION_TABLE[56];
            case 15:
                return VU_INSTRUCTION_TABLE[57];
            case 16:
                return VU_INSTRUCTION_TABLE[58];
            case 28:
                return VU_INSTRUCTION_TABLE[59];
            case 29:
                return VU_INSTRUCTION_TABLE[60];
            case 30:
                return VU_INSTRUCTION_TABLE[61];
            case 31:
                return VU_INSTRUCTION_TABLE[62];
            default:
                throw std::runtime_error("VU: Could not determine the lower instruction");
            }
        }
        case 63:
        {
            switch (fd())
            {
            case 13:
                return VU_INSTRUCTION_TABLE[63];
            case 14:
                return VU_INSTRUCTION_TABLE[64];
            case 15:
                return VU_INSTRUCTION_TABLE[65];
            case 16:
                return VU_INSTRUCTION_TABLE[66];
            case 28:
                return VU_INSTRUCTION_TABLE[67];
            case 30:
                return VU_INSTRUCTION_TABLE[68];
            default:
                throw std::runtime_error("VU: Could not determine the lower instruction");
            }
        }

        default:
            throw std::runtime_error("VU: Could not determine the lower instruction");
        }
    }

    default:
        throw std::runtime_error("VU: Could not determine the lower instruction");
    }
}

MipsInstructionInfo VuInstruction::upper_lookup() const
{
    switch (opcode())
    {
    case 0:
        return VU_INSTRUCTION_TABLE[69];
    case 1:
        return VU_INSTRUCTION_TABLE[70];
    case 2:
        return VU_INSTRUCTION_TABLE[71];
    case 3:
        return VU_INSTRUCTION_TABLE[72];
    case 4:
        return VU_INSTRUCTION_TABLE[73];
    case 5:
        return VU_INSTRUCTION_TABLE[74];
    case 6:
        return VU_INSTRUCTION_TABLE[75];
    case 7:
        return VU_INSTRUCTION_TABLE[76];
    case 8:
        return VU_INSTRUCTION_TABLE[77];
    case 9:
        return VU_INSTRUCTION_TABLE[78];
    case 10:
        return VU_INSTRUCTION_TABLE[79];
    case 11:
        return VU_INSTRUCTION_TABLE[80];
    case 12:
        return VU_INSTRUCTION_TABLE[81];
    case 13:
        return VU_INSTRUCTION_TABLE[82];
    case 14:
        return VU_INSTRUCTION_TABLE[83];
    case 15:
        return VU_INSTRUCTION_TABLE[84];
    case 16:
        return VU_INSTRUCTION_TABLE[85];
    case 17:
        return VU_INSTRUCTION_TABLE[86];
    case 18:
        return VU_INSTRUCTION_TABLE[87];
    case 19:
        return VU_INSTRUCTION_TABLE[88];
    case 20:
        return VU_INSTRUCTION_TABLE[89];
    case 21:
        return VU_INSTRUCTION_TABLE[90];
    case 22:
        return VU_INSTRUCTION_TABLE[91];
    case 23:
        return VU_INSTRUCTION_TABLE[92];
    case 24:
        return VU_INSTRUCTION_TABLE[93];
    case 25:
        return VU_INSTRUCTION_TABLE[94];
    case 26:
        return VU_INSTRUCTION_TABLE[95];
    case 27:
        return VU_INSTRUCTION_TABLE[96];
    case 28:
        return VU_INSTRUCTION_TABLE[97];
    case 29:
        return VU_INSTRUCTION_TABLE[98];
    case 30:
        return VU_INSTRUCTION_TABLE[99];
    case 31:
        return VU_INSTRUCTION_TABLE[100];
    case 32:
        return VU_INSTRUCTION_TABLE[101];
    case 33:
        return VU_INSTRUCTION_TABLE[102];
    case 34:
        return VU_INSTRUCTION_TABLE[103];
    case 35:
        return VU_INSTRUCTION_TABLE[104];
    case 36:
        return VU_INSTRUCTION_TABLE[105];
    case 37:
        return VU_INSTRUCTION_TABLE[106];
    case 38:
        return VU_INSTRUCTION_TABLE[107];
    case 39:
        return VU_INSTRUCTION_TABLE[108];
    case 40:
        return VU_INSTRUCTION_TABLE[109];
    case 41:
        return VU_INSTRUCTION_TABLE[110];
    case 42:
        return VU_INSTRUCTION_TABLE[111];
    case 43:
        return VU_INSTRUCTION_TABLE[112];
    case 44:
        return VU_INSTRUCTION_TABLE[113];
    case 45:
        return VU_INSTRUCTION_TABLE[114];
    case 46:
        return VU_INSTRUCTION_TABLE[115];
    case 47:
        return VU_INSTRUCTION_TABLE[116];
    case 60:
    {
        switch (fd())
        {
        case 0:
            return VU_INSTRUCTION_TABLE[117];
        case 1:
            return VU_INSTRUCTION_TABLE[118];
        case 2:
            return VU_INSTRUCTION_TABLE[119];
        case 3:
            return VU_INSTRUCTION_TABLE[120];
        case 4:
            return VU_INSTRUCTION_TABLE[121];
        case 5:
            return VU_INSTRUCTION_TABLE[122];
        case 6:
            return VU_INSTRUCTION_TABLE[123];
        case 7:
            return VU_INSTRUCTION_TABLE[124];
        case 8:
            return VU_INSTRUCTION_TABLE[125];
        case 9:
            return VU_INSTRUCTION_TABLE[126];
        case 10:
            return VU_INSTRUCTION_TABLE[127];
        case 11:
            return VU_INSTRUCTION_TABLE[128];
        default:
            throw std::runtime_error("VU: Could not determine the upper instruction");
        }
    }
    case 61:
    {
        switch (fd())
        {
        case 0:
            return VU_INSTRUCTION_TABLE[129];
        case 1:
            return VU_INSTRUCTION_TABLE[130];
        case 2:
            return VU_INSTRUCTION_TABLE[131];
        case 3:
            return VU_INSTRUCTION_TABLE[132];
        case 4:
            return VU_INSTRUCTION_TABLE[133];
        case 5:
            return VU_INSTRUCTION_TABLE[134];
        case 6:
            return VU_INSTRUCTION_TABLE[135];
        case 7:
            return VU_INSTRUCTION_TABLE[136];
        case 8:
            return VU_INSTRUCTION_TABLE[137];
        case 9:
            return VU_INSTRUCTION_TABLE[138];
        case 10:
            return VU_INSTRUCTION_TABLE[139];
        case 11:
            return VU_INSTRUCTION_TABLE[140];
        default:
            throw std::runtime_error("VU: Could not determine the upper instruction");
        }
    }
    case 62:
    {
        switch (fd())
        {
        case 0:
            return VU_INSTRUCTION_TABLE[141];
        case 1:
            return VU_INSTRUCTION_TABLE[142];
        case 2:
            return VU_INSTRUCTION_TABLE[143];
        case 3:
            return VU_INSTRUCTION_TABLE[144];
        case 4:
            return VU_INSTRUCTION_TABLE[145];
        case 5:
            return VU_INSTRUCTION_TABLE[146];
        case 6:
            return VU_INSTRUCTION_TABLE[147];
        case 7:
            return VU_INSTRUCTION_TABLE[148];
        case 8:
            return VU_INSTRUCTION_TABLE[149];
        case 9:
            return VU_INSTRUCTION_TABLE[150];
        case 10:
            return VU_INSTRUCTION_TABLE[151];
        case 11:
            return VU_INSTRUCTION_TABLE[152];
        default:
            throw std::runtime_error("VU: Could not determine the upper instruction");
        }
    }
    case 63:
    {
        switch (fd())
        {
        case 0:
            return VU_INSTRUCTION_TABLE[153];
        case 1:
            return VU_INSTRUCTION_TABLE[154];
        case 2:
            return VU_INSTRUCTION_TABLE[155];
        case 3:
            return VU_INSTRUCTION_TABLE[156];
        case 4:
            return VU_INSTRUCTION_TABLE[157];
        case 5:
            return VU_INSTRUCTION_TABLE[158];
        case 6:
            return VU_INSTRUCTION_TABLE[159];
        case 7:
            return VU_INSTRUCTION_TABLE[160];
        case 8:
            return VU_INSTRUCTION_TABLE[161];
        case 9:
            return VU_INSTRUCTION_TABLE[162];
        case 11:
            return VU_INSTRUCTION_TABLE[163];
        default:
            throw std::runtime_error("VU: Could not determine the upper instruction");
        }
    }

    default:
        throw std::runtime_error("VU: Could not determine the upper instruction");
    }
}
