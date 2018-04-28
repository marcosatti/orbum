#pragma once

#include <utility>
#include <memory>
#include <functional>
#include <vector>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/lockfree/queue.hpp>
#include <Macros.hpp>
#include <EnumMap.hpp>
#include <Queues.hpp>
#include <TaskExecutor.hpp>

#include "Controller/ControllerEvent.hpp"
#include "Controller/ControllerType.hpp"

struct RResources;
class CController;

/// Core runtime options.
struct SHARED_EXPORT CoreOptions
{
	/// Contstructs default core options.
	/// See inside for details.
	static CoreOptions make_default();

	// Notes: 
    // For single-threaded operation, set number_workers to 1.
    // us = microseconds.
	// Boot ROM is required, other roms are optional -> empty string will cause it to not be loaded.

	/* Log dir path.             */ std::string logs_dir_path;
	/* Roms dir path.            */ std::string roms_dir_path;
	/* Memory dumps dir path.    */ std::string dumps_dir_path;
	/* Boot ROM file name.       */ std::string boot_rom_file_name;
	/* ROM1 file name.           */ std::string rom1_file_name;
	/* ROM2 file name.           */ std::string rom2_file_name;
	/* EROM file name.           */ std::string erom_file_name;

	/* Time slice per run in us. */ double time_slice_per_run_us;

    /* Number of worker threads .*/ size_t number_workers;

	/* System speed biases.      */ EnumMap<ControllerType::Type, double> system_biases;
};

/// Entry point into all Orbum core emulation.
/// This is the manager for the PS2's execution. 
/// Execution occurs in synchronised blocks - the core waits until all events
/// are processed by the controllers before dispatching any new ones.
class SHARED_EXPORT Core
{
public:
	Core(const CoreOptions & options);
	~Core();

	/// Returns a reference to the logging functionality.
	static boost::log::sources::logger_mt & get_logger()
	{
		return logger;
	}

	/// Returns the runtime core options.
	const CoreOptions & get_options() const
	{
		return options;
	}

	/// Returns the task executor.
	TaskExecutor & get_task_executor() const
	{
		return *task_executor;
	}

	/// Returns a reference to the PS2 resources.
	RResources & get_resources() const
	{
		return *resources;
	}

	/// Enqueues a controller event that is dispatched on the next synchronised run.
	void enqueue_controller_event(const ControllerType::Type c_type, const ControllerEvent & event)
	{
		controller_event_queue.push({ c_type, event });
	}

	/// Runs the core and updates the state.
	/// This is the main loop function.
	void run();

	/// Dumps all memory objects to the ./dumps folder.
	void dump_all_memory() const;

private:	
	/// Initialises logging using options.
	void init_logging();

	/// Logging source.
	static boost::log::sources::logger_mt logger;

	/// Core options.
	CoreOptions options;

	/// PS2 Resources.
	std::unique_ptr<RResources> resources;

	/// Controller Event handling queues.
	struct EventEntry
	{ 
		ControllerType::Type t; 
		ControllerEvent e;
	};
	MpmcQueue<EventEntry, 128> controller_event_queue;

	/// Controllers.
	EnumMap<ControllerType::Type, std::unique_ptr<CController>> controllers;
	
	/// Task executor.
	std::unique_ptr<TaskExecutor> task_executor;
};

