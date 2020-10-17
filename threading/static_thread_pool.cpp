//
// Created by Vova on 17.10.2020.
//

#include "static_thread_pool.h"

void thread_wrapper(size_t thread_index, const std::function<void(size_t)>& function_to_launch_at_each_iteration) {
	while (true) {
		//TODO
		function_to_launch_at_each_iteration(thread_index);
	}
}

static_thread_pool::static_thread_pool (size_t thread_number, const std::function<void(size_t)>& function_to_launch_at_each_iteration)
{
	for (size_t thread_index = 0; thread_index < thread_number; ++thread_index) {
		m_threads.emplace_back(thread_wrapper, thread_index, function_to_launch_at_each_iteration);
	}
}
