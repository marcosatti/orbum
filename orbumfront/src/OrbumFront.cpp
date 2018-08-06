#include <csignal>
#include <iostream>
#include <string>

#include <boost/filesystem.hpp>

#include <Core.hpp>
#include <Macros.hpp>

#if defined(WIN32)
#include <windows.h>
#endif

bool quit = false;
volatile bool show_main_menu = false;

#if defined(WIN32)
BOOL WINAPI console_handler(DWORD signal) 
{
    show_main_menu = true;
    return TRUE;
}
#else
void signal_handler(int signal)
{
    show_main_menu = true;
}
#endif

void main_menu(CoreApi& core);

int main(int argc, char* argv[])
{
    std::cout << "Command line: ";
    for (int i = 0; i < argc; i++)
        std::cout << argv[i] << ", ";

    std::cout << std::endl
              << "Working directory: " << boost::filesystem::initial_path() << std::endl;

#if defined(WIN32)
    SetConsoleCtrlHandler(console_handler, TRUE);
#else
    std::signal(SIGINT, signal_handler);
#endif

    try
    {
        CoreApi core(CoreOptions::make_default());

        try
        {
            while (!quit)
            {
                core.run();
                if (show_main_menu)
                    main_menu(core);
            }
        }
        catch (const std::runtime_error& e)
        {
            std::cout << "Core running fatal error: " << e.what() << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Core init/exit/internal fatal error: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Core init/exit/internal fatal error" << std::endl;
    }

    std::cout << "Exiting" << std::endl;
    return 0;
}

void main_menu(CoreApi& core) 
{
    while (true)
    {
        std::cout << "\nOrbum main menu\n"
                  << "  1. (s)ave state (json)\n"
                  << "  2. (d)ump all memory (binary)\n"
                  << "  3. (c)ontinue\n"
                  << "  4. (q)uit\n"
                  << "\nSelect an option: "
                  << std::flush;

        char c = '\0';
        try
        {
            std::string line;
            std::getline(std::cin, line);
            c = line.at(0);
        }
        catch (const std::out_of_range&)
        {
            std::cout << "Invalid option" << std::endl;
            continue;
        }

        switch (c)
        {
        case '1':
        case 's':
        {
            std::cout << "Saving state..." << std::endl;
            core.save_state();
            std::cout << "Saved state ok" << std::endl;
            break;
        }
        case '2':
        case 'd':
        {
            std::cout << "Dumping memory..." << std::endl;
            core.dump_all_memory();
            std::cout << "Dumped memory ok" << std::endl;
            break;
        }
        case '3':
        case 'c':
        {
            goto exit_menu;
        }
        case '4':
        case 'q':
        {
            quit = true;
            goto exit_menu;
        }
        }

    }

exit_menu:
    std::cout << std::endl;
    show_main_menu = false;
}
