//
// Created by Vova on 17.10.2020.
//

#include "thread_utils.h"
#include "displaying/print_stl.h"

static void improve_distribution (size_t task_number, std::vector<std::pair<size_t, size_t>> &distribution_to_improve)
{
	distribution_to_improve.back().second = task_number;

	bool flag = false;
	for (auto& p : distribution_to_improve) {
		if (!flag) {
			if (p.second >= task_number) {
				p.second = task_number;
				flag = true;
			}
		}
		else p = {0, 0};
	}
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


std::vector<std::pair<size_t, size_t>> adaptively_distribute_task_ranges(size_t task_number, size_t group_number) {
	std::vector<std::pair<size_t, size_t>> res(group_number);

	auto current_value = 0ULL;
	for (size_t group_index = 0; group_index < group_number; ++group_index) {
		res[group_index].first = current_value;
		size_t tasks_left = task_number - current_value; // Including the tasks for this one
		size_t groups_left = group_number - group_index; // Including this group

		auto this_delta = size_t(std::round(double(tasks_left) / groups_left));
		current_value += this_delta;

		res[group_index].second = current_value;
	}

	// std::cout << res << std::endl;
	// improve_distribution(task_number, res);

	// std::cout << res << std::endl;

	return res;
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


	improve_distribution(task_number, res);

	return res;
}
