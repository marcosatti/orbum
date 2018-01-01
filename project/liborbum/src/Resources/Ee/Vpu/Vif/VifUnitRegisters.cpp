#include "Resources/Ee/Vpu/Vif/VifUnitRegisters.hpp"

bool VifUnitRegister_Stat::is_stalled()
{
    uword value = read_uword();

    if (VSS.extract_from(value)
        || VFS.extract_from(value)
        || VIS.extract_from(value)
        || INT.extract_from(value)
        || ER0.extract_from(value)
        || ER1.extract_from(value))
    {
        return true;
    }

    return false;
}