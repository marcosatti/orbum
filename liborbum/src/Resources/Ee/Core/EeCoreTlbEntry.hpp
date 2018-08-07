#pragma once

/// Custom Mask type, provides useful cached values when constructed.
struct Mask
{
    Mask(const uword pagemask = 0) :
        pagemask(pagemask),
        evenodd_mask(1 << 12),
        tlb_mask(0xFFFFE000)
    {
        // Determine evenodd index.
        // Values have been precalculated.
        switch (pagemask & 0xFFF)
        {
        case 0x0: // 4KB
            evenodd_mask = (1 << 12);
            break;
        case 0x3: // 16 KB
            evenodd_mask = (1 << 14);
            break;
        case 0xF: // 64 KB
            evenodd_mask = (1 << 16);
            break;
        case 0x3F: // 256 KB
            evenodd_mask = (1 << 18);
            break;
        case 0xFF: // 1 MB
            evenodd_mask = (1 << 20);
            break;
        case 0x3FF: // 4 MB
            evenodd_mask = (1 << 22);
            break;
        case 0xFFF: // 16 MB
            evenodd_mask = (1 << 24);
            break;
        default:
            throw std::runtime_error("Invalid mask supplied to TLB entry");
        }

        // Calculate mask for use in TLB.
        tlb_mask = 0xFE000000 | (((~pagemask) & 0xFFF) << 13);
    }

    uword pagemask;
    uword evenodd_mask;
    uword tlb_mask;

public:
    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(
            CEREAL_NVP(pagemask),
            CEREAL_NVP(evenodd_mask),
            CEREAL_NVP(tlb_mask)
        );
    }
};

/// EE Core TLB entry, similar to a MIPS TLB entry.
/// A TLB entry is heavily related to the COP0 registers
/// Entry{Hi, Lo0, Lo1}, PageMask and others.
/// See EE Core Users Manual page 120 - 123 about the TLB.
/// For the internal struct array below, index 0 corresponds to the Even
/// infomation, and index 1 correponds to the Odd information.
struct EeCoreTlbEntry
{
    Mask mask;
    uword vpn2;
    bool g;
    ubyte asid;
    bool s;

    struct
    {
        uword pfn;
        bool c;
        bool d;
        bool v;

        template<class Archive>
        void serialize(Archive & archive)
        {
            archive(
                CEREAL_NVP(pfn),
                CEREAL_NVP(c),
                CEREAL_NVP(d),
                CEREAL_NVP(v)
            );
        }
    } physical_info[2]; // Index 0 = Even, index 1 = Odd.

    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(
            CEREAL_NVP(mask),
            CEREAL_NVP(vpn2),
            CEREAL_NVP(g),
            CEREAL_NVP(asid),
            CEREAL_NVP(s),
            CEREAL_NVP(physical_info)
        );
    }
};