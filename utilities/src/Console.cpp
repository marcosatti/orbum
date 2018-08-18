#include "Console.hpp"
#include "Macros.hpp"

#if defined(ENV_WINDOWS)
#define NOMINMAX
#include <Windows.h>
#elif defined(ENV_UNIX)
#include <iostream>
#endif

void print_title(const std::string title)
{
#if defined(ENV_WINDOWS)
    SetConsoleTitle(title.c_str());
#elif defined(ENV_UNIX)
    std::cout << "\033]0;" << title << "\007";
#endif
}