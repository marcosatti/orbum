#include "Common/Global/Globals.h"
#include "Common/Types/Runnable/Runnable_t.h"

void Runnable_t::runMain()
{
	// Set to paused initially.
	State.mStatus = Pause;
	
    while (true)
	{
		// Wait for control thread to notify this thread - mutex is auto unlocked during wait(), relocked upon being notified.
		// If a spurious wakeup happens (when mThreadStatus = Paused), then it will loop back around without any trouble.
		std::unique_lock<std::mutex> lock(State.mLock);
		State.mCondVar.wait(lock);

		// Execute subclass run() function, catch any exception and let the manager decide what to do.
		switch (State.mStatus)
		{
		case Run:
		{
			try
			{
				// Run work to do.
				run();

				// Finished, wait for manager again.
				State.mStatus = Pause;
			}
			catch (...)
			{
				State.mStatus = Exception;
				State.mException = std::current_exception();
			}
            break;
		}
		case Stop:
		{
			// Manager has signaled to exit this thread.
			goto exit;
		}
		case Exception:
		{
			// Uh oh, what happened? Did the manager set the status wrongly?
			std::string msg = "Thread status was set to an invalid state! (By manager?) Please fix!";
			log(Fatal, msg.c_str());
			throw std::runtime_error(msg);
		}
		}
	}
	
	exit:
	log(Info, "Thread %d successfully exited ok.", std::this_thread::get_id());
}

void Runnable_t::notify(Runnable_t::Status status)
{
    std::unique_lock<std::mutex> lock(State.mLock);
    State.mStatus = status;
    State.mCondVar.notify_one();
}
