//
// Created by Vova on 27.05.2020.
//

#pragma once

#include "pythonic_pch.h"

inline std::vector<std::pair<size_t, size_t>> distribute_task_ranges(size_t task_number, size_t group_number)
{
	assert(group_number > 0);
	if (task_number == 0) {
		std::vector<std::pair<size_t, size_t>> res(group_number);
		return res;
	};

	std::vector<std::pair<size_t, size_t>> res(group_number);
	auto tasks_per_thread = static_cast<size_t>(std::ceil(double(task_number) / group_number));

	/*
	size_t this_index = 0;
	while(this_index < task_number) {
		res.emplace_back(this_index, this_index + tasks_per_thread);
		this_index += tasks_per_thread;
	}
	res.back().second = task_number;
	*/

	size_t prev_end = 0;
	for (size_t index = 0; index < group_number; index++) {
		res[index].first = prev_end;
		prev_end += tasks_per_thread;
		// prev_end = cut(prev_end, 0, task_number);
		res[index].second = prev_end;
	}
	res.back().second = task_number;

	bool flag = false;
	for (auto& p : res) {
		if (!flag) {
			if (p.second >= task_number) {
				p.second = task_number;
				flag = true;
			}
		}
		else p = {0, 0};
	}

	return res;
}
