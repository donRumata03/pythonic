//
// Created by Vova on 17.10.2020.
//

#include "thread_utils.h"

std::vector<std::pair<size_t, size_t>> adaptively_distribute_task_ranges(size_t task_number, size_t group_number) {
	std::vector<std::pair<size_t, size_t>> res(group_number);

	// double
}


static bool validate_task_range_distribution(size_t task_number, size_t group_number, const std::vector<std::pair<size_t, size_t>>& distr) {
	if (distr.size() != group_number) return false;

	if (distr.front().first != 0) return false;
	if (distr.back().second != task_number) return false;

	for (size_t pair_index = 1; pair_index < group_number; ++pair_index) {
		const auto& this_p = distr[pair_index];
		const auto& prev_p = distr[pair_index - 1];

		if (prev_p.second < prev_p.first) return false;
		if (prev_p.second != this_p.first) return false;
	}

	return true;

}


std::vector<std::pair<size_t, size_t>> distribute_task_ranges (size_t task_number, size_t group_number)
{
	// Do some stuff:
	std::vector<std::pair<size_t, size_t>> res = adaptively_distribute_task_ranges(task_number, group_number);

	// Validate:
	if (!validate_task_range_distribution(task_number, group_number, res)) {
		std::cerr <<
			"Failed to adaptively distribute task ranges for task number = " << task_number << ", group_number = " << group_number << " => distribute dummy"
		<< std::endl;
		return dummy_distribute_task_ranges(task_number, group_number);
	}

	return res;
}




std::vector<std::pair<size_t, size_t>> dummy_distribute_task_ranges (size_t task_number, size_t group_number)
{
	assert(group_number > 0);
	if (task_number == 0) {
		std::vector<std::pair<size_t, size_t>> res(group_number);
		return res;
	}

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
