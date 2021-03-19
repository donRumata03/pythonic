//
// Created by Vova on 24.05.2020.
//

#include "statistics.h"
#include <cmath>

#include "simple_functions.h"

double normal(const double x, const double sigma, const double mediana) noexcept {
	return (1 / (sigma * sqrt(2 * pi))) * pow(e, -square(mediana - x) / (2 * square(sigma)));
}

void logariphmate_function(pms &points)
{
	for (auto& point : points)
	{
		point.first = log(point.first);
	}
}


/*

nd_array<double> count_nd_density(vector<vector<double>>& numbers, const size_t target_number, const double percent_sigma)
{
	constexpr auto debugging_density_counter = 1;
	size_t dimensions = numbers[0].size();
	if constexpr (debugging_density_counter == 1) { for (auto& i : numbers) { assert(i.size() == dimensions); } }


	vector<size_t> dimension_vals;
	dimension_vals.reserve(dimensions);
	for (size_t dim_counter = 0; dim_counter < target_number; dim_counter++) {
		dimension_vals.push_back(target_number);
	}
	auto result = nd_array<double>(dimensions, dimension_vals); // Now it is initialized



	return result;
}

 */

/////////////////////////

double geometric_mean(const std::vector<double>& numbers)
{
	double res = 1;
	for (double val : numbers) res *= val;
	return pow(res, 1. / numbers.size());
}


double n_ometric_mean(const std::vector<double>& numbers, const double n)
{
	double res = 1;
	for (double val : numbers) res *= val;
	return pow(res, 1. / numbers.size());
}

/////////////////////////

double harmonic_mean(const std::vector<double>& numbers)
{
	auto numerator = double(numbers.size());
	double denominator = 0;
	for (double val : numbers) denominator += 1 / val;
	return numerator / denominator;
}

double n_monic_mean(const std::vector<double>& numbers, const double n)
{
	auto numerator = double(numbers.size());
	double denominator = 0;
	for (double val : numbers) denominator += 1 / val;
	return numerator / denominator;
}

/////////////////////////////////


double quadratic_mean(const std::vector<double>& numbers)
{
	double sm = 0;
	for (double val : numbers) sm += sgn(val) * val * val;
	return sgn(sm) * sqrt(abs(sm / numbers.size()));
}


double n_atic_mean(const std::vector<double>& numbers, const double n)
{
	double sm = 0;
	for (double val : numbers) sm += sgn(val) * pow(abs(val), n);
	return sgn(sm) * pow(abs(sm) / numbers.size(), 1 / n);
}

double weighted_average(const std::vector<double> &ms, const std::vector<double> &weights)
{
	assert(ms.size() == weights.size());

	double weight_sum = sum(weights);

	double weighted_sum = 0;
	for (size_t index = 0; index < ms.size(); index++) {
		weighted_sum += weights[index] * ms[index];
	}

	return weighted_sum / weight_sum;
}

double sign_safe_pow(double X, double Y)
{
	return sgn(X) * pow(abs(X), Y);
}

void normalize(std::vector<std::pair<double, double>> &graph, const double target_area)
{
	double area = count_graph_area(graph);
	double mul = target_area / area;
	for (auto& point : graph) point.second *= mul;
}

double weighted_average(const std::vector<std::pair<double, double>>& data)
{
	std::vector<double> ms, weights;
	ms.reserve(data.size());
	weights.reserve(data.size());
	for (auto& v : data) {
		ms.push_back(v.first);
		weights.push_back(v.second);
	}
	return weighted_average(ms, weights);
}

////////////////////////


/// Economics-like stuff:

double count_Gini_index (const std::vector<double>& values)
{
	double abs_total_difference = 0;

	for (const auto& item : values) {
		for (const auto& other_item : values) {
			abs_total_difference += std::abs(item - other_item);
		}
	}

	return abs_total_difference / (2. * values.size() * sum(values));
}

