#pragma once

#include <functional>
#include <mutex>
#include <stdexcept>

#include <boost/lockfree/spsc_queue.hpp>

#include <condition_variable>

// TODO: the Mpsc/Spmc/Spsc classes are just Mpmc aliases...
//       In order to support the "events" a mutex is needed
//       anyway, even for simple cases like the Spsc queue.

/// MPMC blocking/try queue.
/// Thread safe for all producers and consumers.
template <typename ItemTy, size_t capacity>
class MpmcQueue
{
public:
    using QueueTy = boost::lockfree::spsc_queue<ItemTy, boost::lockfree::capacity<capacity>>;
    using SizeTy = typename QueueTy::size_type;

    static constexpr std::chrono::nanoseconds ZERO_TIMEOUT = std::chrono::nanoseconds(0);

    bool has_read_available(const SizeTy n_items = 1) const
    {
        return queue.read_available() >= n_items;
    }

    bool has_write_available(const SizeTy n_items = 1) const
    {
        return queue.write_available() >= n_items;
    }

    bool is_empty() const
    {
        return !has_read_available();
    }

    bool is_full() const
    {
        return !has_write_available();
    }

    void wait_for_empty()
    {
        std::unique_lock<std::mutex> lock(mutex);
        empty_cv.wait(lock, [this] { return is_empty(); });
    }

    void wait_for_full()
    {
        std::unique_lock<std::mutex> lock(mutex);
        full_cv.wait(lock, [this] { return is_full(); });
    }

    void pop(ItemTy& item, const std::function<void()>& atomic_fn = [] {})
    {
        std::unique_lock<std::mutex> lock(mutex);

        push_cv.wait(lock, [this] { return !is_empty(); });

        _pop(item, atomic_fn);
    }

    bool try_pop(ItemTy& item, const std::chrono::nanoseconds timeout = ZERO_TIMEOUT, const std::function<void()>& atomic_fn = [] {})
    {
        std::unique_lock<std::mutex> lock(mutex);

        if (push_cv.wait_for(lock, timeout, [this] { return !is_empty(); }))
        {
            _pop(item, atomic_fn);
            return true;
        }

        return false;
    }

    void push(const ItemTy& item, const std::function<void()>& atomic_fn = [] {})
    {
        std::unique_lock<std::mutex> lock(mutex);

        pop_cv.wait(lock, [this] { return !is_full(); });

        _push(item, atomic_fn);
    }

    bool try_push(const ItemTy& item, const std::chrono::nanoseconds timeout = ZERO_TIMEOUT, const std::function<void()>& atomic_fn = [] {})
    {
        std::unique_lock<std::mutex> lock(mutex);

        if (pop_cv.wait_for(lock, timeout, [this] { return !is_full(); }))
        {
            _push(item, atomic_fn);
            return true;
        }

        return false;
    }

    /// Not thread safe.
    void reset()
    {
        queue.reset();
    }

private:
    /// Internal pop method used when lock is held.
    void _pop(ItemTy& item, const std::function<void()>& atomic_fn)
    {
        atomic_fn();

        if (!queue.pop(item))
            throw std::runtime_error("Popping MpmcQueue failed");

        if (is_empty())
            empty_cv.notify_one();

        pop_cv.notify_one();
    }

    /// Internal push method used when lock is held.
    void _push(const ItemTy& item, const std::function<void()>& atomic_fn)
    {
        atomic_fn();

        if (!queue.push(item))
            throw std::runtime_error("Pushing MpmcQueue failed");

        if (is_full())
            full_cv.notify_one();

        push_cv.notify_one();
    }

    std::mutex mutex;
    std::condition_variable pop_cv;
    std::condition_variable push_cv;
    std::condition_variable empty_cv;
    std::condition_variable full_cv;
    QueueTy queue;
};

/// MPSC blocking/try queue.
/// Thread safe for all producers and only one consumer allowed.
template <typename ItemTy, size_t capacity>
using MpscQueue = MpmcQueue<ItemTy, capacity>;

/// SPMC blocking/try queue.
/// Thread safe for all consumers and only one producer allowed.
template <typename ItemTy, size_t capacity>
using SpmcQueue = MpmcQueue<ItemTy, capacity>;

/// SPSC blocking/try queue.
/// No thread safety - only 1 producer and 1 consumer allowed.
template <typename ItemTy, size_t capacity>
using SpscQueue = MpmcQueue<ItemTy, capacity>;
