#pragma once

#include <mutex>
#include <condition_variable>
#include <memory>
#include <exception>
#include <thread>

#include "Common/Types/Util/Runnable_t.h"

class ThreadedRunnable_t
{
public:
    enum class Command
    {
        None,
        Run,
        Stop
    };
    enum class Status
    {
        Running,
        Paused,
        Stopping,
        Stopped
    };

    /*
    Constructs a new thread with the runnable object, waits for the 'Paused' state before returning.
    */
    ThreadedRunnable_t(const std::shared_ptr<Runnable_t> & runnable);

	/*
	Deconstructs this object by notifying 'Stop' and waits for the thread to join before returning.
	*/
	~ThreadedRunnable_t();

    /*
    Manager function to notify this thread of a command, and wait for it to be received.
    When successfully sent status, function returns, never earlier.
    */
    void notify(const Command command);

    /*
    Manager function to check for a command to complete, and if needed wait until it is done.
    When successfully received status, function returns, never earlier.
	If the thread encountered an exception, it will be rethrown from here.
    */
    void synchronise(const Status status);

private:
	/*
	Main thread function, calls Runnable_t::run() on the Run command until the Stop command is given.
	If an exception occurs while running, it will be propagated to the manager upon calling synchronise().
	*/
	void main();

    /*
    Runnable state, used to communicate between the manager and this runnable.
    */
    struct State_t
    {
        Status mStatus;
        Command mCommand;
        std::mutex mMutex;
        std::condition_variable mCVStatus;
        std::condition_variable mCVCommand;
		std::exception_ptr mExceptionPtr;
    };
    State_t mState;

	/*
	Runnable object that provides run().
	*/
	std::shared_ptr<Runnable_t> mRunnable;

	/*
	Thread object, created with Runnable_t::run().
	*/
	std::thread mThread;
};
