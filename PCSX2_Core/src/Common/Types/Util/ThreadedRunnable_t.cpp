#include "Common/Types/Util/ThreadedRunnable_t.h"

ThreadedRunnable_t::ThreadedRunnable_t(const std::shared_ptr<Runnable_t>& runnable) :
    mState(),
    mRunnable(runnable)
{
    // Construct a new thread with a "ready" state.
    mState.mStatus = Status::Paused;
    mState.mCommand = Command::None;
    mThread = std::thread(&ThreadedRunnable_t::main, this);
    synchronise(Status::Paused);
}

ThreadedRunnable_t::~ThreadedRunnable_t()
{
    // Tell this thread to stop, synchronise and join it.
    notify(Command::Stop);
    synchronise(Status::Stopped);
    mThread.join();
}

void ThreadedRunnable_t::main()
{
    std::unique_lock<std::mutex> lock(mState.mMutex);
    while (true)
    {
        // Wait for the thread manager to give a command.
        mState.mCVCommand.wait(lock, [&]() { return mState.mCommand != Command::None; });

        if (mState.mCommand == Command::Run)
        {
            // Run the runnable object function, capturing any exceptions for the manager to deal with.
            mState.mStatus = Status::Running;
            mState.mCommand = Command::None;
            try
            {
                mRunnable->run();
            }
            catch (...)
            {
                mState.mExceptionPtr = std::current_exception();
            }

            // Ready to receive a command again.
            mState.mStatus = Status::Paused;
            mState.mCVStatus.notify_one();
        }
        else if (mState.mCommand == Command::Stop)
        {
            // We have stopped the thread; it must be constructed again.
            mState.mStatus = Status::Stopping;
            mState.mCommand = Command::None;
            mState.mStatus = Status::Stopped;
            mState.mCVStatus.notify_one();
            break;
        }
    }
}

void ThreadedRunnable_t::notify(const Command command)
{
    std::unique_lock<std::mutex> lock(mState.mMutex);
    mState.mCommand = command;
    mState.mCVCommand.notify_one();
}

void ThreadedRunnable_t::synchronise(const Status status)
{
    std::unique_lock<std::mutex> lock(mState.mMutex);
    mState.mCVStatus.wait(lock, [&]() { return (mState.mStatus == status) && (mState.mCommand == Command::None); });
    if (mState.mExceptionPtr)
    {
        std::exception_ptr ex = mState.mExceptionPtr;
        mState.mExceptionPtr = nullptr;
        std::rethrow_exception(ex);
    }
}
