#include <iostream>
#include <csignal>
#include <boost/filesystem.hpp>
#include <Macros.hpp>

#include <Core.hpp>

volatile bool DEBUG_RUN = true;

void signal_handler(int signal)
{
	DEBUG_RUN = false;
}

int main(int argc, char * argv[])
{
	std::cout << "Command line: ";
	for (int i = 0; i < argc; i++)
		std::cout << argv[i] << ", ";
	std::cout << std::endl << "Working directory: " << boost::filesystem::initial_path() << std::endl;
	std::signal(SIGINT, signal_handler);
	std::signal(SIGBREAK, signal_handler);

	try 
	{
		Core core(CoreOptions::make_default());

		try
		{
			while (DEBUG_RUN)
				core.run();
		}
		catch (std::runtime_error & e)
		{
			std::cout << "Core running fatal error: " << e.what() << std::endl;
		}

		core.dump_all_memory();
	}
	catch (...)
	{
		std::cout << "Core init/exit/internal fatal error" << std::endl;
	}

	std::cout << "Exiting" << std::endl;
	return 0;
}