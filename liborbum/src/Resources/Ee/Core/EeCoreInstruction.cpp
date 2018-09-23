#include "Resources/Ee/Core/EeCoreInstruction.hpp"

MipsInstructionInfo EE_CORE_INSTRUCTION_TABLE[387] =
    {
        {"SLL", 48, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"SRL", 49, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"SRA", 50, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"SLLV", 51, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"SRLV", 52, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"SRAV", 53, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"JR", 54, EeCoreInstruction::CPI_R5900_BRANCH},
        {"JALR", 55, EeCoreInstruction::CPI_R5900_BRANCH},
        {"MOVZ", 56, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"MOVN", 57, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"SYSCALL", 58, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"BREAK", 59, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"SYNC", 60, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"MFHI", 61, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"MTHI", 62, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"MFLO", 63, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"MTLO", 64, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"DSLLV", 65, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"DSRLV", 66, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"DSRAV", 67, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"MULT", 68, EeCoreInstruction::CPI_R5900_MULTIPLY},
        {"MULTU", 69, EeCoreInstruction::CPI_R5900_MULTIPLY},
        {"DIV", 70, EeCoreInstruction::CPI_R5900_DIVIDE},
        {"DIVU", 71, EeCoreInstruction::CPI_R5900_DIVIDE},
        {"ADD", 72, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"ADDU", 73, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"SUB", 74, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"SUBU", 75, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"AND", 76, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"OR", 77, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"XOR", 78, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"NOR", 79, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"MFSA", 80, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"MTSA", 81, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"SLT", 82, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"SLTU", 83, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"DADD", 84, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"DADDU", 85, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"DSUB", 86, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"DSUBU", 87, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"TGE", 88, EeCoreInstruction::CPI_R5900_BRANCH},
        {"TGEU", 89, EeCoreInstruction::CPI_R5900_BRANCH},
        {"TLT", 90, EeCoreInstruction::CPI_R5900_BRANCH},
        {"TLTU", 91, EeCoreInstruction::CPI_R5900_BRANCH},
        {"TEQ", 92, EeCoreInstruction::CPI_R5900_BRANCH},
        {"TNE", 93, EeCoreInstruction::CPI_R5900_BRANCH},
        {"DSLL", 94, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"DSRL", 95, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"DSRA", 96, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"DSLL32", 97, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"DSRL32", 98, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"DSRA32", 99, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"BLTZ", 100, EeCoreInstruction::CPI_R5900_BRANCH},
        {"BGEZ", 101, EeCoreInstruction::CPI_R5900_BRANCH},
        {"BLTZL", 102, EeCoreInstruction::CPI_R5900_BRANCH},
        {"BGEZL", 103, EeCoreInstruction::CPI_R5900_BRANCH},
        {"TGEI", 104, EeCoreInstruction::CPI_R5900_BRANCH},
        {"TGEIU", 105, EeCoreInstruction::CPI_R5900_BRANCH},
        {"TLTI", 106, EeCoreInstruction::CPI_R5900_BRANCH},
        {"TLTIU", 107, EeCoreInstruction::CPI_R5900_BRANCH},
        {"TEQI", 108, EeCoreInstruction::CPI_R5900_BRANCH},
        {"TNEI", 109, EeCoreInstruction::CPI_R5900_BRANCH},
        {"BLTZAL", 110, EeCoreInstruction::CPI_R5900_BRANCH},
        {"TGEZAL", 111, EeCoreInstruction::CPI_R5900_BRANCH},
        {"BLTZALL", 112, EeCoreInstruction::CPI_R5900_BRANCH},
        {"BGEZALL", 113, EeCoreInstruction::CPI_R5900_BRANCH},
        {"MTSAB", 114, EeCoreInstruction::CPI_R5900_BRANCH},
        {"MTSAH", 115, EeCoreInstruction::CPI_R5900_BRANCH},
        {"PADDW", 137, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PSUBW", 138, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PCGTW", 139, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PMAXW", 140, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PADDH", 141, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PSUBH", 142, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PCGTH", 143, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PMAXH", 144, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PADDB", 145, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PSUBB", 146, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PCGTB", 147, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PADDSW", 148, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PSUBSW", 149, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PEXTLW", 150, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PPACW", 151, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PADDSH", 152, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PSUBSH", 153, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PEXTLH", 154, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PPACH", 155, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PADDSB", 156, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PSUBSB", 157, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PEXTLB", 158, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PPACB", 159, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PEXT5", 160, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PPAC5", 161, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PABSW", 162, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PCEQW", 163, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PMINW", 164, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PADSBH", 165, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PABSH", 166, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PCEQH", 167, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PMINH", 168, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PCEQB", 169, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PADDUW", 170, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PSUBUW", 171, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PEXTUW", 172, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PADDUH", 173, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PSUBUH", 174, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PEXTUH", 175, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PADDUB", 176, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PSUBUB", 177, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PEXTUB", 178, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"QFSRV", 179, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PMADDW", 180, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PSLLVW", 181, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PSRLVW", 182, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PMSUBW", 183, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PMFHI", 184, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PMFLO", 185, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PINTH", 186, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PMULTW", 187, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PDIVW", 188, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PCPYLD", 189, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PMADDH", 190, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PHMADH", 191, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PAND", 192, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PXOR", 193, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PMSUBH", 194, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PHMSBH", 195, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PEXEH", 196, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PREVH", 197, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PMULTH", 198, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PDIVBW", 199, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PEXEW", 200, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PROT3W", 201, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PMADDUW", 202, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PSRAVW", 203, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PMTHI", 204, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PMTLO", 205, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PINTEH", 206, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PMULTUW", 207, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PDIVUW", 208, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PCPYUD", 209, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"POR", 210, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PNOR", 211, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PEXCH", 212, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PCPYH", 213, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PEXCW", 214, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"MADD", 116, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"MADDU", 117, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PLZCW", 118, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"MFHI1", 119, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"MTHI1", 120, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"MFLO1", 121, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"MTLO1", 122, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"MULT1", 123, EeCoreInstruction::CPI_R5900_MULTIPLY},
        {"MULTU1", 124, EeCoreInstruction::CPI_R5900_MULTIPLY},
        {"DIV1", 125, EeCoreInstruction::CPI_R5900_DIVIDE},
        {"DIVU1", 126, EeCoreInstruction::CPI_R5900_DIVIDE},
        {"MADD1", 127, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"MADDU1", 128, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PMFHL", 129, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PMTHL", 130, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PSLLH", 131, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PSRLH", 132, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PSRAH", 133, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PSLLW", 134, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PSRLW", 135, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"PSRAW", 136, EeCoreInstruction::CPI_MMI_DEFAULT},
        {"BC0F", 217, EeCoreInstruction::CPI_COP_BRANCH_DELAY},
        {"BC0T", 218, EeCoreInstruction::CPI_COP_BRANCH_DELAY},
        {"BC0FL", 219, EeCoreInstruction::CPI_COP_BRANCH_DELAY_LIKELY},
        {"BC0TL", 220, EeCoreInstruction::CPI_COP_BRANCH_DELAY_LIKELY},
        {"TLBR", 221, EeCoreInstruction::CPI_COP_DEFAULT},
        {"TLBWI", 222, EeCoreInstruction::CPI_COP_DEFAULT},
        {"TLBWR", 223, EeCoreInstruction::CPI_COP_DEFAULT},
        {"TLBP", 224, EeCoreInstruction::CPI_COP_DEFAULT},
        {"ERET", 225, EeCoreInstruction::CPI_COP_DEFAULT},
        {"EI", 226, EeCoreInstruction::CPI_COP_DEFAULT},
        {"DI", 227, EeCoreInstruction::CPI_COP_DEFAULT},
        {"MFC0", 215, EeCoreInstruction::CPI_COP_DEFAULT},
        {"MTC0", 216, EeCoreInstruction::CPI_COP_DEFAULT},
        {"BC1F", 232, EeCoreInstruction::CPI_COP_DEFAULT},
        {"BC1T", 233, EeCoreInstruction::CPI_COP_BRANCH_DELAY},
        {"BC1FL", 234, EeCoreInstruction::CPI_COP_BRANCH_DELAY},
        {"BC1TL", 235, EeCoreInstruction::CPI_COP_BRANCH_DELAY_LIKELY},
        {"ADD_S", 236, EeCoreInstruction::CPI_COP_DEFAULT},
        {"SUB_S", 237, EeCoreInstruction::CPI_COP_DEFAULT},
        {"MUL_S", 238, EeCoreInstruction::CPI_COP_DEFAULT},
        {"DIV_S", 239, EeCoreInstruction::CPI_COP_DEFAULT},
        {"SQRT_S", 240, EeCoreInstruction::CPI_COP_DEFAULT},
        {"ABS_S", 241, EeCoreInstruction::CPI_COP_DEFAULT},
        {"MOV_S", 242, EeCoreInstruction::CPI_COP_DEFAULT},
        {"NEG_S", 243, EeCoreInstruction::CPI_COP_DEFAULT},
        {"RSQRT_S", 244, EeCoreInstruction::CPI_COP_DEFAULT},
        {"ADDA_S", 245, EeCoreInstruction::CPI_COP_DEFAULT},
        {"SUBA_S", 246, EeCoreInstruction::CPI_COP_DEFAULT},
        {"MULA_S", 247, EeCoreInstruction::CPI_COP_DEFAULT},
        {"MADD_S", 248, EeCoreInstruction::CPI_COP_DEFAULT},
        {"MSUB_S", 249, EeCoreInstruction::CPI_COP_DEFAULT},
        {"MADDA_S", 250, EeCoreInstruction::CPI_COP_DEFAULT},
        {"MSUBA_S", 251, EeCoreInstruction::CPI_COP_DEFAULT},
        {"CVTW_S", 252, EeCoreInstruction::CPI_COP_DEFAULT},
        {"MAX_S", 253, EeCoreInstruction::CPI_COP_DEFAULT},
        {"MIN_S", 254, EeCoreInstruction::CPI_COP_DEFAULT},
        {"C.F_S", 255, EeCoreInstruction::CPI_COP_DEFAULT},
        {"C.EQ_S", 256, EeCoreInstruction::CPI_COP_DEFAULT},
        {"C.LT_S", 257, EeCoreInstruction::CPI_COP_DEFAULT},
        {"C.LE_S", 258, EeCoreInstruction::CPI_COP_DEFAULT},
        {"CVTS_S", 259, EeCoreInstruction::CPI_COP_DEFAULT},
        {"MFC1", 228, EeCoreInstruction::CPI_COP_DEFAULT},
        {"CFC1", 229, EeCoreInstruction::CPI_COP_DEFAULT},
        {"MTC1", 230, EeCoreInstruction::CPI_COP_DEFAULT},
        {"CTC1", 231, EeCoreInstruction::CPI_COP_DEFAULT},
        {"BC2F", 264, EeCoreInstruction::CPI_COP_DEFAULT},
        {"BC2T", 265, EeCoreInstruction::CPI_COP_DEFAULT},
        {"BC2FL", 266, EeCoreInstruction::CPI_COP_DEFAULT},
        {"BC2TL", 267, EeCoreInstruction::CPI_COP_DEFAULT},
        {"QMFC2", 260, EeCoreInstruction::CPI_COP_DEFAULT},
        {"CFC2", 261, EeCoreInstruction::CPI_COP_DEFAULT},
        {"QMTC2", 262, EeCoreInstruction::CPI_COP_DEFAULT},
        {"CTC2", 263, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VADDAbc.0", 323, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VSUBAbc.0", 324, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMADDAbc.0", 325, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMSUBAbc.0", 326, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VITOF0", 327, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VFTOI0", 328, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMULAbc.0", 329, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMULAq", 330, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VADDAq", 331, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VSUBAq", 332, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VADDA", 333, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VSUBA", 334, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMOVE", 335, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VLQI", 336, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VDIV", 337, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMTIR", 338, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VRNEXT", 339, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VADDAbc.1", 340, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VSUBAbc.1", 341, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMADDAbc.1", 342, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMSUBAbc.1", 343, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VITOF4", 344, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VFTIO4", 345, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMULAbc.1", 346, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VABS", 347, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMADDAq", 348, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMSUBAq", 349, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMADDA", 350, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMSUBA", 351, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMR32", 352, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VSQI", 353, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VSQRT", 354, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMFIR", 355, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VRGET", 356, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VADDAbc.2", 357, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VSUBAbc.2", 358, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMADDAbc.2", 359, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMSUBAbc.2", 360, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VITOF12", 361, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VFTIO12", 362, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMULAbc.2", 363, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMULAi", 364, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VADDAi", 365, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VSUBAi", 366, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMULA", 367, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VOPMULA", 368, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VLQD", 369, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VRSQRT", 370, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VILWR", 371, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VRINIT", 372, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VADDAbc.3", 373, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VSUBAbc.3", 374, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMADDAbc.3", 375, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMSUBAbc.3", 376, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VITOF15", 377, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VFTIO15", 378, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMULAbc.3", 379, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VCLIP", 380, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMADDAi", 381, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMSUBAi", 382, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VNOP", 383, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VSQD", 384, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VWAITQ", 385, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VISWR", 386, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VRXOR", 387, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VADDbc.0", 268, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VADDbc.1", 269, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VADDbc.2", 270, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VADDbc.3", 271, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VSUBbc.0", 272, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VSUBbc.1", 273, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VSUBbc.2", 274, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VSUBbc.3", 275, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMADDbc.0", 276, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMADDbc.1", 277, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMADDbc.2", 278, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMADDbc.3", 279, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMSUBbc.0", 280, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMSUBbc.1", 281, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMSUBbc.2", 282, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMSUBbc.3", 283, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMAXbc.0", 284, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMAXbc.1", 285, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMAXbc.2", 286, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMAXbc.3", 287, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMINIbc.0", 288, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMINIbc.1", 289, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMINIbc.2", 290, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMINIbc.3", 291, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMULbc.0", 292, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMULbc.1", 293, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMULbc.2", 294, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMULbc.3", 295, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMULq", 296, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMAXi", 297, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMULi", 298, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMINIi", 299, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VADDq", 300, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMADDq", 301, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VADDi", 302, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMADDi", 303, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VSUBq", 304, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMSUBq", 305, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VSUBi", 306, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMSUBi", 307, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VADD", 308, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMADD", 309, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMUL", 310, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMAX", 311, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VSUB", 312, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMSUB", 313, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VOPMSUB", 314, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VMINI", 315, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VIADD", 316, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VISUB", 317, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VIADDI", 318, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VIAND", 319, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VIOR", 320, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VCALLMS", 321, EeCoreInstruction::CPI_COP_DEFAULT},
        {"VCALLMSR", 322, EeCoreInstruction::CPI_COP_DEFAULT},
        {"J", 1, EeCoreInstruction::CPI_R5900_BRANCH},
        {"JAL", 2, EeCoreInstruction::CPI_R5900_BRANCH},
        {"BEQ", 3, EeCoreInstruction::CPI_R5900_BRANCH},
        {"BNE", 4, EeCoreInstruction::CPI_R5900_BRANCH},
        {"BLEZ", 5, EeCoreInstruction::CPI_R5900_BRANCH},
        {"BGTZ", 6, EeCoreInstruction::CPI_R5900_BRANCH},
        {"ADDI", 7, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"ADDIU", 8, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"SLTI", 9, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"SLTIU", 10, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"ANDI", 11, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"ORI", 12, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"XORI", 13, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"LUI", 14, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"BEQL", 15, EeCoreInstruction::CPI_R5900_BRANCH},
        {"BNEL", 16, EeCoreInstruction::CPI_R5900_BRANCH},
        {"BLEZL", 17, EeCoreInstruction::CPI_R5900_BRANCH},
        {"BGTZL", 18, EeCoreInstruction::CPI_R5900_BRANCH},
        {"DADDI", 19, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"DADDIU", 20, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"LDL", 21, EeCoreInstruction::CPI_R5900_LOAD},
        {"LDR", 22, EeCoreInstruction::CPI_R5900_LOAD},
        {"LQ", 23, EeCoreInstruction::CPI_R5900_LOAD},
        {"SQ", 24, EeCoreInstruction::CPI_R5900_STORE},
        {"LB", 25, EeCoreInstruction::CPI_R5900_LOAD},
        {"LH", 26, EeCoreInstruction::CPI_R5900_LOAD},
        {"LWL", 27, EeCoreInstruction::CPI_R5900_LOAD},
        {"LW", 28, EeCoreInstruction::CPI_R5900_LOAD},
        {"LBU", 29, EeCoreInstruction::CPI_R5900_LOAD},
        {"LHU", 30, EeCoreInstruction::CPI_R5900_LOAD},
        {"LWR", 31, EeCoreInstruction::CPI_R5900_LOAD},
        {"LWU", 32, EeCoreInstruction::CPI_R5900_LOAD},
        {"SB", 33, EeCoreInstruction::CPI_R5900_STORE},
        {"SH", 34, EeCoreInstruction::CPI_R5900_STORE},
        {"SWL", 35, EeCoreInstruction::CPI_R5900_STORE},
        {"SW", 36, EeCoreInstruction::CPI_R5900_STORE},
        {"SDL", 37, EeCoreInstruction::CPI_R5900_STORE},
        {"SDR", 38, EeCoreInstruction::CPI_R5900_STORE},
        {"SWR", 39, EeCoreInstruction::CPI_R5900_STORE},
        {"CACHE", 40, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"LWC1", 41, EeCoreInstruction::CPI_R5900_LOAD},
        {"PREF", 42, EeCoreInstruction::CPI_R5900_DEFAULT},
        {"LQC2", 43, EeCoreInstruction::CPI_R5900_LOAD},
        {"LD", 44, EeCoreInstruction::CPI_R5900_LOAD},
        {"SWC1", 45, EeCoreInstruction::CPI_R5900_STORE},
        {"SQC2", 46, EeCoreInstruction::CPI_R5900_STORE},
        {"SD", 47, EeCoreInstruction::CPI_R5900_STORE}};

EeCoreInstruction::EeCoreInstruction(const uword value) :
    MipsInstruction(value),
    info(nullptr)
{
}

MipsInstructionInfo* EeCoreInstruction::lookup() const
{
    switch (opcode())
    {
    case 0:
    {
        switch (funct())
        {
        case 0:
            return &EE_CORE_INSTRUCTION_TABLE[0];
        case 2:
            return &EE_CORE_INSTRUCTION_TABLE[1];
        case 3:
            return &EE_CORE_INSTRUCTION_TABLE[2];
        case 4:
            return &EE_CORE_INSTRUCTION_TABLE[3];
        case 6:
            return &EE_CORE_INSTRUCTION_TABLE[4];
        case 7:
            return &EE_CORE_INSTRUCTION_TABLE[5];
        case 8:
            return &EE_CORE_INSTRUCTION_TABLE[6];
        case 9:
            return &EE_CORE_INSTRUCTION_TABLE[7];
        case 10:
            return &EE_CORE_INSTRUCTION_TABLE[8];
        case 11:
            return &EE_CORE_INSTRUCTION_TABLE[9];
        case 12:
            return &EE_CORE_INSTRUCTION_TABLE[10];
        case 13:
            return &EE_CORE_INSTRUCTION_TABLE[11];
        case 15:
            return &EE_CORE_INSTRUCTION_TABLE[12];
        case 16:
            return &EE_CORE_INSTRUCTION_TABLE[13];
        case 17:
            return &EE_CORE_INSTRUCTION_TABLE[14];
        case 18:
            return &EE_CORE_INSTRUCTION_TABLE[15];
        case 19:
            return &EE_CORE_INSTRUCTION_TABLE[16];
        case 20:
            return &EE_CORE_INSTRUCTION_TABLE[17];
        case 22:
            return &EE_CORE_INSTRUCTION_TABLE[18];
        case 23:
            return &EE_CORE_INSTRUCTION_TABLE[19];
        case 24:
            return &EE_CORE_INSTRUCTION_TABLE[20];
        case 25:
            return &EE_CORE_INSTRUCTION_TABLE[21];
        case 26:
            return &EE_CORE_INSTRUCTION_TABLE[22];
        case 27:
            return &EE_CORE_INSTRUCTION_TABLE[23];
        case 32:
            return &EE_CORE_INSTRUCTION_TABLE[24];
        case 33:
            return &EE_CORE_INSTRUCTION_TABLE[25];
        case 34:
            return &EE_CORE_INSTRUCTION_TABLE[26];
        case 35:
            return &EE_CORE_INSTRUCTION_TABLE[27];
        case 36:
            return &EE_CORE_INSTRUCTION_TABLE[28];
        case 37:
            return &EE_CORE_INSTRUCTION_TABLE[29];
        case 38:
            return &EE_CORE_INSTRUCTION_TABLE[30];
        case 39:
            return &EE_CORE_INSTRUCTION_TABLE[31];
        case 40:
            return &EE_CORE_INSTRUCTION_TABLE[32];
        case 41:
            return &EE_CORE_INSTRUCTION_TABLE[33];
        case 42:
            return &EE_CORE_INSTRUCTION_TABLE[34];
        case 43:
            return &EE_CORE_INSTRUCTION_TABLE[35];
        case 44:
            return &EE_CORE_INSTRUCTION_TABLE[36];
        case 45:
            return &EE_CORE_INSTRUCTION_TABLE[37];
        case 46:
            return &EE_CORE_INSTRUCTION_TABLE[38];
        case 47:
            return &EE_CORE_INSTRUCTION_TABLE[39];
        case 48:
            return &EE_CORE_INSTRUCTION_TABLE[40];
        case 49:
            return &EE_CORE_INSTRUCTION_TABLE[41];
        case 50:
            return &EE_CORE_INSTRUCTION_TABLE[42];
        case 51:
            return &EE_CORE_INSTRUCTION_TABLE[43];
        case 52:
            return &EE_CORE_INSTRUCTION_TABLE[44];
        case 54:
            return &EE_CORE_INSTRUCTION_TABLE[45];
        case 56:
            return &EE_CORE_INSTRUCTION_TABLE[46];
        case 58:
            return &EE_CORE_INSTRUCTION_TABLE[47];
        case 59:
            return &EE_CORE_INSTRUCTION_TABLE[48];
        case 60:
            return &EE_CORE_INSTRUCTION_TABLE[49];
        case 62:
            return &EE_CORE_INSTRUCTION_TABLE[50];
        case 63:
            return &EE_CORE_INSTRUCTION_TABLE[51];
        default:
            throw std::runtime_error("EE Core: Could not determine instruction");
        }
    }
    case 1:
    {
        switch (rt())
        {
        case 0:
            return &EE_CORE_INSTRUCTION_TABLE[52];
        case 1:
            return &EE_CORE_INSTRUCTION_TABLE[53];
        case 2:
            return &EE_CORE_INSTRUCTION_TABLE[54];
        case 3:
            return &EE_CORE_INSTRUCTION_TABLE[55];
        case 8:
            return &EE_CORE_INSTRUCTION_TABLE[56];
        case 9:
            return &EE_CORE_INSTRUCTION_TABLE[57];
        case 10:
            return &EE_CORE_INSTRUCTION_TABLE[58];
        case 11:
            return &EE_CORE_INSTRUCTION_TABLE[59];
        case 12:
            return &EE_CORE_INSTRUCTION_TABLE[60];
        case 14:
            return &EE_CORE_INSTRUCTION_TABLE[61];
        case 16:
            return &EE_CORE_INSTRUCTION_TABLE[62];
        case 17:
            return &EE_CORE_INSTRUCTION_TABLE[63];
        case 18:
            return &EE_CORE_INSTRUCTION_TABLE[64];
        case 19:
            return &EE_CORE_INSTRUCTION_TABLE[65];
        case 24:
            return &EE_CORE_INSTRUCTION_TABLE[66];
        case 25:
            return &EE_CORE_INSTRUCTION_TABLE[67];
        default:
            throw std::runtime_error("EE Core: Could not determine instruction");
        }
    }
    case 28:
    {
        switch (funct())
        {
        case 8:
        {
            switch (shamt())
            {
            case 0:
                return &EE_CORE_INSTRUCTION_TABLE[68];
            case 1:
                return &EE_CORE_INSTRUCTION_TABLE[69];
            case 2:
                return &EE_CORE_INSTRUCTION_TABLE[70];
            case 3:
                return &EE_CORE_INSTRUCTION_TABLE[71];
            case 4:
                return &EE_CORE_INSTRUCTION_TABLE[72];
            case 5:
                return &EE_CORE_INSTRUCTION_TABLE[73];
            case 6:
                return &EE_CORE_INSTRUCTION_TABLE[74];
            case 7:
                return &EE_CORE_INSTRUCTION_TABLE[75];
            case 8:
                return &EE_CORE_INSTRUCTION_TABLE[76];
            case 9:
                return &EE_CORE_INSTRUCTION_TABLE[77];
            case 10:
                return &EE_CORE_INSTRUCTION_TABLE[78];
            case 16:
                return &EE_CORE_INSTRUCTION_TABLE[79];
            case 17:
                return &EE_CORE_INSTRUCTION_TABLE[80];
            case 18:
                return &EE_CORE_INSTRUCTION_TABLE[81];
            case 19:
                return &EE_CORE_INSTRUCTION_TABLE[82];
            case 20:
                return &EE_CORE_INSTRUCTION_TABLE[83];
            case 21:
                return &EE_CORE_INSTRUCTION_TABLE[84];
            case 22:
                return &EE_CORE_INSTRUCTION_TABLE[85];
            case 23:
                return &EE_CORE_INSTRUCTION_TABLE[86];
            case 24:
                return &EE_CORE_INSTRUCTION_TABLE[87];
            case 25:
                return &EE_CORE_INSTRUCTION_TABLE[88];
            case 26:
                return &EE_CORE_INSTRUCTION_TABLE[89];
            case 27:
                return &EE_CORE_INSTRUCTION_TABLE[90];
            case 30:
                return &EE_CORE_INSTRUCTION_TABLE[91];
            case 31:
                return &EE_CORE_INSTRUCTION_TABLE[92];
            default:
                throw std::runtime_error("EE Core: Could not determine instruction");
            }
        }
        case 40:
        {
            switch (shamt())
            {
            case 1:
                return &EE_CORE_INSTRUCTION_TABLE[93];
            case 2:
                return &EE_CORE_INSTRUCTION_TABLE[94];
            case 3:
                return &EE_CORE_INSTRUCTION_TABLE[95];
            case 4:
                return &EE_CORE_INSTRUCTION_TABLE[96];
            case 5:
                return &EE_CORE_INSTRUCTION_TABLE[97];
            case 6:
                return &EE_CORE_INSTRUCTION_TABLE[98];
            case 7:
                return &EE_CORE_INSTRUCTION_TABLE[99];
            case 10:
                return &EE_CORE_INSTRUCTION_TABLE[100];
            case 16:
                return &EE_CORE_INSTRUCTION_TABLE[101];
            case 17:
                return &EE_CORE_INSTRUCTION_TABLE[102];
            case 18:
                return &EE_CORE_INSTRUCTION_TABLE[103];
            case 20:
                return &EE_CORE_INSTRUCTION_TABLE[104];
            case 21:
                return &EE_CORE_INSTRUCTION_TABLE[105];
            case 22:
                return &EE_CORE_INSTRUCTION_TABLE[106];
            case 24:
                return &EE_CORE_INSTRUCTION_TABLE[107];
            case 25:
                return &EE_CORE_INSTRUCTION_TABLE[108];
            case 26:
                return &EE_CORE_INSTRUCTION_TABLE[109];
            case 27:
                return &EE_CORE_INSTRUCTION_TABLE[110];
            default:
                throw std::runtime_error("EE Core: Could not determine instruction");
            }
        }
        case 9:
        {
            switch (shamt())
            {
            case 0:
                return &EE_CORE_INSTRUCTION_TABLE[111];
            case 2:
                return &EE_CORE_INSTRUCTION_TABLE[112];
            case 3:
                return &EE_CORE_INSTRUCTION_TABLE[113];
            case 4:
                return &EE_CORE_INSTRUCTION_TABLE[114];
            case 8:
                return &EE_CORE_INSTRUCTION_TABLE[115];
            case 9:
                return &EE_CORE_INSTRUCTION_TABLE[116];
            case 10:
                return &EE_CORE_INSTRUCTION_TABLE[117];
            case 12:
                return &EE_CORE_INSTRUCTION_TABLE[118];
            case 13:
                return &EE_CORE_INSTRUCTION_TABLE[119];
            case 14:
                return &EE_CORE_INSTRUCTION_TABLE[120];
            case 16:
                return &EE_CORE_INSTRUCTION_TABLE[121];
            case 17:
                return &EE_CORE_INSTRUCTION_TABLE[122];
            case 18:
                return &EE_CORE_INSTRUCTION_TABLE[123];
            case 19:
                return &EE_CORE_INSTRUCTION_TABLE[124];
            case 20:
                return &EE_CORE_INSTRUCTION_TABLE[125];
            case 21:
                return &EE_CORE_INSTRUCTION_TABLE[126];
            case 26:
                return &EE_CORE_INSTRUCTION_TABLE[127];
            case 27:
                return &EE_CORE_INSTRUCTION_TABLE[128];
            case 28:
                return &EE_CORE_INSTRUCTION_TABLE[129];
            case 29:
                return &EE_CORE_INSTRUCTION_TABLE[130];
            case 30:
                return &EE_CORE_INSTRUCTION_TABLE[131];
            case 31:
                return &EE_CORE_INSTRUCTION_TABLE[132];
            default:
                throw std::runtime_error("EE Core: Could not determine instruction");
            }
        }
        case 41:
        {
            switch (shamt())
            {
            case 0:
                return &EE_CORE_INSTRUCTION_TABLE[133];
            case 3:
                return &EE_CORE_INSTRUCTION_TABLE[134];
            case 8:
                return &EE_CORE_INSTRUCTION_TABLE[135];
            case 9:
                return &EE_CORE_INSTRUCTION_TABLE[136];
            case 10:
                return &EE_CORE_INSTRUCTION_TABLE[137];
            case 12:
                return &EE_CORE_INSTRUCTION_TABLE[138];
            case 13:
                return &EE_CORE_INSTRUCTION_TABLE[139];
            case 14:
                return &EE_CORE_INSTRUCTION_TABLE[140];
            case 18:
                return &EE_CORE_INSTRUCTION_TABLE[141];
            case 19:
                return &EE_CORE_INSTRUCTION_TABLE[142];
            case 26:
                return &EE_CORE_INSTRUCTION_TABLE[143];
            case 27:
                return &EE_CORE_INSTRUCTION_TABLE[144];
            case 30:
                return &EE_CORE_INSTRUCTION_TABLE[145];
            default:
                throw std::runtime_error("EE Core: Could not determine instruction");
            }
        }
        case 0:
            return &EE_CORE_INSTRUCTION_TABLE[146];
        case 1:
            return &EE_CORE_INSTRUCTION_TABLE[147];
        case 4:
            return &EE_CORE_INSTRUCTION_TABLE[148];
        case 16:
            return &EE_CORE_INSTRUCTION_TABLE[149];
        case 17:
            return &EE_CORE_INSTRUCTION_TABLE[150];
        case 18:
            return &EE_CORE_INSTRUCTION_TABLE[151];
        case 19:
            return &EE_CORE_INSTRUCTION_TABLE[152];
        case 24:
            return &EE_CORE_INSTRUCTION_TABLE[153];
        case 25:
            return &EE_CORE_INSTRUCTION_TABLE[154];
        case 26:
            return &EE_CORE_INSTRUCTION_TABLE[155];
        case 27:
            return &EE_CORE_INSTRUCTION_TABLE[156];
        case 32:
            return &EE_CORE_INSTRUCTION_TABLE[157];
        case 33:
            return &EE_CORE_INSTRUCTION_TABLE[158];
        case 48:
            return &EE_CORE_INSTRUCTION_TABLE[159];
        case 49:
            return &EE_CORE_INSTRUCTION_TABLE[160];
        case 52:
            return &EE_CORE_INSTRUCTION_TABLE[161];
        case 54:
            return &EE_CORE_INSTRUCTION_TABLE[162];
        case 55:
            return &EE_CORE_INSTRUCTION_TABLE[163];
        case 60:
            return &EE_CORE_INSTRUCTION_TABLE[164];
        case 62:
            return &EE_CORE_INSTRUCTION_TABLE[165];
        case 63:
            return &EE_CORE_INSTRUCTION_TABLE[166];
        default:
            throw std::runtime_error("EE Core: Could not determine instruction");
        }
    }
    case 16:
    {
        switch (rs())
        {
        case 8:
        {
            switch (rt())
            {
            case 0:
                return &EE_CORE_INSTRUCTION_TABLE[167];
            case 1:
                return &EE_CORE_INSTRUCTION_TABLE[168];
            case 2:
                return &EE_CORE_INSTRUCTION_TABLE[169];
            case 3:
                return &EE_CORE_INSTRUCTION_TABLE[170];
            default:
                throw std::runtime_error("EE Core: Could not determine instruction");
            }
        }
        case 16:
        {
            switch (funct())
            {
            case 1:
                return &EE_CORE_INSTRUCTION_TABLE[171];
            case 2:
                return &EE_CORE_INSTRUCTION_TABLE[172];
            case 6:
                return &EE_CORE_INSTRUCTION_TABLE[173];
            case 8:
                return &EE_CORE_INSTRUCTION_TABLE[174];
            case 24:
                return &EE_CORE_INSTRUCTION_TABLE[175];
            case 56:
                return &EE_CORE_INSTRUCTION_TABLE[176];
            case 57:
                return &EE_CORE_INSTRUCTION_TABLE[177];
            default:
                throw std::runtime_error("EE Core: Could not determine instruction");
            }
        }
        case 0:
            return &EE_CORE_INSTRUCTION_TABLE[178];
        case 4:
            return &EE_CORE_INSTRUCTION_TABLE[179];
        default:
            throw std::runtime_error("EE Core: Could not determine instruction");
        }
    }
    case 17:
    {
        switch (rs())
        {
        case 8:
        {
            switch (rt())
            {
            case 0:
                return &EE_CORE_INSTRUCTION_TABLE[180];
            case 1:
                return &EE_CORE_INSTRUCTION_TABLE[181];
            case 2:
                return &EE_CORE_INSTRUCTION_TABLE[182];
            case 3:
                return &EE_CORE_INSTRUCTION_TABLE[183];
            default:
                throw std::runtime_error("EE Core: Could not determine instruction");
            }
        }
        case 16:
        {
            switch (funct())
            {
            case 0:
                return &EE_CORE_INSTRUCTION_TABLE[184];
            case 1:
                return &EE_CORE_INSTRUCTION_TABLE[185];
            case 2:
                return &EE_CORE_INSTRUCTION_TABLE[186];
            case 3:
                return &EE_CORE_INSTRUCTION_TABLE[187];
            case 4:
                return &EE_CORE_INSTRUCTION_TABLE[188];
            case 5:
                return &EE_CORE_INSTRUCTION_TABLE[189];
            case 6:
                return &EE_CORE_INSTRUCTION_TABLE[190];
            case 7:
                return &EE_CORE_INSTRUCTION_TABLE[191];
            case 21:
                return &EE_CORE_INSTRUCTION_TABLE[192];
            case 23:
                return &EE_CORE_INSTRUCTION_TABLE[193];
            case 24:
                return &EE_CORE_INSTRUCTION_TABLE[194];
            case 25:
                return &EE_CORE_INSTRUCTION_TABLE[195];
            case 27:
                return &EE_CORE_INSTRUCTION_TABLE[196];
            case 28:
                return &EE_CORE_INSTRUCTION_TABLE[197];
            case 29:
                return &EE_CORE_INSTRUCTION_TABLE[198];
            case 30:
                return &EE_CORE_INSTRUCTION_TABLE[199];
            case 35:
                return &EE_CORE_INSTRUCTION_TABLE[200];
            case 39:
                return &EE_CORE_INSTRUCTION_TABLE[201];
            case 40:
                return &EE_CORE_INSTRUCTION_TABLE[202];
            case 47:
                return &EE_CORE_INSTRUCTION_TABLE[203];
            case 49:
                return &EE_CORE_INSTRUCTION_TABLE[204];
            case 51:
                return &EE_CORE_INSTRUCTION_TABLE[205];
            case 53:
                return &EE_CORE_INSTRUCTION_TABLE[206];
            default:
                throw std::runtime_error("EE Core: Could not determine instruction");
            }
        }
        case 20:
        {
            switch (funct())
            {
            case 32:
                return &EE_CORE_INSTRUCTION_TABLE[207];
            default:
                throw std::runtime_error("EE Core: Could not determine instruction");
            }
        }
        case 0:
            return &EE_CORE_INSTRUCTION_TABLE[208];
        case 2:
            return &EE_CORE_INSTRUCTION_TABLE[209];
        case 4:
            return &EE_CORE_INSTRUCTION_TABLE[210];
        case 6:
            return &EE_CORE_INSTRUCTION_TABLE[211];
        default:
            throw std::runtime_error("EE Core: Could not determine instruction");
        }
    }
    case 18:
    {
        switch (co())
        {
        case 0:
        {
            switch (dest())
            {
            case 8:
            {
                switch (rt())
                {
                case 0:
                    return &EE_CORE_INSTRUCTION_TABLE[212];
                case 1:
                    return &EE_CORE_INSTRUCTION_TABLE[213];
                case 2:
                    return &EE_CORE_INSTRUCTION_TABLE[214];
                case 3:
                    return &EE_CORE_INSTRUCTION_TABLE[215];
                default:
                    throw std::runtime_error("EE Core: Could not determine instruction");
                }
            }
            case 1:
                return &EE_CORE_INSTRUCTION_TABLE[216];
            case 2:
                return &EE_CORE_INSTRUCTION_TABLE[217];
            case 5:
                return &EE_CORE_INSTRUCTION_TABLE[218];
            case 6:
                return &EE_CORE_INSTRUCTION_TABLE[219];
            default:
                throw std::runtime_error("EE Core: Could not determine instruction");
            }
        }
        case 1:
        {
            switch (funct())
            {
            case 60:
            {
                switch (shamt())
                {
                case 0:
                    return &EE_CORE_INSTRUCTION_TABLE[220];
                case 1:
                    return &EE_CORE_INSTRUCTION_TABLE[221];
                case 2:
                    return &EE_CORE_INSTRUCTION_TABLE[222];
                case 3:
                    return &EE_CORE_INSTRUCTION_TABLE[223];
                case 4:
                    return &EE_CORE_INSTRUCTION_TABLE[224];
                case 5:
                    return &EE_CORE_INSTRUCTION_TABLE[225];
                case 6:
                    return &EE_CORE_INSTRUCTION_TABLE[226];
                case 7:
                    return &EE_CORE_INSTRUCTION_TABLE[227];
                case 8:
                    return &EE_CORE_INSTRUCTION_TABLE[228];
                case 9:
                    return &EE_CORE_INSTRUCTION_TABLE[229];
                case 10:
                    return &EE_CORE_INSTRUCTION_TABLE[230];
                case 11:
                    return &EE_CORE_INSTRUCTION_TABLE[231];
                case 12:
                    return &EE_CORE_INSTRUCTION_TABLE[232];
                case 13:
                    return &EE_CORE_INSTRUCTION_TABLE[233];
                case 14:
                    return &EE_CORE_INSTRUCTION_TABLE[234];
                case 15:
                    return &EE_CORE_INSTRUCTION_TABLE[235];
                case 16:
                    return &EE_CORE_INSTRUCTION_TABLE[236];
                default:
                    throw std::runtime_error("EE Core: Could not determine instruction");
                }
            }
            case 61:
            {
                switch (shamt())
                {
                case 0:
                    return &EE_CORE_INSTRUCTION_TABLE[237];
                case 1:
                    return &EE_CORE_INSTRUCTION_TABLE[238];
                case 2:
                    return &EE_CORE_INSTRUCTION_TABLE[239];
                case 3:
                    return &EE_CORE_INSTRUCTION_TABLE[240];
                case 4:
                    return &EE_CORE_INSTRUCTION_TABLE[241];
                case 5:
                    return &EE_CORE_INSTRUCTION_TABLE[242];
                case 6:
                    return &EE_CORE_INSTRUCTION_TABLE[243];
                case 7:
                    return &EE_CORE_INSTRUCTION_TABLE[244];
                case 8:
                    return &EE_CORE_INSTRUCTION_TABLE[245];
                case 9:
                    return &EE_CORE_INSTRUCTION_TABLE[246];
                case 10:
                    return &EE_CORE_INSTRUCTION_TABLE[247];
                case 11:
                    return &EE_CORE_INSTRUCTION_TABLE[248];
                case 12:
                    return &EE_CORE_INSTRUCTION_TABLE[249];
                case 13:
                    return &EE_CORE_INSTRUCTION_TABLE[250];
                case 14:
                    return &EE_CORE_INSTRUCTION_TABLE[251];
                case 15:
                    return &EE_CORE_INSTRUCTION_TABLE[252];
                case 16:
                    return &EE_CORE_INSTRUCTION_TABLE[253];
                default:
                    throw std::runtime_error("EE Core: Could not determine instruction");
                }
            }
            case 62:
            {
                switch (shamt())
                {
                case 0:
                    return &EE_CORE_INSTRUCTION_TABLE[254];
                case 1:
                    return &EE_CORE_INSTRUCTION_TABLE[255];
                case 2:
                    return &EE_CORE_INSTRUCTION_TABLE[256];
                case 3:
                    return &EE_CORE_INSTRUCTION_TABLE[257];
                case 4:
                    return &EE_CORE_INSTRUCTION_TABLE[258];
                case 5:
                    return &EE_CORE_INSTRUCTION_TABLE[259];
                case 6:
                    return &EE_CORE_INSTRUCTION_TABLE[260];
                case 7:
                    return &EE_CORE_INSTRUCTION_TABLE[261];
                case 8:
                    return &EE_CORE_INSTRUCTION_TABLE[262];
                case 9:
                    return &EE_CORE_INSTRUCTION_TABLE[263];
                case 10:
                    return &EE_CORE_INSTRUCTION_TABLE[264];
                case 11:
                    return &EE_CORE_INSTRUCTION_TABLE[265];
                case 13:
                    return &EE_CORE_INSTRUCTION_TABLE[266];
                case 14:
                    return &EE_CORE_INSTRUCTION_TABLE[267];
                case 15:
                    return &EE_CORE_INSTRUCTION_TABLE[268];
                case 16:
                    return &EE_CORE_INSTRUCTION_TABLE[269];
                default:
                    throw std::runtime_error("EE Core: Could not determine instruction");
                }
            }
            case 63:
            {
                switch (shamt())
                {
                case 0:
                    return &EE_CORE_INSTRUCTION_TABLE[270];
                case 1:
                    return &EE_CORE_INSTRUCTION_TABLE[271];
                case 2:
                    return &EE_CORE_INSTRUCTION_TABLE[272];
                case 3:
                    return &EE_CORE_INSTRUCTION_TABLE[273];
                case 4:
                    return &EE_CORE_INSTRUCTION_TABLE[274];
                case 5:
                    return &EE_CORE_INSTRUCTION_TABLE[275];
                case 6:
                    return &EE_CORE_INSTRUCTION_TABLE[276];
                case 7:
                    return &EE_CORE_INSTRUCTION_TABLE[277];
                case 8:
                    return &EE_CORE_INSTRUCTION_TABLE[278];
                case 9:
                    return &EE_CORE_INSTRUCTION_TABLE[279];
                case 11:
                    return &EE_CORE_INSTRUCTION_TABLE[280];
                case 13:
                    return &EE_CORE_INSTRUCTION_TABLE[281];
                case 14:
                    return &EE_CORE_INSTRUCTION_TABLE[282];
                case 15:
                    return &EE_CORE_INSTRUCTION_TABLE[283];
                case 16:
                    return &EE_CORE_INSTRUCTION_TABLE[284];
                default:
                    throw std::runtime_error("EE Core: Could not determine instruction");
                }
            }
            case 0:
                return &EE_CORE_INSTRUCTION_TABLE[285];
            case 1:
                return &EE_CORE_INSTRUCTION_TABLE[286];
            case 2:
                return &EE_CORE_INSTRUCTION_TABLE[287];
            case 3:
                return &EE_CORE_INSTRUCTION_TABLE[288];
            case 4:
                return &EE_CORE_INSTRUCTION_TABLE[289];
            case 5:
                return &EE_CORE_INSTRUCTION_TABLE[290];
            case 6:
                return &EE_CORE_INSTRUCTION_TABLE[291];
            case 7:
                return &EE_CORE_INSTRUCTION_TABLE[292];
            case 8:
                return &EE_CORE_INSTRUCTION_TABLE[293];
            case 9:
                return &EE_CORE_INSTRUCTION_TABLE[294];
            case 10:
                return &EE_CORE_INSTRUCTION_TABLE[295];
            case 11:
                return &EE_CORE_INSTRUCTION_TABLE[296];
            case 12:
                return &EE_CORE_INSTRUCTION_TABLE[297];
            case 13:
                return &EE_CORE_INSTRUCTION_TABLE[298];
            case 14:
                return &EE_CORE_INSTRUCTION_TABLE[299];
            case 15:
                return &EE_CORE_INSTRUCTION_TABLE[300];
            case 16:
                return &EE_CORE_INSTRUCTION_TABLE[301];
            case 17:
                return &EE_CORE_INSTRUCTION_TABLE[302];
            case 18:
                return &EE_CORE_INSTRUCTION_TABLE[303];
            case 19:
                return &EE_CORE_INSTRUCTION_TABLE[304];
            case 20:
                return &EE_CORE_INSTRUCTION_TABLE[305];
            case 21:
                return &EE_CORE_INSTRUCTION_TABLE[306];
            case 22:
                return &EE_CORE_INSTRUCTION_TABLE[307];
            case 23:
                return &EE_CORE_INSTRUCTION_TABLE[308];
            case 24:
                return &EE_CORE_INSTRUCTION_TABLE[309];
            case 25:
                return &EE_CORE_INSTRUCTION_TABLE[310];
            case 26:
                return &EE_CORE_INSTRUCTION_TABLE[311];
            case 27:
                return &EE_CORE_INSTRUCTION_TABLE[312];
            case 28:
                return &EE_CORE_INSTRUCTION_TABLE[313];
            case 29:
                return &EE_CORE_INSTRUCTION_TABLE[314];
            case 30:
                return &EE_CORE_INSTRUCTION_TABLE[315];
            case 31:
                return &EE_CORE_INSTRUCTION_TABLE[316];
            case 32:
                return &EE_CORE_INSTRUCTION_TABLE[317];
            case 33:
                return &EE_CORE_INSTRUCTION_TABLE[318];
            case 34:
                return &EE_CORE_INSTRUCTION_TABLE[319];
            case 35:
                return &EE_CORE_INSTRUCTION_TABLE[320];
            case 36:
                return &EE_CORE_INSTRUCTION_TABLE[321];
            case 37:
                return &EE_CORE_INSTRUCTION_TABLE[322];
            case 38:
                return &EE_CORE_INSTRUCTION_TABLE[323];
            case 39:
                return &EE_CORE_INSTRUCTION_TABLE[324];
            case 40:
                return &EE_CORE_INSTRUCTION_TABLE[325];
            case 41:
                return &EE_CORE_INSTRUCTION_TABLE[326];
            case 42:
                return &EE_CORE_INSTRUCTION_TABLE[327];
            case 43:
                return &EE_CORE_INSTRUCTION_TABLE[328];
            case 44:
                return &EE_CORE_INSTRUCTION_TABLE[329];
            case 45:
                return &EE_CORE_INSTRUCTION_TABLE[330];
            case 46:
                return &EE_CORE_INSTRUCTION_TABLE[331];
            case 47:
                return &EE_CORE_INSTRUCTION_TABLE[332];
            case 48:
                return &EE_CORE_INSTRUCTION_TABLE[333];
            case 49:
                return &EE_CORE_INSTRUCTION_TABLE[334];
            case 50:
                return &EE_CORE_INSTRUCTION_TABLE[335];
            case 52:
                return &EE_CORE_INSTRUCTION_TABLE[336];
            case 53:
                return &EE_CORE_INSTRUCTION_TABLE[337];
            case 56:
                return &EE_CORE_INSTRUCTION_TABLE[338];
            case 57:
                return &EE_CORE_INSTRUCTION_TABLE[339];
            default:
                throw std::runtime_error("EE Core: Could not determine instruction");
            }
        }
        default:
            throw std::runtime_error("EE Core: Could not determine instruction");
        }
    }
    case 2:
        return &EE_CORE_INSTRUCTION_TABLE[340];
    case 3:
        return &EE_CORE_INSTRUCTION_TABLE[341];
    case 4:
        return &EE_CORE_INSTRUCTION_TABLE[342];
    case 5:
        return &EE_CORE_INSTRUCTION_TABLE[343];
    case 6:
        return &EE_CORE_INSTRUCTION_TABLE[344];
    case 7:
        return &EE_CORE_INSTRUCTION_TABLE[345];
    case 8:
        return &EE_CORE_INSTRUCTION_TABLE[346];
    case 9:
        return &EE_CORE_INSTRUCTION_TABLE[347];
    case 10:
        return &EE_CORE_INSTRUCTION_TABLE[348];
    case 11:
        return &EE_CORE_INSTRUCTION_TABLE[349];
    case 12:
        return &EE_CORE_INSTRUCTION_TABLE[350];
    case 13:
        return &EE_CORE_INSTRUCTION_TABLE[351];
    case 14:
        return &EE_CORE_INSTRUCTION_TABLE[352];
    case 15:
        return &EE_CORE_INSTRUCTION_TABLE[353];
    case 20:
        return &EE_CORE_INSTRUCTION_TABLE[354];
    case 21:
        return &EE_CORE_INSTRUCTION_TABLE[355];
    case 22:
        return &EE_CORE_INSTRUCTION_TABLE[356];
    case 23:
        return &EE_CORE_INSTRUCTION_TABLE[357];
    case 24:
        return &EE_CORE_INSTRUCTION_TABLE[358];
    case 25:
        return &EE_CORE_INSTRUCTION_TABLE[359];
    case 26:
        return &EE_CORE_INSTRUCTION_TABLE[360];
    case 27:
        return &EE_CORE_INSTRUCTION_TABLE[361];
    case 30:
        return &EE_CORE_INSTRUCTION_TABLE[362];
    case 31:
        return &EE_CORE_INSTRUCTION_TABLE[363];
    case 32:
        return &EE_CORE_INSTRUCTION_TABLE[364];
    case 33:
        return &EE_CORE_INSTRUCTION_TABLE[365];
    case 34:
        return &EE_CORE_INSTRUCTION_TABLE[366];
    case 35:
        return &EE_CORE_INSTRUCTION_TABLE[367];
    case 36:
        return &EE_CORE_INSTRUCTION_TABLE[368];
    case 37:
        return &EE_CORE_INSTRUCTION_TABLE[369];
    case 38:
        return &EE_CORE_INSTRUCTION_TABLE[370];
    case 39:
        return &EE_CORE_INSTRUCTION_TABLE[371];
    case 40:
        return &EE_CORE_INSTRUCTION_TABLE[372];
    case 41:
        return &EE_CORE_INSTRUCTION_TABLE[373];
    case 42:
        return &EE_CORE_INSTRUCTION_TABLE[374];
    case 43:
        return &EE_CORE_INSTRUCTION_TABLE[375];
    case 44:
        return &EE_CORE_INSTRUCTION_TABLE[376];
    case 45:
        return &EE_CORE_INSTRUCTION_TABLE[377];
    case 46:
        return &EE_CORE_INSTRUCTION_TABLE[378];
    case 47:
        return &EE_CORE_INSTRUCTION_TABLE[379];
    case 49:
        return &EE_CORE_INSTRUCTION_TABLE[380];
    case 51:
        return &EE_CORE_INSTRUCTION_TABLE[381];
    case 54:
        return &EE_CORE_INSTRUCTION_TABLE[382];
    case 55:
        return &EE_CORE_INSTRUCTION_TABLE[383];
    case 57:
        return &EE_CORE_INSTRUCTION_TABLE[384];
    case 62:
        return &EE_CORE_INSTRUCTION_TABLE[385];
    case 63:
        return &EE_CORE_INSTRUCTION_TABLE[386];
    default:
        throw std::runtime_error("EE Core: Could not determine instruction");
    }
}
