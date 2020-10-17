//
// Created by Vova on 17.10.2020.
//

#pragma once

#include "pythonic_pch.h"
#include "other/typedefs.h"

class static_thread_pool
{
	std::vector<std::thread> m_threads;
	// std::atomic<bool> threads_are_working = false; <- todo!

	std::mutex running_cv_protector;
	bool thread_ending_state_ready = false;
	bool threads_should_be_run = false;
	std::condition_variable running_cv;

	std::vector<bool> threads_ready;    // Updated by threads after ending,
										// read by main thread to set true to all_threads_ready,
										// is reset by main thread after ending
	std::atomic<lint> max_all_threads_ready_run = -1;   // All the threads have finished work for all the indexes <= max_all_threads_ready_run
														// Set by main thread,
														// All the threads are waiting for all the others to be ready.


public:
	explicit static_thread_pool(size_t thread_number, const std::function<void(size_t)>& function_to_launch_at_each_iteration);

	////////////////////////////////////////////////////////////////////////
	static_thread_pool(const static_thread_pool& other) = delete;
	static_thread_pool(static_thread_pool&& other) = delete;

	static_thread_pool& operator= (const static_thread_pool& other) = delete;
	static_thread_pool& operator= (static_thread_pool&& other) = delete;
	////////////////////////////////////////////////////////////////////////

	void join();
	void compute();

private:
	void inform_thread_ending_state(bool continue_or_not);
	void wait_for_threads_ready();
};


