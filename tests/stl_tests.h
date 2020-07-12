//
// Created by Vova on 12.06.2020.
//

#pragma once

#include <pythonic.h>

#include <execution>

inline void test_parallel_for_each()
{
	std::vector<double> v(1e+9);

	{
		Timer parallel_timer("Parallel execution");
		std::for_each(std::execution::par_unseq, v.begin(), v.end(), [] (auto &c) {
			c++;
		});
	}

	{
		Timer sequence_timer("Sequence execution");
		std::for_each(std::execution::seq, v.begin(), v.end(), [] (auto &c) {
			c++;
		});
	}

	{
		Timer sequence_timer("Sequence execution");
		std::for_each(v.begin(), v.end(), [] (auto &c) {
			c++;
		});
	}
}
