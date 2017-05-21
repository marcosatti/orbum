#pragma once

#include <mutex>
#include <condition_variable>

/*
Base class that provides threading resources, used by a thread manager.
*/
class ThreadableObject_t
{
public:
	enum ThreadStatus
	{
		Running,
		Exception,
		Stopped
	};

	explicit ThreadableObject_t();

	/*
	Notify the this system's condition variable and sets the thread state to running.
	Used by a manager to wake up the thread this system runs on.
	*/
	void threadNotify();

	/*
	The main thread loop, used when constructing a std::thread or similar.
	Calls the run() function when notified by the VM, and handles exceptions by setting the state.
	*/
	void threadRun();

	/*
	Returns the state of this thread.
	*/
	ThreadStatus threadGetStatus() const;

	/*
	Main function that is run when the thread is notified.
	Implemented by subclasses.
	*/
	virtual void run() = 0;

private:
	/*
	Threading resources, used to synchronise between the VM and this system thread.
	*/
	std::condition_variable mThreadCV;
	std::mutex mThreadMutex;
	ThreadStatus mThreadStatus;

	/*
	Exception message.
	Upon an exception occuring in the subclass, the message is set and used by the VM to re-throw from the main thread.
	*/
	std::string mExceptionMessage;
};