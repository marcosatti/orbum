#include "VM/Types/ThreadableObject_t.h"

ThreadableObject_t::ThreadableObject_t()
{
}

void ThreadableObject_t::threadNotify()
{
}

void ThreadableObject_t::threadRun()
{
	while (true)
	{
		// Wait for control thread to say run - mutex is auto unlocked during wait, relocked upon notify.
		{
			std::unique_lock<std::mutex> lock(mThreadMutex);
			mThreadCV.wait(lock, [this]() { return mThreadStatus == Running; });
			if (getVM()->getStatus() == VM::Stopped)
				break;
		}

		// Execute subclass run() function, catch any exception and let the VM decide what to do.
		try
		{
			// Run work to do.
			run();

			// Finished, wait for VM again.
			mThreadStatus = Stopped;
		}
		catch (const std::exception & ex)
		{
			mThreadStatus = Exception;
			mExceptionMessage = ex.what();
		}
	}
}

ThreadableObject_t::ThreadStatus ThreadableObject_t::threadGetStatus() const
{
	return mThreadStatus;
}
