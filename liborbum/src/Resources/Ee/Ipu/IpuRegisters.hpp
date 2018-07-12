#include "Common/Types/Register/SizedDwordRegister.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"

class IpuRegister_Cmd : public SizedDwordRegister 
{
public:
    static constexpr Bitfield BUSY = Bitfield(63, 1);
    static constexpr Bitfield CODE = Bitfield(28, 4);
    static constexpr Bitfield DATA = Bitfield(0, 32);
    static constexpr Bitfield OPTION = Bitfield(0, 28);

    // Note: I actually preferred the is_* methods to be `const`.

    /// When reading, bit 63 serves as the BUSY bit, which denotes the progress of
    /// the decoding process. When it is set to 1, the decoding process is still
    /// being executed.
    /// Refer to EE User's Manual pg 183.
    bool is_busy();
    void set_busy();
};

class IpuRegister_Top : public SizedDwordRegister 
{
public:
    static constexpr Bitfield BSTOP = Bitfield(0, 32);
    static constexpr Bitfield BUSY  = Bitfield(63, 1);

    /// BSTOP field is ineffective if BUSY is set to 1.
    bool is_busy();
    void set_busy();
};

class IpuRegister_Ctrl : public SizedWordRegister 
{
public:
    static constexpr Bitfield IFC = Bitfield(0, 4);
    static constexpr Bitfield OFC = Bitfield(4, 4);
    static constexpr Bitfield CBP = Bitfield(8, 6);
    static constexpr Bitfield ECD = Bitfield(14, 1);
    static constexpr Bitfield SCD = Bitfield(15, 1);
    static constexpr Bitfield IDP = Bitfield(16, 2);
    static constexpr Bitfield AS  = Bitfield(20, 1);
    static constexpr Bitfield IVF = Bitfield(21, 1);
    static constexpr Bitfield QST = Bitfield(22, 1);
    static constexpr Bitfield MP1 = Bitfield(23, 1);
    static constexpr Bitfield PCT = Bitfield(24, 3);
    static constexpr Bitfield RST = Bitfield(30, 1);
    static constexpr Bitfield BUSY = Bitfield(31, 1);

    bool is_busy();
    void set_busy();
};