#pragma once

#include <functional>
#include <memory>
#include <utility>
#include <vector>

#include <boost/lockfree/queue.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

#include <cereal/archives/json.hpp>

#include <EnumMap.hpp>
#include <Macros.hpp>
#include <Queues.hpp>
#include <TaskExecutor.hpp>

#include "Controller/ControllerEvent.hpp"
#include "Controller/ControllerType.hpp"

#ifdef orbum_EXPORTS
#define CORE_API SHARED_EXPORT
#else
#define CORE_API SHARED_IMPORT
#endif

class RResources;
class CController;

/// Core runtime options.
struct CORE_API CoreOptions
{
    /// Contstructs default core options.
    /// See inside for details.
    static CoreOptions make_default();

    // Notes:
    // - For single-threaded operation, set number_workers to 1.
    // - us = microseconds.
    // - Boot ROM is required, other roms are optional -> empty string will cause it to not be loaded.
    // - Speed biases are a ratio, 1.0x is normal speed.

    /* Log dir path.             */ const char* logs_dir_path;
    /* Roms dir path.            */ const char* roms_dir_path;
    /* Memory dumps dir path.    */ const char* dumps_dir_path;
    /* Save states dir path.     */ const char* save_states_dir_path;
    /* Boot ROM file name.       */ const char* boot_rom_file_name;
    /* ROM1 file name.           */ const char* rom1_file_name;
    /* ROM2 file name.           */ const char* rom2_file_name;
    /* EROM file name.           */ const char* erom_file_name;

    /* Time slice per run in us. */ double time_slice_per_run_us;

    /* Number of worker threads. */ size_t number_workers;

    /* EE Core speed bias.       */ double system_bias_eecore;
    /* EE Dmac speed bias.       */ double system_bias_eedmac;
    /* EE Timers speed bias.     */ double system_bias_eetimers;
    /* EE Intc speed bias.       */ double system_bias_eeintc;
    /* GIF speed bias.           */ double system_bias_gif;
    /* IPU speed bias.           */ double system_bias_ipu;
    /* VIF speed bias.           */ double system_bias_vif;
    /* VU speed bias.            */ double system_bias_vu;
    /* IOP Core speed bias.      */ double system_bias_iopcore;
    /* IOP Dmac speed bias.      */ double system_bias_iopdmac;
    /* IOP Timers speed bias.    */ double system_bias_ioptimers;
    /* IOP Intc speed bias.      */ double system_bias_iopintc;
    /* CDVD speed bias.          */ double system_bias_cdvd;
    /* SPU2 speed bias.          */ double system_bias_spu2;
    /* GS Core speed bias.       */ double system_bias_gscore;
    /* CRTC speed bias.          */ double system_bias_crtc;
    /* SIO0 speed bias.          */ double system_bias_sio0;
    /* SIO2 speed bias.          */ double system_bias_sio2;
};

/// Exported Core class interface.
class CORE_API CoreApi
{
public:
    CoreApi(const CoreOptions& options);
    ~CoreApi();

    void run();
    void dump_all_memory() const;
    void save_state();

private:
    class Core* impl;
};

/// Entry point into all Orbum core emulation.
/// This is the manager for the PS2's execution.
/// Execution occurs in synchronised blocks - the core waits until all events
/// are processed by the controllers before dispatching any new ones.
class Core
{
public:
    static constexpr const char * DATETIME_FORMAT = "%Y-%m-%d_%H-%M-%S";
    
    Core(const CoreOptions& options);
    ~Core();

    /// Runs the core and updates the state.
    /// This is the main loop function.
    void run();

    /// Dumps all memory objects to the ./dumps folder.
    void dump_all_memory() const;

    /// Returns a reference to the logging functionality.
    static boost::log::sources::logger_mt& get_logger();

    /// Returns the runtime core options.
    const CoreOptions& get_options() const
    {
        return options;
    }

    /// Returns the task executor.
    TaskExecutor& get_task_executor() const
    {
        return *task_executor;
    }

    /// Returns a reference to the PS2 resources.
    RResources& get_resources() const
    {
        return *resources;
    }

    /// Enqueues a controller event that is dispatched on the next synchronised run.
    void enqueue_controller_event(const ControllerType::Type c_type, const ControllerEvent& event)
    {
        controller_event_queue.push({c_type, event});
    }

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

public:
    /// Save the current emulator state. JSON is used for debugging purposes
    /// (makes it easy to view state).
    /// TODO: for debugging only for now - some things are not serialized,
    /// but most of the important stuff is. 
    void save_state();
};
