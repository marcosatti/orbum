#include <stdexcept>

#include "Resources/Iop/Timers/IopTimersUnits.hpp"

constexpr bool is_32b_count_mode(const int unit_id)
{
    if (unit_id >= 0 && unit_id < 3)
        return false;
    else if (unit_id >= 3 && unit_id < 6)
        return true;
    else
        throw std::runtime_error("Invalid IOP timer unit id specified.");
}

IopTimersUnit_Base::IopTimersUnit_Base(const int unit_id) :
    unit_id(unit_id),
    count(is_32b_count_mode(unit_id))
{
}