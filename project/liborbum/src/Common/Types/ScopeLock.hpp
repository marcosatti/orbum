#pragma once

#include <mutex>

/// Provides a scope lock mechanism for synchronous resources.
/// Intended to be locked for the entire duration for a read-modify-write cycle
/// of the owning controller, while also being used by another controller 
/// (ie: CPU bus access) for writing in an interleaved fashion.
class ScopeLock
{
public: 
    /// Locks the mutex and returns a guard.
    std::unique_lock<std::recursive_mutex> scope_lock()
    {
        return std::unique_lock<std::recursive_mutex>(mutex);
    }

private:
    /// Recursive mutex.
    std::recursive_mutex mutex;
};