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
        case 10:
            return &INSTRUCTION_TABLE[8];
        case 11:
            return &INSTRUCTION_TABLE[9];
        case 12:
            return &INSTRUCTION_TABLE[10];
        case 13:
            return &INSTRUCTION_TABLE[11];
        case 15:
            return &INSTRUCTION_TABLE[12];
        case 16:
            return &INSTRUCTION_TABLE[13];
        case 17:
            return &INSTRUCTION_TABLE[14];
        case 18:
            return &INSTRUCTION_TABLE[15];
        case 19:
            return &INSTRUCTION_TABLE[16];
        case 20:
            return &INSTRUCTION_TABLE[17];
        case 22:
            return &INSTRUCTION_TABLE[18];
        case 23:
            return &INSTRUCTION_TABLE[19];
        case 24:
            return &INSTRUCTION_TABLE[20];
        case 25:
            return &INSTRUCTION_TABLE[21];
        case 26:
            return &INSTRUCTION_TABLE[22];
        case 27:
            return &INSTRUCTION_TABLE[23];
        case 32:
            return &INSTRUCTION_TABLE[24];
        case 33:
            return &INSTRUCTION_TABLE[25];
        case 34:
            return &INSTRUCTION_TABLE[26];
        case 35:
            return &INSTRUCTION_TABLE[27];
        case 36:
            return &INSTRUCTION_TABLE[28];
        case 37:
            return &INSTRUCTION_TABLE[29];
        case 38:
            return &INSTRUCTION_TABLE[30];
        case 39:
            return &INSTRUCTION_TABLE[31];
        case 40:
            return &INSTRUCTION_TABLE[32];
        case 41:
            return &INSTRUCTION_TABLE[33];
        case 42:
            return &INSTRUCTION_TABLE[34];
        case 43:
            return &INSTRUCTION_TABLE[35];
        case 44:
            return &INSTRUCTION_TABLE[36];
        case 45:
            return &INSTRUCTION_TABLE[37];
        case 46:
            return &INSTRUCTION_TABLE[38];
        case 47:
            return &INSTRUCTION_TABLE[39];
        case 48:
            return &INSTRUCTION_TABLE[40];
        case 49:
            return &INSTRUCTION_TABLE[41];
        case 50:
            return &INSTRUCTION_TABLE[42];
        case 51:
            return &INSTRUCTION_TABLE[43];
        case 52:
            return &INSTRUCTION_TABLE[44];
        case 54:
            return &INSTRUCTION_TABLE[45];
        case 56:
            return &INSTRUCTION_TABLE[46];
        case 58:
            return &INSTRUCTION_TABLE[47];
        case 59:
            return &INSTRUCTION_TABLE[48];
        case 60:
            return &INSTRUCTION_TABLE[49];
        case 62:
            return &INSTRUCTION_TABLE[50];
        case 63:
            return &INSTRUCTION_TABLE[51];
        default:
            throw std::runtime_error("Could not determine instruction");
        }
    }
    case 1:
    {
        switch (inst.rt())
        {
        case 0:
            return &INSTRUCTION_TABLE[52];
        case 1:
            return &INSTRUCTION_TABLE[53];
        case 2:
            return &INSTRUCTION_TABLE[54];
        case 3:
            return &INSTRUCTION_TABLE[55];
        case 8:
            return &INSTRUCTION_TABLE[56];
        case 9:
            return &INSTRUCTION_TABLE[57];
        case 10:
            return &INSTRUCTION_TABLE[58];
        case 11:
            return &INSTRUCTION_TABLE[59];
        case 12:
            return &INSTRUCTION_TABLE[60];
        case 14:
            return &INSTRUCTION_TABLE[61];
        case 16:
            return &INSTRUCTION_TABLE[62];
        case 17:
            return &INSTRUCTION_TABLE[63];
        case 18:
            return &INSTRUCTION_TABLE[64];
        case 19:
            return &INSTRUCTION_TABLE[65];
        case 24:
            return &INSTRUCTION_TABLE[66];
        case 25:
            return &INSTRUCTION_TABLE[67];
        default:
            throw std::runtime_error("Could not determine instruction");
        }
    }
    case 28:
    {
        switch (inst.funct())
        {
        case 8:
        {
            switch (inst.shamt())
            {
            case 0:
                return &INSTRUCTION_TABLE[68];
            case 1:
                return &INSTRUCTION_TABLE[69];
            case 2:
                return &INSTRUCTION_TABLE[70];
            case 3:
                return &INSTRUCTION_TABLE[71];
            case 4:
                return &INSTRUCTION_TABLE[72];
            case 5:
                return &INSTRUCTION_TABLE[73];
            case 6:
                return &INSTRUCTION_TABLE[74];
            case 7:
                return &INSTRUCTION_TABLE[75];
            case 8:
                return &INSTRUCTION_TABLE[76];
            case 9:
                return &INSTRUCTION_TABLE[77];
            case 10:
                return &INSTRUCTION_TABLE[78];
            case 16:
                return &INSTRUCTION_TABLE[79];
            case 17:
                return &INSTRUCTION_TABLE[80];
            case 18:
                return &INSTRUCTION_TABLE[81];
            case 19:
                return &INSTRUCTION_TABLE[82];
            case 20:
                return &INSTRUCTION_TABLE[83];
            case 21:
                return &INSTRUCTION_TABLE[84];
            case 22:
                return &INSTRUCTION_TABLE[85];
            case 23:
                return &INSTRUCTION_TABLE[86];
            case 24:
                return &INSTRUCTION_TABLE[87];
            case 25:
                return &INSTRUCTION_TABLE[88];
            case 26:
                return &INSTRUCTION_TABLE[89];
            case 27:
                return &INSTRUCTION_TABLE[90];
            case 30:
                return &INSTRUCTION_TABLE[91];
            case 31:
                return &INSTRUCTION_TABLE[92];
            default:
                throw std::runtime_error("Could not determine instruction");
            }
        }
        case 40:
        {
            switch (inst.shamt())
            {
            case 1:
                return &INSTRUCTION_TABLE[93];
            case 2:
                return &INSTRUCTION_TABLE[94];
            case 3:
                return &INSTRUCTION_TABLE[95];
            case 4:
                return &INSTRUCTION_TABLE[96];
            case 5:
                return &INSTRUCTION_TABLE[97];
            case 6:
                return &INSTRUCTION_TABLE[98];
            case 7:
                return &INSTRUCTION_TABLE[99];
            case 10:
                return &INSTRUCTION_TABLE[100];
            case 16:
                return &INSTRUCTION_TABLE[101];
            case 17:
                return &INSTRUCTION_TABLE[102];
            case 18:
                return &INSTRUCTION_TABLE[103];
            case 20:
                return &INSTRUCTION_TABLE[104];
            case 21:
                return &INSTRUCTION_TABLE[105];
            case 22:
                return &INSTRUCTION_TABLE[106];
            case 24:
                return &INSTRUCTION_TABLE[107];
            case 25:
                return &INSTRUCTION_TABLE[108];
            case 26:
                return &INSTRUCTION_TABLE[109];
            case 27:
                return &INSTRUCTION_TABLE[110];
            default:
                throw std::runtime_error("Could not determine instruction");
            }
        }
        case 9:
        {
            switch (inst.shamt())
            {
            case 0:
                return &INSTRUCTION_TABLE[111];
            case 2:
                return &INSTRUCTION_TABLE[112];
            case 3:
                return &INSTRUCTION_TABLE[113];
            case 4:
                return &INSTRUCTION_TABLE[114];
            case 8:
                return &INSTRUCTION_TABLE[115];
            case 9:
                return &INSTRUCTION_TABLE[116];
            case 10:
                return &INSTRUCTION_TABLE[117];
            case 12:
                return &INSTRUCTION_TABLE[118];
            case 13:
                return &INSTRUCTION_TABLE[119];
            case 14:
                return &INSTRUCTION_TABLE[120];
            case 16:
                return &INSTRUCTION_TABLE[121];
            case 17:
                return &INSTRUCTION_TABLE[122];
            case 18:
                return &INSTRUCTION_TABLE[123];
            case 19:
                return &INSTRUCTION_TABLE[124];
            case 20:
                return &INSTRUCTION_TABLE[125];
            case 21:
                return &INSTRUCTION_TABLE[126];
            case 26:
                return &INSTRUCTION_TABLE[127];
            case 27:
                return &INSTRUCTION_TABLE[128];
            case 28:
                return &INSTRUCTION_TABLE[129];
            case 29:
                return &INSTRUCTION_TABLE[130];
            case 30:
                return &INSTRUCTION_TABLE[131];
            case 31:
                return &INSTRUCTION_TABLE[132];
            default:
                throw std::runtime_error("Could not determine instruction");
            }
        }
        case 41:
        {
            switch (inst.shamt())
            {
            case 0:
                return &INSTRUCTION_TABLE[133];
            case 3:
                return &INSTRUCTION_TABLE[134];
            case 8:
                return &INSTRUCTION_TABLE[135];
            case 9:
                return &INSTRUCTION_TABLE[136];
            case 10:
                return &INSTRUCTION_TABLE[137];
            case 12:
                return &INSTRUCTION_TABLE[138];
            case 13:
                return &INSTRUCTION_TABLE[139];
            case 14:
                return &INSTRUCTION_TABLE[140];
            case 18:
                return &INSTRUCTION_TABLE[141];
            case 19:
                return &INSTRUCTION_TABLE[142];
            case 26:
                return &INSTRUCTION_TABLE[143];
            case 27:
                return &INSTRUCTION_TABLE[144];
            case 30:
                return &INSTRUCTION_TABLE[145];
            default:
                throw std::runtime_error("Could not determine instruction");
            }
        }
        case 0:
            return &INSTRUCTION_TABLE[146];
        case 1:
            return &INSTRUCTION_TABLE[147];
        case 4:
            return &INSTRUCTION_TABLE[148];
        case 16:
            return &INSTRUCTION_TABLE[149];
        case 17:
            return &INSTRUCTION_TABLE[150];
        case 18:
            return &INSTRUCTION_TABLE[151];
        case 19:
            return &INSTRUCTION_TABLE[152];
        case 24:
            return &INSTRUCTION_TABLE[153];
        case 25:
            return &INSTRUCTION_TABLE[154];
        case 26:
            return &INSTRUCTION_TABLE[155];
        case 27:
            return &INSTRUCTION_TABLE[156];
        case 32:
            return &INSTRUCTION_TABLE[157];
        case 33:
            return &INSTRUCTION_TABLE[158];
        case 48:
            return &INSTRUCTION_TABLE[159];
        case 49:
            return &INSTRUCTION_TABLE[160];
        case 52:
            return &INSTRUCTION_TABLE[161];
        case 54:
            return &INSTRUCTION_TABLE[162];
        case 55:
            return &INSTRUCTION_TABLE[163];
        case 60:
            return &INSTRUCTION_TABLE[164];
        case 62:
            return &INSTRUCTION_TABLE[165];
        case 63:
            return &INSTRUCTION_TABLE[166];
        default:
            throw std::runtime_error("Could not determine instruction");
        }
    }
    case 16:
    {
        switch (inst.rs())
        {
        case 8:
        {
            switch (inst.rt())
            {
            case 0:
                return &INSTRUCTION_TABLE[167];
            case 1:
                return &INSTRUCTION_TABLE[168];
            case 2:
                return &INSTRUCTION_TABLE[169];
            case 3:
                return &INSTRUCTION_TABLE[170];
            default:
                throw std::runtime_error("Could not determine instruction");
            }
        }
        case 16:
        {
            switch (inst.funct())
            {
            case 1:
                return &INSTRUCTION_TABLE[171];
            case 2:
                return &INSTRUCTION_TABLE[172];
            case 6:
                return &INSTRUCTION_TABLE[173];
            case 8:
                return &INSTRUCTION_TABLE[174];
            case 24:
                return &INSTRUCTION_TABLE[175];
            case 56:
                return &INSTRUCTION_TABLE[176];
            case 57:
                return &INSTRUCTION_TABLE[177];
            default:
                throw std::runtime_error("Could not determine instruction");
            }
        }
        case 0:
            return &INSTRUCTION_TABLE[178];
        case 4:
            return &INSTRUCTION_TABLE[179];
        default:
            throw std::runtime_error("Could not determine instruction");
        }
    }
    case 17:
    {
        switch (inst.rs())
        {
        case 8:
        {
            switch (inst.rt())
            {
            case 0:
                return &INSTRUCTION_TABLE[180];
            case 1:
                return &INSTRUCTION_TABLE[181];
            case 2:
                return &INSTRUCTION_TABLE[182];
            case 3:
                return &INSTRUCTION_TABLE[183];
            default:
                throw std::runtime_error("Could not determine instruction");
            }
        }
        case 16:
        {
            switch (inst.funct())
            {
            case 0:
                return &INSTRUCTION_TABLE[184];
            case 1:
                return &INSTRUCTION_TABLE[185];
            case 2:
                return &INSTRUCTION_TABLE[186];
            case 3:
                return &INSTRUCTION_TABLE[187];
            case 4:
                return &INSTRUCTION_TABLE[188];
            case 5:
                return &INSTRUCTION_TABLE[189];
            case 6:
                return &INSTRUCTION_TABLE[190];
            case 7:
                return &INSTRUCTION_TABLE[191];
            case 21:
                return &INSTRUCTION_TABLE[192];
            case 23:
                return &INSTRUCTION_TABLE[193];
            case 24:
                return &INSTRUCTION_TABLE[194];
            case 25:
                return &INSTRUCTION_TABLE[195];
            case 27:
                return &INSTRUCTION_TABLE[196];
            case 28:
                return &INSTRUCTION_TABLE[197];
            case 29:
                return &INSTRUCTION_TABLE[198];
            case 30:
                return &INSTRUCTION_TABLE[199];
            case 35:
                return &INSTRUCTION_TABLE[200];
            case 39:
                return &INSTRUCTION_TABLE[201];
            case 40:
                return &INSTRUCTION_TABLE[202];
            case 47:
                return &INSTRUCTION_TABLE[203];
            case 49:
                return &INSTRUCTION_TABLE[204];
            case 51:
                return &INSTRUCTION_TABLE[205];
            case 53:
                return &INSTRUCTION_TABLE[206];
            default:
                throw std::runtime_error("Could not determine instruction");
            }
        }
        case 20:
        {
            switch (inst.funct())
            {
            case 32:
                return &INSTRUCTION_TABLE[207];
            default:
                throw std::runtime_error("Could not determine instruction");
            }
        }
        case 0:
            return &INSTRUCTION_TABLE[208];
        case 2:
            return &INSTRUCTION_TABLE[209];
        case 4:
            return &INSTRUCTION_TABLE[210];
        case 6:
            return &INSTRUCTION_TABLE[211];
        default:
            throw std::runtime_error("Could not determine instruction");
        }
    }
    case 18:
    {
        switch (inst.co())
        {
        case 0:
        {
            switch (inst.dest())
            {
            case 8:
            {
                switch (inst.rt())
                {
                case 0:
                    return &INSTRUCTION_TABLE[212];
                case 1:
                    return &INSTRUCTION_TABLE[213];
                case 2:
                    return &INSTRUCTION_TABLE[214];
                case 3:
                    return &INSTRUCTION_TABLE[215];
                default:
                    throw std::runtime_error("Could not determine instruction");
                }
            }
            case 1:
                return &INSTRUCTION_TABLE[216];
            case 2:
                return &INSTRUCTION_TABLE[217];
            case 5:
                return &INSTRUCTION_TABLE[218];
            case 6:
                return &INSTRUCTION_TABLE[219];
            default:
                throw std::runtime_error("Could not determine instruction");
            }
        }
        case 1:
        {
            switch (inst.funct())
            {
            case 60:
            {
                switch (inst.shamt())
                {
                case 0:
                    return &INSTRUCTION_TABLE[220];
                case 1:
                    return &INSTRUCTION_TABLE[221];
                case 2:
                    return &INSTRUCTION_TABLE[222];
                case 3:
                    return &INSTRUCTION_TABLE[223];
                case 4:
                    return &INSTRUCTION_TABLE[224];
                case 5:
                    return &INSTRUCTION_TABLE[225];
                case 6:
                    return &INSTRUCTION_TABLE[226];
                case 7:
                    return &INSTRUCTION_TABLE[227];
                case 8:
                    return &INSTRUCTION_TABLE[228];
                case 9:
                    return &INSTRUCTION_TABLE[229];
                case 10:
                    return &INSTRUCTION_TABLE[230];
                case 11:
                    return &INSTRUCTION_TABLE[231];
                case 12:
                    return &INSTRUCTION_TABLE[232];
                case 13:
                    return &INSTRUCTION_TABLE[233];
                case 14:
                    return &INSTRUCTION_TABLE[234];
                case 15:
                    return &INSTRUCTION_TABLE[235];
                case 16:
                    return &INSTRUCTION_TABLE[236];
                default:
                    throw std::runtime_error("Could not determine instruction");
                }
            }
            case 61:
            {
                switch (inst.shamt())
                {
                case 0:
                    return &INSTRUCTION_TABLE[237];
                case 1:
                    return &INSTRUCTION_TABLE[238];
                case 2:
                    return &INSTRUCTION_TABLE[239];
                case 3:
                    return &INSTRUCTION_TABLE[240];
                case 4:
                    return &INSTRUCTION_TABLE[241];
                case 5:
                    return &INSTRUCTION_TABLE[242];
                case 6:
                    return &INSTRUCTION_TABLE[243];
                case 7:
                    return &INSTRUCTION_TABLE[244];
                case 8:
                    return &INSTRUCTION_TABLE[245];
                case 9:
                    return &INSTRUCTION_TABLE[246];
                case 10:
                    return &INSTRUCTION_TABLE[247];
                case 11:
                    return &INSTRUCTION_TABLE[248];
                case 12:
                    return &INSTRUCTION_TABLE[249];
                case 13:
                    return &INSTRUCTION_TABLE[250];
                case 14:
                    return &INSTRUCTION_TABLE[251];
                case 15:
                    return &INSTRUCTION_TABLE[252];
                case 16:
                    return &INSTRUCTION_TABLE[253];
                default:
                    throw std::runtime_error("Could not determine instruction");
                }
            }
            case 62:
            {
                switch (inst.shamt())
                {
                case 0:
                    return &INSTRUCTION_TABLE[254];
                case 1:
                    return &INSTRUCTION_TABLE[255];
                case 2:
                    return &INSTRUCTION_TABLE[256];
                case 3:
                    return &INSTRUCTION_TABLE[257];
                case 4:
                    return &INSTRUCTION_TABLE[258];
                case 5:
                    return &INSTRUCTION_TABLE[259];
                case 6:
                    return &INSTRUCTION_TABLE[260];
                case 7:
                    return &INSTRUCTION_TABLE[261];
                case 8:
                    return &INSTRUCTION_TABLE[262];
                case 9:
                    return &INSTRUCTION_TABLE[263];
                case 10:
                    return &INSTRUCTION_TABLE[264];
                case 11:
                    return &INSTRUCTION_TABLE[265];
                case 13:
                    return &INSTRUCTION_TABLE[266];
                case 14:
                    return &INSTRUCTION_TABLE[267];
                case 15:
                    return &INSTRUCTION_TABLE[268];
                case 16:
                    return &INSTRUCTION_TABLE[269];
                default:
                    throw std::runtime_error("Could not determine instruction");
                }
            }
            case 63:
            {
                switch (inst.shamt())
                {
                case 0:
                    return &INSTRUCTION_TABLE[270];
                case 1:
                    return &INSTRUCTION_TABLE[271];
                case 2:
                    return &INSTRUCTION_TABLE[272];
                case 3:
                    return &INSTRUCTION_TABLE[273];
                case 4:
                    return &INSTRUCTION_TABLE[274];
                case 5:
                    return &INSTRUCTION_TABLE[275];
                case 6:
                    return &INSTRUCTION_TABLE[276];
                case 7:
                    return &INSTRUCTION_TABLE[277];
                case 8:
                    return &INSTRUCTION_TABLE[278];
                case 9:
                    return &INSTRUCTION_TABLE[279];
                case 11:
                    return &INSTRUCTION_TABLE[280];
                case 13:
                    return &INSTRUCTION_TABLE[281];
                case 14:
                    return &INSTRUCTION_TABLE[282];
                case 15:
                    return &INSTRUCTION_TABLE[283];
                case 16:
                    return &INSTRUCTION_TABLE[284];
                default:
                    throw std::runtime_error("Could not determine instruction");
                }
            }
            case 0:
                return &INSTRUCTION_TABLE[285];
            case 1:
                return &INSTRUCTION_TABLE[286];
            case 2:
                return &INSTRUCTION_TABLE[287];
            case 3:
                return &INSTRUCTION_TABLE[288];
            case 4:
                return &INSTRUCTION_TABLE[289];
            case 5:
                return &INSTRUCTION_TABLE[290];
            case 6:
                return &INSTRUCTION_TABLE[291];
            case 7:
                return &INSTRUCTION_TABLE[292];
            case 8:
                return &INSTRUCTION_TABLE[293];
            case 9:
                return &INSTRUCTION_TABLE[294];
            case 10:
                return &INSTRUCTION_TABLE[295];
            case 11:
                return &INSTRUCTION_TABLE[296];
            case 12:
                return &INSTRUCTION_TABLE[297];
            case 13:
                return &INSTRUCTION_TABLE[298];
            case 14:
                return &INSTRUCTION_TABLE[299];
            case 15:
                return &INSTRUCTION_TABLE[300];
            case 16:
                return &INSTRUCTION_TABLE[301];
            case 17:
                return &INSTRUCTION_TABLE[302];
            case 18:
                return &INSTRUCTION_TABLE[303];
            case 19:
                return &INSTRUCTION_TABLE[304];
            case 20:
                return &INSTRUCTION_TABLE[305];
            case 21:
                return &INSTRUCTION_TABLE[306];
            case 22:
                return &INSTRUCTION_TABLE[307];
            case 23:
                return &INSTRUCTION_TABLE[308];
            case 24:
                return &INSTRUCTION_TABLE[309];
            case 25:
                return &INSTRUCTION_TABLE[310];
            case 26:
                return &INSTRUCTION_TABLE[311];
            case 27:
                return &INSTRUCTION_TABLE[312];
            case 28:
                return &INSTRUCTION_TABLE[313];
            case 29:
                return &INSTRUCTION_TABLE[314];
            case 30:
                return &INSTRUCTION_TABLE[315];
            case 31:
                return &INSTRUCTION_TABLE[316];
            case 32:
                return &INSTRUCTION_TABLE[317];
            case 33:
                return &INSTRUCTION_TABLE[318];
            case 34:
                return &INSTRUCTION_TABLE[319];
            case 35:
                return &INSTRUCTION_TABLE[320];
            case 36:
                return &INSTRUCTION_TABLE[321];
            case 37:
                return &INSTRUCTION_TABLE[322];
            case 38:
                return &INSTRUCTION_TABLE[323];
            case 39:
                return &INSTRUCTION_TABLE[324];
            case 40:
                return &INSTRUCTION_TABLE[325];
            case 41:
                return &INSTRUCTION_TABLE[326];
            case 42:
                return &INSTRUCTION_TABLE[327];
            case 43:
                return &INSTRUCTION_TABLE[328];
            case 44:
                return &INSTRUCTION_TABLE[329];
            case 45:
                return &INSTRUCTION_TABLE[330];
            case 46:
                return &INSTRUCTION_TABLE[331];
            case 47:
                return &INSTRUCTION_TABLE[332];
            case 48:
                return &INSTRUCTION_TABLE[333];
            case 49:
                return &INSTRUCTION_TABLE[334];
            case 50:
                return &INSTRUCTION_TABLE[335];
            case 52:
                return &INSTRUCTION_TABLE[336];
            case 53:
                return &INSTRUCTION_TABLE[337];
            case 56:
                return &INSTRUCTION_TABLE[338];
            case 57:
                return &INSTRUCTION_TABLE[339];
            default:
                throw std::runtime_error("Could not determine instruction");
            }
        }
        default:
            throw std::runtime_error("Could not determine instruction");
        }
    }
    case 2:
        return &INSTRUCTION_TABLE[340];
    case 3:
        return &INSTRUCTION_TABLE[341];
    case 4:
        return &INSTRUCTION_TABLE[342];
    case 5:
        return &INSTRUCTION_TABLE[343];
    case 6:
        return &INSTRUCTION_TABLE[344];
    case 7:
        return &INSTRUCTION_TABLE[345];
    case 8:
        return &INSTRUCTION_TABLE[346];
    case 9:
        return &INSTRUCTION_TABLE[347];
    case 10:
        return &INSTRUCTION_TABLE[348];
    case 11:
        return &INSTRUCTION_TABLE[349];
    case 12:
        return &INSTRUCTION_TABLE[350];
    case 13:
        return &INSTRUCTION_TABLE[351];
    case 14:
        return &INSTRUCTION_TABLE[352];
    case 15:
        return &INSTRUCTION_TABLE[353];
    case 20:
        return &INSTRUCTION_TABLE[354];
    case 21:
        return &INSTRUCTION_TABLE[355];
    case 22:
        return &INSTRUCTION_TABLE[356];
    case 23:
        return &INSTRUCTION_TABLE[357];
    case 24:
        return &INSTRUCTION_TABLE[358];
    case 25:
        return &INSTRUCTION_TABLE[359];
    case 26:
        return &INSTRUCTION_TABLE[360];
    case 27:
        return &INSTRUCTION_TABLE[361];
    case 30:
        return &INSTRUCTION_TABLE[362];
    case 31:
        return &INSTRUCTION_TABLE[363];
    case 32:
        return &INSTRUCTION_TABLE[364];
    case 33:
        return &INSTRUCTION_TABLE[365];
    case 34:
        return &INSTRUCTION_TABLE[366];
    case 35:
        return &INSTRUCTION_TABLE[367];
    case 36:
        return &INSTRUCTION_TABLE[368];
    case 37:
        return &INSTRUCTION_TABLE[369];
    case 38:
        return &INSTRUCTION_TABLE[370];
    case 39:
        return &INSTRUCTION_TABLE[371];
    case 40:
        return &INSTRUCTION_TABLE[372];
    case 41:
        return &INSTRUCTION_TABLE[373];
    case 42:
        return &INSTRUCTION_TABLE[374];
    case 43:
        return &INSTRUCTION_TABLE[375];
    case 44:
        return &INSTRUCTION_TABLE[376];
    case 45:
        return &INSTRUCTION_TABLE[377];
    case 46:
        return &INSTRUCTION_TABLE[378];
    case 47:
        return &INSTRUCTION_TABLE[379];
    case 49:
        return &INSTRUCTION_TABLE[380];
    case 51:
        return &INSTRUCTION_TABLE[381];
    case 54:
        return &INSTRUCTION_TABLE[382];
    case 55:
        return &INSTRUCTION_TABLE[383];
    case 57:
        return &INSTRUCTION_TABLE[384];
    case 62:
        return &INSTRUCTION_TABLE[385];
    case 63:
        return &INSTRUCTION_TABLE[386];
    default:
        throw std::runtime_error("Could not determine instruction");
    }
}
