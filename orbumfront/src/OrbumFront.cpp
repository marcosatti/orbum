#include <cstdio>
#include <csignal>
#include <iostream>

#include <boost/filesystem.hpp>

#include <Core.hpp>
#include <Macros.hpp>

bool quit = false;
volatile bool show_main_menu = false;

void signal_handler(int signal)
{
    show_main_menu = true;
    
    // This is a win32 specific thing? Otherwise subsequent signals are not caught...
    // https://stackoverflow.com/questions/43959514/why-the-second-sigint-cant-be-captured-on-win32
    std::signal(SIGINT, signal_handler);
    std::signal(SIGBREAK, signal_handler);
}

void main_menu(CoreApi& core) 
{
    char c = '\0';
    do
    {
        switch (c)
        {
        case '1':
        case 's':
        {
            puts("Saving state...");
            core.save_state();
            puts("Saved state ok");
            break;
        }
        case '2':
        case 'd':
        {
            puts("Dumping memory...");
            core.dump_all_memory();
            puts("Dumped memory ok");
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

        puts("Orbum main menu");
        puts("  1. (s)ave state (json)");
        puts("  2. (d)ump all memory (binary)");
        puts("  3. (c)ontinue");
        puts("  4. (q)uit");
        fputs("Select an option: ", stdout);

    } while ((c = getchar()));

exit_menu:
    puts("");
    show_main_menu = false;
}

int main(int argc, char* argv[])
{
    std::cout << "Command line: ";
    for (int i = 0; i < argc; i++)
        std::cout << argv[i] << ", ";

    std::cout << std::endl
              << "Working directory: " << boost::filesystem::initial_path() << std::endl;

    std::signal(SIGINT, signal_handler);
    std::signal(SIGBREAK, signal_handler);

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