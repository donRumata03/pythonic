//
// Created by Vova on 13.12.2020.
//

#pragma once

#include <pythonic.h>

// #include "pythonic_pch.h"
// #include "other/typedefs.h"

void work_proportional_to(li how_much) {
	std::vector<double> vector(how_much);

	double last = 0;
	for(auto& v : vector) {
		v = (last + 1) / 10;
		last = v;
	}
}

inline void test_multirun_timer() {
	MultirunTimer timer;

	li iterations = 10000;
	for (li i = 0; i < iterations; ++i) {
		timer.signal_work_starting();
		work_proportional_to(i);
		timer.signal_work_ending();
	}

	auto data = timer.time_history();
	assert(data.size() == iterations);
	std::cout << data << std::endl;

	std::cout << timer.total_time().count() << "ns total time, " << timer.average_time().count() << "time at average" << std::endl;

	pms pairs(data.size());
	size_t index = 0;
	std::generate(pairs.begin(), pairs.end(), [&index, &data](){
		auto res = std::pair{ double(index), double(data[index].count()) };
		index++;
		return res;
	});

	add_pairs_to_plot(pairs);
	show_plot();
}
