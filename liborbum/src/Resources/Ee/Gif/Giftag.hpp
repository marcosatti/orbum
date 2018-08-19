#pragma once

#include <stdexcept>

#include "Common/Types/Bitfield.hpp"
#include "Common/Types/Primitive.hpp"

class Giftag
{
public:
    static constexpr Bitfield NLOOP = Bitfield(0, 15);
    static constexpr Bitfield EOP = Bitfield(15, 1);
    static constexpr Bitfield PRE = Bitfield(46, 1);
    static constexpr Bitfield PRIM = Bitfield(47, 11);
    static constexpr Bitfield FLG = Bitfield(58, 2);
    static constexpr Bitfield NREG = Bitfield(60, 4);
    static constexpr Bitfield REGS0 = Bitfield(64, 4);
    static constexpr Bitfield REGS1 = Bitfield(68, 4);
    static constexpr Bitfield REGS2 = Bitfield(72, 4);
    static constexpr Bitfield REGS3 = Bitfield(76, 4);
    static constexpr Bitfield REGS4 = Bitfield(80, 4);
    static constexpr Bitfield REGS5 = Bitfield(84, 4);
    static constexpr Bitfield REGS6 = Bitfield(88, 4);
    static constexpr Bitfield REGS7 = Bitfield(92, 4);
    static constexpr Bitfield REGS8 = Bitfield(96, 4);
    static constexpr Bitfield REGS9 = Bitfield(100, 4);
    static constexpr Bitfield REGS10 = Bitfield(104, 4);
    static constexpr Bitfield REGS11 = Bitfield(108, 4);
    static constexpr Bitfield REGS12 = Bitfield(112, 4);
    static constexpr Bitfield REGS13 = Bitfield(116, 4);
    static constexpr Bitfield REGS14 = Bitfield(120, 4);
    static constexpr Bitfield REGS15 = Bitfield(124, 4);

    enum DataFormat
    {
        Packed,
        Reglist,
        Image,
        Disabled // Disabled means the same operation mode as Image.
    };

    Giftag(const uqword tag) :
        tag(tag)
    {
    }

    int nloop() const
    {
        return NLOOP.extract_from<int>(tag);
    }

    bool eop() const
    {
        return EOP.extract_from<int>(tag) > 0;
    }

    bool pre() const
    {
        return EOP.extract_from<int>(tag) > 0;
    }

    DataFormat flg() const
    {
        switch (FLG.extract_from<int>(tag))
        {
        case 0:
            return Packed;
        case 1:
            return Reglist;
        case 2:
            return Image;
        case 3:
            return Disabled;
        default:
            throw std::runtime_error("Unknown Giftag data format");
        }
    }

    int nreg() const
    {
        int nreg = NREG.extract_from<int>(tag);

        if (nreg >= 16 || nreg < 0)
            throw std::runtime_error("Unknown nreg value");

        return (nreg == 0) ? 16 : nreg;
    }

    int regs0() const
    {
        return REGS0.extract_from<int>(tag);
    }

    int regs1() const
    {
        return REGS1.extract_from<int>(tag);
    }

    int regs2() const
    {
        return REGS2.extract_from<int>(tag);
    }

    int regs3() const
    {
        return REGS3.extract_from<int>(tag);
    }

    int regs4() const
    {
        return REGS4.extract_from<int>(tag);
    }

    int regs5() const
    {
        return REGS5.extract_from<int>(tag);
    }

    int regs6() const
    {
        return REGS6.extract_from<int>(tag);
    }

    int regs7() const
    {
        return REGS7.extract_from<int>(tag);
    }

    int regs8() const
    {
        return REGS8.extract_from<int>(tag);
    }

    int regs9() const
    {
        return REGS9.extract_from<int>(tag);
    }

    int regs10() const
    {
        return REGS10.extract_from<int>(tag);
    }

    int regs11() const
    {
        return REGS11.extract_from<int>(tag);
    }

    int regs12() const
    {
        return REGS12.extract_from<int>(tag);
    }

    int regs13() const
    {
        return REGS13.extract_from<int>(tag);
    }

    int regs14() const
    {
        return REGS14.extract_from<int>(tag);
    }

    int regs15() const
    {
        return REGS15.extract_from<int>(tag);
    }

private:
    uqword tag;
};