//
// Created by Vova on 24.07.2020.
//

#pragma once

#include <pythonic.h>

inline void test_point_comparison() {
	point p1 = {
			1, 2
	};

	point p2 = {
			1, 3.
	};

	std::cout << p1 << " " << p2 << std::endl;

	std::cout << std::boolalpha << std::endl;
	std::cout << (p1 == p2) << std::endl;
	std::cout << (p1 > p2) << std::endl;
	std::cout << (p1 <= p2) << std::endl;
	// std::cout << (p1 <=> p2) << std::endl;


}

inline void point_operator_test () {
	std::cout << (point{ 1, 2 } + point { 3, 4 }) << std::endl;
	std::cout << (point{ 1, 2 } - point { 3, 4 }) << std::endl;
	std::cout << (point{ 1, 2 } * point { 3, 4 }) << std::endl;
	std::cout << (point{ 1, 2 } / point { 3, 4 }) << std::endl;
	std::cout << sqrt(point{ 2, 3 }) << std::endl;
	std::cout << pow(point{ 1, 2 }, 5) << std::endl;
}

inline void point_scaling_test() {
	std::cout << point{1, 1}.scale_from(point{2, 1}, -1) << std::endl;
	std::cout << point{1, 1}.scale_from(point{0, 0}, -1) << std::endl;
	std::cout << point{1, 1}.scale_from(point{100, 1000}, 1) << std::endl;
	std::cout << point{1, 1}.scale_from(point{0, 1}, 2) << std::endl;
	std::cout << point{1, 1}.scale_from(point{2, 2}, 2) << std::endl;

	std::cout << point{1, 1}.scale_x_from(0, 2).scale_y_from(1, 2) << std::endl;
	std::cout << point{1, 1}.scale_x_from(2, 2).scale_y_from(2, 2) << std::endl;
}

inline void vector_perpendicularity_test() {
	std::vector<std::pair<point, point>> tests = {
			{ { 1., 1. }, { 1., -1. } },
			{ { 1., 1. }, { 1., 1. } },
			{ { 1., 1. }, { -1., 1. } },
			{ { 1., 1. }, { -1., -1. } },
			{ { 1., 100. }, { 100., 1. } },
			{ { 0., 100. }, { 100., 0. } },
			{ { 0., 100. }, { 100., 1e-6 } },
	};

	for(auto& test : tests) {
		std::cout << test << " : " << std::boolalpha << are_perpendicular(test.first, test.second) << std::endl;
	}
}
