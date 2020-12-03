//
// Created by Vova on 27.05.2020.
//

#include <other/typedefs.h>
#include "randomizator.h"



std::vector<double> normal_distribute(const double mu, const double sigma, size_t samples)
{
	return distribute<std::normal_distribution<double>, double, double, double >(mu, sigma, samples);
}

std::vector<double> uniform_distribute(const double from, const double to, size_t samples)
{
	return distribute<std::uniform_real_distribution<double>, double, double, double>(from, to, samples);
}

double pythonic_random()
{
	auto r = rand();
	if (r == RAND_MAX) {
		/* std::cout << "It's equal!" << std::endl; */
		r--;
	}
	return double(r) / RAND_MAX;
}

double random(std::mt19937 &gen)
{
	auto r = gen();
	if (r == std::mt19937::max()) {
		/* std::cout << "I`s equal!" << std::endl; */
		r--;
	}

	return double(r) / std::mt19937::max(); // RAND_MAX;
}

double randval(const double from, const double to)
{
	return from + pythonic_random() * (to - from);
}

double randval(const double from, const double to, std::mt19937 &gen)
{
	return from + random(gen) * (to - from);
}

size_t get_roulette_index (const std::vector<double> &russian_roulette, const double value)
{
	lint l = -1, r = russian_roulette.size();

	while (l != r - 1) {
		lint mid = (r + l) / 2;
		if (russian_roulette[mid] > value) {
			r = mid;
		}
		else {
			l = mid;
		}
	}

	return r;
}

std::vector<double> make_russian_roulette (const std::vector<double> &probabilities)
{
	std::vector<double> russian_roulette(probabilities.size());

	double prob_sum = 0;

	for (double val : probabilities) prob_sum += val;

	assert(prob_sum != 0);

	bool is_first = true;
	size_t index = 0;
	for (auto& prob : probabilities) {
		double relative_prob = prob / prob_sum;
		russian_roulette[index] = (is_first ? relative_prob : relative_prob + russian_roulette[index - 1]);
		is_first = false;
		index++;
	}

	return russian_roulette;
}
