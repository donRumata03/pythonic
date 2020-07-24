//
// Created by Vova on 10.07.2020.
//

#pragma once

#include <pythonic.h>

#include <functional>


/*
template<class... args, class... function_args> void invoke_function(const std::function<void(function_args...)>& function, args... Args)
{
	f = [](int i, double val){ std::cout << i << " " << val << std::endl; };

	f(1, 1.);
	f(Args...);
}
*/

inline void test_copying_to() {
	std::vector<double> values = {
			1.,
			4.6,
			7,
			34.65
	};

	std::unordered_set<double> set(4);
	std::cout << type_name<decltype(set)::value_type>() << std::endl;
	// std::copy(values.begin(), values.end(), set.begin());

	auto new_set = copy_to<std::unordered_set<double>/*, std::vector<double>*/>(values);
	// auto vec = copy_to<std::vector<double>, std::array<double, 4>>(values);



	std::cout << new_set << std::endl;
	// std::cout << vec << std::endl;
}

inline void test_point_index_operator(){
	point pnt(23.9, 2.39);
	std::cout << pnt[0] << " " << pnt[1] << std::endl;

	pnt[0] = 56.6;
	std::cout << pnt << std::endl;

	pnt[1] = 5.66;
	std::cout << pnt[0] << " " << pnt[1] << std::endl;

	const point cpnt = pnt;
	std::cout << cpnt << std::endl;
	std::cout << cpnt[0] << " " << cpnt[1] << std::endl;

	// cpnt[1] = 30.; <- compile-time error
	// pnt[2] = 30.; <- runtime error
}
