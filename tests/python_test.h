//
// Created by Vova on 27.05.2020.
//

#pragma once

#include <pythonic.h>

inline void test_splitting(){
	std::string words = recode::to_cp1251("Hello, привЕт! Это - our test.. What ты думаешь_по этому поводу? То-то");

	auto splitted = split_words(words);

	std::vector<std::string> res;
	for(auto& w : splitted) res.emplace_back(to_utf8(w));

	std::cout << res << std::endl;
}

inline void test_smoothing(){
	auto xs = linspace(1, 100, 10000);
	auto noise = normal_distribute(0, 1000, 10000);

	auto ys = element_wise_sum(element_wise_product(xs, xs), noise);

	pms smoothed, brute_smoothed;

	{
		Timer t("Long smoothing");
		smoothed = smooth(zip(xs, ys));
	}
	{
		Timer t("Brute smoothing");
		brute_smoothed = smooth(zip(xs, ys), 0.1, -1, 0.5);
	}

	add_to_plot(xs, ys);
	add_to_plot(smoothed);
	add_to_plot(brute_smoothed);
	show_plot();
}

inline void circle_test(){
	circle c ({0, 1}, {1, 0}, {sqrt(2) / 2, sqrt(2) / 2});
	std::cout << c << std::endl;
}

inline void cut_tests(){
	std::vector<std::string> tests = {
			"Hello!    ",
			"   d                   ",
			"   asok",
			"",
			"    "
	};

	for (auto& test : tests) std::cout << ";" << cut_spaces(test) << ";" << std::endl;
}

inline void test_mult(){
	std::vector<size_t> vec = {1, 4, 22};

	std::vector<double> d = vec * double(1.5);

	std::cout << d << std::endl;
}


inline void test_almost_equal() {
	std::cout << 1 << " " << 1 << " " << almost_equal(1., 1.) << std::endl;
	std::cout << 1 << " " << 2 << " " << almost_equal(1., 2.) << std::endl;
	std::cout << 2 << " " << 1 << " " << almost_equal(2., 1.) << std::endl;

	std::cout << 1e-20 << " " << 1e-20         << " " << almost_equal(1e-20, 1e-20) << std::endl;
	std::cout << 1e-20 << " " << 2e-20         << " " << almost_equal(1e-20, 2e-20) << std::endl;
	std::cout << -1    << " " << "-1. + 1e-20" << " " << almost_equal(-1., (-1. + 1e-20)) << std::endl;
	std::cout << -1    << " " << -2            << " " << almost_equal(-1., -2.) << std::endl;

	std::cout << 0    << " " << 0            << " " << almost_equal(0., 0.) << std::endl;
}
