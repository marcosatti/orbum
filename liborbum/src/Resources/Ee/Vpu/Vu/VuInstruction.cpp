#include "Resources/Ee/Vpu/Vu/VuInstruction.hpp"
#include "Resources/Ee/Vpu/Vu/VuPipelines.hpp"

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
        // Branch instructions prefixed with "I" uses IALU too, but since the results
        // are bypassed and not used by CFC2, they are instead unified with other branch
        // instructions.

        // Some instructions (such as WAITP) are related to FDIV/EFU/IALU pipeline,
        // but they actually follow the basic pipeline...

        // Lower Instructions
        {"LQ", 109, 6, VuPipeline::Basic},
        {"SQ", 112, 6, VuPipeline::Basic},
        {"ILW", 115, 6, VuPipeline::Basic},
        {"ISW", 116, 6, VuPipeline::Basic},
        {"IADDIU", 100, 6, VuPipeline::IALU},
        {"ISUBIU", 104, 6, VuPipeline::IALU},
        {"FCEQ", 132, 6, VuPipeline::Basic},
        {"FCSET", 134, 6, VuPipeline::Basic},
        {"FCAND", 131, 6, VuPipeline::Basic},
        {"FCOR", 133, 6, VuPipeline::Basic},
        {"FSEQ", 125, 6, VuPipeline::Basic},
        {"FSSET", 127, 6, VuPipeline::Basic},
        {"FSAND", 124, 6, VuPipeline::Basic},
        {"FSOR", 126, 6, VuPipeline::Basic},
        {"FMEQ", 129, 6, VuPipeline::Basic},
        {"FMAND", 128, 6, VuPipeline::Basic},
        {"FMOR", 130, 6, VuPipeline::Basic},
        {"FCGET", 135, 6, VuPipeline::Basic},
        {"B", 142, 4, VuPipeline::Basic},
        {"BAL", 143, 4, VuPipeline::Basic},
        {"JR", 144, 4, VuPipeline::Basic},
        {"JALR", 145, 4, VuPipeline::Basic},
        {"IBEQ", 136, 4, VuPipeline::Basic},
        {"IBNE", 141, 4, VuPipeline::Basic},
        {"IBLTZ", 140, 4, VuPipeline::Basic},
        {"IBGTZ", 138, 4, VuPipeline::Basic},
        {"IBLEZ", 139, 4, VuPipeline::Basic},
        {"IBGEZ", 137, 4, VuPipeline::Basic},
        {"IADD", 98, 6, VuPipeline::IALU},
        {"ISUB", 103, 6, VuPipeline::IALU},
        {"IADDI", 99, 6, VuPipeline::IALU},
        {"IAND", 101, 6, VuPipeline::IALU},
        {"IOR", 102, 6, VuPipeline::IALU},
        {"MOVE", 105, 6, VuPipeline::Basic},
        {"LQI", 111, 6, VuPipeline::Basic},
        {"DIV", 95, 9, VuPipeline::FDIV},
        {"MTIR", 107, 6, VuPipeline::Basic},
        {"RNEXT", 121, 6, VuPipeline::Basic},
        {"MFP", 146, 6, VuPipeline::Basic},
        {"XTOP", 162, 6, VuPipeline::Basic},
        {"XGKICK", 161, 6, VuPipeline::Basic},
        {"ESADD", 148, 13, VuPipeline::EFU},
        {"EATANxy", 152, 56, VuPipeline::EFU},
        {"ESQRT", 156, 14, VuPipeline::EFU},
        {"ESIN", 158, 31, VuPipeline::EFU},
        {"MR32", 108, 6, VuPipeline::Basic},
        {"SQI", 114, 6, VuPipeline::Basic},
        {"SQRT", 96, 9, VuPipeline::FDIV},
        {"MFIR", 106, 6, VuPipeline::Basic},
        {"RGET", 120, 6, VuPipeline::Basic},
        {"XITOP", 163, 6, VuPipeline::Basic},
        {"ERSADD", 149, 20, VuPipeline::EFU},
        {"EATANxz", 153, 56, VuPipeline::EFU},
        {"ERSQRT", 157, 20, VuPipeline::EFU},
        {"EATAN", 159, 56, VuPipeline::EFU},
        {"LQD", 110, 6, VuPipeline::Basic},
        {"RSQRT", 97, 15, VuPipeline::FDIV},
        {"ILWR", 117, 6, VuPipeline::Basic},
        {"RINIT", 119, 6, VuPipeline::Basic},
        {"ELENG", 150, 20, VuPipeline::EFU},
        {"ESUM", 154, 14, VuPipeline::EFU},
        {"ERCPR", 155, 14, VuPipeline::EFU},
        {"EEXP", 160, 46, VuPipeline::EFU},
        {"SQD", 113, 6, VuPipeline::Basic},
        {"WAITQ", 123, 6, VuPipeline::FDIV},
        {"ISWR", 118, 6, VuPipeline::Basic},
        {"RXOR", 122, 6, VuPipeline::Basic},
        {"ERLENG", 151, 26, VuPipeline::EFU},
        {"WAITP", 147, 6, VuPipeline::EFU},

        // Upper Instructions
        {"ADDbc_0", 4, 6, VuPipeline::FMAC},
        {"ADDbc_1", 5, 6, VuPipeline::FMAC},
        {"ADDbc_2", 6, 6, VuPipeline::FMAC},
        {"ADDbc_3", 7, 6, VuPipeline::FMAC},
        {"SUBbc_0", 18, 6, VuPipeline::FMAC},
        {"SUBbc_1", 19, 6, VuPipeline::FMAC},
        {"SUBbc_2", 20, 6, VuPipeline::FMAC},
        {"SUBbc_3", 21, 6, VuPipeline::FMAC},
        {"MADDbc_0", 46, 6, VuPipeline::FMAC},
        {"MADDbc_1", 47, 6, VuPipeline::FMAC},
        {"MADDbc_2", 48, 6, VuPipeline::FMAC},
        {"MADDbc_3", 49, 6, VuPipeline::FMAC},
        {"MSUBbc_0", 60, 6, VuPipeline::FMAC},
        {"MSUBbc_1", 61, 6, VuPipeline::FMAC},
        {"MSUBbc_2", 62, 6, VuPipeline::FMAC},
        {"MSUBbc_3", 63, 6, VuPipeline::FMAC},
        {"MAXbc_0", 73, 6, VuPipeline::FMAC},
        {"MAXbc_1", 74, 6, VuPipeline::FMAC},
        {"MAXbc_2", 75, 6, VuPipeline::FMAC},
        {"MAXbc_3", 76, 6, VuPipeline::FMAC},
        {"MINIbc_0", 79, 6, VuPipeline::FMAC},
        {"MINIbc_1", 80, 6, VuPipeline::FMAC},
        {"MINIbc_2", 81, 6, VuPipeline::FMAC},
        {"MINIbc_3", 82, 6, VuPipeline::FMAC},
        {"MULbc_0", 32, 6, VuPipeline::FMAC},
        {"MULbc_1", 33, 6, VuPipeline::FMAC},
        {"MULbc_2", 34, 6, VuPipeline::FMAC},
        {"MULbc_3", 35, 6, VuPipeline::FMAC},
        {"MULq", 31, 6, VuPipeline::FMAC},
        {"MAXi", 72, 6, VuPipeline::FMAC},
        {"MULi", 30, 6, VuPipeline::FMAC},
        {"MINIi", 78, 6, VuPipeline::FMAC},
        {"ADDq", 3, 6, VuPipeline::FMAC},
        {"MADDq", 45, 6, VuPipeline::FMAC},
        {"ADDi", 2, 6, VuPipeline::FMAC},
        {"MADDi", 44, 6, VuPipeline::FMAC},
        {"SUBq", 17, 6, VuPipeline::FMAC},
        {"MSUBq", 59, 6, VuPipeline::FMAC},
        {"SUBi", 16, 6, VuPipeline::FMAC},
        {"MSUBi", 58, 6, VuPipeline::FMAC},
        {"ADD", 1, 6, VuPipeline::FMAC},
        {"MADD", 43, 6, VuPipeline::FMAC},
        {"MUL", 29, 6, VuPipeline::FMAC},
        {"MAX", 71, 6, VuPipeline::FMAC},
        {"SUB", 15, 6, VuPipeline::FMAC},
        {"MSUB", 57, 6, VuPipeline::FMAC},
        {"OPMSUB", 84, 6, VuPipeline::FMAC},
        {"MINI", 77, 6, VuPipeline::FMAC},
        {"ADDAbc_0", 11, 6, VuPipeline::FMAC},
        {"SUBAbc_0", 25, 6, VuPipeline::FMAC},
        {"MADDAbc_0", 53, 6, VuPipeline::FMAC},
        {"MSUBAbc_0", 67, 6, VuPipeline::FMAC},
        {"ITOF0", 90, 6, VuPipeline::FMAC},
        {"FTOI0", 86, 6, VuPipeline::FMAC},
        {"MULAbc_0", 39, 6, VuPipeline::FMAC},
        {"MULAq", 38, 6, VuPipeline::FMAC},
        {"ADDAq", 10, 6, VuPipeline::FMAC},
        {"SUBAq", 24, 6, VuPipeline::FMAC},
        {"ADDA", 8, 6, VuPipeline::FMAC},
        {"SUBA", 22, 6, VuPipeline::FMAC},
        {"ADDAbc_1", 12, 6, VuPipeline::FMAC},
        {"SUBAbc_1", 26, 6, VuPipeline::FMAC},
        {"MADDAbc_1", 54, 6, VuPipeline::FMAC},
        {"MSUBAbc_1", 68, 6, VuPipeline::FMAC},
        {"ITOF4", 91, 6, VuPipeline::FMAC},
        {"FTOI4", 87, 6, VuPipeline::FMAC},
        {"MULAbc_1", 40, 6, VuPipeline::FMAC},
        {"ABS", 0, 6, VuPipeline::FMAC},
        {"MADDAq", 52, 6, VuPipeline::FMAC},
        {"MSUBAq", 66, 6, VuPipeline::FMAC},
        {"MADDA", 50, 6, VuPipeline::FMAC},
        {"MSUBA", 64, 6, VuPipeline::FMAC},
        {"ADDAbc_2", 13, 6, VuPipeline::FMAC},
        {"SUBAbc_2", 27, 6, VuPipeline::FMAC},
        {"MADDAbc_2", 55, 6, VuPipeline::FMAC},
        {"MSUBAbc_2", 69, 6, VuPipeline::FMAC},
        {"ITOF12", 92, 6, VuPipeline::FMAC},
        {"FTOI12", 88, 6, VuPipeline::FMAC},
        {"MULAbc_2", 41, 6, VuPipeline::FMAC},
        {"MULAi", 37, 6, VuPipeline::FMAC},
        {"ADDAi", 9, 6, VuPipeline::FMAC},
        {"SUBAi", 23, 6, VuPipeline::FMAC},
        {"MULA", 36, 6, VuPipeline::FMAC},
        {"OPMULA", 83, 6, VuPipeline::FMAC},
        {"ADDAbc_3", 14, 6, VuPipeline::FMAC},
        {"SUBAbc_3", 28, 6, VuPipeline::FMAC},
        {"MADDAbc_3", 56, 6, VuPipeline::FMAC},
        {"MSUBAbc_3", 70, 6, VuPipeline::FMAC},
        {"ITOF15", 93, 6, VuPipeline::FMAC},
        {"FTOI15", 89, 6, VuPipeline::FMAC},
        {"MULAbc_3", 42, 6, VuPipeline::FMAC},
        {"CLIP", 94, 6, VuPipeline::FMAC},
        {"MADDAi", 51, 6, VuPipeline::FMAC},
        {"MSUBAi", 65, 6, VuPipeline::FMAC},
        {"NOP", 85, 6, VuPipeline::FMAC}};

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
