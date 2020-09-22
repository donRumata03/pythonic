//
// Created by Vova on 24.05.2020.
//

#pragma once

#include <iostream>
#include <cassert>
#include <algorithm>
#include <string>

#include <unordered_map>
#include <map>


#include "simple_functions.h"

// Function prototypes
double normal(double x, double sigma, double mediana) noexcept;
void logariphmate_function(pms &points);

template <class T>
double count_average(const std::vector<T>& ms) noexcept;

double geometric_mean(const std::vector<double>& numbers);
double n_ometric_mean(const std::vector<double>& numbers, double n);

double harmonic_mean(const std::vector<double>& numbers);
double n_monic_mean(const std::vector<double>& numbers, double n);

double quadratic_mean(const std::vector<double>& numbers);
double n_atic_mean(const std::vector<double>& numbers, double n);


struct quadratic_mean_functor
{
	double operator ()(const std::vector<double>& values) const
	{
		return quadratic_mean(values);
	}
};

struct arithmetic_mean_functor
{
	double operator ()(const std::vector<double>& values) const
	{
		return count_average(values);
	}
};

struct geometric_mean_functor
{
	double operator ()(const std::vector<double>& values) const
	{
		return geometric_mean(values);
	}
};

struct harmonic_mean_functor
{
	double operator ()(const std::vector<double>& values) const
	{
		return harmonic_mean(values);
	}
};

//////////////////////////////////////////////////////////////////////////////////

struct n_atic_mean_functor
{
	double operator ()(const std::vector<double>& values, const double n) const
	{
		return n_atic_mean(values, n);
	}
};

struct n_ometric_mean_functor
{
	double operator ()(const std::vector<double>& values, const double n) const
	{
		return n_ometric_mean(values, n);
	}
};

struct n_monic_mean_functor
{
	double operator ()(const std::vector<double>& values, const double n) const
	{
		return n_monic_mean(values, n);
	}
};

// Template functions implementations:

template <class T>
T sum(const std::vector<T>& ms)  noexcept {
	T accumulator = static_cast<T>(0);
	for (const auto& val : ms) {
		accumulator += val;
	}
	return accumulator;
}

template <class T>
T product(const std::vector<T>& ms)  noexcept {
	T accumulator = static_cast<T>(1);
	for (const auto& val : ms) {
		accumulator *= val;
	}
	return accumulator;
}


inline double weighted_average(const std::vector<double>& ms, const std::vector<double>& weights);
inline double weighted_average(const std::vector<std::pair<double, double>>& data);


inline double sign_safe_pow(double X, double Y);


template <class T>
double count_average(const std::vector<T>& ms) noexcept {
	return sum(ms) / (static_cast<double>(ms.size()));
}


template <class T>
T sigma(const std::vector<T>& ms, bool mediana_known = false, double mediana = 0)  noexcept {
	T middle_val = mediana_known ? mediana : count_average(ms);
	T S_deltas = 0.;
	std::for_each(begin(ms), end(ms), [&](T val) { S_deltas += (val - middle_val) * (val - middle_val); });
	return sqrt(S_deltas / (ms.size()));
}


// nd_array<double> count_nd_density(std::vector<std::vector<double>>& numbers, size_t target_number, double percent_sigma);


template<class T, class E> std::vector<std::pair<T, E>> get_sorted_elements(const std::unordered_map<T, E>& m) {
	std::vector<std::pair<T, E>> res;
	for (auto& p : m) res.emplace_back(p);

	sort(res.begin(), res.end(), [](std::pair<T, E>& p, std::pair<T, E>& e) { return p.second > e.second; });
	return res;
}

template<class T, class E> std::vector<std::pair<T, E>> get_sorted_elements(const std::map<T, E>& m) {
	vector<pair<T, E>> res;
	for (auto& p : m) res.emplace_back(p);

	sort(res.begin(), res.end(), [](pair<T, E>& p, pair<T, E>& e) { return p.second > e.second; });

	return res;
}


template<class T> std::vector<std::pair<T, size_t>> get_sorted_elements(const std::vector<T>& elements) {
	unordered_map<T, size_t> res;

	for (auto& el : elements) ++res[el];
	return get_sorted_elements(res);
}

template<class T> std::unordered_map<T, size_t> make_Counter(const std::vector<T>& elements) {
	std::unordered_map<T, size_t> res;

	for (auto& el : elements) ++res[el];
	return res;
}

// Log and exp wrappers for means

template<class mean_functor, class ... Args> auto logomean(const std::vector<double>& values, Args ... args) -> decltype(mean_functor()(values, args...))
{
	std::vector<double> fake_values = values;
	for (auto& val : fake_values) { val = log(val); }
	// if constexpr (typeid(decltype(mean_functor()(fake_values, args...))) == typeid(double))
	return exp(mean_functor()(fake_values, args...));
	/*if constexpr (typeid(decltype(mean_functor()(fake_values, args...))) == typeid(vector<double>))
	{
		auto ret_values = mean_functor()(fake_values, args...);
		for (auto& val : ret_values) { val = exp(val); }
		return ret_values;
	}*/
}

template<class mean_functor, class ... Args> double expomean(const std::vector<double>& values, Args ... args)
{
	vector<double> fake_values = values;
	for (auto& val : fake_values) val = exp(val);
	return log(mean_functor()(fake_values, args...));
}


// Throw points out of n * sigma:
inline std::vector<double> dropout_data_outliers(const std::vector<double>& values, const double n = 0.7, const bool debug = false)
{
	double n_sigma = sigma(values) * n;
	double mediana = count_average(values);

	if (debug)
	{
		std::cout << "Sigma: " << n_sigma / n << " Sigma * n: " << n_sigma << std::endl;
		std::cout << "Mediana: " << mediana << std::endl;
	}

	std::vector<double> res;
	for (auto& r : values) 	if (abs(r - mediana) < n_sigma) res.push_back(r);
	return res;
}

// Logging:
inline void logariphmate(std::vector<double>& values)
{
	for (auto& val : values) val = log(val);
}

inline std::vector<double> get_logariphmated(const std::vector<double>& values)
{
	auto res = values;
	logariphmate(res);

	return res;
}

// Exping:
inline void exponentate(std::vector<double>& values)
{
	for (auto& val : values) val = exp(val);
}

inline std::vector<double> get_exponentated(const std::vector<double>& values)
{
	auto res = values;
	exponentate(res);
	return res;
}

///////////// Exping graphs

// X
inline void exponentate_x(std::vector<std::pair<double, double>>& values)
{
	for (auto& val : values) val = { exp(val.first), val.second };
}

inline std::vector<std::pair<double, double>> get_exponentated_x(const std::vector<std::pair<double, double>>& values)
{
	auto res = values;
	exponentate_x(res);
	return res;
}

// Y
inline void exponentate_y(std::vector<std::pair<double, double>>& values)
{
	for (auto& val : values) val = { val.first, exp(val.second) };
}

inline std::vector<std::pair<double, double>> get_exponentated_y(const std::vector<std::pair<double, double>>& values)
{
	auto res = values;
	exponentate_y(res);
	return res;
}


///////////// Logging graphs

// X
inline void logariphmate_x(std::vector<std::pair<double, double>>& values)
{
	for (auto& val : values) val = { log(val.first), val.second };
}

inline std::vector<std::pair<double, double>> get_logariphmated_x(const std::vector<std::pair<double, double>>& values)
{
	auto res = values;
	logariphmate_x(res);
	return res;
}

// Y
inline void logariphmate_y(std::vector<std::pair<double, double>>& values)
{
	for (auto& val : values) val = { val.first, log(val.second) };
}

inline std::vector<std::pair<double, double>> get_logariphmated_y(const std::vector<std::pair<double, double>>& values)
{
	auto res = values;
	logariphmate_y(res);
	return res;
}

inline double count_graph_area(const std::vector<std::pair<double, double>>& graph) {
	double S = 0;

	for (size_t index = 1; index < graph.size(); index++) {
		S += (graph[index].first - graph[index - 1].first) * (graph[index].second + graph[index - 1].second);
	}

	return S;
}

inline void normalize(std::vector<std::pair<double, double>>& graph, const double target_area = 1);
