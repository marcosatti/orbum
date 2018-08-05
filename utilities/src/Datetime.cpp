#include "Datetime.hpp"

std::string datetime_fmt(const char* format, const std::time_t datetime)
{
    char buf[100];

    if (!std::strftime(buf, sizeof(buf), format, std::localtime(&datetime))) 
        throw std::runtime_error("Failed to print current time");

    return std::string(buf);
}