MipsInstructionInfo lookup(const MipsInstruction & inst)
{
    switch (inst.opcode())
    {
    case 0:
    {
        switch (inst.funct())
        {
        case 0:
            return &INSTRUCTION_TABLE[0];
        case 2:
            return &INSTRUCTION_TABLE[1];
        case 3:
            return &INSTRUCTION_TABLE[2];
        case 4:
            return &INSTRUCTION_TABLE[3];
        case 6:
            return &INSTRUCTION_TABLE[4];
        case 7:
            return &INSTRUCTION_TABLE[5];
        case 8:
            return &INSTRUCTION_TABLE[6];
        case 9:
            return &INSTRUCTION_TABLE[7];
        case 12:
            return &INSTRUCTION_TABLE[8];
        case 13:
            return &INSTRUCTION_TABLE[9];
        case 16:
            return &INSTRUCTION_TABLE[10];
        case 17:
            return &INSTRUCTION_TABLE[11];
        case 18:
            return &INSTRUCTION_TABLE[12];
        case 19:
            return &INSTRUCTION_TABLE[13];
        case 24:
            return &INSTRUCTION_TABLE[14];
        case 25:
            return &INSTRUCTION_TABLE[15];
        case 26:
            return &INSTRUCTION_TABLE[16];
        case 27:
            return &INSTRUCTION_TABLE[17];
        case 32:
            return &INSTRUCTION_TABLE[18];
        case 33:
            return &INSTRUCTION_TABLE[19];
        case 34:
            return &INSTRUCTION_TABLE[20];
        case 35:
            return &INSTRUCTION_TABLE[21];
        case 36:
            return &INSTRUCTION_TABLE[22];
        case 37:
            return &INSTRUCTION_TABLE[23];
        case 38:
            return &INSTRUCTION_TABLE[24];
        case 39:
            return &INSTRUCTION_TABLE[25];
        case 42:
            return &INSTRUCTION_TABLE[26];
        case 43:
            return &INSTRUCTION_TABLE[27];
        default:
            throw std::runtime_error("Could not determine instruction");
        }
    }
    case 1:
    {
        switch (inst.rt())
        {
        case 0:
            return &INSTRUCTION_TABLE[28];
        case 1:
            return &INSTRUCTION_TABLE[29];
        case 15:
            return &INSTRUCTION_TABLE[30];
        case 16:
            return &INSTRUCTION_TABLE[31];
        default:
            throw std::runtime_error("Could not determine instruction");
        }
    }
    case 16:
    {
        switch (inst.rs())
        {
        case 0:
            return &INSTRUCTION_TABLE[32];
        case 2:
            return &INSTRUCTION_TABLE[33];
        case 4:
            return &INSTRUCTION_TABLE[34];
        case 6:
            return &INSTRUCTION_TABLE[35];
        case 16:
            return &INSTRUCTION_TABLE[36];
        default:
            throw std::runtime_error("Could not determine instruction");
        }
    }
    case 18:
    {
        switch (inst.funct())
        {
        case 0:
        {
            switch (inst.rs())
            {
            case 0:
                return &INSTRUCTION_TABLE[37];
            case 2:
                return &INSTRUCTION_TABLE[38];
            case 4:
                return &INSTRUCTION_TABLE[39];
            case 6:
                return &INSTRUCTION_TABLE[40];
            default:
                throw std::runtime_error("Could not determine instruction");
            }
        }
        case 1:
            return &INSTRUCTION_TABLE[41];
        case 6:
            return &INSTRUCTION_TABLE[42];
        case 12:
            return &INSTRUCTION_TABLE[43];
        case 16:
            return &INSTRUCTION_TABLE[44];
        case 17:
            return &INSTRUCTION_TABLE[45];
        case 18:
            return &INSTRUCTION_TABLE[46];
        case 19:
            return &INSTRUCTION_TABLE[47];
        case 20:
            return &INSTRUCTION_TABLE[48];
        case 21:
            return &INSTRUCTION_TABLE[49];
        case 27:
            return &INSTRUCTION_TABLE[50];
        case 28:
            return &INSTRUCTION_TABLE[51];
        case 30:
            return &INSTRUCTION_TABLE[52];
        case 32:
            return &INSTRUCTION_TABLE[53];
        case 40:
            return &INSTRUCTION_TABLE[54];
        case 41:
            return &INSTRUCTION_TABLE[55];
        case 42:
            return &INSTRUCTION_TABLE[56];
        case 45:
            return &INSTRUCTION_TABLE[57];
        case 46:
            return &INSTRUCTION_TABLE[58];
        case 48:
            return &INSTRUCTION_TABLE[59];
        case 61:
            return &INSTRUCTION_TABLE[60];
        case 62:
            return &INSTRUCTION_TABLE[61];
        default:
            throw std::runtime_error("Could not determine instruction");
        }
    }
    case 2:
        return &INSTRUCTION_TABLE[62];
    case 3:
        return &INSTRUCTION_TABLE[63];
    case 4:
        return &INSTRUCTION_TABLE[64];
    case 5:
        return &INSTRUCTION_TABLE[65];
    case 6:
        return &INSTRUCTION_TABLE[66];
    case 7:
        return &INSTRUCTION_TABLE[67];
    case 8:
        return &INSTRUCTION_TABLE[68];
    case 9:
        return &INSTRUCTION_TABLE[69];
    case 10:
        return &INSTRUCTION_TABLE[70];
    case 11:
        return &INSTRUCTION_TABLE[71];
    case 12:
        return &INSTRUCTION_TABLE[72];
    case 13:
        return &INSTRUCTION_TABLE[73];
    case 14:
        return &INSTRUCTION_TABLE[74];
    case 15:
        return &INSTRUCTION_TABLE[75];
    case 32:
        return &INSTRUCTION_TABLE[76];
    case 33:
        return &INSTRUCTION_TABLE[77];
    case 34:
        return &INSTRUCTION_TABLE[78];
    case 35:
        return &INSTRUCTION_TABLE[79];
    case 36:
        return &INSTRUCTION_TABLE[80];
    case 37:
        return &INSTRUCTION_TABLE[81];
    case 38:
        return &INSTRUCTION_TABLE[82];
    case 40:
        return &INSTRUCTION_TABLE[83];
    case 41:
        return &INSTRUCTION_TABLE[84];
    case 42:
        return &INSTRUCTION_TABLE[85];
    case 43:
        return &INSTRUCTION_TABLE[86];
    case 46:
        return &INSTRUCTION_TABLE[87];
    case 50:
        return &INSTRUCTION_TABLE[88];
    case 58:
        return &INSTRUCTION_TABLE[89];
    default:
        throw std::runtime_error("Could not determine instruction");
    }
}
