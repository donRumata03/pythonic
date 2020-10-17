//
// Created by Vova on 15.10.2020.
//

#pragma once

#include <pythonic.h>

inline void test_thread_distribution ()
{
	//                    tasks | threads
	std::vector<std::pair<size_t, size_t>> examples = {
						// { 0, 0 },
						{ 1, 1 },
						{ 100, 1 },
						{ 1, 2 },
						{ 6, 12 },


	};

	std::cout << "Testing thread distributing" << std::endl;

	for (auto& example : examples) {
		std::vector<std::pair<size_t, size_t>> ranges = distribute_task_ranges(example.first, example.second);
		std::cout << example << "\t\t\t : \t\t\t" << ranges << std::endl;
	}
}
