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
