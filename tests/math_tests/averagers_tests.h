//
// Created by Vova on 25.07.2021.
//

#pragma once

#include <pythonic.h>

inline void test_averages() {
	std::vector<double> ms = {
			3.4155, 3.40202, 3.41788, 3.41788, 3.41788, 3.41645, 3.41788, 3.41788, 3.40239, 3.41788
	};

	std::cout << "A: " << count_average(ms) << std::endl;
	std::cout << "Q: " << quadratic_mean(ms) << std::endl;
	std::cout << "G: " << geometric_mean(ms) << std::endl;
	std::cout << "H: " << harmonic_mean(ms) << std::endl;
	display_delimiter();

	for (const auto& pw : { 1., 0.001, -1., 2., 40., -40. }) {
		std::cout << "pow " << pw << ": " << n_atic_mean(ms, pw) << std::endl;
	}
}


inline void test_n_atic_means_for_same_numbers() {
	std::vector<double> ms = {
			100, 100, 90, 100, 110
	};


	for (const auto& pw : { 1., 0.001, -1., 2., 40., -40., -3. }) {
		std::cout << "pow " << pw << ": " << n_atic_mean(ms, pw) << std::endl;
	}
}
