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
	inform_thread_ending_state(true);

	wait_for_threads_ready();
}

void static_thread_pool::join ()
{
	inform_thread_ending_state(false);

	for(auto& thread : m_threads) thread.join();
}


void thread_wrapper(size_t thread_index, const std::function<void(size_t)>& function_to_launch_at_each_iteration) {
	while (true) {
		// TODO
		function_to_launch_at_each_iteration(thread_index);
	}
}




void static_thread_pool::inform_thread_ending_state (bool continue_or_not)
{

}


