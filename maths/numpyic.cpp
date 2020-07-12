//
// Created by Vova on 26.05.2020.
//

#include "numpyic.h"

std::vector<double> linspace(const double start, const double end, const size_t count, const bool endpoint)
{
	if (count == 0) return {};

	assert(count != 1 || !endpoint);

	std::vector<double> res;
	res.reserve(count);

	double step = endpoint ? (end - start) / double(count - 1) : (end - start) / double(count);

	double value = start;
	for(size_t index = 0; index < count; index++) {
		if (index == count - 1 && endpoint) value = end;
		res.push_back(value);
		value += step;
	}

	return res;
}

std::vector<double> arange (double start, double end, double step)
{
	size_t count = 1 + size_t(std::round((end - start) / step));
	return linspace(start, end, count);
}


std::vector<double> element_wise_sum(const std::vector<double> &vec1, const std::vector<double> &vec2)
{
	assert(vec1.size() == vec2.size());

	std::vector<double> res (vec1.size());

	for(size_t i = 0; i < vec1.size(); i++) res[i] = vec1[i] + vec2[i];
	return res;
}

std::vector<double> element_wise_product(const std::vector<double> &vec1, const std::vector<double> &vec2)
{
	assert(vec1.size() == vec2.size());

	std::vector<double> res (vec1.size());

	for(size_t i = 0; i < vec1.size(); i++) res[i] = vec1[i] * vec2[i];
	return res;
}

