#include "Common/Types/Register/SizedDwordRegister.hpp"

class IpuRegister_Cmd : public SizedDwordRegister 
{
public:
    static constexpr Bitfield BUSY = Bitfield(63, 63);
    static constexpr Bitfield CODE = Bitfield(28, 31);
    static constexpr Bitfield DATA = Bitfield(0, 31);
    static constexpr Bitfield OPTION = Bitfield(0, 27);

    // Note: I actually preferred the is_* methods to be `const`.

    /// When reading, bit 63 serves as the BUSY bit, which denotes the progress of
    /// the decoding process. When it is set to 1, the decoding process is still
    /// being executed.
    /// Refer to EE User's Manual pg 183.
    bool is_busy();
    void set_busy();
};
