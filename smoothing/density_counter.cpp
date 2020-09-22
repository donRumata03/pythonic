//
// Created by Vova on 26.05.2020.
//

#include "density_counter.h"

pms count_number_density(const std::vector<double>& input_numbers, double percent_sigma, lint target_number, double percent_frame_width)
{
	auto numbers(input_numbers);
	if (target_number == -1LL) target_number = input_numbers.size();

	std::sort(numbers.begin(), numbers.end());
	double first_num = numbers[0], last_num = numbers.at(numbers.size() - 1);
	double width = last_num - first_num;
	double Sigma = percent_sigma * width;
	auto frame_width = size_t(percent_frame_width * numbers.size());
	double target_step = width / target_number;

	pms result;
	result.reserve(target_number);

	size_t corresponding_index = 0;

	double summary_S = 0;

	for (size_t i = 0; i < target_number; i++) {
		// Get to the right corresponding index, for which point at it is more than this one, maybe: get booth left and right side
		double accum = 0;
		double this_x = first_num + target_step * i;
		for (auto& number : numbers) { // TODO : watch only the points in the window! (TO IMPROVE PERFORMANCE)
			accum += normal(this_x, Sigma, number);
		}
		summary_S += accum;
		result.push_back({ this_x, accum });
	}

	for(auto& point : result) {
		point.second /= summary_S / target_number;
	}

	return result;
}



/*
nd_array<double> count_nd_density(std::vector<nd_point<(double)...>)
{

	return nd_array<double>(0, std::vector());
}

 */
