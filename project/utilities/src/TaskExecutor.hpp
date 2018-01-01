#pragma once

#include <stdexcept>
#include <memory>
#include <thread>
#include <functional>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <chrono>
#include <Queues.hpp>

typedef MpmcQueue<std::function<void()>, 128> TaskQueue;

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
	int busy_counter;
	std::mutex busy_counter_mtx;
	std::condition_variable busy_counter_cv;
};

struct TaskSync
{
	TaskSync() : exit(false) {}

	TaskQueue task_queue;
	BusyCounter busy_count;
	bool exit;
};

/// Threaded worker, runs functors from a given task queue.
class Worker
{
public:
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

	void handle_exception_check() const
	{
		if (ex_ptr)
			std::rethrow_exception(ex_ptr);
	}

private:
    void main_thread_()
    {
		while (!task_sync.exit && !ex_ptr && !local_exit)
		{
			std::function<void()> task_fn;
			if (task_sync.task_queue.try_pop(task_fn, std::chrono::nanoseconds(500), [this] { task_sync.busy_count++; }))
			{
				try
				{
					task_fn();
				}
				catch (...)
				{
					ex_ptr = std::current_exception();
				}
				task_sync.busy_count--;
			}
		}
    }


	bool local_exit; // Kinda not needed but makes the code a bit nicer by not exposing join()
	                 // publicly, instead guaranteeing the thread will exit.
	TaskSync & task_sync;
	std::exception_ptr ex_ptr;
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
		task_sync.task_queue.push(fn);
    }

	void wait_for_idle()
	{
		while (true)
		{
			// Wait for idle task threads.
			task_sync.busy_count.wait_for_idle();

			// Check if any worker raised an exception.
			for (const auto& worker : workers)
				worker->handle_exception_check();

			// Make sure the task queue is actually empty - we could have caught
			// the workers in a state where they are in the process of
			// retrieving a task.
			if (task_sync.task_queue.is_empty())
				break;
		}
	}

private:
	TaskSync task_sync;
	std::vector<std::unique_ptr<Worker>> workers;
};
