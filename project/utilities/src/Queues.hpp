#pragma once

#include <functional>
#include <stdexcept>
#include <mutex>
#include <condition_variable>
#include <boost/lockfree/spsc_queue.hpp>

/// MPMC blocking/try queue.
/// Thread safe for all producers and consumers.
template<typename ItemTy, size_t capacity>
class MpmcQueue
{
public:
	typedef boost::lockfree::spsc_queue<ItemTy, boost::lockfree::capacity<capacity>> QueueTy;
	typedef typename QueueTy::size_type SizeTy;

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
		std::unique_lock<std::mutex> empty_guard(empty_lock);
		empty_cv.wait(empty_guard, [this] { return is_empty(); });
	}

	void pop(ItemTy & item)
	{
		std::unique_lock<std::mutex> reading_guard(reading_lock);

		if (is_empty())
		{
			std::unique_lock<std::mutex> empty_guard(empty_lock);
			empty_cv.wait(empty_guard, [this] { return !is_empty(); });
		}

		if (!queue.pop(item))
				throw std::runtime_error("Popping MpmcQueue failed");
		full_cv.notify_one();
	}

	/// Tries to pop the front of the queue with a timeout.
	/// Executes the given lambda atomically (while popping the queue).
	bool try_pop(ItemTy & item, const std::chrono::nanoseconds timeout, const std::function<void()> & atomic_fn)
	{
		std::unique_lock<std::mutex> reading_guard(reading_lock);
		bool item_available = true;

		if (is_empty())
		{
			std::unique_lock<std::mutex> empty_guard(empty_lock);
			item_available = empty_cv.wait_for(empty_guard, timeout, [this] { return !is_empty(); });
		}

		if (item_available)
		{
			atomic_fn();
			if (!queue.pop(item))
				throw std::runtime_error("Popping MpmcQueue failed");
			full_cv.notify_one();
			return true;
		}

		return false;
	}

	bool try_pop(ItemTy & item)
	{
		return try_pop(item, std::chrono::nanoseconds(0), [] {});
	}

	void push(const ItemTy & item)
	{
		std::unique_lock<std::mutex> writing_guard(writing_lock);

		if (is_full())
		{
			std::unique_lock<std::mutex> full_guard(full_lock);
			full_cv.wait(full_guard, [this] { return !is_full(); });
		}

		if (!queue.push(item))
			throw std::runtime_error("Pushing MpmcQueue failed");
		empty_cv.notify_one();
	}

	/// Tries to push to the back of the queue with a timeout.
	/// Executes the given lambda atomically (while pushing the queue).
	bool try_push(const ItemTy & item, const std::chrono::nanoseconds timeout, const std::function<void()> & atomic_fn)
	{
		std::unique_lock<std::mutex> writing_guard(writing_lock);
		bool space_available = true;

		if (is_full())
		{
			std::unique_lock<std::mutex> full_guard(full_lock);
			space_available = full_cv.wait(full_guard, timeout, [this] { return !is_full(); });
		}

		if (space_available)
		{
			atomic_fn();
			if (!queue.push(item))
				throw std::runtime_error("Pushing MpmcQueue failed");
			empty_cv.notify_one();
			return true;
		}

		return false;
	}

	bool try_push(const ItemTy & item)
	{
		return try_push(item, std::chrono::nanoseconds(0), [] {});
	}

	/// Not thread safe.
	void reset()
	{
		queue.reset();
	}

private:
	std::mutex reading_lock;
	std::mutex writing_lock;
	std::mutex empty_lock;
	std::mutex full_lock;
	std::condition_variable empty_cv;
	std::condition_variable full_cv;
	QueueTy queue;
};

/// SPSC blocking/try queue.
/// No thread safety - only 1 producer and 1 consumer allowed.
template<typename ItemTy, size_t capacity>
class SpscQueue
{
public:
	typedef boost::lockfree::spsc_queue<ItemTy, boost::lockfree::capacity<capacity>> QueueTy;
	typedef typename QueueTy::size_type SizeTy;

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
		std::unique_lock<std::mutex> empty_guard(empty_lock);
		empty_cv.wait(empty_guard, [this] { return is_empty(); });
	}

	void pop(ItemTy & item)
	{
		if (is_empty())
		{
			std::unique_lock<std::mutex> empty_guard(empty_lock);
			empty_cv.wait(empty_guard, [this] { return !is_empty(); });
		}

		if (!queue.pop(item))
			throw std::runtime_error("Could not pop from MpmcQueue.");
		full_cv.notify_one();
	}

	bool try_pop(ItemTy & item)
	{
		bool result = queue.pop(item);
		if (result)
			full_cv.notify_one();
		return result;
	}

	void push(const ItemTy & item)
	{
		if (is_full())
		{
			std::unique_lock<std::mutex> full_guard(full_lock);
			full_cv.wait(full_guard, [this] { return !is_full(); });
		}

		if (!queue.push(item))
			throw std::runtime_error("Could not push to MpmcQueue.");
		empty_cv.notify_one();
	}

	bool try_push(const ItemTy & item)
	{
		bool result = queue.push(item);
		if (result)
			empty_cv.notify_one();
		return result;
	}

	/// Not thread safe.
	void reset()
	{
		queue.reset();
	}

private:
	std::mutex empty_lock;
	std::mutex full_lock;
	std::condition_variable empty_cv;
	std::condition_variable full_cv;
	QueueTy queue;
};
