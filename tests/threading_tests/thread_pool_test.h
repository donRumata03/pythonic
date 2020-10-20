//
// Created by Vova on 18.10.2020.
//

#pragma once

#include <pythonic.h>

inline void test_thread_pool() {
	std::mutex wm;
	static_thread_pool pool(12, [&wm](size_t thread_index){
		/*
		{
			std::lock_guard lck(wm);
			std::cout << "Thread " << thread_index << "working..." << std::endl;
		}
		std::this_thread::sleep_for(1s);

		{
			std::lock_guard lck(wm);
			std::cout << "Thread " << thread_index << "finished this iteration." << std::endl;
		}
		*/
	});

	// std::this_thread::sleep_for(2s);


	pool.compute();

	// std::this_thread::sleep_for(3s);

	pool.compute();

	// pool.join();
}
