#include "Common/Global/Globals.h"
#include "Common/Types/Runnable/Runnable_t.h"

#if defined(BUILD_DEBUG)
#define DEBUG_LOG_RUNNABLE_ACTIVITY 1
#endif

void Runnable_t::threadMain()
{
    // Initialise lock and set to paused.
    std::unique_lock<std::mutex> lock(State.mLock);
    State.mStatus = Pause;

    while (true)
    {
#if DEBUG_LOG_RUNNABLE_ACTIVITY
		log(Debug, "Calling cv.wait() on thread %d (%s). Owns lock? %d", std::this_thread::get_id(), DEBUG_SYSTEM_STRINGS[getContext()], lock.owns_lock());
#endif
        // Wait for control thread to notify this thread - mutex is auto unlocked during wait(), relocked upon being notified.
        // If a spurious wakeup happens (when State.mStatus = Paused), then it will loop back around without any trouble.
        State.mCondVar.wait(lock);

        // Execute subclass run() function, catch any exception and let the manager decide what to do.
        if (State.mStatus == Run)
        {
            try
            {
                // Run work to do.
#if DEBUG_LOG_RUNNABLE_ACTIVITY
                log(Debug, "Calling run() on thread %d (%s). Owns lock? %d", std::this_thread::get_id(), DEBUG_SYSTEM_STRINGS[getContext()], lock.owns_lock());
#endif
                run();

                // Finished, wait for manager again.
                State.mStatus = Pause;
            }
            catch (...)
            {
                State.mException = std::current_exception();
            }
        }
        else if (State.mStatus == Stop)
        {
            // Manager has signalled to exit this thread.
            break;
        }
		else if (State.mStatus == Pause)
		{
#if DEBUG_LOG_RUNNABLE_ACTIVITY
			log(Debug, "Spurious wakeup on thread %d (%s). Owns lock? %d", std::this_thread::get_id(), DEBUG_SYSTEM_STRINGS[getContext()], lock.owns_lock());
#endif
		}

#if DEBUG_LOG_RUNNABLE_ACTIVITY
		log(Debug, "End of loop on thread %d (%s). Owns lock? %d", std::this_thread::get_id(), DEBUG_SYSTEM_STRINGS[getContext()], lock.owns_lock());
#endif
    }

#if DEBUG_LOG_RUNNABLE_ACTIVITY
    log(Info, "Thread %d successfully exited ok.", std::this_thread::get_id());
#endif
}

void Runnable_t::notify(Status status)
{
    std::unique_lock<std::mutex> lock(State.mLock);
#if DEBUG_LOG_RUNNABLE_ACTIVITY
	log(Debug, "Calling notify() on manager thread. Owns lock? %d", lock.owns_lock());
#endif
    State.mStatus = status;
    State.mCondVar.notify_one();
}

void Runnable_t::synchronise()
{
    std::unique_lock<std::mutex> lock(State.mLock);
#if DEBUG_LOG_RUNNABLE_ACTIVITY
	log(Debug, "Calling synchronise() on manager thread. Owns lock? %d", lock.owns_lock());
#endif
    if (State.mException) 
        std::rethrow_exception(State.mException);
}
