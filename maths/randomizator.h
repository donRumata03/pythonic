//
// Created by Vova on 27.05.2020.
//

#pragma once

#include "pythonic_pch.h"
#include <random>

template<class distributor, class ret, class ... Args>
std::vector<ret> distribute(Args... args, size_t samples)
{
	auto d = distributor(args...);
	std::random_device rd{};
	std::mt19937 gen{ rd() };

	std::vector <ret> res;
	res.reserve(samples);
	for (size_t i = 0; i < samples; i++) {
		res.push_back(d(gen));
	}

	return res;
}

template<class T, class E>
auto uniform_int_distribute(const T from, const E to, const size_t samples)
{
	using dec = decltype(from + to);
	return distribute < std::uniform_int_distribution<dec>, dec, dec, dec >(from, to, samples);
}

std::vector<double> normal_distribute(double mu, double sigma, size_t samples);
std::vector<double> uniform_distribute(double from, double to, size_t samples);



double random();
double random(std::mt19937& gen);
double randval(double from, double to);
double randval(double from, double to, std::mt19937& gen);

template<class T, class E> auto randint(T from, E to) -> decltype(from + to)
{
	using dec = decltype(from + to);
	if (from == to) return from;
	return dec(from) + dec((random() * (to - from))) % dec(to - from);
}
template<class T, class E> auto randint(T from, E to, std::mt19937& gen) -> decltype(from + to)
{
	using dec = decltype(from + to);
	if (from == to) return from;
	return dec(from) + dec((gen() % (to - from)));
}


template<class T, class ... Args> const T& random_choice(const std::vector<T>& values, Args... args)
{
	size_t index = randint(size_t(0), values.size(), args...);
	return values[index];
}


class normalizer
{
	std::vector<double> values;
	size_t m_size = 0;

public:
	explicit normalizer(const size_t samples) : m_size(samples)
	{
		values = normal_distribute(0, 1, m_size);
	}

	void add_samples(const size_t amount)
	{
		auto new_points = normal_distribute(0, 1, amount);
		values.reserve(values.size() + new_points.size());
		m_size += amount;
		for (auto& sample : new_points) values.push_back(sample);
	}

	[[nodiscard]] double generate(const double mu, const double sigma) const
	{
		double usual_sample = random_choice(values);
		return mu + sigma * usual_sample;
	}

	const size_t size() const { return m_size; }
	const std::vector<double>& get_values() const { return values; };
};

size_t get_roulette_index(const std::vector<double>& russian_roulette, double value);

std::vector<double> make_russian_roulette(const std::vector<double>& probabilities);

template<class T> T& probability_choose(const std::vector<T>& vec, const std::vector<double>& probabilities){
	assert(vec.size() == probabilities.size());
	assert(vec.size() != 0);

	std::vector<double> russian_roulette = make_russian_roulette(probabilities);

	std::random_device dev{};
	std::mt19937 mt (dev());

	double value = random(mt);

	return const_cast<T&>(vec[get_roulette_index(russian_roulette, value)]);
}


template<class T> std::vector<T> probability_choose(const std::vector<T>& vec, const std::vector<double>& probabilities, size_t amount){
	assert(vec.size() == probabilities.size());
	assert(vec.size() != 0);

	std::vector<double> russian_roulette = make_russian_roulette(probabilities);


	std::vector<T> res(amount);

	auto randoms = uniform_distribute(0, 1, amount);
	for (int i = 0; i < amount; i++) {
		auto this_value = randoms[i];
		size_t this_index = get_roulette_index(russian_roulette, this_value);
		res[i] = vec[this_index];
	}

	return res;
}
