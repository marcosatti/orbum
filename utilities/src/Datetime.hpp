#include <string>
#include <ctime>

/// Returns a string of the given date and time with the specified format string.
/// Defaults to the current time.
std::string datetime_fmt(const char* format, const std::time_t datetime = std::time(nullptr));
