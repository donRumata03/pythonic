//
// Created by Vova on 26.05.2020.
//

#include "pch.h"
#include "maths/statistics.h"
#include "maths/numpyic.h"

#include "smoothing.h"

pms smooth(const pms& points, double percent_sigma, lint resultive_number_of_points, double percent_frame_width)
{
	assert(percent_frame_width > 0);
	assert(percent_frame_width <= 1);

	double first_x = points[0].first, last_x = points[points.size() - 1].first;

	double width = (last_x - first_x);
	double Sigma = percent_sigma * width;

	auto frame_half_width = static_cast<size_t>(percent_frame_width * points.size() / 2);
	if(resultive_number_of_points == -1) { resultive_number_of_points = int(points.size() * 10); }
	// double step_width = width / resultive_number_of_points;

	size_t corresponding_index = 0;
	pms result;

	for(auto x : linspace(first_x, last_x, resultive_number_of_points)){
		while(corresponding_index != points.size() && points.at(corresponding_index).first < x) { corresponding_index++; }
		double S_for_y = 0, y_coeff_sum = 0;

		auto begin_index = static_cast<size_t>(std::max(lint(0), lint(corresponding_index) - lint(frame_half_width)));
		auto end_index = std::min(static_cast<size_t>(begin_index + (2 * frame_half_width)), points.size());

		for(int smoothing_index = begin_index; smoothing_index < end_index; smoothing_index++){
			double this_coeff = normal(points.at(smoothing_index).first, Sigma, x);
			y_coeff_sum += this_coeff;
			S_for_y += points.at(smoothing_index).second * this_coeff;
		}

		double y = S_for_y / y_coeff_sum;
		result.push_back(std::pair(x, y));
	}
	return result;
}
