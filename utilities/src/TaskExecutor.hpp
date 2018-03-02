#pragma once

#include <exception>
#include <stdexcept>
#include <memory>
#include <thread>
#include <functional>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <chrono>
#include <string>
#include <Queues.hpp>

struct BusyCounter
{
	BusyCounter() : busy_counter(0) {}
	
	void operator++(int)
	{
		std::unique_lock<std::mutex> lock(busy_counter_mtx);
		busy_counter++;
		lock.unlock();
		busy_counter_cv.notify_all();
	}
	
	void operator--(int)
	{
		std::unique_lock<std::mutex> lock(busy_counter_mtx);
		busy_counter--;
		lock.unlock();
		busy_counter_cv.notify_all();
	}
	
	void wait_for_idle()
	{
		std::unique_lock<std::mutex> lock(busy_counter_mtx);
		busy_counter_cv.wait(lock, [this] { return !busy_counter; });
	}

private:
#if defined(BUILD_DEBUG)
    friend class Core;
#endif

	int busy_counter;
	std::mutex busy_counter_mtx;
	std::condition_variable busy_counter_cv;
};

/// Executor/Thread synchronisation resources.
/// With ex_ptr, we don't care if two threads try to write to it at once -
/// we only care that at least one exception occured, doesn't matter which one.
struct TaskSync
{
	TaskSync() : exit(false) {}

	SpmcQueue<std::function<void()>, 128> running_task_queue;
	MpscQueue<std::function<void()>, 128> pending_task_queue;

	BusyCounter thread_busy_counter;
	MpscQueue<std::string, 32> thread_error_queue;
	
	bool exit;
};

/// Threaded worker, runs functors from a given task queue.
class Worker
{
public:
	static constexpr std::chrono::nanoseconds TIMEOUT = std::chrono::nanoseconds(500); 

    Worker(TaskSync & task_sync) :
		local_exit(false),
        task_sync(task_sync)
    {
        thread = std::thread(std::bind(&Worker::main_thread_, this));
    }

	~Worker()
	{
		local_exit = true;
		thread.join();
	}

private:
    void main_thread_()
    {
		while (!task_sync.exit && !local_exit)
		{
			std::function<void()> task_fn;
			if (task_sync.running_task_queue.try_pop(task_fn, TIMEOUT, [this] { task_sync.thread_busy_counter++; }))
			{
				try
				{
					task_fn();
				}
				catch (const std::exception & error)
				{
					// Add exception to global queue for the executor to deal with.
					std::string error_str(error.what());
					task_sync.thread_error_queue.push(error_str);
				}
				task_sync.thread_busy_counter--;
			}
		}
    }

	bool local_exit; // Kinda not needed but makes the code a bit nicer by not 
					 // exposing join() publicly, instead guaranteeing the 
					 // thread will exit.
	TaskSync & task_sync;
    std::thread thread;
};

/// Thread pool task executor.
class TaskExecutor
{
public:
    TaskExecutor(const size_t thread_pool_size)
    {
        for (size_t i = 0; i < thread_pool_size; i++)
            workers.push_back(std::make_unique<Worker>(task_sync));
    }

	~TaskExecutor()
	{
		task_sync.exit = true;
	}

    void enqueue_task(const std::function<void()> & fn)
    {
		task_sync.pending_task_queue.push(fn);
    }

	void dispatch()
	{
		while (!task_sync.pending_task_queue.is_empty())
		{
			std::function<void()> fn;
			task_sync.pending_task_queue.pop(fn);
			task_sync.running_task_queue.push(fn);
		}
	}

	void wait_for_idle()
	{
		// Wait for empty running task queue.
		task_sync.running_task_queue.wait_for_empty();

		// Wait for paused worker threads.
		task_sync.thread_busy_counter.wait_for_idle();
		
		// Check if any exceptions occured, rethrow them on the current thread.
		// TODO: only the first error is thrown for now... Not sure we will
		//       ever change this.
		if (!task_sync.thread_error_queue.is_empty())
		{
			std::string error_str;
			task_sync.thread_error_queue.pop(error_str);
			throw std::runtime_error(error_str);
		}
	}

private:
#if defined(BUILD_DEBUG)
	friend class Core;
#endif

	TaskSync task_sync;
	std::vector<std::unique_ptr<Worker>> workers;
};
