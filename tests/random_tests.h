//
// Created by Vova on 03.06.2020.
//


#pragma once

#include <pythonic.h>

inline void test_random(){
	std::random_device rd;

	std::mt19937 mt { rd() };

	std::cout << size_t(std::mt19937::max) << std::endl;

	for (size_t i = 0; i < 100; i++) {  std::cout << random(mt) << std::endl; }
}

inline void test_probability_choice() {
	std::vector<std::string> values = { "Hello!", "Hi!", "Привет!" };

	std::vector<double> fitnesses = { 50, 100, 200 };

	std::cout << probability_choose(values, fitnesses) << std::endl;
	std::cout << probability_choose(values, fitnesses, 20) << std::endl;

	std::cout << probability_choose(std::vector{1}, {1.}) << std::endl;
	std::cout << "Zero sum: " << std::endl;
	std::cout << probability_choose(std::vector{1}, {0.}) << std::endl;
}
