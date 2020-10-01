//
// Created by Vova on 26.05.2020.
//

#pragma once

#include "statistics.h"

std::vector<double> linspace(double start, double end, size_t count = 50, bool endpoint = true);
std::vector<double> arange(double start, double end, double step = 1); // TODO

std::vector<double> element_wise_sum(const std::vector<double>& vec1, const std::vector<double>& vec2);
std::vector<double> element_wise_product(const std::vector<double>& vec1, const std::vector<double>& vec2);

template<typename IndexingType, class T>
std::vector<std::pair<IndexingType, T>> enumerate (const std::vector<T>& vector) {
	std::vector<std::pair<IndexingType, T>> res(vector.size());
	for (size_t i = 0; i < vector.size(); ++i) {
		res[i] = { IndexingType(i), vector[i] };
	}

	return res;
}




template<class T, class E>
void operator*= (std::vector<T>& vec, E number) {
	for(auto& v : vec) v *= number;
}

template<class T, class E>
auto operator* (const std::vector<T>& vec, E number) -> std::vector<decltype(vec[0] * number)> {
	using dec = decltype(vec[0] * number);
	std::vector<dec> res(vec.size());
	// std::copy(vec.begin(), vec.end(), res.begin());
	for (size_t index = 0; index < vec.size(); ++index) {
		res[index] = dec(vec[index]);
	}
	res *= number;
	return res;
}

