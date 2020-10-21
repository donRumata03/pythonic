//
// Created by Vova on 17.10.2020.
//


#include "static_thread_pool.h"

#include "displaying/print_stl.h"

std::mutex print_mutex;

void safe_print(const std::string& to_print) {
	std::lock_guard<std::mutex> lck (print_mutex);
	std::cout << to_print << std::endl;
}

// std::atomic<size_t> threads_came_through_variable = 0;


////////////////////////////////////////////////////// Thread wrapper ////////////////////////////////////////////////

void thread_wrapper(
		size_t thread_index,
		const std::function<void(size_t)>& function_to_launch_at_each_iteration,
		static_thread_pool& parent_thread_pool
) {

	lint this_iteration = 0;
	while (true) {
		/// Passively Wait to start (don`t consume CPU cycles for checking):
		std::unique_lock<std::mutex> lck(parent_thread_pool.running_cv_protector);
		parent_thread_pool.running_cv.wait(lck, [&parent_thread_pool](){ return parent_thread_pool.thread_ending_state_ready; });

		bool threads_should_be_run_or_not = parent_thread_pool.threads_should_be_run;

		lck.unlock();

		if (!threads_should_be_run_or_not) break;

		// std::this_thread::sleep_for(0.1s);

		// safe_print("thread " + std::to_string(thread_index) + " gone through the condition variable, " + "threads_should_be_run_or_not is " + std::to_string(threads_should_be_run_or_not));

		/// Do work:
		function_to_launch_at_each_iteration(thread_index);

		parent_thread_pool.this_it_ready_thread_number++;

		/// Say that I`m ready:
		parent_thread_pool.threads_ready[thread_index] = true;
		while (parent_thread_pool.max_all_threads_ready_run < this_iteration) {
			/// Wait all the other threads
		}


		this_iteration++;
	}
}



// void thread_wrapper(size_t thread_index, const std::function<void(size_t)>& function_to_launch_at_each_iteration);

/**
 * Public methods:
 */

void static_thread_pool::init (size_t thread_number,
                               const std::function<void (size_t)> &function_to_launch_at_each_iteration)
{
	if (is_initialized) throw std::runtime_error("Pool is already initialized!");
	is_initialized = true;

	m_thread_number = thread_number;
	threads_ready.assign(thread_number, false);

	for (size_t thread_index = 0; thread_index < thread_number; ++thread_index) {
		m_threads.emplace_back(thread_wrapper,
		                       thread_index,
		                       function_to_launch_at_each_iteration,
		                       std::ref(*this)
		);
	}
}


static_thread_pool::static_thread_pool (size_t thread_number, const std::function<void(size_t)>& function_to_launch_at_each_iteration)
{
	init(thread_number, function_to_launch_at_each_iteration);
}


void static_thread_pool::compute ()
{
	inform_thread_next_iteration();
	wait_for_threads_ready();
}

void static_thread_pool::join ()
{
	inform_thread_ending();

	for(auto& thread : m_threads)
		thread.join();
}


////////////////////////////////////////////////////// Thread pool helpers ////////////////////////////////////////////////

void static_thread_pool::inform_thread_ending_state (bool continue_or_not)
{
	std::lock_guard<std::mutex> locker(running_cv_protector);
	threads_should_be_run = continue_or_not;
	thread_ending_state_ready = true;
	running_cv.notify_all();
}

void static_thread_pool::wait_for_threads_ready ()
{
	/// ACTIVE Waiting for all threads to complete:
	// safe_print("[main thread]: start waiting");

	while(
		//	std::any_of(threads_ready.begin(), threads_ready.end(), [](bool val){ return !val; })
		this_it_ready_thread_number < m_thread_number
		)
	{
		// Wait
	}

	// safe_print("[main thread]: ended waiting");


	/// All threads ready => reset everything to the initial state:
	std::fill(threads_ready.begin(), threads_ready.end(), false); // Clear thread ready
	this_it_ready_thread_number = 0;
	thread_ending_state_ready = false;

	// threads_should_be_run = false;

	// safe_print("[main thread]: informed");

	/// Release other threads
	max_all_threads_ready_run++;

	// safe_print("[main thread]: released");
}



