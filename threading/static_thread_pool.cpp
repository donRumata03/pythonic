//
// Created by Vova on 17.10.2020.
//


#include "static_thread_pool.h"


/**
 * Public methods:
 */

void thread_wrapper(size_t thread_index, const std::function<void(size_t)>& function_to_launch_at_each_iteration);


static_thread_pool::static_thread_pool (size_t thread_number, const std::function<void(size_t)>& function_to_launch_at_each_iteration)
{
	for (size_t thread_index = 0; thread_index < thread_number; ++thread_index) {
		m_threads.emplace_back(thread_wrapper, thread_index, function_to_launch_at_each_iteration);
	}
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

////////////////////////////////////////////////////// Thread wrapper ////////////////////////////////////////////////

void thread_wrapper(
		size_t thread_index,
		const std::function<void(size_t)>& function_to_launch_at_each_iteration,
		static_thread_pool& parent_thread_pool
) {

	lint this_iteration = 0;
	while (true) {
		/// Passively Wait to start (don`t consume CPU cycles for checking):
		safe_print(thread_prefix + "Waiting for job...");
		std::unique_lock<std::mutex> lck(running_cv_protector);
		parent_thread_pool.running_cv.wait(lck, [](){ return threads_should_be_run; });

		parent_thread_pool.

		lck.unlock();

		/// Do work:
		function_to_launch_at_each_iteration(thread_index);

		// Say that I`m ready:
		threads_ready[my_index] = true;
		while (max_all_threads_ready_run < lint(run_index)) {
			/// Wait all threads
		}


		this_iteration++;
	}
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
	while(std::any_of(threads_ready.begin(), threads_ready.end(), [](bool val){ return !val; })) {
		// Wait
	}

	/// All threads ready => reset everything to the initial state:
	std::fill(threads_ready.begin(), threads_ready.end(), false); // Clear thread ready
	thread_ending_state_ready = false;
	// threads_should_be_run = false;

	/// Release other threads
	max_all_threads_ready_run++;
}


