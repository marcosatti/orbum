#include "Resources/Ee/Timers/EeTimersUnits.hpp"

EeTimersUnit::EeTimersUnit() :
    unit_id(nullptr),
    count(nullptr),
    mode(nullptr),
    compare(nullptr),
    hold(nullptr)
{
}

EeTimersUnit_Base::EeTimersUnit_Base(const int unit_id) :
    unit_id(unit_id)
{
}

EeTimersUnit_Hold::EeTimersUnit_Hold(const int unit_id) :
    EeTimersUnit_Base(unit_id)
{
}