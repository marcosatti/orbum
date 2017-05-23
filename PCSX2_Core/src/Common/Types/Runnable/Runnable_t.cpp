#include "Common/Global/Globals.h"
#include "Common/Types/Runnable/Runnable_t.h"

void Runnable_t::threadMain()
{
    // Initialise lock and set to paused.
    std::unique_lock<std::mutex> lock(State.mLock);
    State.mStatus = Pause;

    while (true)
    {
        // Wait for control thread to notify this thread - mutex is auto unlocked during wait(), relocked upon being notified.
        // If a spurious wakeup happens (when State.mStatus = Paused), then it will loop back around without any trouble.
        State.mCondVar.wait(lock);

        // Execute subclass run() function, catch any exception and let the manager decide what to do.
        if (State.mStatus == Run)
        {
            try
            {
                // Run work to do.
#if defined(BUILD_DEBUG)
                log(Debug, "Calling run() on thread %d (%s).", std::this_thread::get_id(), DEBUG_SYSTEM_STRINGS[getContext()]);
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
    }

    log(Info, "Thread %d successfully exited ok.", std::this_thread::get_id());
}

void Runnable_t::notify(Status status)
{
    std::unique_lock<std::mutex> lock(State.mLock);
    State.mStatus = status;
    State.mCondVar.notify_one();
}

void Runnable_t::synchronise()
{
    std::unique_lock<std::mutex> lock(State.mLock);
    if (State.mException) 
        std::rethrow_exception(State.mException);
}
