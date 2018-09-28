#pragma once

#include <variant>

#include "Common/Types/Bitfield.hpp"
#include "Resources/Ee/Vpu/Vu/VuInstruction.hpp"

enum class VuSpecialRegs 
{
    ACC,
    CLIP,
    I,
    P,
    PC, // program counter
    Q,
    R,
    SF, // sticky flag
    MAC // mac flag
};

typedef std::variant<Bitfield, VuSpecialRegs> VuDecodeInfo;

struct VuDecodedInst
{
    // Used for storing the field specifier (dest, fsf/ftf, bc, etc..)
    // Note: Integer GPRs do not have a field.
    enum FieldSpecifier
    {
        FsfFtf = 0,
        Dest = 1,
        Bc = 2,
        Int = 3,
    };

    // Default constructor
    VuDecodedInst() :
        dest_reg(std::nullopt),
        source_reg_1(std::nullopt),
        source_reg_2(std::nullopt),
        source_reg_3(std::nullopt),
        field(FieldSpecifier::Dest)
    {
    }

    VuDecodedInst(
        std::optional<VuDecodeInfo> dest,
        std::optional<VuDecodeInfo> src_1,
        std::optional<VuDecodeInfo> src_2,
        std::optional<VuDecodeInfo> src_3,
        int dest_field
    ) :
        dest_reg(dest),
        source_reg_1(src_1),
        source_reg_2(src_2),
        source_reg_3(src_3),
        field(dest_field)
    {
    }

    std::optional<VuDecodeInfo> dest_reg;
    std::optional<VuDecodeInfo> source_reg_1;
    std::optional<VuDecodeInfo> source_reg_2;
    std::optional<VuDecodeInfo> source_reg_3;
    
    int field;
};

class VuInstructionDecoder
{
public:
    VuInstructionDecoder(const VuInstruction lower, const VuInstruction upper);

    const VuDecodedInst& decode_lower() const;
    const VuDecodedInst& decode_upper() const;

    const VuInstruction& get_lower_inst() const;
    const VuInstruction& get_upper_inst() const;

    std::optional<int> lower_dest() const;
    std::optional<int> upper_dest() const;

    std::optional<int> lower_src(int index) const;
    std::optional<int> upper_src(int index) const;

private:
    VuInstruction lower_inst;
    VuInstruction upper_inst;

    VuDecodedInst decoded_inst_lower;
    VuDecodedInst decoded_inst_upper;
};
