#include <stdexcept>
#include <thread>
#include <boost/log/core.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/format.hpp>
#include <boost/filesystem.hpp>
#include <chrono>
#include <Console.hpp>
#include <Macros.hpp>

#include "Core.hpp"

#include "Controller/Gs/Crtc/CCrtc.hpp"
#include "Controller/Gs/Core/CGsCore.hpp"
#include "Controller/Cdvd/CCdvd.hpp"
#include "Controller/Spu2/CSpu2.hpp"
#include "Controller/Iop/Dmac/CIopDmac.hpp"
#include "Controller/Iop/Intc/CIopIntc.hpp"
#include "Controller/Iop/Timers/CIopTimers.hpp"
#include "Controller/Iop/Sio0/CSio0.hpp"
#include "Controller/Iop/Sio2/CSio2.hpp"
#include "Controller/Ee/Vpu/Vif/CVif.hpp"
#include "Controller/Ee/Vpu/Vu/Interpreter/CVuInterpreter.hpp"
#include "Controller/Ee/Ipu/CIpu.hpp"
#include "Controller/Ee/Gif/CGif.hpp"
#include "Controller/Ee/Intc/CEeIntc.hpp"
#include "Controller/Ee/Timers/CEeTimers.hpp"
#include "Controller/Ee/Dmac/CEeDmac.hpp"
#include "Controller/Iop/Core/Interpreter/CIopCoreInterpreter.hpp"
#include "Controller/Ee/Core/Interpreter/CEeCoreInterpreter.hpp"

#include "Resources/RResources.hpp"

boost::log::sources::logger_mt Core::logger;

CoreOptions CoreOptions::make_default()
{
    return CoreOptions 
    {
		"./logs/",
		"./bios/",
		"./dumps/",
        "scph10000.bin",
        "",
        "",
        "",
        200,
        3, //std::thread::hardware_concurrency() - 1,
		{2.0, 1.0, 1.0, 1.0, // TODO: while in development, cheat for now :)
		 1.0, 1.0, 1.0, 1.0,
		 2.0, 1.0, 1.0, 1.0, 
		 1.0, 1.0, 1.0, 1.0, 
		 1.0, 1.0 }
        // EnumMap<ControllerType::Type, double>(1.0)
    };
}

Core::Core(const CoreOptions & options) :
    options(options)
{
	// Initialise logging.
	init_logging();

	BOOST_LOG(get_logger()) << "Core initialising... please wait";

	// Initialise resources.
	resources = std::make_unique<RResources>();
	initialise_resources(resources);

	// Initialise roms (boot_rom (required), rom1, rom2, erom).
	get_resources().boot_rom.read_from_file(options.roms_dir_path + options.boot_rom_file_name, Constants::EE::ROM::SIZE_BOOT_ROM);
	if (!options.rom1_file_name.empty())
		get_resources().rom1.read_from_file(options.roms_dir_path + options.rom1_file_name, Constants::EE::ROM::SIZE_ROM1);
	if (!options.rom2_file_name.empty())
		get_resources().rom2.read_from_file(options.roms_dir_path + options.rom2_file_name, Constants::EE::ROM::SIZE_ROM2);
	if (!options.erom_file_name.empty())
		get_resources().erom.read_from_file(options.roms_dir_path + options.erom_file_name, Constants::EE::ROM::SIZE_EROM);

    // Initialise controllers.
    controllers[ControllerType::Type::EeCore] = std::make_unique<CEeCoreInterpreter>(this);
    controllers[ControllerType::Type::EeDmac] = std::make_unique<CEeDmac>(this);
    controllers[ControllerType::Type::EeTimers] = std::make_unique<CEeTimers>(this);
    controllers[ControllerType::Type::EeIntc] = std::make_unique<CEeIntc>(this);
    controllers[ControllerType::Type::Gif] = std::make_unique<CGif>(this);
    controllers[ControllerType::Type::Ipu] = std::make_unique<CIpu>(this);
    controllers[ControllerType::Type::Vif] = std::make_unique<CVif>(this);
    controllers[ControllerType::Type::Vu] = std::make_unique<CVuInterpreter>(this);
    controllers[ControllerType::Type::IopCore] = std::make_unique<CIopCoreInterpreter>(this);
    controllers[ControllerType::Type::IopDmac] = std::make_unique<CIopDmac>(this);
    controllers[ControllerType::Type::IopTimers] = std::make_unique<CIopTimers>(this);
    controllers[ControllerType::Type::IopIntc] = std::make_unique<CIopIntc>(this);
    controllers[ControllerType::Type::Cdvd] = std::make_unique<CCdvd>(this);
    controllers[ControllerType::Type::Spu2] = std::make_unique<CSpu2>(this);
    controllers[ControllerType::Type::GsCore] = std::make_unique<CGsCore>(this);
    controllers[ControllerType::Type::Crtc] = std::make_unique<CCrtc>(this);
    controllers[ControllerType::Type::Sio0] = std::make_unique<CSio0>(this);
    controllers[ControllerType::Type::Sio2] = std::make_unique<CSio2>(this);

    // Task executor.
    task_executor = std::make_unique<TaskExecutor>(options.number_workers);

	BOOST_LOG(get_logger()) << "Core initialised";
}

Core::~Core()
{
	BOOST_LOG(get_logger()) << "Core shutting down";
}

const CoreOptions & Core::get_options() const
{
    return options;
}

RResources & Core::get_resources() const
{
    return *resources;
}

void Core::run()
{
#if defined(BUILD_DEBUG)
    static double DEBUG_TIME_ELAPSED = 0.0;
    static double DEBUG_TIME_LOGGED = 0.0;
	static std::chrono::high_resolution_clock::time_point DEBUG_T1 = std::chrono::high_resolution_clock::now();
    if ((DEBUG_TIME_ELAPSED - DEBUG_TIME_LOGGED) > 0.01e6)
    {
		const std::chrono::high_resolution_clock::time_point DEBUG_T2 = std::chrono::high_resolution_clock::now();
		const std::chrono::duration<double, std::micro> duration = DEBUG_T2 - DEBUG_T1;
        
        const std::string info = str(boost::format("Emulation time elapsed: %.3f (%.4fx)") 
			% (DEBUG_TIME_ELAPSED / 1e6)
			% ((DEBUG_TIME_ELAPSED - DEBUG_TIME_LOGGED) / duration.count()));

		BOOST_LOG(get_logger()) << info;
		//print_title(info);

        DEBUG_TIME_LOGGED = DEBUG_TIME_ELAPSED;
		DEBUG_T1 = DEBUG_T2;
    }
    DEBUG_TIME_ELAPSED += options.time_slice_per_run_us;
#endif

    // Enqueue time events (always done on each run).
    auto event = ControllerEvent{ ControllerEvent::Type::Time, options.time_slice_per_run_us };
    for (int i = 0; i < static_cast<int>(ControllerType::Type::COUNT); i++) // TODO: find better syntax..
    {
        auto controller = static_cast<ControllerType::Type>(i);
		enqueue_controller_event(controller, event);
    }

    // Package events into tasks and send to workers.
	EventEntry entry;
    while (controller_event_queue.try_pop(entry))
    {
        auto task = [this, entry] ()
        {
			if (controllers[entry.t])
				controllers[entry.t]->handle_event_marshall_(entry.e);
        };

        task_executor->enqueue_task(task);
    }

    // Dispatch all tasks and wait for resynchronisation.
    task_executor->dispatch();
	task_executor->wait_for_idle();

#if defined(BUILD_DEBUG)
    if (!task_executor->task_sync.running_task_queue.is_empty() || task_executor->task_sync.thread_busy_counter.busy_counter)
        throw std::runtime_error("Task queue was not empty!");
#endif
}

void Core::enqueue_controller_event(const ControllerType::Type c_type, const ControllerEvent & event)
{
	EventEntry qe{ c_type, event };
	controller_event_queue.push(qe);
}

TaskExecutor & Core::get_task_executor() const
{
	return *task_executor;
}

boost::log::sources::logger_mt & Core::get_logger()
{
	return logger;
}

void Core::dump_all_memory() const
{
	boost::filesystem::create_directory(options.dumps_dir_path);
	get_resources().ee.main_memory.write_to_file(options.dumps_dir_path + "End_Dump_EE.bin");
	get_resources().iop.main_memory.write_to_file(options.dumps_dir_path + "End_Dump_IOP.bin");
	get_resources().spu2.main_memory.write_to_file(options.dumps_dir_path + "End_Dump_SPU2.bin");
	get_resources().cdvd.nvram.memory.write_to_file(options.dumps_dir_path + "End_Dump_CDVD_NVRAM.bin");
	BOOST_LOG(get_logger()) << "Dumped all memory objects ok";
}

void Core::init_logging()
{
	boost::filesystem::create_directory(options.logs_dir_path);
	boost::log::add_common_attributes();
	boost::log::add_file_log
	(
		boost::log::keywords::file_name = options.logs_dir_path + "liborbum_%Y-%m-%d_%H-%M-%S.log",
		boost::log::keywords::format = "[%TimeStamp%]: %Message%"
	);
	boost::log::add_console_log
	(
		std::cout,
		boost::log::keywords::format = "[%TimeStamp%]: %Message%"
	);
}