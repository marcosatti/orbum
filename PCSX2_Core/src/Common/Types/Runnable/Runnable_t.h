#pragma once

#include <stdexcept>
#include <mutex>
#include <condition_variable>

#include "Common/Types/System_t.h"

/*
Interface class for a (repeatable) runnable task/component that can be optionally run on a separate thread.
Design follows from here:
- https://stackoverflow.com/questions/37019144/control-each-thread-by-its-own-condition-variable-c
- https://stackoverflow.com/questions/233127/how-can-i-propagate-exceptions-between-threads

Example usage (see VM.h/cpp for a more concrete example):

// Create a new thread.
thread = std::thread(&Runnable_t::runMain, runnable);

// Run the task, synchronise after.
runnable.notify(Runnable_t::Status::Run);
*** Do some other work on manager thread. ***
runnable.synchronise(); <-- Throws exception if one occurred while running.

// Stop the task and kill the thread.
runnable.notify(Runnable_t::Status::Stop);
thread.join();
*/
class Runnable_t
{
public:
    virtual ~Runnable_t() = default;

    enum Status
    {
        Run,
        Stop,
        Pause
    };

    /*
    Notify's this task and causes it to react to a changed state (ie: wake up if on another thread).
    */
    void notify(Status status);

    /*
    Performs a synchronisation with the calling thread by locking the internal mutex.
    Also checks the exception state and re-throws if not null.
    Intended to be used from a manager thread.
    */
    void synchronise();

    /*
    Main thread function, for use in a new thread.
    Runs the task (implemented by run()), and controls the runnable state.
    Intended to be used as the main function loop in a new thread.
    */
    void threadMain();
    
    /*
    Runs the task implemented. 
    */
    virtual void run() = 0;

#if defined(BUILD_DEBUG)
    /*
    Returns the context, used for debug.
    */
    virtual System_t getContext() const = 0;
#endif 

private:
    struct State_t
    {
        Status                  mStatus;
        std::exception_ptr      mException;
        std::mutex              mLock;
        std::condition_variable mCondVar;
    };
    State_t State;
};
