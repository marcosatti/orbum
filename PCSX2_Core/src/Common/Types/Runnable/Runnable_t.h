#include <stdexcept>
#include <mutex>
#include <condition_variable>

/*
Interface class for a runnable task/component that can be optionally run on a separate thread.
Design follows from here:
- https://stackoverflow.com/questions/37019144/control-each-thread-by-its-own-condition-variable-c
- https://stackoverflow.com/questions/233127/how-can-i-propagate-exceptions-between-threads
*/
class Runnable_t
{
public:
    enum Status
    {
        Run,
        Stop,
        Pause,
        Exception
    };

    struct State_t
    {
        Status                  mStatus;
        std::exception_ptr      mException;
        std::mutex              mLock;
        std::condition_variable mCondVar;
    };
    State_t State;

    /*
    Notify's this task and causes it to react to a changed state (ie: wake up if on another thread).
    */
    void notify(Status status);

    /*
    Runs the task (implemented by run()), and controls the runnable state.
    Intended to be used as the main function loop in a new thread.
    */
    void runMain();
    
    /*
    Runs the task implemented. 
    */
    virtual void run() = 0;
};
