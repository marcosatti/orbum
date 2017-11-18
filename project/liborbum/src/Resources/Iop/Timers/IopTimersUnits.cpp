#include "Resources/Iop/Timers/IopTimersUnits.hpp"

IopTimersUnit::IopTimersUnit(const int timer_id) :
    count(timer_id),
    mode(timer_id)
{
}