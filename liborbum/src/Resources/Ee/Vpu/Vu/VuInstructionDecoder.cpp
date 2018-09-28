#include "Resources/Ee/Vpu/Vu/VuInstructionDecoder.hpp"

/// Each VuInstruction specifies 3 registers (one for the destination reg
/// and others for source) and uses 4 at most (eg MADD/MSUB). In this table index 0
/// stores the destination reg, while index 1, 2 & 3 stores the source reg(s).
/// If the destination bitfield is set to nullopt, then it is assumed that the
/// instruction uses special registers such as P, Q or ACC.
VuDecodedInst VU_DECODE_TABLE[Constants::EE::VPU::VU::NUMBER_VU_INSTRUCTIONS] {
    //              DESTINATION           SOURCE (1)           SOURCE (2)        SOURCE (3)             FIELDS
    // Upper Instructions
    VuDecodedInst(VuInstruction::FT,   VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::Dest), // ABS
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Dest), // ADD
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuSpecialRegs::I,  std::nullopt,      VuDecodedInst::Dest), // ADDi
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuSpecialRegs::Q,  std::nullopt,      VuDecodedInst::Dest), // ADDq
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Bc), // ADDbc_0
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Bc), // ADDbc_1
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Bc), // ADDbc_2
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Bc), // ADDbc_3
    VuDecodedInst(VuSpecialRegs::ACC,  VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Dest), // ADDA
    VuDecodedInst(VuSpecialRegs::ACC,  VuInstruction::FS,   VuSpecialRegs::I,  std::nullopt,      VuDecodedInst::Dest), // ADDAi
    VuDecodedInst(VuSpecialRegs::ACC,  VuInstruction::FS,   VuSpecialRegs::Q,  std::nullopt,      VuDecodedInst::Dest), // ADDAq
    VuDecodedInst(VuSpecialRegs::ACC,  VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Bc), // ADDAbc_0
    VuDecodedInst(VuSpecialRegs::ACC,  VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Bc), // ADDAbc_1
    VuDecodedInst(VuSpecialRegs::ACC,  VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Bc), // ADDAbc_2
    VuDecodedInst(VuSpecialRegs::ACC,  VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Bc), // ADDAbc_3
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Dest), // SUB
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuSpecialRegs::I,  std::nullopt,      VuDecodedInst::Dest), // SUBi
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuSpecialRegs::Q,  std::nullopt,      VuDecodedInst::Dest), // SUBq
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Bc), // SUBbc_0
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Bc), // SUBbc_1
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Bc), // SUBbc_2
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Bc), // SUBbc_3
    VuDecodedInst(VuSpecialRegs::ACC,  VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Dest), // SUBA
    VuDecodedInst(VuSpecialRegs::ACC,  VuInstruction::FS,   VuSpecialRegs::I,  std::nullopt,      VuDecodedInst::Dest), // SUBAi
    VuDecodedInst(VuSpecialRegs::ACC,  VuInstruction::FS,   VuSpecialRegs::Q,  std::nullopt,      VuDecodedInst::Dest), // SUBAq
    VuDecodedInst(VuSpecialRegs::ACC,  VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Bc), // SUBAbc_0
    VuDecodedInst(VuSpecialRegs::ACC,  VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Bc), // SUBAbc_1
    VuDecodedInst(VuSpecialRegs::ACC,  VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Bc), // SUBAbc_2
    VuDecodedInst(VuSpecialRegs::ACC,  VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Bc), // SUBAbc_3
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Dest), // MUL
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuSpecialRegs::I,  std::nullopt,      VuDecodedInst::Dest), // MULi
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuSpecialRegs::Q,  std::nullopt,      VuDecodedInst::Dest), // MULq
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Bc), // MULbc_0
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Bc), // MULbc_1
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Bc), // MULbc_2
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Bc), // MULbc_3
    VuDecodedInst(VuSpecialRegs::ACC,  VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Dest), // MULA
    VuDecodedInst(VuSpecialRegs::ACC,  VuInstruction::FS,   VuSpecialRegs::I,  std::nullopt,      VuDecodedInst::Dest), // MULAi
    VuDecodedInst(VuSpecialRegs::ACC,  VuInstruction::FS,   VuSpecialRegs::Q,  std::nullopt,      VuDecodedInst::Dest), // MULAq
    VuDecodedInst(VuSpecialRegs::ACC,  VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Bc), // MULAbc_0
    VuDecodedInst(VuSpecialRegs::ACC,  VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Bc), // MULAbc_1
    VuDecodedInst(VuSpecialRegs::ACC,  VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Bc), // MULAbc_2
    VuDecodedInst(VuSpecialRegs::ACC,  VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Bc), // MULAbc_3
    VuDecodedInst(VuInstruction::FD,   VuSpecialRegs::ACC,  VuInstruction::FS, VuInstruction::FT, VuDecodedInst::Dest), // MADD
    VuDecodedInst(VuInstruction::FD,   VuSpecialRegs::ACC,  VuInstruction::FS, VuSpecialRegs::I,  VuDecodedInst::Dest), // MADDi
    VuDecodedInst(VuInstruction::FD,   VuSpecialRegs::ACC,  VuInstruction::FS, VuSpecialRegs::Q,  VuDecodedInst::Dest), // MADDq
    VuDecodedInst(VuInstruction::FD,   VuSpecialRegs::ACC,  VuInstruction::FS, VuInstruction::FT, VuDecodedInst::Bc), // MADDbc_0
    VuDecodedInst(VuInstruction::FD,   VuSpecialRegs::ACC,  VuInstruction::FS, VuInstruction::FT, VuDecodedInst::Bc), // MADDbc_1
    VuDecodedInst(VuInstruction::FD,   VuSpecialRegs::ACC,  VuInstruction::FS, VuInstruction::FT, VuDecodedInst::Bc), // MADDbc_2
    VuDecodedInst(VuInstruction::FD,   VuSpecialRegs::ACC,  VuInstruction::FS, VuInstruction::FT, VuDecodedInst::Bc), // MADDbc_3
    VuDecodedInst(VuSpecialRegs::ACC,  VuSpecialRegs::ACC,  VuInstruction::FS, VuInstruction::FT, VuDecodedInst::Dest), // MADDA
    VuDecodedInst(VuSpecialRegs::ACC,  VuSpecialRegs::ACC,  VuInstruction::FS, VuSpecialRegs::I,  VuDecodedInst::Dest), // MADDAi
    VuDecodedInst(VuSpecialRegs::ACC,  VuSpecialRegs::ACC,  VuInstruction::FS, VuSpecialRegs::Q,  VuDecodedInst::Dest), // MADDAq
    VuDecodedInst(VuSpecialRegs::ACC,  VuSpecialRegs::ACC,  VuInstruction::FS, VuInstruction::FT, VuDecodedInst::Bc), // MADDAbc_0
    VuDecodedInst(VuSpecialRegs::ACC,  VuSpecialRegs::ACC,  VuInstruction::FS, VuInstruction::FT, VuDecodedInst::Bc), // MADDAbc_1
    VuDecodedInst(VuSpecialRegs::ACC,  VuSpecialRegs::ACC,  VuInstruction::FS, VuInstruction::FT, VuDecodedInst::Bc), // MADDAbc_2
    VuDecodedInst(VuSpecialRegs::ACC,  VuSpecialRegs::ACC,  VuInstruction::FS, VuInstruction::FT, VuDecodedInst::Bc), // MADDAbc_3
    VuDecodedInst(VuInstruction::FD,   VuSpecialRegs::ACC,  VuInstruction::FS, VuInstruction::FT, VuDecodedInst::Dest), // MSUB
    VuDecodedInst(VuInstruction::FD,   VuSpecialRegs::ACC,  VuInstruction::FS, VuSpecialRegs::I,  VuDecodedInst::Dest), // MSUBi
    VuDecodedInst(VuInstruction::FD,   VuSpecialRegs::ACC,  VuInstruction::FS, VuSpecialRegs::Q,  VuDecodedInst::Dest), // MSUBq
    VuDecodedInst(VuInstruction::FD,   VuSpecialRegs::ACC,  VuInstruction::FS, VuInstruction::FT, VuDecodedInst::Bc), // MSUBbc_0
    VuDecodedInst(VuInstruction::FD,   VuSpecialRegs::ACC,  VuInstruction::FS, VuInstruction::FT, VuDecodedInst::Bc), // MSUBbc_1
    VuDecodedInst(VuInstruction::FD,   VuSpecialRegs::ACC,  VuInstruction::FS, VuInstruction::FT, VuDecodedInst::Bc), // MSUBbc_2
    VuDecodedInst(VuInstruction::FD,   VuSpecialRegs::ACC,  VuInstruction::FS, VuInstruction::FT, VuDecodedInst::Bc), // MSUBbc_3
    VuDecodedInst(VuSpecialRegs::ACC,  VuSpecialRegs::ACC,  VuInstruction::FS, VuInstruction::FT, VuDecodedInst::Dest), // MSUBA
    VuDecodedInst(VuSpecialRegs::ACC,  VuSpecialRegs::ACC,  VuInstruction::FS, VuSpecialRegs::I,  VuDecodedInst::Dest), // MSUBAi
    VuDecodedInst(VuSpecialRegs::ACC,  VuSpecialRegs::ACC,  VuInstruction::FS, VuSpecialRegs::Q,  VuDecodedInst::Dest), // MSUBAq
    VuDecodedInst(VuSpecialRegs::ACC,  VuSpecialRegs::ACC,  VuInstruction::FS, VuInstruction::FT, VuDecodedInst::Bc), // MSUBAbc_0
    VuDecodedInst(VuSpecialRegs::ACC,  VuSpecialRegs::ACC,  VuInstruction::FS, VuInstruction::FT, VuDecodedInst::Bc), // MSUBAbc_1
    VuDecodedInst(VuSpecialRegs::ACC,  VuSpecialRegs::ACC,  VuInstruction::FS, VuInstruction::FT, VuDecodedInst::Bc), // MSUBAbc_2
    VuDecodedInst(VuSpecialRegs::ACC,  VuSpecialRegs::ACC,  VuInstruction::FS, VuInstruction::FT, VuDecodedInst::Bc), // MSUBAbc_3
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Dest), // MAX
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuSpecialRegs::I,  std::nullopt,      VuDecodedInst::Dest), // MAXi
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Bc), // MAXbc_0
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Bc), // MAXbc_1
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Bc), // MAXbc_2
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Bc), // MAXbc_3
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Dest), // MINI
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuSpecialRegs::I,  std::nullopt,      VuDecodedInst::Dest), // MINIi
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Bc), // MINIbc_0
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Bc), // MINIbc_1
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Bc), // MINIbc_2
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Bc), // MINIbc_3
    VuDecodedInst(VuSpecialRegs::ACC,  VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Dest), // OPMULA
    VuDecodedInst(VuSpecialRegs::ACC,  VuSpecialRegs::ACC,  VuInstruction::FS, VuInstruction::FT, VuDecodedInst::Dest), // OPMSUB
    VuDecodedInst(std::nullopt,        std::nullopt,        std::nullopt,      std::nullopt,      VuDecodedInst::Dest), // NOP
    VuDecodedInst(VuInstruction::FT,   VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::Dest), // FTOI0
    VuDecodedInst(VuInstruction::FT,   VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::Dest), // FTOI4
    VuDecodedInst(VuInstruction::FT,   VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::Dest), // FTOI12
    VuDecodedInst(VuInstruction::FT,   VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::Dest), // FTOI15
    VuDecodedInst(VuInstruction::FT,   VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::Dest), // ITOF0
    VuDecodedInst(VuInstruction::FT,   VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::Dest), // ITOF4
    VuDecodedInst(VuInstruction::FT,   VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::Dest), // ITOF12
    VuDecodedInst(VuInstruction::FT,   VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::Dest), // ITOF15
    VuDecodedInst(VuSpecialRegs::CLIP, VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Dest), // CLIP
      
    // Lower Instructions
    VuDecodedInst(VuSpecialRegs::Q,    VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::FsfFtf), // DIV
    VuDecodedInst(VuSpecialRegs::Q,    VuInstruction::FT,   std::nullopt,      std::nullopt,      VuDecodedInst::FsfFtf), // SQRT
    VuDecodedInst(VuSpecialRegs::Q,    VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::FsfFtf), // RSQRT
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Int), // IADD
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::Int), // IADDI
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::Int), // IADDIU
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Int), // IAND
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Int), // IOR
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   VuInstruction::FT, std::nullopt,      VuDecodedInst::Int), // ISUB
    VuDecodedInst(VuInstruction::FD,   VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::Int), // ISUBI
    VuDecodedInst(VuInstruction::FT,   VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::Dest), // MOVE
    VuDecodedInst(VuInstruction::FT,   VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::Dest), // MFIR
    VuDecodedInst(VuInstruction::FT,   VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::FsfFtf), // MTIR
    VuDecodedInst(VuInstruction::FT,   VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::Dest), // MR32
    VuDecodedInst(VuInstruction::FT,   VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::Dest), // LQ
    VuDecodedInst(VuInstruction::FT,   VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::Dest), // LQD
    VuDecodedInst(VuInstruction::FT,   VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::Dest), // LQI
    VuDecodedInst(VuInstruction::FS,   VuInstruction::FT,   std::nullopt,      std::nullopt,      VuDecodedInst::Dest), // SQ
    VuDecodedInst(VuInstruction::FS,   VuInstruction::FT,   std::nullopt,      std::nullopt,      VuDecodedInst::Dest), // SQD
    VuDecodedInst(VuInstruction::FS,   VuInstruction::FT,   std::nullopt,      std::nullopt,      VuDecodedInst::Dest), // SQI
    VuDecodedInst(VuInstruction::FT,   VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::Int), // ILW
    VuDecodedInst(VuInstruction::FT,   VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::Int), // ISW
    VuDecodedInst(VuInstruction::FT,   VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::Int), // ILWR
    VuDecodedInst(VuInstruction::FT,   VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::Int), // ISWR
    VuDecodedInst(VuSpecialRegs::R,    VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::FsfFtf), // RINIT
    VuDecodedInst(VuInstruction::FT,   VuSpecialRegs::R,    std::nullopt,      std::nullopt,      VuDecodedInst::Dest), // RGET
    VuDecodedInst(VuInstruction::FT,   VuSpecialRegs::R,    std::nullopt,      std::nullopt,      VuDecodedInst::Dest), // RNEXT
    VuDecodedInst(VuSpecialRegs::R,    VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::FsfFtf), // RXOR
    VuDecodedInst(std::nullopt,        std::nullopt,        std::nullopt,      std::nullopt,      VuDecodedInst::Dest), // WAITQ
    VuDecodedInst(VuInstruction::FT,   VuSpecialRegs::SF,   std::nullopt,      std::nullopt,      VuDecodedInst::Int ), // FSAND
    VuDecodedInst(VuInstruction::FT,   VuSpecialRegs::SF,   std::nullopt,      std::nullopt,      VuDecodedInst::Int ), // FSEQ
    VuDecodedInst(VuInstruction::FT,   VuSpecialRegs::SF,   std::nullopt,      std::nullopt,      VuDecodedInst::Int ), // FSOR
    VuDecodedInst(VuSpecialRegs::SF,   std::nullopt,        std::nullopt,      std::nullopt,      VuDecodedInst::Int ), // FSSET
    VuDecodedInst(VuInstruction::FT,   VuSpecialRegs::MAC,  VuInstruction::FS, std::nullopt,      VuDecodedInst::Int ), // FMAND
    VuDecodedInst(VuInstruction::FT,   VuSpecialRegs::MAC,  VuInstruction::FS, std::nullopt,      VuDecodedInst::Int ), // FMEQ
    VuDecodedInst(VuInstruction::FT,   VuSpecialRegs::MAC,  VuInstruction::FS, std::nullopt,      VuDecodedInst::Int ), // FMOR
    VuDecodedInst(VuInstruction::FT,   VuSpecialRegs::CLIP, std::nullopt,      std::nullopt,      VuDecodedInst::Int ), // FCAND
    VuDecodedInst(VuInstruction::FT,   VuSpecialRegs::CLIP, std::nullopt,      std::nullopt,      VuDecodedInst::Int ), // FCEQ
    VuDecodedInst(VuInstruction::FT,   VuSpecialRegs::CLIP, std::nullopt,      std::nullopt,      VuDecodedInst::Int ), // FCOR
    VuDecodedInst(VuSpecialRegs::CLIP, std::nullopt,        std::nullopt,      std::nullopt,      VuDecodedInst::Int ), // FCSET
    VuDecodedInst(VuInstruction::FT,   VuSpecialRegs::CLIP, std::nullopt,      std::nullopt,      VuDecodedInst::Int ), // FCGET
    VuDecodedInst(VuSpecialRegs::PC,   VuInstruction::FT,   VuInstruction::FS, std::nullopt,      VuDecodedInst::Int ), // IBEQ
    VuDecodedInst(VuSpecialRegs::PC,   VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::Int ), // IBGEZ
    VuDecodedInst(VuSpecialRegs::PC,   VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::Int ), // IBGTZ
    VuDecodedInst(VuSpecialRegs::PC,   VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::Int ), // IBLEZ
    VuDecodedInst(VuSpecialRegs::PC,   VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::Int ), // IBLTZ
    VuDecodedInst(VuSpecialRegs::PC,   VuInstruction::FT,   VuInstruction::FS, std::nullopt,      VuDecodedInst::Int ), // IBNE
    VuDecodedInst(VuSpecialRegs::PC,   std::nullopt,        std::nullopt,      std::nullopt,      VuDecodedInst::Int ), // B
    VuDecodedInst(VuInstruction::FT,   std::nullopt,        std::nullopt,      std::nullopt,      VuDecodedInst::Int ), // BAL
    VuDecodedInst(VuSpecialRegs::PC,   std::nullopt,        std::nullopt,      std::nullopt,      VuDecodedInst::Int ), // J
    VuDecodedInst(VuInstruction::FT,   std::nullopt,        std::nullopt,      std::nullopt,      VuDecodedInst::Int ), // JALR
    VuDecodedInst(VuInstruction::FT,   VuSpecialRegs::P,    std::nullopt,      std::nullopt,      VuDecodedInst::Dest), // MFP
    VuDecodedInst(std::nullopt,        std::nullopt,        std::nullopt,      std::nullopt,      VuDecodedInst::Dest), // WAITP
    VuDecodedInst(VuSpecialRegs::P,    VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::Dest), // ESADD
    VuDecodedInst(VuSpecialRegs::P,    VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::Dest), // ERSADD
    VuDecodedInst(VuSpecialRegs::P,    VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::Dest), // ELENG
    VuDecodedInst(VuSpecialRegs::P,    VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::Dest), // ERLENG
    VuDecodedInst(VuSpecialRegs::P,    VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::Dest), // EATANxy
    VuDecodedInst(VuSpecialRegs::P,    VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::Dest), // EATANxz
    VuDecodedInst(VuSpecialRegs::P,    VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::Dest), // ESUM
    VuDecodedInst(VuSpecialRegs::P,    VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::FsfFtf), // ERCPR
    VuDecodedInst(VuSpecialRegs::P,    VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::FsfFtf), // ESQRT
    VuDecodedInst(VuSpecialRegs::P,    VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::FsfFtf), // ERSQRT
    VuDecodedInst(VuSpecialRegs::P,    VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::FsfFtf), // ESIN
    VuDecodedInst(VuSpecialRegs::P,    VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::FsfFtf), // EATAN
    VuDecodedInst(VuSpecialRegs::P,    VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::FsfFtf), // EEXP
    VuDecodedInst(std::nullopt,        VuInstruction::FS,   std::nullopt,      std::nullopt,      VuDecodedInst::Int), // XGKICK
    VuDecodedInst(VuInstruction::FT,   std::nullopt,        std::nullopt,      std::nullopt,      VuDecodedInst::Int), // XTOP
    VuDecodedInst(VuInstruction::FT,   std::nullopt,        std::nullopt,      std::nullopt,      VuDecodedInst::Int), // XITOP
};

VuInstructionDecoder::VuInstructionDecoder(VuInstruction lower, VuInstruction upper) :
    lower_inst(lower),
    upper_inst(upper),
    decoded_inst_lower(VU_DECODE_TABLE[lower.lower_lookup().impl_index]),
    decoded_inst_upper(VU_DECODE_TABLE[lower.upper_lookup().impl_index])
{
}

const VuDecodedInst& VuInstructionDecoder::decode_lower() const
{
    return decoded_inst_lower;
}

const VuDecodedInst& VuInstructionDecoder::decode_upper() const
{
    return decoded_inst_upper;
}

const VuInstruction& VuInstructionDecoder::get_upper_inst() const
{
    return upper_inst;
}

const VuInstruction& VuInstructionDecoder::get_lower_inst() const
{
    return lower_inst;
}

std::optional<int> VuInstructionDecoder::upper_dest() const
{
    if (decoded_inst_upper.dest_reg.has_value())
    {
        VuDecodeInfo value = decoded_inst_upper.dest_reg.value();
        if (Bitfield* ptr = std::get_if<Bitfield>(&value))
        {
            return ptr->extract_from(upper_inst.value);
        }
    }

    return std::nullopt;
}

std::optional<int> VuInstructionDecoder::upper_src(int index) const
{
    const std::optional<VuDecodeInfo>* src_regs[3] = { 
        &decoded_inst_upper.source_reg_1,
        &decoded_inst_upper.source_reg_2,
        &decoded_inst_upper.source_reg_3
    };

    if (src_regs[index]->has_value())
    {
        VuDecodeInfo value = src_regs[index]->value();
        if (Bitfield* ptr = std::get_if<Bitfield>(&value))
        {
            return ptr->extract_from(upper_inst.value);
        }
    }

    return std::nullopt;
}

std::optional<int> VuInstructionDecoder::lower_dest() const
{
    if (decoded_inst_lower.dest_reg.has_value())
    {
        VuDecodeInfo value = decoded_inst_lower.dest_reg.value();
        if (Bitfield* ptr = std::get_if<Bitfield>(&value))
        {
            return ptr->extract_from(lower_inst.value);
        }
    }

    return std::nullopt;
}

std::optional<int> VuInstructionDecoder::lower_src(int index) const
{
    const std::optional<VuDecodeInfo>* src_regs[3] = { 
        &decoded_inst_lower.source_reg_1,
        &decoded_inst_lower.source_reg_2,
        &decoded_inst_lower.source_reg_3
    };

    if (src_regs[index]->has_value())
    {
        VuDecodeInfo value = src_regs[index]->value();
        if (auto ptr = std::get_if<Bitfield>(&value))
        {
            return ptr->extract_from(lower_inst.value);
        }
    }

    return std::nullopt;
}
