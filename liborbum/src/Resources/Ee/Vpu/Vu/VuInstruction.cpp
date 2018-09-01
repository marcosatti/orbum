#include "Resources/Ee/Vpu/Vu/VuInstruction.hpp"

MipsInstructionInfo VU_INSTRUCTION_TABLE[Constants::EE::VPU::VU::NUMBER_VU_INSTRUCTIONS] =
    {
        // TODO: determine the proper cycles per instruction
        {"LQ", 109, 1},
        {"SQ", 112, 1},
        {"ILW", 115, 1},
        {"ISW", 116, 1},
        {"IADDIU", 100, 1},
        {"ISUBIU", 104, 1},
        {"FCEQ", 132, 1},
        {"FCSET", 134, 1},
        {"FCAND", 131, 1},
        {"FCOR", 133, 1},
        {"FSEQ", 125, 1},
        {"FSSET", 127, 1},
        {"FSAND", 124, 1},
        {"FSOR", 126, 1},
        {"FMEQ", 129, 1},
        {"FMAND", 128, 1},
        {"FMOR", 130, 1},
        {"FCGET", 135, 1},
        {"B", 142, 1},
        {"BAL", 143, 1},
        {"JR", 144, 1},
        {"JALR", 145, 1},
        {"IBEQ", 136, 1},
        {"IBNE", 141, 1},
        {"IBLTZ", 140, 1},
        {"IBGTZ", 138, 1},
        {"IBLEZ", 139, 1},
        {"IBGEZ", 137, 1},
        {"IADD", 98, 1},
        {"ISUB", 103, 1},
        {"IADDI", 99, 1},
        {"IAND", 101, 1},
        {"IOR", 102, 1},
        {"MOVE", 105, 1},
        {"LQI", 111, 1},
        {"DIV", 95, 1},
        {"MTIR", 107, 1},
        {"RNEXT", 121, 1},
        {"MFP", 146, 1},
        {"XTOP", 162, 1},
        {"XGKICK", 161, 1},
        {"ESADD", 148, 1},
        {"EATANxy", 152, 1},
        {"ESQRT", 156, 1},
        {"ESIN", 158, 1},
        {"MR32", 108, 1},
        {"SQI", 114, 1},
        {"SQRT", 96, 1},
        {"MFIR", 106, 1},
        {"RGET", 120, 1},
        {"XITOP", 163, 1},
        {"ERSADD", 149, 1},
        {"EATANxz", 153, 1},
        {"ERSQRT", 157, 1},
        {"EATAN", 159, 1},
        {"LQD", 110, 1},
        {"RSQRT", 97, 1},
        {"ILWR", 117, 1},
        {"RINIT", 119, 1},
        {"ELENG", 150, 1},
        {"ESUM", 154, 1},
        {"ERCPR", 155, 1},
        {"EEXP", 160, 1},
        {"SQD", 113, 1},
        {"WAITQ", 123, 1},
        {"ISWR", 118, 1},
        {"RXOR", 122, 1},
        {"ERLENG", 151, 1},
        {"WAITP", 147, 1},
        {"ADDbc_0", 4, 1},
        {"ADDbc_1", 5, 1},
        {"ADDbc_2", 6, 1},
        {"ADDbc_3", 7, 1},
        {"SUBbc_0", 18, 1},
        {"SUBbc_1", 19, 1},
        {"SUBbc_2", 20, 1},
        {"SUBbc_3", 21, 1},
        {"MADDbc_0", 46, 1},
        {"MADDbc_1", 47, 1},
        {"MADDbc_2", 48, 1},
        {"MADDbc_3", 49, 1},
        {"MSUBbc_0", 60, 1},
        {"MSUBbc_1", 61, 1},
        {"MSUBbc_2", 62, 1},
        {"MSUBbc_3", 63, 1},
        {"MAXbc_0", 73, 1},
        {"MAXbc_1", 74, 1},
        {"MAXbc_2", 75, 1},
        {"MAXbc_3", 76, 1},
        {"MINIbc_0", 79, 1},
        {"MINIbc_1", 80, 1},
        {"MINIbc_2", 81, 1},
        {"MINIbc_3", 82, 1},
        {"MULbc_0", 32, 1},
        {"MULbc_1", 33, 1},
        {"MULbc_2", 34, 1},
        {"MULbc_3", 35, 1},
        {"MULq", 31, 1},
        {"MAXi", 72, 1},
        {"MULi", 30, 1},
        {"MINIi", 78, 1},
        {"ADDq", 3, 1},
        {"MADDq", 45, 1},
        {"ADDi", 2, 1},
        {"MADDi", 44, 1},
        {"SUBq", 17, 1},
        {"MSUBq", 59, 1},
        {"SUBi", 16, 1},
        {"MSUBi", 58, 1},
        {"ADD", 1, 1},
        {"MADD", 43, 1},
        {"MUL", 29, 1},
        {"MAX", 71, 1},
        {"SUB", 15, 1},
        {"MSUB", 57, 1},
        {"OPMSUB", 84, 1},
        {"MINI", 77, 1},
        {"ADDAbc_0", 11, 1},
        {"SUBAbc_0", 25, 1},
        {"MADDAbc_0", 53, 1},
        {"MSUBAbc_0", 67, 1},
        {"ITOF0", 90, 1},
        {"FTOI0", 86, 1},
        {"MULAbc_0", 39, 1},
        {"MULAq", 38, 1},
        {"ADDAq", 10, 1},
        {"SUBAq", 24, 1},
        {"ADDA", 8, 1},
        {"SUBA", 22, 1},
        {"ADDAbc_1", 12, 1},
        {"SUBAbc_1", 26, 1},
        {"MADDAbc_1", 54, 1},
        {"MSUBAbc_1", 68, 1},
        {"ITOF4", 91, 1},
        {"FTOI4", 87, 1},
        {"MULAbc_1", 40, 1},
        {"ABS", 0, 1},
        {"MADDAq", 52, 1},
        {"MSUBAq", 66, 1},
        {"MADDA", 50, 1},
        {"MSUBA", 64, 1},
        {"ADDAbc_2", 13, 1},
        {"SUBAbc_2", 27, 1},
        {"MADDAbc_2", 55, 1},
        {"MSUBAbc_2", 69, 1},
        {"ITOF12", 92, 1},
        {"FTOI12", 88, 1},
        {"MULAbc_2", 41, 1},
        {"MULAi", 37, 1},
        {"ADDAi", 9, 1},
        {"SUBAi", 23, 1},
        {"MULA", 36, 1},
        {"OPMULA", 83, 1},
        {"ADDAbc_3", 14, 1},
        {"SUBAbc_3", 28, 1},
        {"MADDAbc_3", 56, 1},
        {"MSUBAbc_3", 70, 1},
        {"ITOF15", 93, 1},
        {"FTOI15", 89, 1},
        {"MULAbc_3", 42, 1},
        {"CLIP", 94, 1},
        {"MADDAi", 51, 1},
        {"MSUBAi", 65, 1},
        {"NOP", 85, 1}};

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
